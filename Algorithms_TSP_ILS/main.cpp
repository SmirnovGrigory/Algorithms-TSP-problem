#include <iostream>
#include <vector>
#include "GCycle.h"
using namespace std;

int main() {
	string my_file = "cases\\case1.txt";
	GCycle solution(my_file);
	solution.generatePath();
	cout << solution.getCost()<<endl;
	solution.ILS();
	cout << "Is Gcycle correct?  "<<solution.isCorrect() << endl;
	cout << endl << solution.getCycle();
}