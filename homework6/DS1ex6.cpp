#include <fstream>
#include <iomanip>
#include "BST.h"
using namespace std;

class List {
	typedef struct pokemonType {
		string raw; // raw data
		int no; // number
		string name; // name
		string tp1; // 1st type
		string tp2; // store the 2nd type
		int tot; // total sum
		int hp; // health point
		int atk; // attack
		int def; // defense
	} pType;
	
	vector<pType> pSet; // all data in input file
	string fileNo;
	BSTree bst; // binary search tree
	
	void show();
	void setMember( pType& pt, string line ); // set all member in pType
	int loc() const; // locate the entry
	
	public:
		List():fileNo("") { 
			bst = BSTree();
		} // constructor
		
		List( string id ):fileNo(id) {
		bst = BSTree();
		} // constructor
		
		int getHeight() const;
		bool isEmpty();
		bool readF(); // read file
		void showAll(); // show pSet
		void buildBST(); // build a binary search tree
		void tSearch( int low ); // threshold search
		void maxDel(); // delete max of a column
		void clearUp();
		void setFileNo( string id );
}; // end List

int main() {
	int command = 0; // user command
 	do { 
 		cout << endl << "*** Binary Search Tree on Pokemon ***";
 		cout << endl << "* 0. QUIT                           *";
 		cout << endl << "* 1. Read one file to build BST     *";
 		cout << endl << "* 2. Threshold search on one column *";
 		cout << endl << "* 3. Delete the max on one column   *";
 		cout << endl << "*******************************";
 		cout << endl << "Input a command(0, 1, 2, 3): ";
 		cin >> command; // get the command
 		if ( command == 0 )
 			break;
 		cout << endl;
 		
 		string id;
 		List lst = List();
			
 		switch (command) { 
 			case 0: break;
 			
 			case 1:
		  		cout << "Input a file number [0: quit]: ";
		 		cin >> id;
		 		lst.setFileNo( id );		
		 		cout << endl;
		 		
 				if ( lst.readF() ) {
 					lst.buildBST();
 					lst.showAll();
				} //if
 				break;
 			
 			case 2:
				int lowest;
 				cout << "Threshold (a positive integer): ";
 				cin >> lowest;
 				lst.tSearch( lowest );	
				break;
				
			case 3:
				break;

 			default: 
				cout << endl << "Command does not exist!" << endl;
 		} // end switch
 		
 	} while (command != 0); // '0': stop the program
 	
 	return 0;		
} // main()

void List::setFileNo( string id ) {
	fileNo = id;
} // setFileNo()

void List::buildBST() {
	for ( int i = 0; i < pSet.size(); i++ ) {
		bst.add( pSet[i].hp, i );
	} // for
} // buildBST()

void List::setMember( pType& pt, string line ) {
	vector<string> data;
	string word = "";
	char pre = '\0';
	int counter = 0;
	
	for ( char& c : line ) {
		
		if ( c != '\t' && c != ' ' ) {
			word += c;
		} // if
		else {
			data.push_back( word );
			word = "";
		} // else	
		pre = c;
	} // for

	pt.raw = line;
	pt.no = atoi( data[0].c_str() );
	pt.name = data[1];
	pt.tp1 = data[2];
	pt.tp2 = data[3];
	pt.tot = atoi( data[4].c_str() );
	pt.hp = atoi( data[5].c_str() );
	pt.atk = atoi( data[6].c_str() );
	pt.def = atoi( data[7].c_str() );
} // setMember()

bool List::readF() {
	ifstream file;
	file.open( "input" + fileNo + ".txt" );
			
	if ( !file.is_open() ) {
		// if can't open file output error messege
		cout << "### input" + fileNo + ".txt does not exist! ###" << endl;
		return false;
	} // if
	else {
		// open file succesfully
		string line;
		int counter = 1;
		
		while ( getline( file, line ) ) {
			if ( counter > 1 ) {
				pType pt;
				setMember( pt, line );
				pSet.push_back( pt );
			} // if
			counter++;
		} // while
	} // else
			
	file.close();
	return true;	
} // readF()

bool List::isEmpty() {
	if ( pSet.empty() )
		return true;
	else
		return false;
} // isEmpty()

void List::showAll() {
	int height = getHeight();
	cout << "\t#\tName\t\t\tType 1\t\tHP\tAttack\tDefense" << endl;
	
	for ( int i = 0; i < pSet.size(); i++ ) {
		cout << "[  " << i+1 << "]\t" << pSet[i].no << '\t' << std::left << setw(9) << pSet[i].name << 
		"\t\t" << setw(8) << pSet[i].tp1 << "\t" << pSet[i].hp << '\t' << pSet[i].atk << 
		'\t' << pSet[i].def << endl;
	} // for
	
	cout << "HP tree height = " << height << endl;
} // showAll()

void List::tSearch( int low ) {
	bst.test();
	bst.searchGreater( low );
} // tSearch()

int List::getHeight() const {
	return bst.heightOfBST();
} // getHeight()

void List::maxDel() {
	// delete the max hp node;
	
} // maxDel()

void List::clearUp() {
	pSet.clear();
	fileNo = ""; 
} // clearUp()
