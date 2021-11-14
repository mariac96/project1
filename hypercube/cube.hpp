#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>


class dVector
{
	public:
		dVector()
		{
			// std::cout << "Defaul dVector..." << std::endl;
		}
		dVector(int id, std::vector<double> v)
		{
			this->id = id;
			this->v = v;
		}
		int getId(){
			return this->id;
		};
		std::vector<double> getVector(){
			return this->v;
		};
	private:
		int id;
		std::vector<double> v;

};
