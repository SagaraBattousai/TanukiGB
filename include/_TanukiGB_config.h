#ifndef __TANUKIGB_CONFIG_H__
#define __TANUKIGB_CONFIG_H__

//May be able to remove this constexpr shizz
//I think this version supports all the c++20 features I like

/*
#if _MSC_VER >= 1928
#define CONSTEXPR_FUNC constexpr
#endif // _MSC_VER 

#if __clang__ //Due to Android iirc
#define CONSTEXPR_FUNC
#endif
*/

#ifdef _MSC_VER
#define REGION(x) _Pragma("region " #x)
#define END_REGION _Pragma("endregion")
//#define END_REGION(x) _Pragma("endregion " #x)
#else
#define REGION(x)
#define END_REGION
#endif


#if __cpp_concepts >= 201907
#define REQUIRES(x) requires x
#define CONSTRAINT(x) x
#else
#define REQUIRES(x)
#define CONSTRAINT(x) typename
#endif // __cpp_concepts (lower part)

//Using EXPORT and LOCAL instead of EXPORT and NO_EXPORT to 
//Make it harder to mistakenly type export when you don't mean to.

#if defined(_WIN32) || defined(__CYGWIN__)
// Now here is an interesting question....
// See dllexport will be on headers that are used by "other dll's" even though
//   the definition will be only in the "true" dll.
// It doesn't seem to be an issue but one would think that all other dll's should use dllimport
#ifdef TANUKIGB_BUILD_DLL
#define TANUKIGB_EXPORT __declspec(dllexport)
#else
#define TANUKIGB_EXPORT __declspec(dllimport) 
#endif
#define TANUKIGB_LOCAL
#else
#ifndef __has_attribute
#define __has_attribute(x) 0  // Compatibility with non-clang compilers.
#endif

#if (defined(__GNUC__) && (__GNUC__ >= 4)) ||\
      (defined(__clang__) && __has_attribute(visibility))

#define TANUKIGB_EXPORT __attribute__ ((visibility ("default")))
#define TANUKIGB_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define TANUKIGB_EXPORT
#define TANUKIGB_LOCAL
#endif
#endif

#endif
