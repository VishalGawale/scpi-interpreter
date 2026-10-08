#include "scpi/interpreter.h"
#include "scpi/parser.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace scpi {

namespace {

std::string format_number(double value) {
    std::ostringstream out;
    out << std::setprecision(15) << value;
    return out.str();
}

}  // namespace

std::string Interpreter::execute(const std::string& line) {
    auto cmd = parse(line);
    if (!cmd) {
        return "";
    }
    if (cmd->header == "*IDN" && cmd->is_query) {
        return "SIM Instruments,SCPI-Sim,0,1.0";
    }
    if (cmd->header == "*RST") {
        instrument_.reset();
        return "";
    }
    if (cmd->header == "FREQ") {
        if (cmd->is_query) {
            return format_number(instrument_.frequency_hz);
        }
        if (cmd->args.size() != 1) {
            return "-104,\"Data type error\"";
        }
        try {
            instrument_.frequency_hz = std::stod(cmd->args[0]);
        } catch (const std::exception&) {
            return "-104,\"Data type error\"";
        }
        return "";
    }
    // TODO (you): POW goes here, same pattern as FREQ
    return "-113,\"Undefined header\"";
}

}  // namespace scpi