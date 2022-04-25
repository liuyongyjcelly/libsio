#include "sio/check.h"

#include <gtest/gtest.h>
#include <cstdio>

#include "sio/type.h"
#include "sio/vec.h"

namespace sio {

TEST(Check, Basic) {
    vec<int> v = {1,2};
    i32 i = 0;
    i32 sum = 0;
    SIO_CHECK("sum = sum of v[0,i)");
    SIO_CHECK_EQ(i, 0);
    while (i != v.size()) {
        sum += v[i++];
    }
    SIO_CHECK_EQ(i, v.size());

    SIO_CHECK_EQ(sum, 3);
    SIO_CHECK_GE(sum, 3);
    SIO_CHECK_LE(sum, 3);
    SIO_CHECK_GT(sum, 2);
    SIO_CHECK_LT(sum, 4);
}

namespace { // seal test func scope in anonymous namespace
Error test_error_func() {
    return Error::OK;
    //return Error::OutOfMemory;
}
}

TEST(Check, Error) {
    Error err = test_error_func();
    SIO_CHECK(err == Error::OK);
}

} // namespace sio
