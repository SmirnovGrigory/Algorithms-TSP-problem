#include <iostream>
#include <vector>
#include "GCycle.h"
using namespace std;

int main() {
	string my_file = "case1.txt";
	GCycle solution(my_file);
	solution.generatePath();
	cout << solution.getCost()<<endl;
	cout << solution.getCycle();
}