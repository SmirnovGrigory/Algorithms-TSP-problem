#include <iostream>
#include <vector>
#include "GCycle.h"

using namespace std;

void generateStatistics(int n, string &filePath, string &outname) {
    GCycle solution(filePath);
    ofstream outFile(outname);
    for (int i = 0; i < n; i++) {
        solution.generatePath();
        outFile << solution.getCost() << "   ";
        solution.ILS();
        outFile << solution.getCost() << endl << endl;
    }
}

int main() {
    string my_file = "cases/case1.txt";
    GCycle solution(my_file);
    solution.generatePath();
    cout << solution.getCycle() << '\n';
    solution.perturbation(.9);
    cout << solution.getCycle() << '\n';

//    solution.visualiseGraph();
//
//    cout << solution.getCost() << endl;
//    solution.ILS();
//    cout << "Is Gcycle correct?  " << solution.isCorrect() << endl;
//
//    solution.visualiseGraph();
//    my_file = "cases/case131.txt";
    /*GCycle solution(my_file);
    solution.generatePath();
    cout << solution.getCost()<<endl;
    solution.ILS();
    cout << solution.getCost() << endl;
    cout << "Is Gcycle correct?  "<<solution.isCorrect() << endl;
    cout << endl << solution.getCycle();*/
//    string out1_file = "statistics/outcase131.txt";
//    generateStatistics(30, my_file, out1_file);
}

