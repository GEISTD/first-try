#ifndef CALCULATOR_PARSER_H
#define CALCULATOR_PARSER_H

#include <string>
#include <stack>
#include <vector>
#include <cctype>

namespace calculator {

// Token types
enum class TokenType {
    NUMBER,
    FUNCTION,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    COMMA,
    EOF_TOKEN
};

// Token structure
struct Token {
    TokenType type;
    double value;
    std::string text;
    
    Token(TokenType t) : type(t), value(0.0) {}
    Token(TokenType t, double v) : type(t), value(v) {}
    Token(TokenType t, const std::string& s) : type(t), text(s) {}
};

// Parser class for mathematical expressions
class Parser {
private:
    std::string expression;
    size_t pos;
    Token currentToken;

    // Helper methods
    void skipWhitespace();
    bool isDigit(char c);
    bool isOperator(char c);
    void advance();

    // Tokenization
    Token getNextToken();

    // Expression parsing methods
    double parseExpression();
    double parseTerm();
    double parseFactor();
    double parsePrimary();

public:
    Parser(const std::string& expr);
    
    // Main parsing method
    double evaluate();
};

} // namespace calculator

#endif // CALCULATOR_PARSER_H