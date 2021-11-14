#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <bits/stdc++.h>
#include <numeric>
#include <map>
#include <time.h>
#include <math.h>

#include "main.hpp"
#include "lsh.hpp"

using namespace std;

void LSH(int vSize, int L, int k, string queryFile, 
	std::vector<dVector>& dataset, string& outputFile, int d, int w, int N, double R)
{
	int i;
	int TableSize = vSize/4;
	vector<dVector> HashTable[L][TableSize];
	std::vector<double> V[L][k];
	double t[L][k];

	std::random_device normal_generator;
	normal_distribution<double> normal_distribution(0.0, 1.0);

	std::random_device generator;
	uniform_real_distribution<double> uni_distribution(0.0, w-1);

	// create vector with real coordinates distributed
	// according to the normal distribution
	for(int i = 0 ; i < L ; i++)
	{	
		for(int j = 0 ; j < k ; j++)
		{
			for(int ii = 0 ; ii < d ; ii++)
			{
				double number = normal_distribution(normal_generator);
				V[i][j].push_back(number);
			}
			t[i][j] = uni_distribution(generator);
		}
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, INT_MAX);

	// crete random vector rk with values from0 to int max
	std::vector<int> r;
	for(int i = 0 ; i < k ; i++)
		r.push_back(dis(gen));
	// insert each point to hash tables
	for(int i = 0; i < vSize; i++)
	{
		vector<int> hi[L];
		for( int j = 0; j < L; j++)
		{
			std::vector<int> h;
			for( int ii = 0; ii < k; ii++)
			{
				int hashF = hp(dataset.at(i), w, d, V[j][ii], t[j][ii]);
				h.push_back(hashF);
			}
			hi[j] = h;
		}
		for( int j = 0; j < L; j++)
		{
			int bucket = gp(r, hi[j], TableSize);

			HashTable[j][bucket].push_back(dataset.at(i));
		}
	}

	vector<dVector> queries; 

	int ii = 0;
	ifstream file(queryFile);
	if (file.is_open())
	{
		// read line of file to string
		string line;
		while (getline(file, line))
		{
			ii++;
			vector<double> g;
			string temp;
			int j = 0;
			int id = -1;
			// lines contains multiple numbers so we separate them
			for (int i = 0; i < line.length(); i++)
			{
				// save each digit of number to the string
				if(line[i] != ' ')
					temp.push_back(line[i]);
				else
				{	// reach end of the single number
					// so convert it from string
					double x = atof(temp.c_str());
					// first number of line is id
					// and it is not a part of vector
					j++;
					if (j == 1)
						id = x;
					else
						g.push_back(x);
					temp.clear();
				}
			}
			dVector ptrdVector = dVector(id, g);
			queries.push_back(ptrdVector);
			g.clear();
		}
		file.close();
	}

	ofstream output;
	output.open(outputFile.c_str(),std::ofstream::out | std::ofstream::trunc);
	if (!output.is_open())
	{
		cout << "Output Error" << endl;
		exit(-1);
	}
	for(int i = 0 ; i < queries.size(); i++)
	{

		dVector q = queries.at(i);
		vector<double> v1 = q.getVector();
		clock_t begin = clock();
		vector<int> hi[L];
		for( int j = 0; j < L; j++)
		{
			std::vector<int> h;
			for( int ii = 0; ii < k; ii++)
			{
				int hashF = hp(dataset.at(i), w, d, V[j][ii], t[j][ii]);
				h.push_back(hashF);
			}
			hi[j] = h;
		}
		// empty map container that will contain distance and vector ID
		map<double, int> euclDis;

		//list that will contain vectorID of Approximate NN
		list <int> list1;

		for( int j = 0; j < L; j++)
		{
			int bucket = gp(r, hi[j], TableSize);

			for(vector<dVector>::iterator itr = (HashTable[j][bucket]).begin();
				itr != (HashTable[j][bucket]).end(); itr++ )
			{
				vector<double> v2 = (itr)->getVector();
				double dist = EuclideanDistance(v1, v2);
				euclDis.insert(pair<double, int>(dist, (itr)->getId()));
				if(dist < R)
					list1.push_back((itr)->getId());
			}

		}
		clock_t end = clock();
		double tLSH = (double)(end - begin) / CLOCKS_PER_SEC;


		clock_t begin2 = clock();
		double minDist = INFINITY;
		int minId;
		// brute force calculate nearest neighbour sad!
		for( int i = 0; i < vSize; i++)
		{
			dVector d = dataset.at(i);
			vector<double> temp = d.getVector();
			double dist = EuclideanDistance(v1, temp);
			if( dist < minDist)
			{
				minDist = dist;
				minId = d.getId();
			}
		}
		clock_t end2 = clock();
		double tTrue = (double)(end2 - begin2) / CLOCKS_PER_SEC;

		output << "Query: "<< q.getId() << endl;

		// get N-nearest neighbour
		map<double, int>::iterator itr;
		int counter = 0;
		for (itr = euclDis.begin(); itr != euclDis.end(); itr++)
		{

			//cout << itr->second << endl;
			counter++;
			output << "Nearest neighbor-"<< counter <<": " << itr->second << endl;
			if (counter == N)
				break;
		}


		
		output << "distanceLSH: " << itr->first << endl;
		output << "distanceTrue: " << minDist << endl;
		output << "tLSH " << tLSH << endl;
		output << "tTrue: " << tTrue << endl;

		output << "R-near neighbors:"<< endl;
		list <int> :: iterator it;
		for(it = list1.begin(); it != list1.end(); ++it)
			output << *it << endl;

		output<<endl<< endl;
	}
}


int hp(dVector& dv, int w, int d, std::vector<double>& V, double t)
{
	vector<double> p = dv.getVector();
	// calculate p * v by using inner_product
	double pv = (double)inner_product(p.begin(), p.begin() + p.size(), V.begin(), 0.0);
	double h = (pv + t) / (double(w));
	return (int)h;
}



int gp(std::vector<int>& r, std::vector<int>& g, int TableSize)
{
	long long rh = inner_product(g.begin(), g.end() + g.size(), r.begin(), 0);
	long long M = pow(2, 52) - 5;

	int temp = euclidModuloLong(rh, M);
	int bucket = euclidModulo(temp, TableSize);
	return bucket;


}

// returns positive result
int euclidModulo(int x, int y)
{
	return ( (x % y) + y ) % y;
}

int euclidModuloLong(int x, long long y)
{
	return ( (x % y) + y) % y;
}

double EuclideanDistance(std::vector<double>& v1, std::vector<double>& v2)
{
	double dist = 0 ;

	for(int i = 0 ; i < v1.size(); i++)
	{
		double temp = v1.at(i) - v2.at(i);
		dist = dist + temp*temp;
	}
	if(dist != 0)
		dist = sqrt(dist);

	return dist;
}