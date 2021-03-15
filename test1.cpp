#include <iostream>
#include <array>
#include <memory>

class Base_Iterator{};

template<typename T>
class Iterator : public Base_Iterator
{
   T iter; 
   public:
      Iterator(T iter) { this -> iter = iter; }
      ~Iterator(){}

      bool operator != (Iterator<T> rhs) { return iter != other.iter; }
      template<typename U>
      bool operator != (Iterator<U> rhs) { return true; }
      auto operator * () { return *iter; }
      void operator ++ () { ++iter; }
};

template<std::size_t S>
class Packed_Iterator
{
   std::array<std::shared_ptr<Base_Iterator*>, S> pack;
};
