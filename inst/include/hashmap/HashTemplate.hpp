#ifndef hashmap__HashTemplate__hpp
#define hashmap__HashTemplate__hpp

#include "traits.hpp"
#include <boost/unordered_map.hpp>
#include <boost/functional/hash.hpp>

namespace hashmap {

template <int RTYPE>
inline typename traits::cpp_traits<RTYPE>::type
extractor(const Rcpp::Vector<RTYPE>& vec, R_xlen_t i) {
    return vec[i];
}

template <>
inline std::string
extractor<STRSXP>(const Rcpp::Vector<STRSXP>& vec, R_xlen_t i) {
    return Rcpp::as<std::string>(vec[i]);
}

template <typename KeyType, typename ValueType>
class HashTemplate {
public:
    typedef KeyType key_t;
    typedef ValueType value_t;
    typedef boost::unordered_map<key_t, value_t> map_t;

    enum { key_rtype = traits::sexp_traits<key_t>::rtype };
    enum { value_rtype = traits::sexp_traits<value_t>::rtype };

    typedef Rcpp::Vector<key_rtype> key_vec;
    typedef Rcpp::Vector<value_rtype> value_vec;

    typedef typename map_t::size_type size_type;
    typedef typename map_t::const_iterator const_iterator;
    typedef typename map_t::iterator iterator;
    typedef typename map_t::hasher hasher;

private:
    map_t map;

    key_t key_na() const { return traits::get_na<key_t>(); }
    value_t value_na() const { return traits::get_na<value_t>(); }

public:
    HashTemplate() {}
    HashTemplate(const key_vec& keys_, const value_vec& values_)
    {
        R_xlen_t nk = keys_.size(), nv = values_.size(), i = 0, n;
        if (nk != nv) {
            Rcpp::warning("length(keys) != length(values)!");
        }
        n = nk < nv ? nk : nv;
        map.reserve(n);

        for ( ; i < n; i++) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            map[extractor(keys_, i)] = extractor(values_, i);
        }
    }

    size_type size() const { return map.size(); }
    bool empty() const { return map.empty(); }
    void clear() { map.clear(); }
    size_type bucket_count() const { return map.bucket_count(); }
    void rehash(size_type n) { map.rehash(n); }

    Rcpp::Vector<INTSXP> hash_value(const key_vec& keys_) const {
        R_xlen_t i = 0, nk = keys_.size();
        Rcpp::Vector<INTSXP> res = Rcpp::no_init_vector(nk);
        hasher h;

        for ( ; i < nk; i++) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            res[i] = h(extractor(keys_, i));
        }

        return res;
    }

    void insert(const key_vec& keys_, const value_vec& values_) {
        R_xlen_t nk = keys_.size(), nv = values_.size(), i = 0, n;
        if (nk != nv) {
            Rcpp::warning("length(keys) != length(values)!");
        }
        n = nk < nv ? nk : nv;

        for ( ; i < n; i++) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            map[extractor(keys_, i)] = extractor(values_, i);
        }
    }

    void insert(SEXP keys_, SEXP values_) {
        insert(Rcpp::as<key_vec>(keys_), Rcpp::as<value_vec>(values_));
    }

    key_vec keys() const {
        key_vec res(map.size());
        const_iterator first = map.begin(), last = map.end();

        for (R_xlen_t i = 0; first != last; ++first) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            res[i++] = first->first;
        }

        return res;
    }

    value_vec values() const {
        value_vec res(map.size());
        const_iterator first = map.begin(), last = map.end();

        for (R_xlen_t i = 0; first != last; ++first) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            res[i++] = first->second;
        }

        return res;
    }

    void erase(const key_vec& keys_) {
        R_xlen_t i = 0, n = keys_.size();

        for ( ; i < n; i++) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            map.erase(extractor(keys_, i));
        }
    }

    value_vec find(const key_vec& keys_) const {
        R_xlen_t i = 0, n = keys_.size();
        value_vec res(n);
        const_iterator last = map.end();

        for ( ; i < n; i++) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            const_iterator pos = map.find(extractor(keys_, i));
            if (pos != last) {
                res[i] = pos->second;
            } else {
                res[i] = value_na();
            }
        }

        return res;
    }

    value_vec find(SEXP keys_) const {
        return find(Rcpp::as<key_vec>(keys_));
    }

    bool has_key(const key_vec& keys_) const {
        return map.find(extractor(keys_, 0)) != map.end();
    }

    bool has_key(SEXP keys_) const {
        return has_key(Rcpp::as<key_vec>(keys_));
    }

    Rcpp::Vector<LGLSXP> has_keys(const key_vec& keys_) const {
        R_xlen_t i = 0, n = keys_.size();
        Rcpp::Vector<LGLSXP> res = Rcpp::no_init_vector(n);
        const_iterator last = map.end();

        for ( ; i < n; i++) {
            res[i] = (map.find(extractor(keys_, i)) != last) ?
                true : false;
        }

        return res;
    }

    Rcpp::Vector<LGLSXP> has_keys(SEXP keys_) const {
        return has_keys(Rcpp::as<key_vec>(keys_));
    }

    value_vec data() const {
        R_xlen_t i = 0, n = map.size();

        value_vec res(n);
        key_vec knames(n);

        const_iterator first = map.begin(), last = map.end();

        for ( ; first != last; ++first) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            knames[i] = first->first;
            res[i] = first->second;
            ++i;
        }

        SEXP snames;
        PROTECT(snames = Rf_coerceVector(knames, STRSXP));
        Rcpp::Vector<STRSXP> names(snames);
        UNPROTECT(1);

        res.names() = names;
        return res;
    }
};

typedef HashTemplate<std::string, std::string> ss_hash;
typedef HashTemplate<std::string, double> sd_hash;
typedef HashTemplate<std::string, int> si_hash;
typedef HashTemplate<std::string, bool> sb_hash;

typedef HashTemplate<double, double> dd_hash;
typedef HashTemplate<double, std::string> ds_hash;
typedef HashTemplate<double, int> di_hash;
typedef HashTemplate<double, bool> db_hash;

typedef HashTemplate<int, int> ii_hash;
typedef HashTemplate<int, std::string> is_hash;
typedef HashTemplate<int, double> id_hash;
typedef HashTemplate<int, bool> ib_hash;

} // hashmap

#endif // hashmap__HashTemplate__hpp
