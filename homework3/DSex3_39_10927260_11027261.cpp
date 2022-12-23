//²Ä39²Õ 10927260 11027261
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <stack>
#define MAX_LEN 255

using namespace std;

typedef enum { lparen, rparen, plus, minus, times, divide, eos, operand } precedence;

class Node {
	private:
		string arithm;
		Node *next;
	
	public:
		Node(): arithm( "" ), next( NULL ) {};
		Node( string str ):arithm( str ),next( NULL ) {}; //constructor
		
		friend class List;
};

class List {
	private:
		Node* head;
	
	public:
		List(): head( NULL ) {};
		
		void push( string str ) {
			
			Node* node = new Node( str );
			
			if ( head == NULL ) {
				head = node;
				return;
			} // if


			Node* ptr = head;
			
			while ( ptr->next != NULL ) {
				ptr = ptr->next;
			} // while
				
			ptr->next = node;
			return;
		} // push()
		
		void print() {
			if ( head == NULL )
				return;
			
			Node* ptr = head;
			cout << "Postfix expression: ";
			while ( ptr != NULL ) {
				cout << ptr->arithm;
				if ( ptr->next != NULL )
					cout << ", ";
				ptr = ptr->next;
			} // while
			
			cout << endl;
		} // print()
	
}; 



bool isExp(); 
bool isNumumber(); // check is number
bool isOp( char c ); // check is operator
bool isOp( string str );
bool isPar( string str );
bool isPar( const char ); // check is parenthesis
bool isBalanced(); //
bool isInfix( string str, vector<string>& numList );
bool infix2postfix( vector<string>& postfix, vector<string>& infix );
int postfixEval( vector<string> postfix );
bool extraClose();
bool extraOpen();
bool strIsNum();
int prioOp();
precedence getToken( string symbol, int &n, vector<string> postfix );
void mission1( string str );

bool infix2prefix( vector<string>& prefix, vector<string>& infix );
int prefixEval( vector<string> prefix );

int main(){
	int command = -1;			

	
	vector<string> infix, postfix, prefix;

	
	do {
		cout << "* Arithmetic Expression Evaluator *" << endl;
		cout << "* 0. QUIT                         *" << endl;
		cout << "* 1. Infix2postfix Evaluation     *" << endl;
		cout << "***********************************" << endl;
		cout << "Input a choice(0, 1):";
		cin >> command;
		cout << endl;
		
			
		if ( command == 1 ) {	
			string fix = "";
			List list;
			const int max_len = 255;
			cout << "Input an infix expression:";
			
			cin.ignore();
			getline( cin, fix );
			cout << endl;		
			
			if ( isInfix( fix, infix ) ) {
				cout << "It is a legitimate infix expression." << endl;
				infix2postfix( postfix, infix );
		
				for ( int i = 0; i < postfix.size(); i++ )
					list.push( postfix[i] );
			
				list.print();
				cout << "Answer: " << postfixEval( postfix ) << endl;
				cout << endl;
				infix.clear();
				postfix.clear();
			} // if
					
		} // else if
		
		else if ( command == 2 ) {
			string fix = "";
			List list;
			const int max_len = 255;
			cout << "Input an infix expression:";
			
			cin.ignore();
			getline( cin, fix );
			cout << endl;		
			
			if ( isInfix( fix, infix ) ) {
				cout << "It is a legitimate infix expression." << endl;
				infix2prefix( prefix, infix );
		
				for ( int i = 0; i < prefix.size(); i++ )
					list.push( prefix[i] );
			
				list.print();
				cout << "Answer: " << prefixEval( prefix ) << endl;
				cout << endl;
				infix.clear();
				prefix.clear();
			} // if
		} // else if
	} while ( command != 0 );// while
} //main()

bool isNumber( char c ) {
	
	if ( c >= '0' && c <= '9' )
		return true;
	else
		return false;
		
} // isNumber()

bool isOp( string str ) {
	
	if ( str == "+" || str == "-" || str == "*" || str == "/"  )
		return true;
	else
		return false;
} // isOp()

bool isOp( char c ) {
	
	if ( c == '+' || c == '-' || c == '*' || c == '/' ) 
		return true;
	else 
		return false;
		
} // isOp()

bool isPar( string str ) {
	if ( str == "(" || str == ")" )
		return true;
		
	return false;
} // isPar()

bool isPar( const char c ) {
	
	if ( c == '(' || c == ')' )
		return true;
	else
		return false;
	
} // isPar()

bool isBalanced( string str ) {
	int count = 0;
	
	for ( char& c : str ) {
		
		if ( isPar( c ) )
			count++;
	} // for
	
	if ( count % 2 == 0 ) 	
		return true;
	else
		return false;
	
} // isBalanced()

bool strIsNum( string str ) {
	
	for ( auto i : str ) {
		if ( !isNumber( i ) )
			return false;
	} // for
	
	return true;
} // strIsNum

bool isInfix( string str, vector<string>& numList ) {
	 // to store num and operator and parenthesis
	string num = "";
	
	if ( !isBalanced( str ) ) {
		int openP = 0, closeP = 0;
		
		for ( char& c : str ) {
			if ( c == ')' )
				closeP++;
			else if ( c == '(' )
				openP++;
		} // for
		
		if ( openP > closeP ) {
			cout << "Error 2: There is " << openP - closeP << " extra open parenthesis" << endl;
			return false;
		} // if
		else if ( closeP > openP ) {
			cout << "Error 2: There is " << closeP - openP << " extra close parenthesis" << endl;
			return false;
		} // else
			
	} // if
	
	for ( int i = 0; i < str.size(); i++ ) {
		
		if ( !isNumber( str[i] ) && !isOp( str[i] ) && !isPar( str[i] ) && str[i] != ' ' ) {
			cout << "Error 1: " << str[i] << " is not a legitimate character" << endl;
			return false;
		} // if		
		else {
			if ( isNumber( str[i] ) ) {
				num += str[i];
			} // if
			else {
				if ( !num.empty() ) {
					numList.push_back( num );	
					num = "";
				} // if
				
				if ( str[i] != ' ' )
					numList.push_back( string( 1, str[i] ) );
			} // else
		} // else
	} // for
	
	if ( !num.empty() )
		numList.push_back( num );
	
	
	int opCount = 0;
	int numCount = 0;	
	
	for ( int i = 0; i < numList.size(); i++ ) {

		
		if ( isOp( numList[i] ) ) {
			if ( isOp( numList[i+1] ) ) {
				cout << "Error 3: there is extra one operator" << endl;
				return false;
			} // if
			
			opCount++;
		} // if
		
		else if ( strIsNum( numList[i] ) ) {
			numCount++;
		} // else if
	} // for
	
	if ( numCount != opCount + 1 ) {
		cout << "Error 3: there is extra one operand" << endl;
		return false;
	} // if
	
	return true;
} // isInfix()

int prioOp( string s ) {
	
	if ( s == "*" || s == "/" ) {
		return 1;
	} // retrun 
	else if ( s == "+" || s == "-" )
		return 0;
		
	return -1;
} // prioOp()



bool infix2postfix( vector<string>& postfix, vector<string>& infix ) {
	vector<string> stack;
	
	for ( int i = 0; i < infix.size(); i++ ) {
		if ( strIsNum( infix[i] ) ) {
			postfix.push_back( infix[i] );
		} // if
			
		else if ( infix[i] == "(" ) {
			stack.push_back( infix[i] );
		} // else if

		else if ( infix[i] == ")" ) {
			while ( stack.back() != "(" ) {
				postfix.push_back( stack.back() );
				stack.pop_back();
			} // while
			
			stack.pop_back();
		} // else if
		
		else {
			while ( !stack.empty() && prioOp( infix[i] ) < prioOp( stack.back() ) ) {
				postfix.push_back( stack.back() );
				
				if ( !stack.empty() )
					stack.pop_back();
				
			} // while
			stack.push_back( infix[i] );
			
		} // else
		
	} // for
	
	while ( !stack.empty() ) {
		postfix.push_back( stack.back() );
		
		if ( !stack.empty() )
			stack.pop_back();
	} // while
	
	for ( int i = 0; i < postfix.size(); i++ ) {
		if ( isPar( postfix[i] ) ) {
			postfix.erase( postfix.begin() + i );
		} // if
	} // for
	
} // infix2postfix()

bool infix2prefix( vector<string>& prefix, vector<string>& infix ) {
	reverse( infix.begin(), infix.end() );
	
	for ( int i = 0; i < infix.size(); i++ ) {
		if ( infix[i] == "(" ) {
			infix[i] = ")";
		} // if
		else if ( infix[i] == ")" ) {
			infix[i] = "(";
		} // else if
	} // for
	
	infix2postfix( prefix, infix );
	reverse( prefix.begin(), prefix.end() );
} // infix2prefix()


int operation( int a, int b, string op ){
      //Perform operation
      if( op == "+" )
         return a + b;
      else if( op == "-" )
         return b - a;
      else if( op == "*" )
         return a * b;
      else if( op == "/" )
         return b / a;
}

int postfixEval( vector<string> postfix ) {
	int op1, op2;	
	stack<int> st;

	for ( string i : postfix ) {
		if ( isOp( i )  ) {
			op1 = st.top();
			st.pop();
			op2 = st.top();
			st.pop();
			st.push( operation( op1, op2, i ) );
		} // if
		else if ( strIsNum( i ) ) {
			st.push( atoi( i.c_str() ) );
		} // else if
	} // for

	return st.top();

} // postfixEval()

int prefixEval( vector<string> prefix ) {
	stack<int> st;
	int op1, op2;
	
	for ( int i = prefix.size() - 1; i >= 0; i-- ) {

		if ( strIsNum( prefix[i] ) ) {
			st.push( atoi( prefix[i].c_str() ) );
		} // if
		
		else ( isOp( prefix[i] ) ) {
			op1 = st.top();
			st.pop();
			op2 = st.top();
			st.pop();
			st.push( operation( op1, op2, prefix[i] ) );
		} // else		
	} // for
	
	return st.top();
} // prefixEval()

