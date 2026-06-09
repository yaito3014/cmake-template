#include <example/public.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("main")
{
  CHECK(example::func(12) == 12);
  CHECK(example::func(34) == 34);
}
