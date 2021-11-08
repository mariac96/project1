#include <iostream>
#include <string>
#include <cstring>
#include "vectors.h"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "functions.h"

using namespace std;


int main(int argc, char** argv)
{
  string InputFile, QueryFile, OutputFile;
  int k, l, NumberOfNearest;
  float radius;

//  cout << "You have entered " << argc<< " arguments:" << "\n";

  for (int i = 0; i < argc; ++i){
  //  cout << argv[i] << "\n";
    if(strcmp(argv[i],"-i") == 0 ){
        InputFile = argv[i+1];

    }else if(strcmp(argv[i],"-q") == 0 ){
        QueryFile = argv[i+1];

    }else if(strcmp(argv[i],"-k") == 0 ){
      k = atoi(argv[i+1]);

    }else if(strcmp(argv[i],"-L") == 0 ){
      l = atoi(argv[i+1]);

    }else if(strcmp(argv[i],"-o") == 0 ){
      OutputFile = argv[i+1];

    }else if(strcmp(argv[i],"-N") == 0 ){
      NumberOfNearest = atoi(argv[i+1]);

    }else if(strcmp(argv[i],"-R") == 0 ){
      radius = stof(argv[i+1]);
    }
  }

/*  if(InputFile.size() == 0){
    cout << "Please give the input file" << "\n";
    cin >> InputFile;
  }


  if(QueryFile.size() == 0){
    cout << "Please give the query file" << "\n";
    cin >> QueryFile;
  }


  if(OutputFile.size() == 0){
    cout << "Please give the output file" << "\n";
    cin >> OutputFile;
  }*/

  cout << InputFile << "\n";
/*  cout << QueryFile << "\n";
  cout << k << "\n";
  cout << l << "\n";
  cout << OutputFile << "\n";
  cout << radius << "\n";*/


  vector<Points*> InputPoints;
//  readFile(InputFile,&InputPoints);
  cout<<"modulo "<< modulo(-7,-3)<<"\n";
  cout<<"modulo "<< modulo(-7,3)<<"\n";
  cout<<"remainder "<<(-7)%(-3)<<"\n";
  cout<<"remainder "<<(-7)%(-3)<<"\n";
//  InputPoints.at(22)->PrintPoints();
//  InputPoints.at(2)->PrintPoints();
  return 0;
}
