#pragma once

#include <string>

class Object
{
public:
    virtual std::string toString() = 0;
};

class Null : public Object
{
public:
    std::string toString() override
    {
        return "null";
    }
};

class String : public Object
{
public:
    String(std::string str) : str(str) {} 
    std::string toString()
    {
        return str;
    }
private:
    std::string str;
};

class Int : public Object
{
public:
    Int(int i) : i(i) {}
    std::string toString() 
    {
        return std::to_string(i);
    }
private:
    int i;
};

class Double : public Object
{
public:
    Double(double d) : d(d) {}
    std::string toString()
    {
        return std::to_string(d);
    }
private:
    double d;
};