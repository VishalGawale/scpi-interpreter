#pragma once

#include <string>
#include <vector>

namespace scpi {

struct Command {
    std::string header;
    bool is_query = false;
    std::vector<std::string> args;
};

}  // namespace scpi
