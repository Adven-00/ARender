#include <iostream>

#ifdef DEBUG
#  define DEBUG(x) do { std::cout << x << std::cout; } while (0)
#else
#  define DEBUG(x) do {} while (0)
#endif