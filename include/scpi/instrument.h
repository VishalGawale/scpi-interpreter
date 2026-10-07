#pragma once

namespace scpi {

struct Instrument {
    double frequency_hz = 1'000'000.0;
    double power_dbm = 0.0;

    void reset();
};

}  // namespace scpi
