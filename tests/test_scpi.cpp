#include <optional>
#include <string>

#include "check.h"
#include "scpi/interpreter.h"
#include "scpi/parser.h"

static void test_parser() {
    auto idn = scpi::parse("*IDN?");
    CHECK(idn.has_value());
    if (idn) {
        CHECK(idn->header == "*IDN");
        CHECK(idn->is_query);
        CHECK(idn->args.empty());
    }

    auto set = scpi::parse("FREQ 100");
    CHECK(set.has_value());
    if (set) {
        CHECK(set->header == "FREQ");
        CHECK(!set->is_query);
        CHECK(set->args.size() == 1);
        if (set->args.size() == 1) {
            CHECK(set->args[0] == "100");
        }
    }

    auto query = scpi::parse("FREQ?");
    CHECK(query.has_value());
    if (query) {
        CHECK(query->header == "FREQ");
        CHECK(query->is_query);
        CHECK(query->args.empty());
    }

    auto lower = scpi::parse("freq?");
    CHECK(lower.has_value());
    if (lower) {
        CHECK(lower->header == "FREQ");
    }

    CHECK(!scpi::parse("   ").has_value());
    CHECK(!scpi::parse("").has_value());

    auto spaced = scpi::parse("POW   10");
    CHECK(spaced.has_value());
    if (spaced) {
        CHECK(spaced->args.size() == 1);
        if (spaced->args.size() == 1) {
            CHECK(spaced->args[0] == "10");
        }
    }
}

static void test_interpreter() {
    scpi::Interpreter in;

    CHECK(in.execute("*IDN?").find("SCPI-Sim") != std::string::npos);

    CHECK(in.execute("FREQ 2000000") == "");
    CHECK(in.execute("FREQ?") == "2000000");

    CHECK(in.execute("POW 10") == "");
    CHECK(in.execute("POW?") == "10");

    in.execute("*RST");
    CHECK(in.execute("FREQ?") == "1000000");
    CHECK(in.execute("POW?") == "0");

    CHECK(in.execute("NOPE").rfind("-113", 0) == 0);

    CHECK(!in.execute("FREQ abc").empty());
    CHECK(in.execute("FREQ?") == "1000000");

    CHECK(!in.execute("FREQ 10abc").empty());
    CHECK(in.execute("FREQ?") == "1000000");

    CHECK(!in.execute("POW abc").empty());
    CHECK(in.execute("POW?") == "0");

    CHECK(!in.execute("POW 5xyz").empty());
    CHECK(in.execute("POW?") == "0");
}

int main() {
    test_parser();
    test_interpreter();
    return g_failures == 0 ? 0 : 1;
}