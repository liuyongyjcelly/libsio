#include <gtest/gtest.h>

#include "sio/logger.h"
#include "sio/str.h"

namespace sio {

    TEST(Log, Basic) {
    str msg = "This is a log message.";

    SIO_INFO    << msg;
    SIO_WARNING << msg;
    SIO_ERROR   << msg;
    SIO_FATAL   << msg;
}

} // namespace sio
