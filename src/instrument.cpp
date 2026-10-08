#include "scpi/instrument.h"

namespace scpi {

void Instrument::reset() {
    frequency_hz = 1'000'000.0;
    power_dbm = 0.0;
}

}  // namespace scpi
