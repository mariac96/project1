#pragma once
#include "lsh.hpp"

void LSH(int vSize, int L, int K, std::string queryFile, std::vector<dVector>& dataset, std::string& outputFile, int d, int w, int N, double R);

int hp(dVector& dv, int w, int d, std::vector<double>& V, double t);

int euclidModuloLong(int x, long long y);
int euclidModulo(int x, int y);

int gp(std::vector<int>& r, std::vector<int>& g, int TableSize);

double EuclideanDistance(std::vector<double>& v1, std::vector<double>& v2);
