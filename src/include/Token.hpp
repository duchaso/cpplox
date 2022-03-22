#pragma once

#include <string>

#include "TokenType.hpp"
#include "Object.hpp"

class Token 
{
public:
    Token(TokenType type, std::string lexeme, Object* literal, int line);

    std::string toString();
private:
    TokenType type;
    std::string lexeme;
    Object* literal;
    int line;
};