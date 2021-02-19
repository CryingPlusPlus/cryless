#include <vector>
#include <tuple>
#include <array>
#include <iostream>

class Base_Iterator
{
    private:
        std::vector<int>::const_iterator iter;
    public:
        bool operator != (const Base_Iterator & other){ return iter != other.iter; }
        void operator ++ (){}
        auto operator * () { return *iter; }
};

template<typename T>
class Iterator: public Base_Iterator
{
    private:
        T iter;
    public:
        Iterator(T iter) { this -> iter = iter; }
        ~Iterator(){}
        bool operator != (const Iterator<T> & other) { return iter != other.iter; }
        template<typename U>
        bool operator != (const Iterator<U> & other) { return false; }
        void operator ++ () { ++iter; }
        auto operator * () { return *iter; }
};

template <class T, std::size_t N, std::size_t... Is>
auto unpack_impl(std::array<T, N> &arr, std::index_sequence<Is...>) -> decltype(std::make_tuple(arr[Is]...)) {
        return std::make_tuple( arr[Is]...  );
}

template <class T, std::size_t N>
auto unpack(std::array<T, N> &arr) -> decltype(unpack_impl(arr, make_index_sequence<N>{})) {
        return unpack_impl(arr, std::make_index_sequence<N>{});
}

template<std::size_t S, typename U>
auto dereference(std::array<U, S> arr)
{
    return std::tie() = unpack(arr);
}


template<std::size_t S>
class Packed_Iterator
{
    public:
        std::array<Base_Iterator, S> iters;
        Packed_Iterator( std::array<Base_Iterator, S> & iters ) { this -> iters = iters; }
        bool operator != ( const Packed_Iterator & other )
        {
            bool end = true;
            for(int i = 0; i < iters.size(); ++i)
                end = ( iters[i] != other.iters[i] ) ? end : false;
            return end;
        }
        void operator ++ () { std::for_each( iters.begin(), iters.end(), [](auto &iter){ ++iter; } ); }
        auto operator * () { return dereference(); }

};

int main()
{
    std::array<int, 3> arr{1, 2, 3};

    auto [a, b, c] = dereference(arr);
    return 0;
}
