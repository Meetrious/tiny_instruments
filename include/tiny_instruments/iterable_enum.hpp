#ifndef ITERABLE_ENUM_HPP_
#define ITERABLE_ENUM_HPP_

#include <array>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>

/*-- some vague boost-preprocessor-magic one don't need to bother -- */

#define IDENTITY(ELEM) ELEM

#define UNWRAP_PAIR_INTO_ASSIGNMENT(PAIR) \
  BOOST_PP_TUPLE_ELEM(2, 0, PAIR) = BOOST_PP_TUPLE_ELEM(2, 1, PAIR)

#define CONCAT_NAMESPACE_WITH_FIRST_IN_PAIR(NAMESPACE, PAIR) \
  NAMESPACE::BOOST_PP_TUPLE_ELEM(2, 0, PAIR)

#define CONCAT_NAMESPACE_WITH_RAW_ELEM(NAMESPACE, RAW_ELEM) NAMESPACE::RAW_ELEM

#define RAW_ELEM_TO_ENUM_MEMBER(r, empty, RAW_ELEM) \
  BOOST_PP_IIF(                                     \
    BOOST_PP_IS_BEGIN_PARENS(RAW_ELEM),             \
    UNWRAP_PAIR_INTO_ASSIGNMENT,                    \
    IDENTITY                                        \
  )(RAW_ELEM)

#define RAW_ELEM_TO_ARRAY_MEMBER(r, NAMESPACE, RAW_ELEM) \
  BOOST_PP_IIF(                                          \
    BOOST_PP_IS_BEGIN_PARENS(RAW_ELEM),                  \
    CONCAT_NAMESPACE_WITH_FIRST_IN_PAIR,                 \
    CONCAT_NAMESPACE_WITH_RAW_ELEM                       \
  )(NAMESPACE, RAW_ELEM)

#define LIST_ELEMS_INSIDE_ENUM(RAW_ELEMS ...) \
  BOOST_PP_SEQ_ENUM(                          \
    BOOST_PP_SEQ_TRANSFORM(                   \
      RAW_ELEM_TO_ENUM_MEMBER,                \
      BOOST_PP_EMPTY,                         \
      BOOST_PP_VARIADIC_TO_SEQ(RAW_ELEMS)     \
    )                                         \
  )

#define LIST_ELEMS_INSIDE_ARR(PREFIX, RAW_ELEMS...) \
  BOOST_PP_SEQ_ENUM(                                \
    BOOST_PP_SEQ_TRANSFORM(                         \
      RAW_ELEM_TO_ARRAY_MEMBER,                     \
      PREFIX,                                       \
      BOOST_PP_VARIADIC_TO_SEQ(RAW_ELEMS)           \
    )                                               \
  )

#define NUM_OF_ARGS(...) \
  BOOST_PP_SEQ_SIZE(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

/*---------------- more-cohesive-level-code ----------------------- */


/** \note RAW_ELEMS are either just names, or pairs (name,value) */
#define iterable_enum(ENUM_CLASS_NAME, RAW_ELEMS ...)                                           \
  enum class ENUM_CLASS_NAME { LIST_ELEMS_INSIDE_ENUM(RAW_ELEMS) };                             \
  constexpr std::array<const ENUM_CLASS_NAME, NUM_OF_ARGS(RAW_ELEMS)> ENUM_CLASS_NAME##_items = \
    { LIST_ELEMS_INSIDE_ARR(ENUM_CLASS_NAME, RAW_ELEMS) }


#endif  // ITERABLE_ENUM_HPP_
