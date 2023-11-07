/**
 * exceptions.cpp
 */

#include "lucca.hpp"

const char* lucca::exceptions::xUnknown::what() const throw() {
    return "Some kind of unknown astrodynamics exception was thrown";
}
