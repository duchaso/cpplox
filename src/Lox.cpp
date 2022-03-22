#include "include/Lox.hpp"
#include "include/Token.hpp"
#include "include/Scanner.hpp"

bool hadError = false;

static void run(std::string& source)
{
    Scanner scanner(source);
    std::list<Token> tokens = scanner.scanTokens();

    for(Token& token : tokens)
        std::cout << token.toString() << '\n';
}


void error(int line, std::string message)
{
    report(line, "", message);
}
static void report(int line, std::string where, std::string message)
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message << '\n';
    hadError = true;
}

void runFile(std::string& path)
{
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::string source = buffer.str();
    // std::cout << "_------------------------------------------\n";
    // std::cout << source << "\n";
    // std::cout << "-------------------------------------------\n";
    run(source);

    if(hadError) exit(EX_DATAERR);
}

void runPrompt()
{
    while(true)
    {
        std::string line;
        std::cout << "> ";
        std::getline(std::cin, line);
        if(line.empty()) break;
        run(line);
        hadError = false;
    }
}