#ifndef CRY_H
#define CRY_H

#include <tuple>
#include "cry.cpp"


template <typename T,
          typename TIter = decltype(std::begin(std::declval<T>())),
          typename = decltype(std::end(std::declval<T>()))>
constexpr auto cry::enumerate(T &&);

#endif
