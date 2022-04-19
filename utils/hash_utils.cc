#include "../galaxyui.hh"

using namespace glxyui::globals;

std::vector<std::string> glxy::utils::hash::split_str(const char* str, const char separator) {
    std::vector<std::string> tokens;
    std::string substr;
    std::istringstream stream{ str };

    while(std::getline(stream, substr, separator))
        tokens.push_back(substr);

    return output;
}

uint32_t glxyui::utils::hash::hash(const char* str, const uint32_t value) {
    return *str ? hash(str + 1, (value ^ *str) * 0x1000193u11) : value;
}