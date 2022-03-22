#pragma once

#include <string>
#include <list>
#include <map>

#include "TokenType.hpp"
#include "Token.hpp"
#include "Lox.hpp"

class Scanner
{
public:
    Scanner(std::string& source);

    std::list<Token> scanTokens();
    bool isAtEnd();
    void scanToken();
    void addToken(TokenType type);
    void addToken(TokenType type, Object* literal);

    void number();
    void string();
    void identifier();
    void comments();

    char advance();
    bool match(char expected);
    char peek();
    char peekNext();
private:
    std::string source;
    std::list<Token> tokens;
    static std::map<std::string, TokenType> keywords;
    int start = 0;
    int current = 0;
    int line = 1;
};