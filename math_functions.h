#ifndef CALCULATOR_MATH_FUNCTIONS_H
#define CALCULATOR_MATH_FUNCTIONS_H

#include <string>
#include <cmath>
#include <stdexcept>

namespace calculator {

// Mathematical function evaluator
class MathFunctions {
public:
    // Basic operations
    static double sqrt(double x);
    static double square(double x);
    
    // Trigonometric functions (in radians)
    static double sin(double x);
    static double cos(double x);
    static double tan(double x);
    static double asin(double x);
    static double acos(double x);
    static double atan(double x);
    
    // Hyperbolic functions
    static double sinh(double x);
    static double cosh(double x);
    static double tanh(double x);
    
    // Logarithmic functions
    static double log(double x);  // natural log
    static double log10(double x);  // base 10 log
    
    // Exponential function
    static double exp(double x);
    
    // Power function
    static double pow(double base, double exponent);
    
    // Evaluate mathematical function by name
    static double evaluateFunction(const std::string& funcName, double value);
};

} // namespace calculator

#endif // CALCULATOR_MATH_FUNCTIONS_H