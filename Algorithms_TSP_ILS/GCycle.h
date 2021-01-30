#ifndef  GCYCLE_H
#define GCycle_H

#include "Point.h"
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;

class GCycle {
private:
    vector<int> cycle;
    vector<Point> points;
    double **costMatrix;
    int n;

public:
    void readDataStdin() {
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

    void readDataFileStream(string &ifname) {
        ifstream myfile(ifname);
        int n1;
        myfile >> n1;
        this->n = n1;
        this->points.resize(this->n);
        int id, x, y;
        for (int i = 0; i < this->n; i++) {
            myfile >> id >> x >> y;
            this->points[i].setID(id);
            this->points[i].setLoc(x, y);
        }
        myfile.close();
    }

    explicit GCycle(string &ifname) {
//        readDataStdin();
        readDataFileStream(ifname);
        this->costMatrix = new double *[this->n];
        for (int i = 0; i < this->n; i++)
            this->costMatrix[i] = new double[this->n];

        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->n; j++)
                this->costMatrix[i][j] = this->points[i].EuclideanDistance(this->points[j]);

        this->cycle.resize(this->n);
    }

    string getGraphCondition() {
        string data;
        data += to_string(this->n);
        data += '\n';
        for (int i = 0; i < n; ++i)
            data += to_string(this->points[i].getX()) + ' ' + to_string(this->points[i].getY()) + '\n';
        for (int i = 0; i < n; ++i)
            data += to_string(cycle[i]) + ' ';
        data += '\n' + to_string(this->getCost());
        return data;
    }

    void visualiseGraph() {
        ofstream out("file.txt");
        out << getGraphCondition().c_str();
        out.close();
        try {
            int sys_code = system("bash paint.sh");
        } catch (const int a) {
            cout << "Exception was happened\n";
        }
    }

    void chooseBestResult(const string &res, const string &ans) {
        ifstream input(res);
        int bestCost;
        input >> bestCost;
        input.close();
        if (this->getCost() < bestCost) {
            ofstream output(ans);
            output << getCycle();
            output.close();
            ofstream out(res);
            out << getCost();
            out.close();
        }
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
            strCycle += to_string(this->points[this->cycle[i]].getID()) + " ";
        return strCycle;
    }

    void generatePath() {
        random_device seed;
        cout << this->n;
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

    void perturbation(double force) {
        if (force >= 1) force = .9;
        if (force <= 0) force = 0;
        int count = (int) (this->n * force);
        random_device generator;
        unsigned int seed = generator() % (this->n - count);
        shuffle(this->cycle.begin() + seed, this->cycle.begin() + seed + count, generator);
    }

    void freePoints() {
        for (int i = 0; i < this->n; ++i)
            this->points[i].deletePass();
    }

    void switch2Edges(int i, int j) {
        int tmp = cycle[j];
        cycle[j] = cycle[i + 1];
        cycle[i + 1] = tmp;
        i += 2;
        j--;
        while (i < j) {
            tmp = cycle[j];
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
        int I = -1, J = -1;
        double bestReduceCost = -1.;
        for (int i = 0; i < this->n - 1; i++)
            for (int j = i + 2; j < this->n; j++) {
                if (i == 0 && j == this->n - 1)
                    continue;
                double currentCost = costMatrix[cycle[i]][cycle[i + 1]]
                                     + costMatrix[cycle[j]][cycle[(j + 1) % this->n]];
                double potentialCost = costMatrix[cycle[i]][cycle[j]]
                                       + costMatrix[cycle[i + 1]][cycle[(j + 1) % this->n]];
                if (potentialCost < currentCost && (currentCost - potentialCost) > bestReduceCost) {
                    bestReduceCost = currentCost - potentialCost;
                    I = i;
                    J = j;
                }
            }

        if (I == -1 || J == -1 || bestReduceCost == -1)
            return;
        else
            switch2Edges(I, J);
    }

    void opt4() {

    }

    void ILS(int iterations) {
        vector<int> bestCycle(this->n);
        double bestCost = 1e9;
        for (int i = 0; i < iterations; ++i) {
            double previousCost = this->getCost();
            while (true) {
//                this->opt2BestReduce();
                this->opt2AnyReduce();
                double currentCost = this->getCost();
                if (previousCost != currentCost) {
                    //cout << currentCost << endl;
                    previousCost = currentCost;
                } else
                    break;
            }
            if (previousCost < bestCost) {
                bestCost = previousCost;
                copy(this->cycle.begin(), this->cycle.end(), bestCycle.begin());
            }

            double perturbationForce = .003;

            this->perturbation(perturbationForce);
            this->freePoints();
            cout.precision(8);
            if (!(i % 10))
                cout << i / 1000 << "K iteration -> " << this->getCost() << " (best cost is: " << bestCost
                     << " pForce: " << perturbationForce << ")"
                     << endl;
        }
        copy(bestCycle.begin(), bestCycle.end(), this->cycle.begin());
    }

};

#endif // ! GCYCLE_H

