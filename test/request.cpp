#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/http/request.hpp"

using namespace he::http;
using namespace std;
using namespace testing;

TEST(Request, Setters) {
    Request req(GET, "/unchanged", "this data is unchanged");

    req.setPath("/changed");
    EXPECT_THAT(req.getPath(), Eq("/changed"));
    
    req.setMethod(POST);
    EXPECT_THAT(req.getMethod(), Eq(POST));
}