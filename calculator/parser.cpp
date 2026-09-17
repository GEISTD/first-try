#include "parser.h"
#include "math_functions.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <cmath>

namespace calculator {

Parser::Parser(const std::string& expr) : expression(expr), pos(0), currentToken(TokenType::EOF_TOKEN) {
    while (pos < expression.length() && std::isspace(expression[pos])) {
        pos++;
    }
}

void Parser::skipWhitespace() {
    while (pos < expression.length() && std::isspace(expression[pos])) {
        pos++;
    }
}

bool Parser::isDigit(char c) {
    return std::isdigit(c) || c == '.';
}

bool Parser::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

void Parser::advance() {
    currentToken = getNextToken();
}

Token Parser::getNextToken() {
    skipWhitespace();

    if (pos >= expression.length()) {
        return Token(TokenType::EOF_TOKEN);
    }

    char current = expression[pos];

    if (std::isdigit(static_cast<unsigned char>(current)) || current == '.') {
        size_t start = pos;
        bool hasDot = false;

        while (pos < expression.length()) {
            char ch = expression[pos];
            if (std::isdigit(static_cast<unsigned char>(ch))) {
                ++pos;
                continue;
            }
            if (ch == '.') {
                if (hasDot) {
                    throw std::runtime_error("Invalid number format: multiple decimal points");
                }
                hasDot = true;
                ++pos;
                continue;
            }
            break;
        }

        std::string numStr = expression.substr(start, pos - start);
        if (numStr.empty() || numStr == ".") {
            throw std::runtime_error("Invalid number format: " + numStr);
        }

        try {
            double value = std::stod(numStr);
            return Token(TokenType::NUMBER, value);
        } catch (const std::exception&) {
            throw std::runtime_error("Invalid number format: " + numStr);
        }
    }

    if (std::isalpha(static_cast<unsigned char>(current)) || current == '_') {
        size_t start = pos;
        while (pos < expression.length() && (std::isalnum(static_cast<unsigned char>(expression[pos])) || expression[pos] == '_')) {
            pos++;
        }
        return Token(TokenType::FUNCTION, expression.substr(start, pos - start));
    }

    if (current == ',') {
        pos++;
        return Token(TokenType::COMMA);
    }

    if (current == '-') {
        pos++;
        return Token(TokenType::MINUS);
    }

    switch (current) {
        case '+':
            pos++;
            return Token(TokenType::PLUS);
        case '*':
            pos++;
            return Token(TokenType::MULTIPLY);
        case '/':
            pos++;
            return Token(TokenType::DIVIDE);
        case '(':
            pos++;
            return Token(TokenType::LPAREN);
        case ')':
            pos++;
            return Token(TokenType::RPAREN);
        default:
            throw std::runtime_error("Unexpected character: " + std::string(1, current));
    }
}

// Parse expression: term (+|- term)*
double Parser::parseExpression() {
    double result = parseTerm();

    while (currentToken.type == TokenType::PLUS || currentToken.type == TokenType::MINUS) {
        TokenType op = currentToken.type;
        advance();
        double rhs = parseTerm();

        if (op == TokenType::PLUS) {
            result += rhs;
        } else {
            result -= rhs;
        }
    }

    return result;
}

// Parse term: factor (*|/ factor)*
double Parser::parseTerm() {
    double result = parseFactor();

    while (currentToken.type == TokenType::MULTIPLY || currentToken.type == TokenType::DIVIDE) {
        TokenType op = currentToken.type;
        advance();
        double rhs = parseFactor();

        if (op == TokenType::MULTIPLY) {
            result *= rhs;
        } else {
            if (rhs == 0.0) {
                throw std::runtime_error("Division by zero");
            }
            result /= rhs;
        }
    }

    return result;
}

// Parse factor: number | (expression)
double Parser::parseFactor() {
    return parsePrimary();
}

double Parser::parsePrimary() {
    if (currentToken.type == TokenType::MINUS) {
        advance();
        return -parsePrimary();
    }

    if (currentToken.type == TokenType::NUMBER) {
        double value = currentToken.value;
        advance();
        return value;
    }

    if (currentToken.type == TokenType::LPAREN) {
        advance();
        double result = parseExpression();
        if (currentToken.type != TokenType::RPAREN) {
            throw std::runtime_error("Expected closing parenthesis");
        }
        advance();
        return result;
    }

    if (currentToken.type == TokenType::FUNCTION) {
        std::string funcName = currentToken.text;
        advance();

        if (currentToken.type != TokenType::LPAREN) {
            throw std::runtime_error("Expected '(' after function name");
        }
        advance();

        if (funcName == "pow") {
            double base = parseExpression();
            if (currentToken.type != TokenType::COMMA) {
                throw std::runtime_error("Expected ',' in pow(base, exponent)");
            }
            advance();
            double exponent = parseExpression();
            if (currentToken.type != TokenType::RPAREN) {
                throw std::runtime_error("Expected ')' after pow arguments");
            }
            advance();
            return MathFunctions::pow(base, exponent);
        }

        double arg = parseExpression();
        if (currentToken.type != TokenType::RPAREN) {
            throw std::runtime_error("Expected ')' after function argument");
        }
        advance();

        return MathFunctions::evaluateFunction(funcName, arg);
    }

    throw std::runtime_error("Expected number, function, or opening parenthesis");
}

// Main evaluation method
double Parser::evaluate() {
    try {
        advance();
        double result = parseExpression();

        if (currentToken.type != TokenType::EOF_TOKEN) {
            throw std::runtime_error("Unexpected characters at end of expression");
        }

        return result;
    } catch (const std::exception& e) {
        throw std::runtime_error("Parse error: " + std::string(e.what()));
    }
}

} // namespace calculator