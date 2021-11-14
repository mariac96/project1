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

// ./lsh -i input_small_id -q query_small_id -k 10 -L 6 -o output_file -N 2 -R 20000
int main(int argc, char *argv[])
{
	int k = 4;
	int L = 5;
	int N = 1;
	double R = 10000;
	string inputFile = "./";
	string queryFile = "./";
	string outputFile = "./";

	int d;
	if (argc < 3)
	{
		cout << "Not enough arguments given" << endl;
		exit(0);
	}

	// read all given arguments 
	for (int i = 1; i < argc; i++)
	{
		string s = argv[i];
		// check if after -i aren't at the end of argv
		if( (s == "-i") and (argc > i+1))
			inputFile.append(argv[i+1]);
		// check if after -q aren't at the end of argv
		else if( (s == "-q") and (argc > i+1))
			queryFile.append(argv[i+1]);
		else if( (s == "-o") and (argc > i+1))
			outputFile.append(argv[i+1]);
		else if( (s == "-k") and (argc > i+1))
			k = atoi(argv[i+1]);
		else if( (s == "-L") and (argc > i+1))
			L = atoi(argv[i+1]);
		else if( (s == "-N") and (argc > i+1))
			N = atoi(argv[i+1]);
		else if( (s == "-R") and (argc > i+1))
			R = atof(argv[i+1]);
		// clear string to be sure that is empty in the next iteration
		s.clear();
	}
	
	if (inputFile == "./")
	{
		cout << "Give input File" << endl;
		string temp;
		cin >> temp;
		inputFile.append(temp);
	}
	else if(outputFile == "./")
	{
		// queryFile
		cout << "Give input  output File" << endl;
		string temp;
		cin >> temp;
		outputFile.append(temp);
	}
	else if(queryFile == "./")
	{
		cout << "Give query File" << endl;
		string temp;
		cin >> temp;
		queryFile.append(temp);
	}


	int ii = 0;

	vector<dVector> dataset;
	// open inputFile with ifstream
	ifstream file(inputFile);
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
			// get dismension of vector
			if (ii == 1)
				d = g.size();
			dVector ptrdVector = dVector(id, g);
			dataset.push_back(ptrdVector);

			g.clear();
			// if (ii == 2)
			// 	break;
		}
		file.close();
	}

	// create random natural number w
	// if it is between 300 and 400 we have better results
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(300, 400);
	int w = dis(gen);
	LSH(dataset.size(), L, k, queryFile, dataset, outputFile, d, w, N, R);
	return 0;
}
