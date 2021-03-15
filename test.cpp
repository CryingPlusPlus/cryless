#include <vector>
#include <tuple>
#include <array>
#include <iostream>

class Base_Iterator
{
    //private:
        //std::vector<int>::const_iterator iter;
    //public:
        //bool operator != (const Base_Iterator & other){ return iter != other.iter; }
        //void operator ++ (){}
        //auto operator * () { return 3; }
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
        virtual auto operator * () { return *iter; }
};


template<std::size_t S>
class Packed_Iterator
{
    public:
        std::array<std::shared_ptr<Base_Iterator*>, S> iters;
        Packed_Iterator(std::shared_ptr<Base_Iterator*>, S> & iters ) { this -> iters = iters; }
        bool operator != ( const Packed_Iterator & other )
        {
            bool end = true;
            for(int i = 0; i < iters.size(); ++i)
                end = ( iters[i] != other.iters[i] ) ? end : false;
            return end;
        }
        void operator ++ () { std::for_each( iters.begin(), iters.end(), [](auto &iter){ ++iter; } ); }
        auto operator * () { return unpack(iters); }
    private:
        template <class T, std::size_t N, std::size_t... Is>
        auto unpack_impl(std::array<T, N> &arr, std::index_sequence<Is...>) -> decltype(std::make_tuple(*arr[Is]...)) {
            return std::make_tuple( *arr[Is]...  );
        }

        template <class T, std::size_t N>
        auto unpack(std::array<T, N> &arr) -> decltype(unpack_impl(arr, std::make_index_sequence<N>{})) {
            return unpack_impl(arr, std::make_index_sequence<N>{});
        }
};
int main()
{
    std::vector<int> vec1{1, 2, 3};
    std::vector<int> vec2{4, 5, 6};
    Iterator i1{ std::begin(vec1) };
    Iterator i2{ std::begin(vec2) };
    std::array<Base_Iterator, 2> arr{ i1, i2 };
    Packed_Iterator packed{arr};
    int a, b, c, d;
    std::tie(a, b) = *packed;
    std::cout << a << " " << b << std::endl;
    ++packed;
    std::tie(c, d) = *packed;
    std::cout << c << " " << d << std::endl;
    return 0;
}
