#include <iostream>
#include <vector>
#include "vectors.h"
#include <cstring>
#include "functions.h"

using namespace std;

Points::~Points() {
  Coordinates.clear();
}

Points::Points(string stringID){
  id = stringID;
}

void Points::AddCoordinate(double coordinate){
  Coordinates.push_back(coordinate);
}

void Points::PrintPoints(){
  cout << "ID = " <<id << "\n";;
  for (int i = 0; i < Coordinates.size(); i++) {
    cout << Coordinates.at(i) << "\n";;
  }
}
