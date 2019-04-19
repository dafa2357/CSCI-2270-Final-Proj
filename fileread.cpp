#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <climits>
using namespace std;
//type handling for input and output use BOOST FILESYSTEM LIBRARY

long long * inFiProbs(string inFilename, string oFile){///REMOVE ALL instaces of output file
	ifstream inFile;//creatae ifstream;
	inFile.open( inFilename, ios::in|ios::binary);//open file as binary input
	if(!(inFile.is_open()) || !(inFile.good())) {//check if open and good
		cout<<"File Not Opened."<<endl;
		inFile.close();
		return nullptr;
  	}
	
	long long * probability = new long long [UCHAR_MAX + 1];//creates probability array
	for( int i = 0; i <= UCHAR_MAX ; i++){//set all counts to zero //using unsigned char ++ overloads for() ++ iteratore????
		probability[i] = 0;
	}

  	unsigned char ILikeTurtles = 0; //temp storage of single byte
  	std::streambuf * inF = inFile.rdbuf();//creates accesible stream buffer
	ofstream outf ( oFile, std::ofstream::binary| std::ofstream::trunc);//creates output file of same type               //USED FOR TESTING: REMOVE
	
	while( inF->sgetc() != EOF){ //checks for valid input
    		ILikeTurtles = inF->sbumpc();//gets uchar from file moves to next position in streambuf
  		//  cout<<":"<<ILikeTurtles                                                                                  //USED FOR TESTING: REMOVE
    		probability[ILikeTurtles]++;
    		outf<<ILikeTurtles;//outputs uchar to file                                                                   //USED FOR TESTING: REMOVE
  	}

	//cout<<"3"<<endl;                                                                                                    //USED FOR TESTING: REMOVE
	outf.close();                                                                                                         //USED FOR TESTING: REMOVE
	inFile.close();
	return probability;

}


int main()
{
	long long * pr = inFiProbs("lec12.pptx", "testy.pptx");
	unsigned char q =0;
	for( q = 0; q < UCHAR_MAX; q++ )//prints counts of each uchar from inFile                 //USED FOR TESTING: REMOVE
		cout<< q << pr[q] <<endl;

/*///////////////////////////////////////
  MAKE WORK WITH DIRCTORIES
  PUSH FUNCTION FOR OUT FILE
  read file again while encoding with tree getchar pushchar
//////////////////////////////////////*/


	return 0;
}

/*///////////////////////////////////////////////////////////////////
                          OTHER METHOD
///////////////////////////////////////////////////////////////////*/

/*#include <iostream>
#include <fstream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int

using namespace std ;

int main()
{
	ifstream inFile;
	size_t size = 0; // here

	inFile.open( "test.txt", ios::in|ios::binary );
	char* oData = 0;

	inFile.seekg(0, ios::end); // set the pointer to the end
	size = inFile.tellg() ; // get the length of the file
	cout << "Size of file: " << size;
	inFile.seekg(0, ios::beg); // set the pointer to the beginning

	oData = new char[ size+1 ]; //  for the '\0'
	inFile.read( oData, size );
	oData[size] = '\0' ; // set '\0'
	cout << " oData size: " << size << "\n";

  inFile.close();

	//print data
	for ( size_t i = 0; i < size; i++ )
	{
		cout << oData[i];
    cout << "\n";
		cout << oData[i] << " + 'a' = " << ( oData[i] + 'a' );
		cout << "\n\n";

	}

	return 0;
}
*/
