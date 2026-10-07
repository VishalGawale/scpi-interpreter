#include <iostream>
#include <string>

#include "scpi/interpreter.h"

int main() {
    scpi::Interpreter interpreter;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line == "quit") {
            break;
        }
        const std::string response = interpreter.execute(line);
        if (!response.empty()) {
            std::cout << response << '\n';
        }
    }
    return 0;
}