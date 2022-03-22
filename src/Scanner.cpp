#include "include/Scanner.hpp"

std::map<std::string, TokenType> Scanner::keywords =
{
    {"and",     AND},
    {"class",   CLASS},
    {"else",    ELSE},
    {"false",   FALSE},
    {"for",     FOR},
    {"fun",     FUN},
    {"if",      IF},
    {"nil",     NIL},
    {"or",      OR},
    {"print",   PRINT},
    {"return",  RETURN},
    {"super",   SUPER},
    {"this",    THIS},
    {"true",    TRUE},
    {"var",     VAR},
    {"while",   WHILE}

};

Scanner::Scanner(std::string& source) : source(source) 
{}

bool Scanner::isAtEnd()
{
    return current >= source.length();
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}
bool isAlpha(char c)
{
    return  (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c == '_');
}
bool isAlphaNumeric(char c)
{
    return isAlpha(c) || isDigit(c);
}

void Scanner::addToken(TokenType type)
{
    addToken(type, new Null());
}
void Scanner::addToken(TokenType type, Object* literal)
{
    std::string text = source.substr(start, current-start);
    tokens.push_back({type, text, literal, line});
}


void Scanner::scanToken()
{
    char c = advance();
    switch (c)
    {
        case '(': addToken(LEFT_PAREN); break;
        case ')': addToken(RIGHT_PAREN); break;
        case '{': addToken(LEFT_BRACE); break;
        case '}': addToken(RIGHT_BRACE); break;
        case ',': addToken(COMMA); break;
        case '.': addToken(DOT); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case ';': addToken(SEMICOLON); break;
        case '*': addToken(STAR); break; 

        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;
        
        case '/':
            if (match('/')) 
            {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd()) advance();
            } else if(match('*')) {
                comments();
            } else {
                addToken(SLASH);
            }
            break;

        case ' ':
        case '\r':
        case '\t':
            //ignore whitespace.
            break;
        case '\n':
            ++line;
            break; 

        case '"': string(); break;

        default:
            if(isDigit(c))
            {
                number();
            } else if(isAlpha(c)) {
                identifier();
            } else {
                error(line, "Unexpected character.");
            }
            break;
    }
}

void Scanner::number()
{
    while(isDigit(peek())) advance();

    if(peek() == '.' && isDigit(peekNext()))
    {
        advance();
        while(isDigit(peek())) advance();
    }

    addToken(NUMBER, new Double( std::stod(source.substr(start, current))));
}

void Scanner::string()
{
    while(peek() != '"' && !isAtEnd())
    {
        if(peek() == '\n') line++;
        advance();
    }

    if(isAtEnd())
    {
        error(line, "Unterminated string");
        return;
    }
    
    advance();

    String* value = new String(source.substr(start+1, current-1));
    addToken(STRING, value);
}

void Scanner::identifier()
{
    while(isAlphaNumeric(peek())) advance();
    std::string text = source.substr(start, current);

    TokenType type{};
    if(keywords.find(text) == keywords.end()) 
        type = IDENTIFIER;
    else
        type = keywords.find(text)->second;

    addToken(type);
}
/* */
void Scanner::comments()
{
    while(true)
    {
        if(isAtEnd())
            break;
        if(peek() == '*' && peekNext() == '/')
        {
            advance();
            advance();
            break;
        }
        if(peek() == '\n') ++line;
        advance();
    }
}

char Scanner::advance()
{
    return source[current++];
}
bool Scanner::match(char expected)
{
    if(isAtEnd()) return false;
    if(source[current] != expected) return false;

    current++;
    return true;
}
char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}
char Scanner::peekNext()
{
    if(current + 1 >= source.length()) return '\0';
    return source[current+1];
}

std::list<Token> Scanner::scanTokens()
{
    while(!isAtEnd())
    {
        start = current;
        scanToken();
    }
    tokens.push_back(Token(E0F, "", new Null(), line));
    return tokens;
}