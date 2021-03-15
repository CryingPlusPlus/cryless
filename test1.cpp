#include <iostream>
#include <array>
#include <memory>

class Base_Iterator{};

template<typename T>
class Iterator : public Base_Iterator
{
   T iter; 
};
