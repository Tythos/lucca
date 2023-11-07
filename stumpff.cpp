/**
 * stumpff.cpp
 */

#include <cmath>
#include "lucca.hpp"

float lucca::stumpff::sine(float x) {
    if (0.0 < x) {
        float sx = std::sqrt(x);
        return (sx - std::sin(sx)) / (sx * sx * sx);
    } else if (x < 0.0) {
        float sx = std::sqrt(-x);
        return (std::sinh(sx) - sx) / (sx * sx * sx);
    }
    return 1.0 / 6.0;
}

float lucca::stumpff::cosine(float x) {
    if (0.0 < x) {
        float sx = std::sqrt(x);
        return (1.0 - std::cos(sx)) / x;
    } else if (x < 0.0) {
        float sx = std::sqrt(-x);
        return (std::cosh(sx) - 1.0) / (-x);
    }
    return 1.0 / 2.0;
}
