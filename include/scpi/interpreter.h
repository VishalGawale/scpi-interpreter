#pragma once

#include <string>

#include "scpi/instrument.h"

namespace scpi {

class Interpreter {
public:
    std::string execute(const std::string& line);

private:
    Instrument instrument_;
};

}  // namespace scpi
