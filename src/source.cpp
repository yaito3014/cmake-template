#include <private.hpp>

#include <example/public.hpp>

namespace example {

int func_internal(int x) { return x; }

int func(int x) { return func_internal(x); }

}  // namespace example
