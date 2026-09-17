#include "math_functions.h"
#include <string>
#include <cmath>
#include <stdexcept>
#include <cctype>

namespace calculator {

// Basic operations
double MathFunctions::sqrt(double x) {
    if (x < 0) {
        throw std::runtime_error("Cannot calculate square root of negative number");
    }
    return std::sqrt(x);
}

double MathFunctions::square(double x) {
    return x * x;
}

// Trigonometric functions (in radians)
double MathFunctions::sin(double x) {
    return std::sin(x);
}

double MathFunctions::cos(double x) {
    return std::cos(x);
}

double MathFunctions::tan(double x) {
    if (std::abs(std::cos(x)) < 1e-10) {
        throw std::runtime_error("Tangent is undefined at this value");
    }
    return std::tan(x);
}

double MathFunctions::asin(double x) {
    if (x < -1.0 || x > 1.0) {
        throw std::runtime_error("Argument for asin must be between -1 and 1");
    }
    return std::asin(x);
}

double MathFunctions::acos(double x) {
    if (x < -1.0 || x > 1.0) {
        throw std::runtime_error("Argument for acos must be between -1 and 1");
    }
    return std::acos(x);
}

double MathFunctions::atan(double x) {
    return std::atan(x);
}

// Hyperbolic functions
double MathFunctions::sinh(double x) {
    return std::sinh(x);
}

double MathFunctions::cosh(double x) {
    return std::cosh(x);
}

double MathFunctions::tanh(double x) {
    return std::tanh(x);
}

// Logarithmic functions
double MathFunctions::log(double x) {
    if (x <= 0) {
        throw std::runtime_error("Logarithm of non-positive number is undefined");
    }
    return std::log(x);
}

double MathFunctions::log10(double x) {
    if (x <= 0) {
        throw std::runtime_error("Logarithm of non-positive number is undefined");
    }
    return std::log10(x);
}

// Exponential function
double MathFunctions::exp(double x) {
    return std::exp(x);
}

// Power function
double MathFunctions::pow(double base, double exponent) {
    // Handle special cases
    if (base == 0 && exponent < 0) {
        throw std::runtime_error("0 raised to negative power is undefined");
    }
    if (base < 0 && std::floor(exponent) != exponent) {
        throw std::runtime_error("Negative base with non-integer exponent is undefined");
    }
    return std::pow(base, exponent);
}

// Evaluate mathematical function by name
double MathFunctions::evaluateFunction(const std::string& funcName, double value) {
    std::string name = funcName;
    // Convert to lowercase for case-insensitive comparison
    for (char& c : name) {
        c = std::tolower(c);
    }
    
    if (name == "sqrt") return sqrt(value);
    if (name == "square") return square(value);
    if (name == "sin") return sin(value);
    if (name == "cos") return cos(value);
    if (name == "tan") return tan(value);
    if (name == "asin") return asin(value);
    if (name == "acos") return acos(value);
    if (name == "atan") return atan(value);
    if (name == "sinh") return sinh(value);
    if (name == "cosh") return cosh(value);
    if (name == "tanh") return tanh(value);
    if (name == "log") return log(value);
    if (name == "log10") return log10(value);
    if (name == "exp") return exp(value);
    
    throw std::runtime_error("Unknown function: " + funcName);
}

} // namespace calculator