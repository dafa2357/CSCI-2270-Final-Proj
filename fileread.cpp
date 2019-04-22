#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <climits>
#include <bitset>
#include <vector>
#include "HuffTree.hpp"
using namespace std;


//type handling for input and output use BOOST FILESYSTEM LIBRARY

unsigned long long * inFiProbs(string inFilename)
{// , string oFile){///REMOVE ALL instaces of output file
	ifstream inFile;//creatae ifstream;
	inFile.open( inFilename, ios::in|ios::binary);//open file as binary input
	if(!(inFile.is_open()) || !(inFile.good()))
	{//check if open and good
		cout<<"Input File Not Opened."<<endl;
		inFile.close();
		return nullptr;
  }

	unsigned long long * probability = new unsigned long long [UCHAR_MAX + 1];//creates probability array
	for( int i = 0; i <= UCHAR_MAX ; i++)//set all counts to zero //using unsigned char ++ overloads for() ++ iteratore????
		probability[i] = 0;


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

bool pushtofile(string inFilename, ofstream * outf, HuffTree * test){

	if(!(outf->is_open()) || !(outf->good())) {//check output file is open and good
		cout<<"Output File Not Opened."<<endl;
		outf->close();
		return 1;
		}

	ifstream inFile;//create i 	fstream;

	inFile.open( inFilename, ios::in|ios::binary);//open file as binary input
	if(!(inFile.is_open()) || !(inFile.good())) {//check if open and good
		cout<<"Input File Not Opened."<<endl;
		inFile.close();
		return 1;
		}

	std::bitset <1> trucks;
	unsigned char ILikeTurtles = 0; //temp storage of single byte
	vector <int> encodedBits;//temporary vector of bits
	size_t whAtsAbYte = 0;//number of bits in encodedBits vector
	std::streambuf * inF = inFile.rdbuf();//creates accesible stream buffer
	//ofstream outf ( oFile, std::ofstream::binary| std::ofstream::trunc);//creates output file of same type               //USED FOR TESTING: REMOVE

	while( inF->sgetc() != EOF){ //checks for valid input
		ILikeTurtles = inF->sbumpc();//gets uchar from file moves to next position in streambuf
		encodedBits = test->encode(ILikeTurtles);//gets bit vector
		whAtsAbYte = encodedBits.size();//gets length of bit string/vector
		for(size_t i = 0; i < whAtsAbYte; i++){//runs through bit vector pushing single bits to file
			trucks[0] = encodedBits[i];//bit set to correct val
			(*outf)<<trucks[0];//bit pushed to output file
		}
		encodedBits.clear();
	}
	inFile.close();
	return 0;
}


int main()
{
	string filename = "test.txt";
	unsigned long long * pr = inFiProbs(filename);
	size_t q =0;
	for( q = 0; q < UCHAR_MAX; q++ ){//prints counts of each uchar from inFile                 //USED FOR TESTING: REMOVE
		cout<< q <<": "<< pr[q] <<endl;}
		//cout<<"0"<<endl;
	HuffTree * test = new HuffTree(pr);

	//cout<<"1"<<endl;
	std::bitset <1> trucks;
//	unsigned char ILikeTurtles = 0; //temp storage of single byte
	vector <int> encodedBits;//temporary vector of bits
	size_t whAtsAbYte = 0;
	for(q=0; q <= UCHAR_MAX; q++){
		cout<< q << ": ";
		encodedBits = test->encode(q);//gets bit vector
		whAtsAbYte = encodedBits.size();//gets length of bit string/vector
		for(size_t i = 0; i < whAtsAbYte; i++){//runs through bit vector pushing single bits to file
			trucks[0] = encodedBits[i];//bit set to correct val
			cout<<trucks[0];
		}
		cout<<endl;
	}

	char lename = (char)filename.size();//sizeof file name as char
	string ofilename = filename;
	ofilename += ".truck";

//	cout<<"2"<<endl;

	ofstream outf ( ofilename, std::ofstream::binary| std::ofstream::trunc);//creates .truck output file


	outf << lename;
	outf<<filename;
	for( q = 0; q < UCHAR_MAX; q++ ){//puts counts of each uchar to output file::: change to  <=
			outf<< pr[q];}
	pushtofile(filename, &outf, test);



/*///////////////////////////////////////
  MAKE WORK WITH DIRCTORIES
  PUSH FUNCTION FOR OUT FILE
  read file again while encoding with tree getchar pushchar
//////////////////////////////////////*/


	return 0;
}
