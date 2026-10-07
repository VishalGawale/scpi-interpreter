#pragma once

#include <optional>
#include <string>

#include "scpi/command.h"

namespace scpi {

std::optional<Command> parse(const std::string& line);

}  // namespace scpi
