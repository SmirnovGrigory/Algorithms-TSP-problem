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
    double **costMatrix;
    int n;

public:

    void readDataStdin(string &ifname) {
        int n1;
        cin >> n1;
        this->n = n1;
        this->points.resize(this->n);
        int id, x, y;
        for (int i = 0; i < this->n; i++) {
            cin >> id >> x >> y;
            this->points[i].setID(id);
            this->points[i].setLoc(x, y);
        }
    }

    explicit GCycle(string &ifname) {
        ifstream myfile(ifname);
        int n1;
        myfile >> n1;
        this->n = n1;
        this->n = 0;
        cin >> this->n;
        this->points.resize(this->n);
        int id, x, y;
        for (int i = 0; i < this->n; i++) {
            cin >> id >> x >> y;
            this->points[i].setID(id);
            this->points[i].setLoc(x, y);
        }
        myfile.close();

        this->costMatrix = new double *[this->n];
        for (int i = 0; i < this->n; i++)
            this->costMatrix[i] = new double[this->n];

        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->n; j++)
                this->costMatrix[i][j] = this->points[i].EuclideanDistance(this->points[j]);

        this->cycle.resize(this->n);
    }

    ~GCycle() {
        for (int i = 0; i < this->n; i++)
            delete[] this->costMatrix[i];
        delete[] this->costMatrix;
    }

    bool isCorrect() {
        vector<int> passed(this->n);
        for (int i = 0; i < this->n; i++)
            if (passed[this->cycle[i]] == 1)
                return false;
            else
                passed[this->cycle[i]]++;
        return true;
    }

    double getCost() {
        double result = 0;
        for (int i = 0; i < this->n; i++)
            result += costMatrix[cycle[i]][cycle[(i + 1) % this->n]];
        return result;
    }

    string getCycle() {
        string strCycle;
        for (int i = 0; i < this->n; i++)
            strCycle += to_string(this->points[this->cycle[i]].getID()) + "\n";
        return strCycle;
    }

    void generatePath() { //������ i==j � costMatrix ���� ���� �������������������
        random_device seed;
        this->cycle[0] = seed() % this->n;
        this->points[this->cycle[0]].pass();

        for (int i = 0; i < this->n - 1; i++) {
            double minCost = -1;
            int bestPoint = -1;
            for (int j = 0; j < this->n; j++) {
                if (i == j || this->points[j].isPassed())
                    continue;
                double currentCost = this->costMatrix[i][j];
                if (minCost == -1 || currentCost < minCost) {
                    minCost = currentCost;
                    bestPoint = j;
                }
            }
            this->cycle[i + 1] = bestPoint;
            this->points[bestPoint].pass();
        }
    }

    void opt2() { //��������� ������ ���������� ���������
        for (int i = 0; i < this->n - 1; i++)
            for (int j = i + 2; j < this->n; j++) {
                if (i == 0 && j == this->n - 1)
                    continue;
                double currentCost = this->costMatrix[this->cycle[i]][this->cycle[i + 1]]
                                     + this->costMatrix[this->cycle[j]][this->cycle[(j + 1) % this->n]];
                double potentialCost = this->costMatrix[this->cycle[i]][this->cycle[j]]
                                       + this->costMatrix[this->cycle[i + 1]][this->cycle[(j + 1) % this->n]];
                if (potentialCost < currentCost) {
                    int tmp = this->cycle[j];
                    this->cycle[j] = this->cycle[i + 1];
                    this->cycle[i + 1] = tmp;
                    i += 2;
                    j--;
                    while (i < j) { // �������� �� ����� ������ � �����
                        tmp = this->cycle[j];
                        this->cycle[j] = this->cycle[i];
                        this->cycle[i] = tmp;
                        i++;
                        j--;
                    }
                    return;
                }
            }
    }

    void opt4() {

    }

    void ILS() {
        double previousCost = this->getCost();
        while (true) {
            this->opt2();
            double currentCost = this->getCost();
            if (previousCost != currentCost) {
                cout << currentCost << endl;
                previousCost = currentCost;
            } else
                break;
        }
        //������ �������� � opt4
    }
};

#endif // ! GCYCLE_H

