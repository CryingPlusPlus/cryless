#include <iostream>
#include <vector>

class Fisch
{
    public:
        Fisch(){}
        ~Fisch(){ std::cout << "Fisch kaputt" << std::endl; }
        void say()
        {
            std::cout << "Ich bin Fisch" << std::endl;
        }
};

class Lachs : public Fisch
{
    public:
        Lachs(){}
        ~Lachs(){ std::cout << "Lachs kaputt" << std::endl; }
        void say()
        {
            std::cout << "Ich bin ein Lachs" << std::endl;
        }
};

class Tunfisch : public Fisch
{
    public:
        Tunfisch(){}
        ~Tunfisch(){ std::cout << "Tunfisch kaputt" << std::endl; }
        void say()
        {
            std::cout << "Ich bin ein Tunfisch" << std::endl;
        }
};

int main()
{
}
