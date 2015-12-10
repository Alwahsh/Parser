#include <bits/stdc++.h>
using namespace std;

stringstream ss;
string token;

void stmt_sequence(int level);

void tabs(int level) {
	while(level--)
		ss << "  ";
}

void getToken() {
	cin >> token;
}

bool out_of_tokens() {
	return token == "$";
}

void match(string s) {
	if (s == token)
		getToken();
	else throw "error";
}

void factor(int level) {
	tabs(level);
	ss << "factor start" << endl;
	level++;
	if (token == "(") {
		match("(");
		exp(level);
		match(")");
	}
	else if (token == "number") {
		match("number");
	} else
		match("identifier");
	tabs(--level);
	ss << "factor end" << endl;
}

void mulop(int level) {
	tabs(level);
	ss << "mulop start" << endl;
	if (token == "*")
		match("*");
	else
		match("/");
	tabs(level);
	ss << "mulop end" << endl;
}

void term(int level) {
	tabs(level);
	ss << "term start" << endl;
	level++;
	factor(level);
	while(token == "*" || token == "/") {
		mulop(level);
		factor(level);
	}
	tabs(--level);
	ss << "term end" << endl;
}

void addop(int level) {
	tabs(level);
	ss << "addop start" << endl;
	if (token == "+")
		match("+");
	else match("-");
	tabs(level);
	ss << "addop end" << endl;
}

void simple_exp(int level) {
	tabs(level);
	ss << "simple-exp start" << endl;
	level++;
	term(level);
	while (token == "+" || token == "-") {
		addop(level);
		term(level);
	}
	tabs(--level);
	ss << "simple-exp end" << endl;
}

void comparison_op(int level) {
	tabs(level);
	ss << "comparison-op start" << endl;
	if (token == "<")
		match("<");
	else match("=");
	tabs(level);
	ss << "comparison-op end" << endl;
}

void exp(int level) {
	tabs(level);
	ss << "exp start" << endl;
	level++;
	simple_exp(level);
	if (token == "<" || token == "=") {
		comparison_op(level);
		simple_exp(level);
	}
	tabs(--level);
	ss << "exp end" << endl;
}

void if_stmt(int level) {
	tabs(level);
	ss << "if-stmt start" << endl;
	level++;
	match("if");
	exp(level);
	match("then");
	stmt_sequence(level);
	if (token == "else") {
		match("else");
		stmt_sequence(level);
	}
	match("end");
	tabs(--level);
	ss << "if-stmt end" << endl;
}

void repeat_stmt(int level) {
	tabs(level);
	ss << "repeat-stmt start" << endl;
	level++;
	match("repeat");
	stmt_sequence(level);
	match("until");
	exp(level);
	tabs(--level);
	ss << "repeat-stmt end" << endl;
}

void assign_stmt(int level) {
	tabs(level);
	ss << "assign-stmt start" << endl;
	level++;
	match("identifier");
	match(":=");
	exp(level);
	tabs(--level);
	ss << "assign-stmt end" << endl;
}

void read_stmt(int level) {
	tabs(level);
	ss << "read-stmt start" << endl;
	match("read");
	match("identifier");
	tabs(level);
	ss << "read-stmt end" << endl;
}

void write_stmt(int level) {
	tabs(level);
	ss << "write-stmt start" << endl;
	level++;
	match("write");
	exp(level);
	tabs(--level);
	ss << "write-stmt end" << endl;
}

void statement(int level) {
	tabs(level);
	ss << "statement start" << endl;
	level++;
	if (token == "if")
		if_stmt(level);
	else if (token == "repeat")
		repeat_stmt(level);
	else if(token == "identifier")
		assign_stmt(level);
	else if(token == "read")
		read_stmt(level);
	else if(token == "write")
		write_stmt(level);
	else
		throw "error";
	tabs(--level);
	ss << "statement end" << endl;
}

void stmt_sequence(int level) {
	tabs(level);
	ss << "stmt-sequence start" << endl;
	level++;
	statement(level);
	while (token == ";") {
		match(";");
		statement(level);
	}
	tabs(--level);
	ss << "stmt-sequence end" << endl;
}

void program(int level) {
	tabs(level);
	ss << "program start" << endl;
	level++;
	stmt_sequence(level);
	tabs(--level);
	ss << "program end" << endl;
}


int main() {
	freopen("scanner_output.txt", "r", stdin);
	freopen("parser_output.txt", "w", stdout);
	try {
		getToken();
		program(0);
		if (out_of_tokens())
			cout << ss.str();
		else
			throw "error";
	} catch (exception e) {
		cout << "ERROR" << endl;
	}
	return 0;
}
