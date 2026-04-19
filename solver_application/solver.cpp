#include <iostream>
#include "formatter_ex.hpp"
#include "solver.hpp"
int main() {
    int result = solve(2, 3);
    std::cout << format_ex("Result: " + std::to_string(result)) << std::endl;
    return 0;
}
