#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>
#include <string.h>
using namespace std;
int pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
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
		
		void setsOn( int set ) {
			sOn = set;
		} // setsOn()
		
		void setgOn( int set ) {
			gOn = set;
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
				
				for ( int i = 0; i < row.size(); i++ ) {
					if ( row[i] == "學校代碼" )
						pos1 = i;
					else if ( row[i] == "科系代碼" )
						pos2 = i;
					else if ( row[i] == "學生數" )
						pos3 = i;
					else if ( row[i] == "上學年度畢業生數" )
						pos4 = i;
				} // for
				
				
				tmp.setdname( row[pos2] );
				tmp.setcname( row[pos1] );
				tmp.setsOn( atoi( row[pos3].c_str() ) );
				tmp.setgOn( atoi( row[pos4].c_str() ) );
				v.push_back( tmp );
			} // while
			
			file.close();
			return true;
		} // readFile()
		
		bool saveFile( vector<cT>& v, string fileName ) {
			ofstream file;
			file.open( fileName, ios::trunc );
			int count = 0;
			
			for ( auto i : v ) {
					file << i.getrawR() << endl;		
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
		
		void remove( vector<cT> & v, int pos ) {
			
			v.erase( v.begin() + pos );
			
		} // remove()
		
		void removeRecords( vector<cT>& v, string fileName, 
							int sFilter, int gFilter, vector<cT>& newVec ) {
			
			for ( int i = 0; i < v.size(); i++ ) {
				if ( ( v[i].getsOn() >= sFilter ) && ( v[i].getgOn() >= gFilter ) ) {
					newVec.push_back( v[i] );
				} // if
			} // for
		} // remove
		
		void sort( vector<cT> & v ) {
			
			for ( int i = 0; i < v.size(); i++ ) {
				for ( int j = 0; j < v.size() - i - 1; j++ ) {
					if ( v[j].getcname() > v[j+1].getcname() ) {
						cT tmp = v[j];
						v[j] = v[j+1];
						v[j+1] = tmp;
 					} // if
 					else if ( v[j].getcname() == v[j+1].getcname() ) {
 						if ( v[j].getdname() > v[j+1].getdname() ) {
							cT tmp = v[j];
							v[j] = v[j+1];
							v[j+1] = tmp; 								
						} // if
					} // else if
				} // for
			} // for
			
		} // sort()
		
		void mergeData( vector<cT>& v, vector<cT>& v2, vector<cT>& newVec ) {
			int count = 0;
			
			
			for ( auto i : v )
				newVec.push_back( i );
				
			for ( auto j : v2 )
				newVec.push_back( j );
			
			sort( newVec );
			
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
		cout << "* 4. MERGE (Join M files)   *" << endl;
		cout << "*********************************" << endl;
		cout << "Input a choice(0, 1, 2, 3, 4): ";
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
				for ( int i = 0; i < 3; i++ )
					v.erase( v.begin() );
				f.saveFile( v, copyName );
				f.outputFile( copyName );
				cout << "Total count: " << f.countData( copyName ) << endl;
			} // if
			else {
				cout << inputName + " is not exist" << endl;
			} // else
			

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
				vector<cT> newVec;
				int gFilter;
				int sFilter;
				cout << "Input a lower bound on the number of students: ";
				cin >> sFilter;
				cout << endl;
				cout << "Input a lower bound on the number of graduates:";
				cin >> gFilter;
				f.removeRecords( v, copyName, sFilter, gFilter, newVec );
				f.saveFile( newVec, copyName );
				f.outputFile( copyName );
				cout << "Total count: " << f.countData( copyName ) << endl;	
			} // if
			else {
				cout << copyName + " is not exist" << endl;
			} // else			

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
			string copyName1 = "copy" + number1 + ".txt";
			
			while ( !f.readFile( v, copyName1 ) ) {
				cout << copyName1 + " is not exist" << endl;
				cout << "Input 1st file [0] to quit: ";
				cin >> firstFile;
				number1 = getNo( firstFile );
				if ( number1 == "0" )
					continue;
				copyName1 = "copy" + number1 + ".txt";
			} // while()
			
			cout << "Input 2nd file [0] to quit: ";
			cin >> secondFile;
			
			string number2 = getNo( secondFile );
			
			if ( number2 == "0" )
				continue;
				
			string copyName2 = "copy" + number2 + ".txt";
			
			while ( !f.readFile( v2, copyName2 ) ) {
				cout << copyName2 + " is not exist" << endl;
				cout << "Input 2nd file [0] to quit: ";
				cin >> secondFile;
				number2 = getNo( secondFile );
				if ( number2 == "0" )
					continue;
				copyName2 = "copy" + number2 + ".txt";
			} // while()
			
			
			
			string newName = "output" + number1 + "_" + number2 + ".txt";
			vector<cT> newVec; 
			
			f.mergeData( v, v2, newVec );
			f.saveFile( newVec, newName );
			f.outputFile( newName );
			cout << "Total count numbers : " << f.countData( newName ) << endl;	
		
		} // else if
		
		else if ( command == 4 ) {
			vector<cT> all;
			vector<cT> v;
			string outputName = "output";
			string fileName;
			cout << "input file name: ";
			cin >> fileName;
			string number = getNo( fileName );
			
			if ( number == "0" )
				continue;
				
			string name = "copy" + number + ".txt";
			
			while ( !f.readFile( v, name ) ) {
				cout << name + " is not exist" << endl;
				cout << "Input file name [0] to quit: ";
				cin >> fileName;
				number = getNo( fileName );
				
				if ( number == "0" ) {
					v.clear();
					break;
				} // if
				name = "copy" + number + ".txt";
			} // while()	
			
			outputName += number + "_";
			
			
			int mergeTime;
			cout << "input the number of files to be merged: ";
			cin >> mergeTime;
			
			if ( mergeTime <= 0 || mergeTime > 4 ) { // 防呆 
				cout << "### It is NOT in [1,4] ###" << endl;
				v.clear();
				continue;
			} // if
			
			for ( int i = 0; i < mergeTime; i++ ) {
				vector<cT> tmp;
				cout << "Input file name [0] to quit: ";
				cin >> fileName;
				string num = getNo( fileName );
				
				if ( num == "0" ) {
					v.clear();
					break;
				} // if
					
				string inName = "copy" + num + ".txt";
				
				while ( !f.readFile( v, inName ) ) {
					cout << name + " is not exist" << endl;
					cout << "Input fileName ";
					cin >> fileName;
					
					num = getNo( fileName );
					if ( num == "0" ) {
						v.clear();
						break;
					} // if
						
					inName = "copy" + num + ".txt";
				} // while()			
						
				outputName += num;
				if ( i < mergeTime - 1 )
					outputName += "_";

			} // for
			
			outputName += ".txt";
			f.sort( all );
			f.saveFile( v, outputName );
			f.outputFile( outputName );
			cout << "Total count: " << f.countData( outputName ) << endl;
		} // else if
		
	} while( command != 0 );
	
	
} // main()
