#ifndef CRY_H
#define CRY_H

#include <thread>
#include <algorithm>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <iterator>
#include <vector>
#include <future>
#include <tuple>
#include "cry.cpp"
#include "thread_pool.cpp"


using namespace cry;
//enumerate
template <typename T,
          typename TIter = decltype(std::begin(std::declval<T>())),
          typename = decltype(std::end(std::declval<T>()))>
constexpr auto enumerate(T &&);

template<class Container>
constexpr void print_container( const Container &, const char* spacer = " " );

template<class Container, class Condition>
constexpr void remove_if(Container, Condition);

class Thread_Pool
{
    Thread_Pool(std::size_t);
    ~Thread_Pool();

    template<class T>
    auto enqueue(T task) -> std::future<decltype(task())>;
};

template<class InputIt, class UnaryFunction>
constexpr void for_each_iterator(InputIt first, InputIt last, UnaryFunction f);

template<class Container>
constexpr auto max(Container);

#endif
