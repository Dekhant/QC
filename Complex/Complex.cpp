#include <iostream>
#include <sstream>
#include "CComplex.h"

int main()
{
    std::string line;

    while (getline(std::cin, line))
    {
        std::istringstream ss(line);
        CComplex complex;

        ss >> complex;
        std::cout << complex << std::endl;
    }
}