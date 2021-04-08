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
        solution.ILS(10000);
        outFile << solution.getCost() << endl << endl;
    }
}

void test1() {
    // 10K iterations, .228 - force of perturbation
    string file = "cases/case131.txt";
    GCycle solution(file);
    solution.generatePath();
    solution.ILS(100000);
    solution.visualiseGraph();
    // Best result - 568
}

void test2() {
    string file = "cases/case500.txt";
    GCycle solution(file);
    solution.generatePath();
    solution.visualiseGraph();
    solution.ILS(30);
    solution.visualiseGraph();
    // Best result - 3536
}

void test_mona_1000() {
    string testName("mona_1000.txt");
    string file = "cases/" + testName;
    GCycle solution(file);
    solution.generatePath();
    solution.ILS(1000);
    // solution.visualiseGraph();
    solution.chooseBestResult("Answers_GHA/" + testName, "Answers_GHA/" + testName + "ans");
}

void test_lu_980() {
    string testName("lu980.txt");
    string file = "cases/" + testName;
    GCycle solution(file);
    solution.generatePath();
    solution.ILS(1000);
    // solution.visualiseGraph();
    solution.chooseBestResult("Answers/" + testName, "Answers/" + testName + "ans");
}

void test_ja_1000() {
    string testName("ja_1000.txt");
    string file = "cases/" + testName;
    GCycle solution(file);
    solution.generatePath();
    solution.ILS(1000);
    // solution.visualiseGraph();
    solution.chooseBestResult("Answers/" + testName, "Answers/" + testName + "ans");
}

void test_random_1() {
    string testName("random_1.txt");
    string file = "cases/" + testName;
    GCycle solution(file);
    solution.generatePath();
    solution.ILS(1000);
    // solution.visualiseGraph();
    solution.chooseBestResult("Answers/" + testName, "Answers/" + testName + "ans");
}

void test_random_2() {
    string testName("random_2.txt");
    string file = "cases/" + testName;
    GCycle solution(file);
    solution.generatePath();
    solution.ILS(1000);
    // solution.visualiseGraph();
    solution.chooseBestResult("Answers/" + testName, "Answers/" + testName + "ans");
}

void test_random_3() {
    string testName("random_3.txt");
    string file = "cases/" + testName;
    GCycle solution(file);
    solution.generatePath();
    solution.ILS(1000);
    // solution.visualiseGraph();
    solution.chooseBestResult("Answers_GHA/" + testName, "Answers_GHA/" + testName + "ans");
}

int main() {
    test_mona_1000();
    //test_lu_980();
    //test_ja_1000();
    //test_random_1();
    //test_random_2();
    //test_random_3();

    //test1();


}

