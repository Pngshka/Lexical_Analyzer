#pragma once

#include "Hashtable.h"

using namespace std;

class analyzer {
public:
	enum state { H, End, Op, Operators, Mark, VarList, Descriptions, Expr, ER, FIN, Type, Name, begin, operators, Descr, SimpleExpr, FunctionName };
	state Start;
	string str;
	int p;

	analyzer(string& str) {
		this->str = str;
		p = 0;
		Start = H;
	}

	void scan(HashTable&);
	bool type(HashTable& hassh) {
		string h;
		string q;
		while (str[p] != ' ') {
			h += str[p];
			p++;
		}
		q = h;
		q += str[p];
		if (q == "int ") {
			Node y;
			y.Name = h;
			y.Type = "TYPE";
			hassh.insertItem(y.Name, y);
			return true;
		}
		else return false; //cout << "Not int" << endl;

	}
	void id(HashTable& hassh) {
		string h;
		while (str[p] != ' '&&str[p]!=','&&str[p]!=';'&&str[p]!='('&&str[p]!=')') {
			h += str[p];
			p++;
		}
		//if (!isdigit(h))
		Node y;
		y.Name = h;
		y.Type = "ID";
		if (!proverkaID(h)) cerr << "Not name: "<< h << endl;
		hassh.insertItem(y.Name, y);
	}

	bool proverkaID(string s) {
		int i = 0;
		while (s[i])
		{
			if (s[i] >= '0' && s[i] <= '9') { 
				return false;
			}
			i++;
		}
		return true;
	}

	void Const(HashTable& hassh) {
		string h;
		while (str[p] != ' '&&str[p]!=';') {
			h += str[p];
			p++;
		}
		Node y;
		y.Name = h;
		y.Type = "CONST";
		if (!proverkaConst(h)) cerr << "Not const: " << h << endl;
		hassh.insertItem(y.Name, y);
		
	}

	bool proverkaConst(string s) {
		int i = 0;
		while (s[i])
		{
			if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')) {
				return false;
			}
			i++;
		}
		return true;
	}

	void simpleexpr(HashTable& hassh) {
		int left = 0, right = 0;
		while (str[p] != ';') {
			if (isdigit(str[p])) {
				Const(hassh);
				p++;

				//проверка
				if (str[p] == '(') cout << "Error (" << endl;

			} else
			if (str[p] == '+') {

				Node r;
				r.Name = "+";
				r.Type = "OPERATOR";
				hassh.insertItem(r.Name, r);
				p += 2;

				//проверка
				if (str[p]==')') cerr << "Not id or const" << endl;

			} else
			if (str[p] == '-') {

				Node r;
				r.Name = "-";
				r.Type = "OPERATOR";
				hassh.insertItem(r.Name, r);
				p += 2;

				//проверка
				if (str[p] == ')') cerr << "Not id or const" << endl;

			} else
			if (str[p] == '(') {
				right++;

				Node r;
				r.Name = "(";
				r.Type = "DEVIDER";
				hassh.insertItem(r.Name, r);
				p += 2;

				if (str[p] == '+'||str[p]=='-') cerr << "Not +/-" << endl;

			} else
			if (str[p] == ')') {
				left++;

				Node r;
				r.Name = ")";
				r.Type = "DEVIDER";
				hassh.insertItem(r.Name, r);

					if (str[p + 2] != '+' && str[p + 2] != '-') cerr << "Not +/-" << endl;

				p += 2;
			}
			else {
				id(hassh);
				p++;

				if (str[p] == '(') cerr << "Error (" << endl;
			}
		}
		if (right != left) cerr << "Error: ( != )" << endl;
		/*if (isdigit(str[p])) {
			Const();
			if (str[p] == ';') {
				p+=2;
				cout << "sdad " << str[p]<<endl;
				Start = Operators;
				return;
			}
			p++;
			if (str[p-1] != ';' && (str[p] == '+' || str[p] == '-')) {
				p += 2;
				simpleexpr();
				p++;
			}
			else {
				if (str[p] == ')') {
					p += 2;
					//cout << str[p] << endl;
					if (str[p - 1] == ';') {
						p++;
						return;
					}
					//p++;
					if (str[p] == '-' || str[p] == '+') {
						p += 2;
						simpleexpr();
						p++;
					}
				}
				else return;
			}
		}
		else {
			if (str[p] == '(') {
				p += 2;
				simpleexpr();
				p++;
				if (str[p] == ')') {
					p+=2;
					//cout << str[p] << endl;
					if (str[p - 1] == ';') {
						p++;
						return;
					}
					//p++;
					if (str[p] == '-' || str[p] == '+') {
						p += 2;
						simpleexpr();
						p++;
					}
				}
				else return;
			}
			else {
				id();
				if (str[p] == ';') {
					p+=2;
					return;
				}
				p++;
				cout << str[p] << endl;
				if (str[p-1] != ';' && (str[p] == '+' || str[p] == '-')) {
					p += 2;
					simpleexpr();
					p++;
				}
				else {
					if (str[p] == ')') {
						p += 2;
						//cout << str[p] << endl;
						if (str[p - 1] == ';') {
							p++;
							return;
						}
						//p++;
						if (str[p] == '-' || str[p] == '+') {
							p += 2;
							simpleexpr();
							p++;
						}
					}
					else {
						//p += 2;
						return;
					}
				}
			}
		}*/
	}
};

void analyzer::scan(HashTable& hassh) {
	Node k;
	k.Name = ";";
	k.Type = "DEVIDER";
	hassh.insertItem(k.Name, k);

	k.Name = "}";
	k.Type = "DEVIDER";
	hassh.insertItem(k.Name, k);

	k.Name = "{";
	k.Type = "DEVIDER";
	hassh.insertItem(k.Name, k);

	while (Start != FIN)
	{
		string u;
		int q = p;
		switch (Start) {
		case H:
			//if (str[p] == 'i') {
				if (!type(hassh)) cout<<"Not int"<<endl;
			Start = FunctionName;
			//} //else cerr << "Not int" << endl;
			break;

		case FunctionName:
			p++;
			id(hassh);
			p += 5;
			Start = Descriptions;
			break;

		case Descriptions:
			//cout << str[p]<<endl;
			if (str[p] == 'i' && str[p + 1] == 'n' && str[p + 2] == 't' && str[p + 3] == ' ') {
				Start = Descr;
				break;
			}
			else {
				if (str[p] == 'g' && str[p + 1] == 'o' && str[p + 2] == 't' && str[p + 3] == 'o' && str[p + 4] == ' ') {
					Start = Operators;
					break;
				} else cerr << "Not int" << endl;
			}

		case Descr:
			type(hassh);
			Start = VarList;
			break;

		case VarList:
			p++;
			id(hassh);
			if (str[p] == ',') {

				k.Name = ",";
				k.Type = "DEVIDER";
				hassh.insertItem(k.Name, k);

				p++;
				Start = VarList;
				break;
			}
			else {
				if (str[p] == ';') {
					p+=2;
					Start = Descriptions;
					break;
				}
			}
			break;

		case Operators:

			u.clear();
			q = p;
			while (str[q] != ' ') {
				u += str[q];
				q++;
			}

			if (u!="return") {
				Start = Op;
				break;
			}
			else {

				k.Name = "return";
				k.Type = "RESWORD";
				hassh.insertItem(k.Name, k);

				Start = End;
				break;
			}

		case Op:
			q = p;
			while (str[q] != ' ') {
				q++;
			}
			q++;
			if (str[q] == '=') {

				k.Name = "=";
				k.Type = "OPERATOR";
				hassh.insertItem(k.Name, k);

				id(hassh);
				p+=3;
				Start = SimpleExpr;
			}
			else {
				if (str[q] == ':') {

					k.Name = ":";
					k.Type = "DEVIDER";
					hassh.insertItem(k.Name, k);

					id(hassh);
					p += 3;
					Start = Operators;
				}
				else {

					k.Name = "goto";
					k.Type = "RESWORD";
					hassh.insertItem(k.Name, k);

					p += 5;
					id(hassh);
					p += 2;
					Start = Operators;
				}
			}
			break;

		/*case Expr:
			if (isdigit(str[p])) {
				Const();
			}
			else {
				if (str[p] == '(') {
					p++;
					break;
				}
				else {
					if (str[p-1] == ')') {
						if (str[p] == ';') {
							p += 2;
							Start = Operators;
							break;
						}
						else p++;
						break;
					}
					else {
						id();
						p++;
						break;
					}
				}
			}
			if (str[p] == ';') {
				p += 2;
				Start = Operators;
				break;
			}
			else {
				p++;
				cout << "+/-: " << str[p] << endl;
				p += 2;
			}
			break;

		case SimpleExpr:
			if (isdigit(str[p]))
				p++;
			else if (str[p] == '(')
			{
				p++;
				Start=Expr;
				p++;
			}
			else
			{
				p++;
			}
			break;
			*/

		case SimpleExpr:
			simpleexpr(hassh);

			//cout << str[p]<<endl;
			//проверка
			//if (str[p] == ')') {
				//if (str[p + 2] != '+' && str[p + 2] != '-') cout << "Not +/-" << endl;
			//}

			p += 2;
			Start = Operators;
			break;

		case End:
			p += 7;
			id(hassh);
			Start = FIN;
			break;
		}
	}
}

/*
int abc() {
int a, b;
int c;
int d, q;
int e;
goto TTT;
a = ( a + b ) + 3 - 123 - ( 67 + 45 ) + asd - 9 ;
goto M;
Mark : a = ( a + b ) + 3 - 123 - ( 67 + 45 ) + asd - 9 ;
return 0; }
*/