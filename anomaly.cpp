/**
 * anomaly.cpp
 */

#include <cmath>
#include "lucca.hpp"

float lucca::anomaly::true2ecc(float tht_rad, float e) {
    float n = std::sqrt(1.0 - e) * std::tan(0.5 * tht_rad);
    float d = std::sqrt(1.0 + e);
    return lucca::anomaly::angmod(2.0 * std::atan2(n, d));
}

float lucca::anomaly::true2mean(float tht_rad, float e) {
    float E_rad = lucca::anomaly::true2ecc(tht_rad, e);
    return lucca::anomaly::angmod(lucca::anomaly::ecc2mean(E_rad, e));
}

float lucca::anomaly::mean2ecc(float M_rad, float e) {
    float E_rad = M_rad + 0.5 * e;
    if (M_rad > M_PI) {
        E_rad = M_rad - 0.5 * e;
    }
    float r = 1.0;
    float tol = 1e-8;
    int n = 0;
    int max = (int)1e3;
    while (std::abs(r) > tol && n < max) {
        n += 1;
        float f = E_rad - e * std::sin(E_rad) - M_rad;
        float df = 1.0 - e * std::cos(E_rad);
        r = f / df;
        E_rad = E_rad - r;
    }
    if (std::abs(r) > tol) {
        throw lucca::exceptions::xUnknown();
    }
    return lucca::anomaly::angmod(E_rad);
}

float lucca::anomaly::mean2true(float M_rad, float e) {
    float E_rad = lucca::anomaly::mean2ecc(M_rad, e);
    return lucca::anomaly::angmod(lucca::anomaly::ecc2true(E_rad, e));
}

float lucca::anomaly::ecc2true(float E_rad, float e) {
    float n = std::sqrt(1.0 + e) * std::tan(0.5 * E_rad);
    float d = std::sqrt(1.0 - e);
    return lucca::anomaly::angmod(2.0 * std::atan2(n, d));
}

float lucca::anomaly::ecc2mean(float E_rad, float e) {
    return lucca::anomaly::angmod(E_rad - e * std::sin(E_rad));
}

float lucca::anomaly::angmod(float ang_rad) {
    float m = std::fmod(ang_rad, 2 * M_PI);
    return m < 0 ? m + 2 * M_PI : m;
}
