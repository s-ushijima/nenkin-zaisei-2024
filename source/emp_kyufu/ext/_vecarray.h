
#ifndef VECARRAY_H_INCLUDED
#define VECARRAY_H_INCLUDED

#include <vector>

#define VEC(...) __GET_VEC_CONS((__VA_ARGS__, VEC_CONS6, VEC_CONS5, VEC_CONS4, VEC_CONS3, VEC_CONS2, VEC_CONS1)) (__VA_ARGS__, 0)
#define __GET_VEC_CONS(arg) __GET_VEC_CONS_ arg
#define __GET_VEC_CONS_(type, a1, a2, a3, a4, a5, a6, m, ...) m

#define VEC_CONS6(type, axis1, axis2, axis3, axis4, axis5, axis6, def_val) VEC_TYPE6(type)(1+axis1, VEC_CONS4(type, axis2, axis3, axis4, axis5, axis6, (type)def_val))
#define VEC_CONS5(type, axis1, axis2, axis3, axis4, axis5, def_val) VEC_TYPE5(type)(1+axis1, VEC_CONS4(type, axis2, axis3, axis4, axis5, (type)def_val))
#define VEC_CONS4(type, axis1, axis2, axis3, axis4, def_val) VEC_TYPE4(type)(1+axis1, VEC_CONS3(type, axis2, axis3, axis4, (type)def_val))
#define VEC_CONS3(type, axis1, axis2, axis3, def_val) VEC_TYPE3(type)(1+axis1, VEC_CONS2(type, axis2, axis3, (type)def_val))
#define VEC_CONS2(type, axis1, axis2, def_val) VEC_TYPE2(type)(1+axis1, VEC_CONS1(type, axis2, (type)def_val))
#define VEC_CONS1(type, axis1, def_val) VEC_TYPE1(type)(1+axis1, (type)def_val)

#define VEC_TYPE6(type) std::vector<VEC_TYPE5(type) >
#define VEC_TYPE5(type) std::vector<VEC_TYPE4(type) >
#define VEC_TYPE4(type) std::vector<VEC_TYPE3(type) >
#define VEC_TYPE3(type) std::vector<VEC_TYPE2(type) >
#define VEC_TYPE2(type) std::vector<VEC_TYPE1(type) >
#define VEC_TYPE1(type) std::vector<type>

#define AT(...) __GET_AT_MACRO((__VA_ARGS__, AT6, AT5, AT4, AT3, AT2, AT1)) (__VA_ARGS__)

#define __GET_AT_MACRO(args) __GET_AT_MACRO_ args
#define __GET_AT_MACRO_(a1, a2, a3, a4, a5, a6, m, ...) m

#define AT6(axis1, axis2, axis3, axis4, axis5, axis6) at(axis1).at(axis2).at(axis3).at(axis4).at(axis5).at(axis6)
#define AT5(axis1, axis2, axis3, axis4, axis5) at(axis1).at(axis2).at(axis3).at(axis4).at(axis5)
#define AT4(axis1, axis2, axis3, axis4) at(axis1).at(axis2).at(axis3).at(axis4)
#define AT3(axis1, axis2, axis3) at(axis1).at(axis2).at(axis3)
#define AT2(axis1, axis2) at(axis1).at(axis2)
#define AT1(axis1) at(axis1)

typedef VEC_TYPE1(double) v1_t;
typedef VEC_TYPE2(double) v2_t;
typedef VEC_TYPE3(double) v3_t;
typedef VEC_TYPE4(double) v4_t;
typedef VEC_TYPE5(double) v5_t;
typedef VEC_TYPE6(double) v6_t;

#endif