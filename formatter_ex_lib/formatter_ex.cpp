#include "formatter_ex.hpp"
std::string format_ex(const std::string& message) {
    return format(message) + " [EXTENDED]";
}
