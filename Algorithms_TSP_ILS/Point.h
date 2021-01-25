#ifndef POINT_H
#define POINT_H

#include <cmath>

class Point {
private:
	int id = -1;
	int x = 0;
	int y = 0;
	int is_passed = 0;
public:
	void setID(int id_) { id = id_; }
	int getID() { return id; }
	void pass() { is_passed = 1; }
	void deletePass() { is_passed = 0; }
	int isPassed() { return is_passed; }
	int isPointCorrect() { return getID() != -1; }
	void setLoc(int x_, int y_) {
		x = x_;
		y = y_;
	}
	double EuclideanDistance(const Point& another) {
		return sqrt(pow(x - another.x, 2) + pow(y - another.y, 2));
	}
};

#endif // !POINT_H

