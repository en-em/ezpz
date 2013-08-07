#include <iostream>
#include <vector>
#include <ezpz/container_io.h>

std::vector<int> a = { 1, 2, 3, 4 };

int main ()
{
    using ezpz::operator<<;
    using ezpz::operator>>;

    std::vector<int> b;

    std::cout << a << std::endl;
    while (1)
    {
        std::cout << "Enter vector: ";
        b.clear();
        std::cin >> b;
        if (std::cin)
            std::cout << b << std::endl;
        else
        {
            std::cout << "Error entering vector" << std::endl;
            std::cout << "Entered so far:" << std::endl;
            std::cout << b << std::endl;
            b.clear();
            std::cin.clear();
            std::cin.ignore(1000,'\n');
        }
    }
}
