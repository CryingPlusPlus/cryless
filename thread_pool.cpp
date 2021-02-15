#include "cry.h"

namespace cry
{
    class Thread_Pool
    {
        public:
            using Task = std::function<void()>;
            explicit Thread_Pool(std::size_t n_threads)
            {
                init(n_threads);
            }
            ~Thread_Pool()
            {
                exit();
            }
            
            template<class T>
            auto enqueue(T task) -> std::future<decltype(task())>
            {
                auto wrapper = std::make_shared<std::packaged_task<decltype(task()) () >> (std::move(task));
                {
                    std::unique_lock<std::mutex> lock{Event_Mutex};
                    Task_Queue.emplace( [wrapper] {
                            (*wrapper)();
                            });
                }
                Event_Variable.notify_one();
                return wrapper -> get_future();
            }

        private:
            std::vector<std::thread> pool;
            std::queue<Task> Task_Queue;

            std::condition_variable Event_Variable;
            std::mutex Event_Mutex;
            bool die = false;

            void init(std::size_t n_threads)
            {
                for(uint i = 0; i < n_threads; i++)
                {
                    pool.emplace_back([this] {
                                while(true)
                                {
                                    Task task;
                                    {
                                        std::unique_lock<std::mutex> lock{Event_Mutex};
                                        Event_Variable.wait(lock, [this] {
                                                    return die || !Task_Queue.empty();
                                                });
                                        if(die)
                                            break;

                                        task = std::move(Task_Queue.front());
                                        Task_Queue.pop();
                                    }
                                    task();
                                }
                            });
                }
            }

            void exit()
            {
                {
                    std::unique_lock<std::mutex> lock{Event_Mutex};
                    die = true;
                }

                Event_Variable.notify_all();

                for(auto &t : pool)
                    t.join();
            }
    };
}
