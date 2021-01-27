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

		void generatePath() { //€чейки i==j в costMatrix тоже надо проинициализировать
			for (int i = 0; i < points.size(); i++)
				points[i].deletePass();
			random_device seed;
			cycle[0] = seed() % this->n;
			points[cycle[0]].pass();

			for (int i = 0; i < this->n - 1; i++) {
				double minCost = -1;
				int bestPoint = -1;
				for (int j = 0; j < this->n; j++) {
					if (i == j || points[j].isPassed())
						continue;
					double currentCost = costMatrix[i][j];
					if (minCost == -1) {
						minCost = currentCost;
						bestPoint = j;
					}
					else if (currentCost < minCost) {
						minCost = currentCost;
						bestPoint = j;
					}
				}
				cycle[i + 1] = bestPoint;
				points[bestPoint].pass();
			}
		}

		void switch2Edges(int i, int j) {
			int tmp = cycle[j];
			cycle[j] = cycle[i + 1];
			cycle[i + 1] = tmp;
			i += 2;
			j--;
			while (i < j) {
				int tmp = cycle[j];
				cycle[j] = cycle[i];
				cycle[i] = tmp;
				i++;
				j--;
			}
		}

		void opt2AnyReduce() { 
			for (int i = 0; i < this->n - 1; i++)
				for (int j = i + 2; j < this->n; j++) {
					if (i == 0 && j == this->n - 1)
						continue;
					double currentCost = costMatrix[cycle[i]][cycle[i + 1]]
						+ costMatrix[cycle[j]][cycle[(j + 1) % this->n]];
					double potentialCost = costMatrix[cycle[i]][cycle[j]]
						+ costMatrix[cycle[i + 1]][cycle[(j + 1) % this->n]];
					if (potentialCost < currentCost) { 
						switch2Edges(i, j);
						return;
					}
				}
		}

		void opt2BestReduce() {
			int I=-1, J = -1;
			int bestReduceCost = -1;
			for (int i = 0; i < this->n - 1; i++)
				for (int j = i + 2; j < this->n; j++) {
					if (i == 0 && j == this->n - 1)
						continue;
					double currentCost = costMatrix[cycle[i]][cycle[i + 1]]
						+ costMatrix[cycle[j]][cycle[(j + 1) % this->n]];
					double potentialCost = costMatrix[cycle[i]][cycle[j]]
						+ costMatrix[cycle[i + 1]][cycle[(j + 1) % this->n]];
					if (potentialCost < currentCost && (currentCost - potentialCost)>bestReduceCost) {
						bestReduceCost = currentCost - potentialCost;
						I = i;
						J = j;
					}
				}

			if (I==-1 || J == -1 || bestReduceCost==-1)
				return;
			else
				switch2Edges(I, J);
		}

		void opt4() {

		}

		void ILS() {
			double previousCost = this->getCost();
			while (1) {
				this->opt2BestReduce();
				double currentCost = this->getCost();
				if (previousCost != currentCost) {
					//cout << currentCost << endl;
					previousCost = currentCost;
				}
				else
					break;
			}
			//дальше работаем с opt4
		}
};

#endif // ! GCYCLE_H

