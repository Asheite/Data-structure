#include <iostream>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cstring>
// -std=c++11
using namespace std;

int count0 = 0;
int temp = 0;
int temp2 = 0;
bool beUsed[10];
vector<bool> beUsed2;
char output[10];
char arr[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' } ;
vector<string> arr2;
string output2[50];

void handleIO();
void commandOne();
void commandTwo();
void commmandThree();
void generatePer();
void info();
void lenPermutations();
void print();
void permutation();
void permutationM();


int main( void ) {	
	handleIO();
	system( "pause" ) ;
	return 0;
} // main()

void print( vector<int> v, int record ) {
	
	cout << "[" << record << "] ";
	
	for ( int i = 0 ; i < v.size() ; i++ ) {
		cout << v[i];
		if ( i != v.size() - 1 )
		  cout << ", ";
	} // for
	
	cout << endl;
	
} // print()

void permutation( vector<int> v, int record, int in ) {
	// Mission 1
	print( v, record );
	
	if ( next_permutation( v.begin(), v.end() ) ) {
		permutation( v, ++record, in ) ;
	} // if
	else {
		cout << "Mission 1: " << record << " permutations " << endl;
		cout << "L = " << in << endl;
	} // else
	
} // permutation()

void generatePer( vector<int> v, int record ) {
	// Mission 2
	print( v, record );
	
	if ( next_permutation( v.begin(), v.end() ) ) {
		generatePer( v, ++record ) ;
	} // if	
	else {
		cout << "Mission 2: " << record << " permutations " << endl;
	} // else
	
} // generatePer()

void lenPermutations( int length, int length2 ) {
	
  if ( length == 0 ) {
    count0++ ;
    cout << "[" << count0 << "] ";
    cout << output;
		cout << endl;
	} // if
    else
        for ( int i = 1 ; i < 10 ; i++ ) {
            if ( !beUsed[ i ] ) {
                output[ temp - length ] = arr[i];
                beUsed[i] = true ;
                lenPermutations( length - 1, length ) ;               
                beUsed[i] = false ;
            } // if
        } // for
	
} // lenPermutations()

void permutationM( int length, int n, int position, int oLen ) {
  // Mission 4
  if ( length == 0 ) {
    count0++ ;
    cout << "[" << count0 << "] ";
    // cout << output2[position] << " ";
    for ( int i = oLen - 1; i >= 0; i-- ) {
    	cout << output2[position-i] << " ";
		} // for
	cout << endl;
  } // if
    else
        for ( int i = 0 ; i < n ; i++ ) {
            if ( !beUsed2[i] ) {
            	// cout << arr2[i] << endl;
                output2[temp2 - length] = arr2[i];
                beUsed2[i] = true ;
                permutationM( length - 1, n, temp2 - length, oLen ) ;               
                beUsed2[i] = false ;
            } // if
        } // for	
	
} // permutationM()

void commandOne() {
	// Misson1
	vector<int> v;
	int record = 1;
	int num;
	cout << "Input a number: ";
	cin >> num;
	cout << endl;
	  	
	while ( num > 9 || num < 1 ) {
	  cout << "### It is NOT in [1,9] ###" << endl;
	  cout << endl;
	  cout << "Input a number: ";
	  cin >> num;
	  cout << endl;
	} // if
	  	
	for ( int i = 1 ; i <= num ; i++ ) {
	 	v.push_back( i );
	} // for

	permutation( v, record, num );
} // commandOne()

void commandTwo() {
	// Mission2
	clock_t Begin, End;
	vector<int> v;
	int record = 1;
	int number = 0; // how many numbers will be input
	cout << "Input a number: ";
	cin >> number;
	cout << endl;
			
	while ( number > 9 || number < 2 ) {
	 	cout << "### It is NOT in [2,9] ###" << endl;
	 	cout << endl;
	 	cout << "Input a number: ";
	 	cin >> number;
		cout << endl;
	} // if
			
	for ( int i = 0 ; i < number ; i++ ) {
		int a = 0;
		cout << "Input a number: ";
		cin >> a;
		if( i != number - 1 )
			cout << endl;
		
		v.push_back( a ) ;	
	} // for
	
	Begin = clock();
	generatePer( v, record ) ;
	End = clock();
	cout << "Time = " << ( End - Begin ) << " ms" << endl;	
} // commandTwo()

void commandThree() {
	clock_t Begin, End;
	int length = 0;
	int record = 0;
	cout << "Input a number: ";
	cin >> length;

	while ( length > 9 || length < 1 ) {
		cout << endl;
		cout << "### It is NOT in [1,9] ###" << endl;
		cout << endl;
		cout << "Input a number: ";
		cin >> length;
	} // while
	
	temp = length;
	Begin = clock();
	lenPermutations( length, length );
	End = clock();
	cout << "Mission 3: " << count0 << " permutations" << endl; 
	cout << "Time = " << ( End - Begin ) << " ms" << endl;
	
	for ( int i = 0; i < 10; i++ ) {
		output[i] = '\0';
	}	// for
	
	count0 = 0;
} // commandThree()

void commandFour() {
	
	clock_t Begin, End;
	int length = 0;
	int num = 0;
	cout << "Input a number N: ";
	cin >> num; // 決定數字有多少個
	int i; 
	
	for ( i = 1; i <= num; i++  ) {
		arr2.push_back( to_string( i ) );
		beUsed2.push_back( false );
	} // for

	cout << "Input a number M: ";
    cin >> length;
    
	while ( length > num || length < 1 ) {
		cout << endl;
		cout << "### It is NOT in [1,N] ###" << endl;
		cout << endl;
		cout << "Input a number M: ";
		cin >> length;
	} // while	
	
	temp2 = length;
	Begin = clock();
	permutationM( length, num, 0, length );
	End = clock();
	cout << "Mission 4: " << count0 << " permutations" << endl; 
	cout << "Time = " << ( End - Begin ) << " ms" << endl;	

	for ( int i = 0; i < 10; i++ ) {
		output2[i] = '\0';
	}	// for
	
	count0 = 0;

} // commandFour()



void info( int & command ) {
	cout << endl << "** Permutation Generator **";
	cout << endl << "* 0. Quit                 *";
	cout << endl << "* 1. N numbers from 1..N  *";
	cout << endl << "* 2. M numbers from input *";
	cout << endl << "* 3. M numbers from 1..9  *";
	cout << endl << "* 4. M numbers form 1..N  *";
	cout << endl << "***************************";
	cout << endl << "input a choice(0, 1, 2, 3, 4): ";
	cin >> command;
	cout << endl;	
} // info()

void handleIO() {
	int command = 1;
	
	while ( command != 0 ) {
		info( command );
		
	  if ( command == 0 ) 
	    return;
	    
	  else if ( command == 1 ) {
			commandOne();
		} // else if
		
		else if ( command == 2 ) {
			commandTwo();
		} // else if
		
		else if ( command == 3 ) {
			commandThree();
		} // else if
		
		else if ( command == 4 ) {
			commandFour();
		} // else if
		
		else {
			cout << "Command does not exist!" << endl;
		} // else
		
	} // while 
	
} // handleIO()
