#ifndef ENUMERATE_H
#define ENUMERATE_H

#include <tuple>
#include "enumerate.cpp"

template <typename T,
          typename TIter = decltype(std::begin(std::declval<T>())),
          typename = decltype(std::end(std::declval<T>()))>
constexpr auto enumerate(T &&);

#endif
