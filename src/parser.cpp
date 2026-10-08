#include "scpi/parser.h"
#include <cctype>
#include <sstream>
#include <vector>

namespace scpi {

std::optional<Command> parse(const std::string& line) {
    auto first = line.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return std::nullopt;
    }
    auto last = line.find_last_not_of(" \t\r\n");
    std::string trimmed = line.substr(first, last - first + 1);

    std::istringstream stream(trimmed);
    std::vector<std::string> tokens;
    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }

    Command cmd;
    cmd.header = tokens[0];
    if (cmd.header.back() == '?') {
        cmd.is_query = true;
        cmd.header.pop_back();
    }
    for (char& c : cmd.header) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    cmd.args.assign(tokens.begin() + 1, tokens.end());
    return cmd;
}

}  // namespace scpi