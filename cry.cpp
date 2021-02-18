
#include "cry.h"
namespace cry
{
    template <typename T,
              typename TIter = decltype(std::begin(std::declval<T>())),
              typename = decltype(std::end(std::declval<T>()))>
    constexpr auto enumerate(T && iterable)
    {
    //enumerate is not my code!!! Credit: http://reedbeta.com/blog/python-like-enumerate-in-cpp17/
        struct iterator
        {
            size_t i;
            TIter iter;
            bool operator != (const iterator & other) const { return iter != other.iter;  }
            void operator ++ () {++i; ++iter;}
            auto operator * () const { return std::tie(i, *iter);  }
        };

        struct iterable_wrapper
        {
            T iterable;
            auto begin() { return iterator{ 0, std::begin(iterable)   };   }
            auto end() { return iterator{ 0, std::end(iterable)   };   }
             
        };

        return std::move(iterable_wrapper{ std::forward<T>(iterable)  });
    }

    template<class Container>
    constexpr void print_container( const Container &cont, const char* spacer = " " )
    {
        typedef typename Container::value_type T;
        std::copy(cont.begin(), cont.end(), std::ostream_iterator<T>(std::cout, spacer));
        std::cout << std::endl;
    }

    template<class Container, class Condition>
    constexpr void remove_if(Container &cont, Condition condition)
    {
        const auto new_end = std::remove_if(cont.begin(), cont.end(), condition);
        cont.erase(new_end, cont.end());
    }

    template<class InputIt, class UnaryFunction>
    constexpr void for_each_iterator(InputIt first, InputIt last, UnaryFunction f)
    {
        for (; first != last; ++first) 
        {
            f(first);
        }
    }
    template<class Container>
    constexpr auto max(Container cont)
    {
        std::sort(cont.begin(), cont.end());
        return std::move(cont.back());
    }
}
