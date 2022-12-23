// DS1ex5 27 11027257 洪暄妮 10927260 劉宗諺 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <typeinfo>
using namespace std;

vector<string> timeList;

class ClassList {
	typedef struct cT
	{
		string raw; // raw data
		int gNo; // number of graduates
	} collegeType;
	
	vector<collegeType> cSet; // data in a file
	vector<collegeType> store;
	string fileNo; // file Number ex: 501 502...
	string sortName; // name of sorting algorithm
	int bTime; // bubble sort time
	int sTime; // select sort time
	int mTime; // merge sort time
	int qTime; // quick sort time
	int rTime; // radix sort time
		
	void swap( collegeType& x, collegeType& y ) {
		// change two elements in  cSet
		collegeType tmp;
		tmp.raw = x.raw;
		tmp.gNo = x.gNo;
		
		x.raw = y.raw;
		x.gNo = y.gNo;
		
		y.raw = tmp.raw;
		y.gNo = tmp.gNo;
	} // swap()
	
	void merge( int first, int mid, int last ) {
		collegeType tmpArr[ cSet.size() ];
		int first1 = first, last1 = mid;
		int first2 = mid + 1, last2 = last;
		int index = first;
		
		for ( ; ( first1 <= last1 ) && ( first2 <= last2 ); ++index ) {
			if ( cSet[first1].gNo > cSet[first2].gNo ) {
				tmpArr[index] = cSet[first1];
				++first1;
			} // if
			else {
				tmpArr[index] = cSet[first2];
				++first2;
			} // else
		} // for
		
		for ( ; first1 <= last1; ++first1, ++index ) {
			tmpArr[index] = cSet[first1];	
		} // for
		
		for ( ; first2 <= last2; ++first2, ++index ) {
			tmpArr[index] = cSet[first2];
		} // for
		
		for ( index = first; index <= last; ++index ) {
			cSet[index] = tmpArr[index];
		} // for
	} // merge()
	
	int partition( int first, int last ) {
		int pivot = cSet[last].gNo;
		int pre = first - 1;
		
		for ( int i = first; i <= last - 1; i++ ) {
			if ( cSet[i].gNo > pivot ) {
				pre++;
				swap( cSet[pre], cSet[i] );
			} // if
		} // for

		collegeType tmp = cSet[pre+1];
		cSet[pre+1] = cSet[last];
		cSet[last] = tmp;
		return ( pre + 1 );
	} // partition()
	
	int getgNo( string row ) {
		// get graduate number
		int counter = 1;
		string word = "";
		vector<string> rowData;
		
		for ( char&c : row ) {
					
			if ( c != '\t' ) {
				word += c;
			} // if
			else {
				rowData.push_back( word );
				word = "";
			} // else
		} // for
		
		return atoi( rowData[8].c_str() );
		
	} // getgNo()
	
	int indexOfLargest( int size ) {
		int indexSoFar = 0;
		
		for ( int i = 0; i < size; ++i ) {
			if ( cSet[indexSoFar].gNo > cSet[i].gNo ) {
				indexSoFar= i;
			} // if
		} // for
		
		return indexSoFar;
	} // indexOfLargest()
	
	int getMax() {
		int max = cSet[0].gNo;
		for ( int i = 1; i < cSet.size(); i++ ) {
			if ( cSet[i].gNo > max )
				max = cSet[i].gNo;
		} // for
		return max;
	} // getMax()
	
	public:

	
		ClassList():fileNo(""), sortName(""), bTime(0),
		sTime(0), rTime(0), mTime(0), qTime(0) {}
		
		ClassList( string id ):fileNo( id ), sortName(""), bTime(0),
		sTime(0), rTime(0), mTime(0), qTime(0) {}
		
		bool readF( string id ) {
			// read file
			ifstream file;
			file.open( "input" + id + ".txt" );
			
			if ( !file.is_open() ) {
				// if can't open file output error messege
				cout << "### input" + id + ".txt does not exist! ###" << endl;
				return false;
			} // if
			else {
				// open file succesfully
				string line;
				int counter = 1;
				
				while ( getline( file, line ) ) {
					
					if ( counter > 3 ) {
						collegeType ct;
						ct.raw = line;
						ct.gNo = getgNo( line );
						cSet.push_back( ct );
					} // if
					
					counter++;
				} // while
			} // else
			
			for ( auto i : cSet )
				store.push_back( i );  
			file.close();
			return true;
		} // raedF()
		
		void show() {
			for ( auto i : cSet ) {
				cout << i.raw << endl;
			} // for
			cout << endl;
		} // show
		
		void saveF( string id ) {
			ofstream file;

			
			file.open( sortName + id + ".txt" );
			
			if ( file.is_open() ) {
				for ( auto i : cSet ) {
					file << i.raw << endl;
				} // for
				file.close();
			} // if
			else
				return;
				
		} // saveF()
		
		void saveTimeF( string id ) {
			ofstream file;
			ifstream check;
			check.open( "sort_time.txt" );
			
			if ( check.is_open() ) {
				file.open( "sort_time.txt", ios::app );
			
				if ( file.is_open() ) {
					for ( int i = 0; i < timeList.size(); i++ ) {
						file << timeList[i] << endl;
					} // for
				} // if
			} // if
			else {
				file << "檔案編號\t選擇排序\t泡沫排序\t合併排序\t快速排序\t基數排序" << endl;
				for ( auto i : timeList )
					file << i << endl;
			} // else
			file.close();
		} // ofstream
		
		void ssort() {
			// select sort
			clock_t Begin, End;
			Begin = clock();
			for ( int last = cSet.size() - 1; last > 0; --last ) {
				int largest = indexOfLargest( last + 1 );
				swap( cSet[largest], cSet[last] );
			} // for
			
			End = clock();
			sortName = "select_sort";
			sTime = End - Begin;
		} // ssort()
		
		void bsort() {
			// bubble sort
			clock_t Begin, End;
			Begin = clock();
			for ( int pass = 1; pass < cSet.size(); ++pass ) {
				for ( int i = 0; i < cSet.size() - pass; i++ ) {
					// i is the index of cSet
					if ( cSet[i].gNo < cSet[i+1].gNo ) {
						swap( cSet[i], cSet[i+1] );
					} // if
				} // for
			} // for
			
			End = clock();
			sortName = "bubble_sort";
			bTime = End - Begin;
		} // bsort()
		
		void msort( int first, int last ) {
			// merge sort
			clock_t Begin, End;
			Begin = clock();
			if ( first < last ) {			
				int mid = ( first + last ) / 2;
				msort( first, mid );
				msort( mid + 1, last );
				merge( first, mid, last );	
			} // if
			End = clock();
			mTime = End - Begin;
			sortName = "merge_sort";
		} // msort()
		
		void qsort( int first, int last ) {
			// qick sort
			clock_t Begin, End;
			Begin = clock();
			int pivot;
			
			if ( first < last ) {
				pivot = partition( first, last );
				qsort( first, pivot - 1 );
				qsort( pivot + 1, last );
			} // if
			
			End = clock();
			qTime = End - Begin;
			sortName = "quick_sort";
		} // qsort()
		
		void rsort( int first, int last ) {
			// radix sort
			clock_t Begin, End;
			int m = getMax();
			Begin = clock();
			for ( int exp = 1; m / exp > 0; exp *= 10 ) {
				collegeType output[cSet.size()];
				int i, count[10] = {0};
				
				for ( i = 0; i < cSet.size(); i++ )
					count[ ( cSet[i].gNo / exp ) % 10 ]++;
				
				for ( i = 1; i < 10; i++ ) {
					count[i] += count[i - 1];
				} // for
				
				for ( i = cSet.size() - 1; i >= 0; i-- ) {
					output[ count[ ( cSet[i].gNo / exp ) % 10 ] - 1 ] = cSet[i];
					count[ ( cSet[i].gNo / exp ) % 10 ]--; 
				} // for
				
				for ( i = 0; i < cSet.size(); i++ )
					cSet[i] = output[i];
			} // for
			reverse( cSet.begin(), cSet.end() );
			End = clock();
			rTime = End - Begin;
			sortName = "radix_sort";
		} // rsort()
		
		void setTimeList( string id ) {
			timeList.push_back( id + '\t' + to_string( sTime ) + '\t' + to_string( bTime ) + '\t' + 
			to_string( mTime ) + '\t' + to_string( qTime ) + '\t' + to_string( rTime ) );
		} // setTimeList()
		
		void clearUp() {
			cSet.clear();
			sortName = "";
			bTime = 0; 
			sTime = 0; 
			mTime = 0; 
			qTime = 0; 
			rTime = 0; 
		} // clearUp()
		
		int getFirst() {
			return cSet[0].gNo;
		} // getFirst()
		
		int getLast() {
			return cSet[cSet.size() - 1].gNo;
		} // getLast()
		
		void show1Time() {
 			cout << "Selection sort: " << sTime << " ms" << endl;
 			cout << endl;
 			cout << "Bubble sort: " << bTime << " ms" << endl;			
		} // show1Time()
		
		void show2Time() {
 			cout << "Merge sort: " << mTime << " ms" << endl;
 			cout << endl;
 			cout << "quick sort: " << qTime << " ms" << endl;
		} // show2Time()
		
		void show3Time() {
 			cout << "radix sort: " << rTime << " ms" << endl;
		} // show2Time()
		
		void showTime() {
 			cout << "Selection sort: " << sTime << " ms" << endl;
 			cout << endl;
 			cout << "Bubble sort: " << bTime << " ms" << endl;
 			cout << endl;
 			cout << "Merge sort: " << mTime << " ms" << endl;
 			cout << endl;
 			cout << "quick sort: " << qTime << " ms" << endl;
 			cout << endl;
			cout << "radix sort: " << rTime << " ms" << endl;		
		} // showTime()
		
		int getSize() {
			return cSet.size();
		} // getSize()
		
		void reset() {
			// reset cSet
			cSet.clear();
			for ( auto i : store )
				cSet.push_back( i );

		} // reset()
		
		
		~ClassList() {
			clearUp();
		} // desturctor
		
		
}; // end class

int main( void ) {
	int command = 0; // user command
	ClassList cl;
	//cl.setM4();
	
 	do { 
 		cout << endl << "******** Sorting Algorithms *********";
 		cout << endl << "* 0. QUIT                           *";
 		cout << endl << "* 1. Selection sort vs. Bubble sort *";
 		cout << endl << "* 2. Merge sort vs. Quick sort      *";
 		cout << endl << "* 3. Radix sort                     *";
 		cout << endl << "* 4. Comparisons on five methods    *"; 
 		cout << endl << "*******************************";
 		cout << endl << "Input a command(0, 1, 2, 3, 4): ";
 		cin >> command; // get the command
 		if ( command == 0 )
 			break;
 		cout << endl;
 		
 		string id;
 		cout << "Input 501, 502, ...[0]Quit): ";
 		cin >> id;
 		cl = ClassList( id );
 		cout << endl;
 		
 		switch (command) { 
 			case 0: break;
 			
 			case 1:
 				if ( cl.readF( id ) ) {
 					cl.bsort();
 					cl.saveF( id );
 					cl.reset();
 					cl.ssort();
 					cl.saveF( id );
 					cl.show1Time();
 					cl.clearUp();
 				} // if 
 				break;
 			
 			case 2:
 				if ( cl.readF( id ) ) {
 					int first = 0;
 					int last = cl.getSize() - 1;
 					cl.msort( first, last );
 					cl.saveF( id );
 					cl.reset();
 					cl.qsort( first, last );
 					cl.saveF( id );
 					cl.show2Time(); 
 					cl.clearUp();

				 } // if
				break;
				
			case 3:
				if ( cl.readF( id ) ) {
					int first = 0;
					int last = cl.getSize() - 1;
					cl.rsort( first, last );
					cl.saveF( id );
					cl.show3Time();
					cl.clearUp();
					
				} // if
				break;
				
			case 4:
				if ( cl.readF( id ) ) {
					cl.ssort();
					cl.reset();
					cl.bsort();
					cl.reset();
					int first = 0, last = cl.getSize() - 1;
					cl.msort( first, last );
					cl.reset();
					cl.qsort( first, last );
					cl.reset();
					cl.rsort( first, last );
					cl.setTimeList( id );
					cl.showTime();
					cl.saveTimeF( id );
					cl.clearUp();
				} // if
				break;

 			default: 
				cout << endl << "Command does not exist!" << endl;
 		} // end switch
 		
 		for ( auto i : timeList ) cout << i << endl;
 	} while (command != 0); // '0': stop the program
 	
 	return 0;	
} // main()
