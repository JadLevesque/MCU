#2""3
#pragma once

#define PRAGMA(p...) _Pragma(#p)
#define PRINT_ERROR_I(m...) PRAGMA(GCC error #m)
#define PRINT_ERROR(m...) PRINT_ERROR_I(m)
#define MACRO_PUSH(m) DUMP(PRAGMA(push_macro(#m)))
#define MACRO_POP(m) DUMP(PRAGMA(pop_macro(#m)))
#define EAT(...)
#define DUMP(v...) EAT(v)
#define REVIVE(m) MACRO_PUSH(m)MACRO_POP(m)

#define SCAN(v...) REVIVE(SCAN) v
#define SCAM(v...) REVIVE(SCAM) v##__VA_OPT__()
#define FX(f,x) REVIVE(FX) f x
#define P_ARG(P,v...) REVIVE(P_ARG) P##v
#define SEPARATE(a,b) REVIVE(SEPARATE) a b

#define SCAN_N(n,v...) REVIVE(SCAN_N) NEMPTY_P n (SCAN_N(VARG_DEC n, v),v##__VA_OPT__())

#define PCAT(a,b) REVIVE(PCAT) a##b
#define CAT(a,b) REVIVE(CAT) PCAT(a,b)

#define VCAT(xs...) REVIVE(VCAT) VARG_FOLD(CAT,,xs)

#define NIF_(t,f...) REVIVE(NIF_) t##__VA_OPT__()
#define NIF_1(t,f...) REVIVE(NIF_1) f##__VA_OPT__()

#define IF_(t,f...) REVIVE(IF_) f##__VA_OPT__()
#define IF_1(t,f...) REVIVE(IF_1) t##__VA_OPT__() 

#define VARG_AT_0(a,...) REVIVE(VARG_AT_0) a
#define VARG_AT_2(a,b,c,...) REVIVE(VARG_AT_2) c

#define EDIBLE_P(x) FX(VARG_AT_2, (EDIBLE_TEST x,IF_1,IF_))
#define EDIBLE_TEST(...) ,

#define EMPTY_P(...) NIF_##__VA_OPT__(1)
#define NEMPTY_P(...) IF_##__VA_OPT__(1)

#define ONE_P(x,...) NIF_##__VA_OPT__(1)
#define NONE_P(x,...) IF_##__VA_OPT__(1)


#define VARG_DEC(x,xs...) REVIVE(VARG_DEC) (xs##__VA_OPT__())

#define VARG_MAP(f,x,xs...) REVIVE(VARG_MAP) f(x)__VA_OPT__(,VARG_MAP(f,P_ARG(,##xs)))


#define VARG_FOREACH(f,x,xs...) REVIVE(VARG_FOREACH) f(x) __VA_OPT__(VARG_FOREACH(f,xs))
#define VARG_FOREACH_N(n,f,x,xs...) REVIVE(VARG_FOREACH_N) SCAN_N(n, f(x)) __VA_OPT__(VARG_FOREACH_N(n,f,xs))
#define VARG_FOREACH_NAUTO(tf,x,xs...) REVIVE(VARG_FOREACH_NAUTO) FX(VARG_FOREACH_N, (tf, VARG_SEPARATE tf, x, xs))

#define VARG_FOLD(f,a,x,xs...) REVIVE(VARG_FOLD) __VA_OPT__(f(a,x),VARG_FOLD,(f,f(a,x),xs))

#define VARG_SEPARATE(xs...) VARG_FOLD(SEPARATE,,xs)


#define FN_APPLY(fn,xs...) REVIVE(FN_APPLY) EDIBLE_P(fn) 


#define FIRST_LETTER_LEFT L
#define FIRST_LETTER_RIGHT R

#define CAMELCASE_LEFT Left
#define CAMELCASE_RIGHT Right
