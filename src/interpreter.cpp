#include "scpi/interpreter.h"
#include "scpi/parser.h"
#include <cstddef>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

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
            std::size_t pos = 0;
            double value = std::stod(cmd->args[0], &pos);
            if (pos != cmd->args[0].size()) {
                return "-104,\"Data type error\"";
            }
            instrument_.frequency_hz = value;
        } catch (const std::exception&) {
            return "-104,\"Data type error\"";
        }
        return "";
    }
    if (cmd->header == "POW") {
        if (cmd->is_query) {
            return format_number(instrument_.power_dbm);
        }
        if (cmd->args.size() != 1) {
            return "-104,\"Data type error\"";
        }
        try {
            std::size_t pos = 0;
            double value = std::stod(cmd->args[0], &pos);
            if (pos != cmd->args[0].size()) {
                return "-104,\"Data type error\"";
            }
            instrument_.power_dbm = value;
        } catch (const std::exception&) {
            return "-104,\"Data type error\"";
        }
        return "";
    }
    return "-113,\"Undefined header\"";
}

}  // namespace scpi