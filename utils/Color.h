#ifndef COLOR_H
#define COLOR_H

#include <string>

namespace Color {
    const std::string RESET   = "\033[0m";

    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN    = "\033[36m";
    const std::string WHITE   = "\033[37m";

    const std::string BRIGHT_RED     = "\033[91m";
    const std::string BRIGHT_BLACK = "\033[90m";
    const std::string BROWN = "\033[38;5;130m";
}

#endif