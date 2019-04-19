#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <climits>
using namespace std;
//type handling for input and output use BOOST FILESYSTEM LIBRARY

unsigned long long * inFiProbs(string inFilename){// , string oFile){///REMOVE ALL instaces of output file
	ifstream inFile;//creatae ifstream;
	inFile.open( inFilename, ios::in|ios::binary);//open file as binary input
	if(!(inFile.is_open()) || !(inFile.good())) {//check if open and good
		cout<<"File Not Opened."<<endl;
		inFile.close();
		return nullptr;
  	}

	unsigned long long * probability = new unsigned long long [UCHAR_MAX + 1];//creates probability array
	for( int i = 0; i <= UCHAR_MAX ; i++){//set all counts to zero //using unsigned char ++ overloads for() ++ iteratore????
		probability[i] = 0;
	}

  	unsigned char ILikeTurtles = 0; //temp storage of single byte
  	std::streambuf * inF = inFile.rdbuf();//creates accesible stream buffer
	//ofstream outf ( oFile, std::ofstream::binary| std::ofstream::trunc);//creates output file of same type               //USED FOR TESTING: REMOVE

	while( inF->sgetc() != EOF){ //checks for valid input
    		ILikeTurtles = inF->sbumpc();//gets uchar from file moves to next position in streambuf
  		//  cout<<":"<<ILikeTurtles                                                                                  //USED FOR TESTING: REMOVE
    		probability[ILikeTurtles]++;
    		//outf<<ILikeTurtles;//outputs uchar to file                                                                   //USED FOR TESTING: REMOVE
  	}

	//cout<<"3"<<endl;                                                                                                    //USED FOR TESTING: REMOVE
	//outf.close();                                                                                                         //USED FOR TESTING: REMOVE
	inFile.close();
	return probability;

}


int main()
{
	unsigned long long * pr = inFiProbs("lec12.pptx");
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
