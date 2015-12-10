#include <bits/stdc++.h>
using namespace std;

string line;
vector < pair <string,string> > res;
string temp;
string tempp;
enum State { START, INCOMMENT, INNUM, INID, INASSIGN, DONE };
enum Type { SPACE, NUMBER, LETTER, BEGINASSIGN, ENDASSIGN, BEGINCOMMENT, ENDCOMMENT, OTHER };
State state;
set<string> val;
bool errored;
void init_val() {
	string r[] = { "if", "then", "else", "end", "repeat", "until", "read", "write" };
	for (int i = 0; i < 8; i++) {
		val.insert(r[i]);
	}
	string sym[] = { "+", "-", "*", "/", "=", "<", "()", ";", ":=" };
	for (int i = 0; i < 9; i++) val.insert(sym[i]);
}

Type type_of(char c) {
	if (c == ' ')
		return SPACE;
	if (c >= '0' && c <= '9')
		return NUMBER;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return LETTER;
	if (c == ':')
		return BEGINASSIGN;
	if (c == '=')
		return ENDASSIGN;
	if (c == '{')
		return BEGINCOMMENT;
	if (c == '}')
		return ENDCOMMENT;
	return OTHER;
}

void scanline() {
	for (int i = 0; i < line.length(); i++) {
		beginning:
		switch(state) {
		case START:
			temp = line[i];
			switch(type_of(line[i])) {
			case SPACE: break;
			case NUMBER:
				tempp = "number";
				state = INNUM;
				break;
			case LETTER:
				tempp = "identifier";
				state = INID;
				break;
			case BEGINASSIGN:
				tempp = "special symbol";
				state = INASSIGN;
				break;
			case BEGINCOMMENT:
				state = INCOMMENT;
				break;
			default:
				tempp = "special symbol";
				state = DONE;
				break;
			}
			break;
		case INCOMMENT:
			switch(type_of(line[i])) {
			case ENDCOMMENT:
				state = START;
				break;
			default:
				break;
			}
			break;
		case INNUM:
			switch(type_of(line[i])) {
			case NUMBER:
				temp+= line[i];
				break;
			default:
				state = DONE;
				i--;
				break;
			}
			break;
		case INID:
			switch(type_of(line[i])) {
			case LETTER:
				temp+= line[i];
				break;
			default:
				i--;
				state = DONE;
				break;
			}
			break;
		case INASSIGN:
			switch(type_of(line[i])) {
			case ENDASSIGN:
				temp+= line[i];
				state = DONE;
				break;
			default:
				i--;
				state = DONE;
				break;
			}
			break;
		case DONE:
			pair<string,string> k;
			k.first = temp;
			k.second = tempp;
			if (tempp == "identifier" && val.find(temp) != val.end()) {
				k.second = "reserved word";
			}
			if (tempp == "special symbol" && val.find(temp) == val.end()) {
				k.second = "error: unidentified symbol";
				errored = true;
			}
			res.push_back(k);
			state = START;
			goto beginning;
			break;
		}
	}
	if (state == INCOMMENT) return;
	if (state != START) {
		pair<string,string> k;
		k.first = temp;
		k.second = tempp;
		if (tempp == "identifier" && val.find(temp) != val.end()) {
			k.second = "reserved word";
		}
		if (tempp == "special symbol" && val.find(temp) == val.end()) {
			k.second = "error: unidentified symbol";
			errored = true;
		}
		res.push_back(k);
	}
	state = START;
}

void print_for_parser(pair<string, string> k) {
	if (k.second == "reserved word" || k.second == "special symbol")
		cout << k.first;
	else cout << k.second;
	cout << endl;
}

int main() {
	freopen("tiny_sample_code.txt","r",stdin);
	freopen("scanner_output.txt","w",stdout);
	init_val();
	state = START;
	while(getline(cin, line)) {
		scanline();
	}
	if (errored) {
		cout << "ERROR" << endl;
		return 0;
	}
	for (int i = 0; i < res.size(); i++) {
		print_for_parser(res[i]);
	}
	cout << "$" << endl;
	return 0;
}
