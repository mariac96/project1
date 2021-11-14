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
#include "cube.hpp"

using namespace std;

void hyperCube(int vSize, int M, int k, int probes,std::string queryFile, 
	std::vector<dVector>& dataset, string& outputFile, int d, int w, int N, double R)
{

	int cubeSize = pow(2, k);
	vector<dVector> Cube[cubeSize];


	std::vector<double> V[k];
	double t[k];

	std::random_device normal_generator;
	normal_distribution<double> normal_distribution(0.0, 1.0);

	std::random_device generator;
	uniform_real_distribution<double> uni_distribution(0.0, w-1);

	// create vector with real coordinates distributed
	// according to the normal distribution

	for(int i = 0 ; i < k ; i++)
	{
		for(int j = 0 ; j < d ; j++)
		{
			double number = normal_distribution(normal_generator);
			V[i].push_back(number);
		}
		t[i] = uni_distribution(generator);
	}

	map<int, int> myMap;
	// insert each point
	for(int i = 0; i < vSize; i++)
	{

		std::vector<int> h;
		for( int j = 0; j < k; j++)
		{
			int hashF = hp(dataset.at(i), w, d, V[j], t[j]);
			h.push_back(hashF);
		}

		string p = f(h, myMap);
		int bucket = binaryToDecimal(p);
		Cube[bucket].push_back(dataset.at(i));
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

		std::vector<int> h;
		for( int j = 0; j < k; j++)
		{
			int hashF = hp(q, w, d, V[j], t[j]);
			h.push_back(hashF);
		}


		string p = f(h, myMap);
		int bucket = binaryToDecimal(p);

		// empty map container that will contain distance and vector ID
		map<double, int> euclDis;

		//list that will contain vectorID of Approximate NN
		list <int> list1;

		// Check points in same vertex
		for(vector<dVector>::iterator itr = (Cube[bucket]).begin();
			itr != (Cube[bucket]).end(); itr++)
		{
			// calculate distance between query and each point of bucket
			vector<double> v2 = itr->getVector();
			double dist = EuclideanDistance(v1, v2);
			euclDis.insert(pair<double, int>(dist, (itr)->getId()));
			if(dist < R)
				list1.push_back((itr)->getId());

		}

		for(int counterProbes = 0; counterProbes < probes; counterProbes++)
		{
			// bset is initialized with bits of specified binary string
			// size is arbitary
			bitset<100> bset(p);

			// flip function flips  bits i.e.  1 <-> 0
			// starting from end to the start
			for(int ii = 0; ii <= counterProbes; ii++)
				bset.flip(ii);
			string tmp1 = bset.to_string();
			// keep only the part of the string we need
			int l1 = p.length();
			int l2 = tmp1.length();
			string r = tmp1.substr(l2-l1);
			int mybucket = binaryToDecimal(r);
			int counterM = 0;
			// Check points in same vertex
			for(vector<dVector>::iterator itr = (Cube[mybucket]).begin();
				itr != (Cube[mybucket]).end(); itr++)
			{
				// calculate distance between query and each point of bucket
				vector<double> v2 = itr->getVector();
				double dist = EuclideanDistance(v1, v2);
				euclDis.insert(pair<double, int>(dist, (itr)->getId()));
				if(dist < R)
					list1.push_back((itr)->getId());
				counterM++;
				if(counterM == M)
					break;
			}
		}

		clock_t end = clock();
		double tCube = (double)(end - begin) / CLOCKS_PER_SEC;

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

		
		output << "distanceCube: " << itr->first << endl;
		output << "distanceTrue: " << minDist << endl;
		output << "tCube " << tCube << endl;
		output << "tTrue: " << tTrue << endl;

		output << "R-near neighbors:"<< endl;
		list <int> :: iterator it;
		for(it = list1.begin(); it != list1.end(); ++it)
			output << *it << endl;
		output<<endl<< endl;
	}
}

string f(std::vector<int> h, std::map<int, int> &m)
{
	string temp;

	for(int i = 0; i < h.size(); i++)
	{
		static std::random_device r;
		static std::seed_seq seeds{ r(), r(), r(), r(), r(), r() };
		// Construct a meresenne twister random number generator,
		// seeded with the values we just generated. This will give
		// us better quality random numbers than the random device
		static std::mt19937 engine(seeds);
		// Notice how every variable up to this point is static. This
		// is to ensure that they're only ever initialized once during
		// the execution of the program. We don't want to generate a
		// new random number generator at each function call as we'll
		// lose the random state.
		static std::uniform_int_distribution<int> dist(0, 1);
		// Roll the dice

		int coin = dist(engine);

		// if h.at(i) is not present then toss the coin
		// because same h must have same value
		if (m.count(h.at(i)) == 0)
		{
			int coin = dist(engine);
			// m.insert(pair<int, int> (h.at(i), coin));
			temp += to_string(coin);
		}
		else
		{
			coin = m.at(h.at(i));
			temp += to_string(coin);
		}
	
	}
	return temp;
}


int hp(dVector& dv, int w, int d, std::vector<double>& V, double t)
{
	vector<double> p = dv.getVector();
	// calculate p * v by using inner_product
	double pv = (double)inner_product(p.begin(), p.begin() + p.size(), V.begin(), 0.0);
	double h = (pv + t) / (double(w));
	return (int)h;
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



// function to convert binary to decimal
int binaryToDecimal(string n)
{
	string num = n;
	int dec_value = 0;
	// Initializing base value to 1, i.e 2^0
	int base = 1;
	int len = num.length();
	for (int i = len - 1; i >= 0; i--) {
		if (num[i] == '1')
			dec_value += base;
		base = base * 2;
	}
	return dec_value;
}