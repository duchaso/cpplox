#pragma once

class Expr {
public:
	virtual ~Expr(){}
};

class Binary : public Expr {
public:
	Binary(Expr* left, Token op, Expr* right)
		: left(left), op(op), right(right){}
	~Binary(){
		if(!left) delete left;
		if(!right) delete right;
	}
private:
	Expr* left;
	Token op;
	Expr* right;
};

class Grouping : public Expr {
public:
	Grouping(Expr* expression)
		: expression(expression){}
	~Grouping(){
		if(!expression) delete expression;
	}
private:
	Expr* expression;
};

class Literal : public Expr {
public:
	Literal(Object* value)
		: value(value){}
	~Literal(){
		if(!value) delete value;
	}
private:
	Object* value;
};

class Unary : public Expr {
public:
	Unary(Token op, Expr* right)
		: op(op), right(right){}
	~Unary(){
		if(!right) delete right;
	}
private:
	Token op;
	Expr* right;
};

