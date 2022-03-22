#include "include/Token.hpp"


Token::Token(TokenType type, std::string lexeme, Object* literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line)
    {}

std::string Token::toString()
{
    return std::to_string(type) + "\t" + lexeme + "\t" + literal->toString();
}