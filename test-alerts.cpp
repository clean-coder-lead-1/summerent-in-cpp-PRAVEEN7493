#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
//double value, double lowerLimit, double upperLimit) {
TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);

  REQUIRE(inferBreach(25, 20, 30) == NORMAL);

  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
}
