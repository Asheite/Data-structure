#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class cT {
	private:
		string rawR; // one row data
		string cname; // college name
		string dname; // department name
		int sOn; // number of students
		int gOn; // number of graduates
		
	public:
		string getrawR() {
			return rawR;
		} // getrawR()
		
		string getcname() {
			return cname;
		}
		
		string getdname() {
			return dname;
		}
		
		int getsOn() {
			return sOn;
		} // getsOn()
		
		int getgOn() {
			return gOn;
		} // getgOn()
		
		void setrawR( string set ) {
			rawR = set;
		} // setrawR()
		
		void setcname( string set ) {
			cname = set;
		} // setcname()
		
		void setdname ( string set ) {
			dname = set;
		} // setdname()
		
		void setsOn( string set ) {
			sOn = atoi( set.c_str() );
		} // setsOn()
		
		void setgOn( string set ) {
			gOn = atoi( set.c_str() );
		} // setgOn()
		
		string getNo( string input ) {
			string num = "";
			
			for ( char& c : input ) {
				if ( c >= '0' && c <= '9' ) {
					num += c;
				} // if
			} // for
			
			return num;
		} // getNo
		
		bool readFile( vector<cT>& v, string fileName ) {
			ifstream file;
			file.open( fileName );
			
			if ( !file.is_open() )
				return false;
			
			string line;
			
			
			while ( getline( file, line ) ) {
				vector<string> row;
				string voc = "";
				cT tmp;
				tmp.setrawR( line );
				for ( char& c : line ) {
					if ( c != '\t' ) {
						voc += c;
					} // if
					else {
						row.push_back( voc );
						voc = "";
					} // else
				} // for
				tmp.setdname( row[3] );
				tmp.setcname( row[1] );
				tmp.setsOn( row[6] );
				tmp.setgOn( row[8] );
				
				v.push_back( tmp );
			} // while
			
			file.close();
			return true;
		} // readFile()
		
		bool saveFile( vector<cT>& v, string fileName ) {
			ofstream file;
			file.open( fileName );
			int count = 0;
			
			for ( auto i : v ) {
				if ( count > 2 )
					file << i.getrawR() << endl;
				count++;
			} // for
			
			file.close();
		} // saveFile()
		
		void outputFile( string fileName ) {
			ifstream file;
			file.open( fileName );
			string line;
			
			while ( getline( file, line ) ) {
				cout << line << endl;
			} // while
			
			file.close();
		} // outputFile()
		
		void removeRecords( vector<cT>& v, string fileName, 
							int sFilter, int gFilter ) {
			ifstream file;
			file.open( fileName );
			for ( int i = 0; i < v.size(); i++ ) {
				if ( v[i].getsOn() < sFilter && v[i].getgOn() < gFilter ) {
					v.erase( v.begin() + i );
				} // if
			} // for
			
			file.close();
		} // remove
		
		void mergeData( vector<cT>& v, vector<cT>& v2, vector<cT>& newVec ) {
			for ( int i = 0; i < v.size(); i++ ) {
				for ( int j = 0; j < v2.size(); j++ ) {
					newVec.push_back( v[i] );
					if ( v[i].getcname() == v2[j].getcname() ) {
						newVec.insert( i, v2[j] );
					} // if
				} // for
				
			} // for
		} // mergeData()
		
		int countData( string fileName ) {
			ifstream file;
			file.open( fileName );
			string line;
			int count = 0;
			
			while ( getline( file, line ) ) {
				count++;	
			} // while
			
			return count;
		} // countData()
};

string getNo( string input ) {
	string num = "";
			
	for ( char& c : input ) {
		if ( c >= '0' && c <= '9' ) {
			num += c;
		} // if
	} // for
			
			return num;
} // getNo

int main() {
	int command = 0;
	
	do {
		
		cT f;
		cout << "***  File Object Manipulator  ***" << endl;
		cout << "* 0. QUIT                       *" << endl;
		cout << "* 1. COPY (Read & Save a file)  *" << endl;
		cout << "* 2. FILTER (Reduce a file)     *" << endl;
		cout << "* 3. MERGE (Join two files)     *" << endl;
		cout << "*********************************" << endl;
		cout << "Input a choice(0, 1, 2, 3): ";
		cin >> command;
		cout << endl;
		
		if ( command == 0 )
			break;
		else if ( command == 1 ) {
			vector<cT> v;
			string input;
			cout << "Input 201, 202, ...[0]Quit): ";
			cin >> input;
			string number = getNo( input );
			
			if ( number == "0" )
				continue;
			
			string inputName = "input" + number + ".txt";
			string copyName = "copy" + number + ".txt";
			
			if ( f.readFile( v, inputName ) ) {
				
				f.saveFile( v, copyName );
			} // if
			
			f.outputFile( copyName );
		} // else if 
		else if ( command == 2 ) {
			vector<cT> v;
			string input;
			cout << "Input 201, 202, ...[0]Quit): ";
			cin >> input;
			string number = getNo( input );
			
			if ( number == "0" )
				continue;
			
			string inputName = "input" + number + ".txt";
			string copyName = "copy" + number + ".txt";
			
			if ( f.readFile( v, copyName ) ) {
				int gFilter;
				int sFilter;
				cout << "Input a lower bound on the number of students: ";
				cin >> sFilter;
				cout << endl;
				cout << "Input a lower bound on the number of graduates:";
				cin >> gFilter;
				f.removeRecords( v, copyName, sFilter, gFilter );
				f.saveFile( v, copyName );
			} // if
			
			f.outputFile( copyName );			
		} // else if
		
		else if ( command == 3 ) {
			vector<cT> v;
			vector<cT> v2;
			string firstFile;
			string secondFile;
			
			cout << "Input 1st file [0] to quit: ";
			cin >> firstFile;
			string number1 = getNo( firstFile );
			
			if ( number1 == "0" )
				continue;
				
			cout << "Input 2nd file [0] to quit: ";
			cin >> secondFile;
			string number2 = getNo( secondFile );
			
			if ( number2 == "0" )
				continue;
			
			string copyName1 = "copy" + number1 + ".txt";
			string copyName2 = "copy" + number2 + ".txt";
			string newName = "output" + number1 + "_" + number2 + ".txt";
			vector<cT> newVec; 
			
			if ( f.readFile( v, copyName1 ) && f.readFile( v2, copyName2 ) ) {
				f.mergeData( v, v2, newVec );
				f.saveFile( newVec, newName );
			} // if
			
			f.outputFile( newName );
			cout << "Total count numbers : " << f.countData( newName ) << endl;			
		} // else if
		
	} while( command != 0 );
	
	
} // main()
