#ifndef  GCYCLE_H
#define GCycle_H
#include "Point.h"
#include <vector>
#include <fstream>
#include <string>
#include<random>
using namespace std;

class GCycle {
	private:
		vector<int> cycle;
		vector<Point> points;
		double** costMatrix;
		int n;

	public:
		void generatePath() {
			random_device seed;
			cycle[0] = seed() % this->n;
			points[cycle[0]].pass();

			for (int i = 0; i < this->n - 1; i++) {
				double minCost=-1;
				int bestPoint=-1;
				for (int j = 0; j < this->n; j++) {
					if (i==j || points[j].isPassed())
						continue;
					double currentCost = costMatrix[i][j];
					if (minCost == -1) {
						minCost = currentCost;
						bestPoint = j;
					} 
					else if (currentCost<minCost) {
						minCost = currentCost;
						bestPoint = j;
					}
				}
				cycle[i + 1] = bestPoint;
				points[bestPoint].pass();
			}
		}

		GCycle(string& ifname) {
			ifstream myfile(ifname);
			myfile >> this->n;
			this->points.resize(this->n);
			int id, x, y;
			for (int i = 0; i < this->n; i++) {
				myfile >> id >> x >> y;
				points[i].setID(id);
				points[i].setLoc(x, y);
			}
			myfile.close();

			costMatrix = new double* [this->n];
			for (int i = 0; i < this->n; i++)
				costMatrix[i] = new double[n];

			for (int i = 0; i < this->n; i++)
				for (int j = 0; j < this->n; j++)
					costMatrix[i][j] = points[i].EuclideanDistance(points[j]);

			this->cycle.resize(this->n);
		}

		~GCycle() {
			for (int i = 0; i < this->n; i++)
				 delete[] costMatrix[i];
			delete[] costMatrix;
		}

		bool isCorrect() {
			vector<int> passed(this->n);
			for (int i = 0; i < this->n; i++)
				if (passed[cycle[i]] == 1)
					return 0;
				else
					passed[cycle[i]]++;
			return 1;
		}
 
		double getCost() {
			double result = 0;
			for (int i = 0; i < this->n; i++)
				result += costMatrix[cycle[i]][cycle[(i + 1)%this->n]];
			return result;
		}

		string getCycle() {
			string strCycle = "";
			for (int i = 0; i < this->n; i++)
				strCycle += to_string(points[cycle[i]].getID()) + "\n";
			return strCycle;
		}
};

#endif // ! GCYCLE_H

