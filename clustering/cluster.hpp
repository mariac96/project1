#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>


class dVector
{
	public:
		int index;
		dVector()
		{
			// std::cout << "Defaul dVector..." << std::endl;
		}
		dVector(int id, std::vector<double> v)
		{
			this->id = id;
			this->v = v;
			this->clust = false;
		}
		int getId(){
			return this->id;
		};
		std::vector<double> getVector(){
			return this->v;
		};
		void mark()
		{
			this->clust = true;
		};
		bool isMark()
		{
			return clust;
		}
	private:
		int id;
		std::vector<double> v;
		bool clust;

};

class cluster
{
	public:
		cluster(dVector &c)
		{
			this->centroid = c;
		};
		dVector getCentre()
		{
			return this->centroid;
		};
		void assignBuck(std::vector<int> b)
		{
			this->buckets = b;
		}
		std::vector<int> getBuckets()
		{
			return buckets;
		}
		void addToCluster(dVector &d)
		{
			this->dataset.push_back(d);
		}
		int getClusterSize()
		{
			return dataset.size();
		}
		std::vector<dVector>& getDataset()
		{
			return this->dataset;
		}

	private:
		dVector centroid;
		std::vector<dVector> dataset;
		std::vector<int> buckets;

};

double EuclideanDistance(std::vector<double>& v1, std::vector<double>& v2);