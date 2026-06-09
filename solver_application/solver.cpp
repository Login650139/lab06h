#include <cmath>
#include <iostream>

int main()
{
    double a = 0;
    double b = 0;

    std::cin >> a >> b;

    double c = std::sqrt(a * a + b * b);

    std::cout << "c = " << c << std::endl;

    return 0;
}
