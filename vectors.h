#ifndef VECTORS_H_
#define VECTORS_H_

#include <vector>
#include <string>
using namespace std;

class Points{
  private:
    string id;
    vector<double> Coordinates;

  public:
    Points(string stringID);
    ~Points();
    void AddCoordinate(double coordinate);
    void PrintPoints();
};


#endif
