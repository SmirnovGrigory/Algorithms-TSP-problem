#include <iostream>
#include <vector>
#include "GCycle.h"
using namespace std;

void generateStatistics(int n, string& filePath, string& outname) {
	GCycle solution(filePath);
	ofstream outFile(outname);
	for (int i = 0; i < n; i++) {
		solution.generatePath();
		outFile<< solution.getCost() << "   ";
		solution.ILS();
		outFile << solution.getCost() << endl<<endl;
	}
}

int main() {
	string my_file = "cases\\case500.txt";
	/*GCycle solution(my_file);
	solution.generatePath();
	cout << solution.getCost()<<endl;
	solution.ILS();
	cout << solution.getCost() << endl;
	cout << "Is Gcycle correct?  "<<solution.isCorrect() << endl;
	cout << endl << solution.getCycle();*/
	string out1_file = "statistics\\outcase500.txt";
	generateStatistics(1, my_file, out1_file);
}