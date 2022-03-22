#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <sysexits.h>

extern bool hadError;

static void run(std::string& source);
void error(int line, std::string message);
static void report(int line, std::string where, std::string message);

void runFile(std::string& path);
void runPrompt();