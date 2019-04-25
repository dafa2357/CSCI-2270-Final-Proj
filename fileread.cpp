#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <climits>
#include <bitset>
#include <vector>
#include "HuffTree.hpp"
using namespace std;



unsigned long long * inFiProbs(string inFilename)
{
	ifstream inFile;//creatae ifstream;
	inFile.open( inFilename, ios::in|ios::binary);//open file as binary input
	if(!(inFile.is_open()) || !(inFile.good()))//check if open and good
	{
		cout<<"Input File Not Opened."<<endl;
		inFile.close();
		return nullptr;
  }
	unsigned long long * probability = new unsigned long long [UCHAR_MAX + 1];//creates probability array
	for( int i = 0; i <= UCHAR_MAX ; i++)//set all counts to zero //using unsigned char ++ overloads for() ++ iteratore????
		probability[i] = 0;
  unsigned char ILikeTurtles = 0; //temp storage of single byte
	streambuf * inF = inFile.rdbuf();//creates accesible stream buffer
	while( inF->sgetc() != EOF)//checks for valid input
	{
		ILikeTurtles = inF->sbumpc();//gets uchar from file moves to next position in streambuf
    probability[ILikeTurtles]++;
  }

	inFile.close();
	return probability;
}

bool pushtofile(string inFilename, ofstream * outf, HuffTree * test)
{
  //bitset <1> trucks;
  unsigned char buffer = 0;
  unsigned char ILikeTurtles = 0;                   //temp storage of single byte
  vector <int> encodedBits;                         //temporary vector of bits
  size_t whAtsAbYte = 0;                            //number of bits in encodedBits vector
  size_t bufferPos = 7;                             //position in bit buffer trucks
  ifstream inFile;                                  //create ifstream;

  if(!(outf->is_open()) || !(outf->good()))          //check output file is open and good
  {
    cout<<"Output File Not Opened."<<endl;
    outf->close();
    return false;
  }
  inFile.open( inFilename, ios::in|ios::binary);    //open file as binary input
  if(!(inFile.is_open()) || !(inFile.good()))       //check if open and good
  {
    cout<<"Input File Not Opened."<<endl;
    inFile.close();
    return false;
  }
  streambuf *inF = inFile.rdbuf();                            //creates accesible stream buffer

  while( inF->sgetc() != EOF)                       //checks for valid input
  {
    ILikeTurtles = inF->sbumpc();                   //gets uchar from file moves to next position in streambuf
    encodedBits = test->encode(ILikeTurtles);      //gets bit vector
		whAtsAbYte = encodedBits.size();                //gets length of bit string/vector
    for(size_t i = 0; i < whAtsAbYte; i++)          //runs through bit vector pushing single bits to file
    {
      encodedBits[i] &= 1;                          //bit mask for first bit
      buffer |= (unsigned char)encodedBits[i] << bufferPos;                     //add the encoded bit to the output buffer
      if (!bufferPos)
      {
			  (*outf)<< buffer;                            //output buffer to file
				buffer = 0;                                 //reset buffer
				bufferPos = 7;                              //reset buffer position
      }
      else bufferPos--;                             //decrement buffer position
    }
    encodedBits.clear();
  }
  if (bufferPos != 7) (*outf) << buffer;            //send rest of buffer if not full byte of data (0 filled)
  inFile.close();
  return true;
}

unsigned char pullFromFile(ifstream * inF, HuffTree * tree)
{
	unsigned char outChar;
	unsigned char  bits = 0;
	do
	{
		if (!tree->leftOverBits()) (*inF).read((char*)&bits,1);
	} while (!tree->decode(&outChar, bits) );
	return outChar;
}


bool decodeFile(string encodedFi)
{
	unsigned char lenF;
  unsigned long long  pr[256];
	unsigned char a;
	string filename = "a";
	HuffTree * decodeTree;
	unsigned long long charCount = 0;
	ifstream inFile;
	for (size_t q = 0; q <= UCHAR_MAX; q++) pr[q] = 0;
	inFile.open( encodedFi, ios::in|ios::binary);    //open file as binary input
	if(!(inFile.is_open()) || !(inFile.good()))       //check if open and good
  {
    cout<<"Input File Not Opened."<<endl;
    inFile.close();
    return false;
  }
	inFile.read((char*)&lenF,1);
	filename.reserve(lenF);
	for(size_t i = 1; i <= lenF; i++)//USED FOR TESTING CHANGE:i=0: <
	{
		inFile.read((char *)&a, 1);
		filename += a;
	}
	for (size_t i = 0; i <= 255; i++)
	{
		inFile.read((char*)&pr[i], 8);
		charCount += pr[i];
	}
	decodeTree = new HuffTree(pr);
	ofstream outf ( filename, ofstream::binary | ofstream::trunc);//decoded output file created
	a = 0;
	for (size_t i = 0; i < charCount; i++)
	{
		a = pullFromFile(&inFile, decodeTree);
		outf<<a;
	}
	outf.close();
	inFile.close();
	return true;
}

void encodeFile(string filename){

	unsigned long long * pr = inFiProbs(filename);
	size_t q =0;
	HuffTree * test = new HuffTree(pr);
	char lename = (char)filename.size();//sizeof file name as char
	string ofilename = filename;
	ofilename += ".truck";
	ofstream outf ( ofilename, std::ofstream::binary| std::ofstream::trunc);//creates .truck output file
	outf<<lename;
	outf<<filename;
	for( q = 0; q <= UCHAR_MAX; q++ )	//puts counts of each uchar to output file::: change to  <= when 255 found
		outf.write((char *)(&pr[q]), 8);
	pushtofile(filename, &outf, test);
	outf.close();
}

int main(int argc, char* argv[])
{
	if( 2 < argc || argc < 2)
	{
		cout<<"Include filename as command-line argument"<<endl;
		return 1;
	}
	string filename = argv[1];
	string check = ".truck";
	int eger = filename.length();
	bool ftype = true;
	for(int i =  0; i < 6; i++)
			if(check[i] != filename[(eger-6+i)]) ftype = false;

	if(ftype)
	{
		cout<<"Decoding File..."<<endl;
		decodeFile(filename);
	}
	else
	{
		cout<<"encoding File..."<<endl;
		encodeFile(filename);
	}
	return 0;
}
