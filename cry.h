#ifndef CRY_H
#define CRY_H

#include <thread>
#include <algorithm>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <iostream>
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
void print_container( const Container &, const char* spacer = " " );

template<class Container, class Condition>
void remove_if(Container, Condition);

class Thread_Pool
{
    Thread_Pool(std::size_t);
    ~Thread_Pool();

    template<class T>
    auto enqueue(T task) -> std::future<decltype(task())>;
};

#endif
