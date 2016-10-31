// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "../inst/include/hashmap.h"
#include <Rcpp.h>

using namespace Rcpp;

// left_outer_join_impl
Rcpp::DataFrame left_outer_join_impl(const Rcpp::XPtr<hashmap::HashMap>& x, const Rcpp::XPtr<hashmap::HashMap>& y);
RcppExport SEXP hashmap_left_outer_join_impl(SEXP xSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::XPtr<hashmap::HashMap>& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const Rcpp::XPtr<hashmap::HashMap>& >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(left_outer_join_impl(x, y));
    return rcpp_result_gen;
END_RCPP
}
// right_outer_join_impl
Rcpp::DataFrame right_outer_join_impl(const Rcpp::XPtr<hashmap::HashMap>& x, const Rcpp::XPtr<hashmap::HashMap>& y);
RcppExport SEXP hashmap_right_outer_join_impl(SEXP xSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::XPtr<hashmap::HashMap>& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const Rcpp::XPtr<hashmap::HashMap>& >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(right_outer_join_impl(x, y));
    return rcpp_result_gen;
END_RCPP
}
// inner_join_impl
Rcpp::DataFrame inner_join_impl(const Rcpp::XPtr<hashmap::HashMap>& x, const Rcpp::XPtr<hashmap::HashMap>& y);
RcppExport SEXP hashmap_inner_join_impl(SEXP xSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::XPtr<hashmap::HashMap>& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const Rcpp::XPtr<hashmap::HashMap>& >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(inner_join_impl(x, y));
    return rcpp_result_gen;
END_RCPP
}
// full_outer_join_impl
Rcpp::DataFrame full_outer_join_impl(const Rcpp::XPtr<hashmap::HashMap>& x, const Rcpp::XPtr<hashmap::HashMap>& y);
RcppExport SEXP hashmap_full_outer_join_impl(SEXP xSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::XPtr<hashmap::HashMap>& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const Rcpp::XPtr<hashmap::HashMap>& >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(full_outer_join_impl(x, y));
    return rcpp_result_gen;
END_RCPP
}