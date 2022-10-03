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
#define VARG_AT_1(a,b,...) REVIVE(VARG_AT_1) b
#define VARG_AT_2(a,b,c,...) REVIVE(VARG_AT_2) c
#define VARG_AT_3(a,b,c,d,...) REVIVE(VARG_AT_3) d

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
#define VARG_FOREACH_MAGIC(f,x,xs...) REVIVE(VARG_FOREACH_MAGIC) FN_APPLY(f, x) __VA_OPT__(VARG_FOREACH_MAGIC(f,xs))
// TODO: fix VARG_FOREACH_NAUTO
//#define VARG_FOREACH_NAUTO(tf,x,xs...) REVIVE(VARG_FOREACH_NAUTO) FX(VARG_FOREACH_N, (tf, VARG_SEPARATE tf, x, xs))

#define VARG_FOLD(f,a,x,xs...) REVIVE(VARG_FOLD) __VA_OPT__(f(a,x),VARG_FOLD,(f,f(a,x),xs))

#define VARG_SEPARATE(xs...) VARG_FOLD(SEPARATE,,xs)

// TODO: define FN_APPLY
//#define FN_APPLY(fn,xs...) REVIVE(FN_APPLY) EDIBLE_P(fn) 

#define VARG_REVERSE(xs...) REVIVE(VARG_REVERSE) __VA_OPT__(VARG_REVERSE_I(,##xs))
#define VARG_REVERSE_I(P,x,xs...) REVIVE(VARG_REVERSE_I) __VA_OPT__(VARG_REVERSE_I(,P##xs),)P##x


#define FIRST_LETTER_LEFT L
#define FIRST_LETTER_RIGHT R

#define CAMELCASE_LEFT Left
#define CAMELCASE_RIGHT Right

#define XF(x,f) REVIVE(XF) f x
#define PARENS_XF(x,f) REVIVE(PARENS_XF) (f x)

/*!
 * @def FN_APPLY
 * Computes the application of the composed funtion `tf` (tree of functions) on `pxs` (tuple).
 * 
 */
#if 0
#define FN_APPLY(f,xs...) \
REVIVE(FN_APPLY) \
FX ( \
   ,EDIBLE_P (f) (FX (FN_APPLY_EDIBLE, ((xs), VARG_REVERSE f)) \
                 ,f (xs) \
                 ) \
   )
//

#define FN_APPLY_EDIBLE(pxs,f,fs...) REVIVE(FN_APPLY_EDIBLE) FN_APPLY_EDIBLE_I (FX (FN_APPLY, (f, pxs)), ##fs)
#define FN_APPLY_EDIBLE_I(pr,fs...) REVIVE(FN_APPLY_EDIBLE_I) EMPTY_P(fs) (VARG_AT_0, FN_APPLY_EDIBLE) (pr, fs)
#endif

// Either (Varg a -> Varg c) (Tree (Varg a -> Tuple b))
// -> Tuple a
// -> c
#define FN_APPLY(tf, pxs) \
REVIVE(FN_APPLY) \
EDIBLE_P (tf) (FX (FN_APPLY_I, (pxs, VARG_REVERSE tf)) \
              ,tf pxs \
              )
//

#define FN_APPLY_I(pxs, f, fs...) \
REVIVE(FN_APPLY_I) \
EMPTY_P (fs) (VARG_AT_0, FN_APPLY_I) (f pxs, fs)


// TARG_REVERSE (1,2,3) -> (3,2,1)
#define TARG_REVERSE(xs...) REVIVE(TUPLE_REVERSE) (VARG_REVERSE (xs))
// TUPLE_REVERSE ((1,2,3)) -> (3,2,1)
#define TUPLE_REVERSE(t) REVIVE(TUPLE_REVERSE) (VARG_REVERSE t)




PRINT_ERROR
(\n 
FN_APPLY((VARG_AT_1), (1,2,3) )
\n
VARG_FOREACH_MAGIC ((TARG_REVERSE), (1,2,3), (4,5,6), (7,8,9))
\n
)