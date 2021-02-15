#ifndef CRY_H
#define CRY_H

#include <thread>
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


//thread pool
//namespace cry
//{
    //class Thread_Pool
    //{
        //public:
            //Thread_Pool::Thread_Pool(std::size_t);
            //Thread_Pool::~Thread_Pool();
                        
            //template<class T>
            //auto enqueue(T task) -> std::future<decltype(task())>;
    //};
//}
class Thread_Pool
{
    Thread_Pool(std::size_t);
    ~Thread_Pool();

    template<class T>
    auto enqueue(T task) -> std::future<decltype(task())>;
};
//namespace cry
//{
    //class Thread_Pool
    //{
        //public:
            //using Task = std::function<void()>;
            //explicit Thread_Pool(std::size_t);
            //~Thread_Pool();
            
            //template<class T>
            //auto enqueue(T task) -> std::future<decltype(task())>;
        //private:
            //std::vector<std::thread> pool;
            //std::queue<Task> Task_Queue;

            //std::condition_variable Event_Variable;
            //std::mutex Event_Mutex;
            //bool die;

            //void init(std::size_t n_threads);
            //void exit();
    //};
//}

#endif
