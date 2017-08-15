#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <numeric>
using namespace std;
const double pi = 3.14159265358979323846;
double epsilon = 1e-12;

struct Point {
	int x;
	int y;
};



class Circle {
public:
	Circle() {};
	Circle(Point center, int radius);
	bool isInside(Point point);
private:
	Point center;
	int radius;
};

Circle::Circle(Point center, int radius) {
	this->center.x = center.x;
	this->center.y = center.y;
	this->radius = radius;
}

bool Circle::isInside(Point point) {
	vector<double> center_to_point(2); // Where .at(0) is x and .at(1) is y
	double norm;

	if (point.x == this->center.x && point.y == this->center.y) {
		return true;
	}

	center_to_point.at(0) = point.x - this->center.x;
	center_to_point.at(1) = point.y - this->center.y;
	norm = sqrt(inner_product(center_to_point.begin(), center_to_point.end(), center_to_point.begin(), 0.0));
	if (norm <= radius + epsilon) {
		return true;
	}
	else {
		return false;
	}
}

class Square {
public:
	Square(Point corner1, Point corner3);
	Square() {};
	bool isInside(Point point);
private:
	Point corner1;
	Point corner3;
	double side_length;
	bool checkOneCorner(Point point, Point from_corner, Point opposite_corner);
};



Square::Square(Point corner1, Point corner3) {
	this->corner1 = corner1;
	this->corner3 = corner3;
	
	double diagonal_length = sqrt(pow(corner3.y - corner1.y, 2) + pow(corner3.x - corner1.x, 2));
	this->side_length = diagonal_length / sqrt(2);
}



// Checks if a point is inside the square by checking if the vector made from each of the corners
// to the point are within 45 degrees of the diagonal, and the magnitude of the vector is less
// than or equal to the length of the sides of the square.
bool Square::isInside(Point point) {
	if (checkOneCorner(point, this->corner1, this->corner3) || checkOneCorner(point, this->corner3, this->corner1)) {
		return true;
	}
	else {
		return false;
	}
}

bool Square::checkOneCorner(Point point, Point from_corner, Point opposite_corner) {
	vector<double> diagonal_vector(2); // Where .at(0) is x direction and .at(1) is y direction.
	vector<double> point_vector(2);
	double norm_diagonal_vector;
	double norm_point_vector;
	double angle_radians;
	double dot_product;
	double right_side;

	if (point.x == from_corner.x && point.y == from_corner.y) { // If the point we are looking at is a corner of the square, then it is part of the square.
		return true;
	}

	diagonal_vector.at(0) = opposite_corner.x - from_corner.x; // Vector from from_corner to opposite_corner
	diagonal_vector.at(1) = opposite_corner.y - from_corner.y;

	point_vector.at(0) = point.x - from_corner.x; // Vector from from_corner to point
	point_vector.at(1) = point.y - from_corner.y;

	// Calculate norm (magnitude) of vector by taking square root of dot product with itself
	norm_diagonal_vector = sqrt(inner_product(diagonal_vector.begin(), diagonal_vector.end(), diagonal_vector.begin(), 0.0));

	norm_point_vector = sqrt(inner_product(point_vector.begin(), point_vector.end(), point_vector.begin(), 0.0));

	// Definition of dot product (inner_product), where '.' stand for dot product
	// cos(angle) = ( vector1 . vector2 )/ (norm(vector1) * norm(vector2) Therefore:

	dot_product = inner_product(point_vector.begin(), point_vector.end(), diagonal_vector.begin(), 0.0);

	right_side = dot_product / (norm_diagonal_vector * norm_point_vector);

	angle_radians = acos(right_side);

	// If the point_vector is within 45 degrees (pi / 4 radians) of the diagonal_vector, and the length of the vector
	// is less than or equal to the length of the side of the square, then the point is inside the square
	if (angle_radians <= pi / 4 + epsilon && norm_point_vector <= side_length + epsilon) {
		return true;
	}
	else {
		return false;
	}
}

class Canvas {
public:
	void drawSquare();
	void drawCircle();
	void printCanvas();
	Canvas(istream& istream);
private:
	vector<vector<bool> >::iterator row;
	vector<bool>::iterator column;
	vector<vector<bool> > canvas;
	int width;
	int height;
	Square square;
	Circle circle;
};

void Canvas::drawSquare() {
	Point point;

	for (size_t row = 0; row < canvas.size(); row++) {
		point.y = row;
		for (size_t column = 0; column < canvas.at(row).size(); column++) {
			point.x = column;
			if (this->square.isInside(point)) {
				canvas[row][column] = true;
			}
		}
	}
}

void Canvas::drawCircle() {
	Point point;

	for (size_t row = 0; row < canvas.size(); row++) {
		point.y = row;
		for (size_t column = 0; column < canvas.at(row).size(); column++) {
			point.x = column;
			if (this->circle.isInside(point)) {
				canvas[row][column] = true;
			}
		}
	}
}

void Canvas::printCanvas() {
	for (row = canvas.begin(); row < canvas.end(); row++) {
		for (column = row->begin(); column < row->end(); column++) {
			if (*column) {
				cout << "##";
			}
			else {
				cout << "..";
			}

		}
		cout << '\n';
	}
}

Canvas::Canvas(istream& istream) {
	Point center_circle;
	int radius;
	Point corner1;
	Point corner3;

	istream >> this->width >> this->height // I scream for istream
		>> center_circle.x >> center_circle.y >> radius
		>> corner1.x >> corner1.y >> corner3.x >> corner3.y;


	this->canvas.resize(this->height);

	for (auto &i : canvas) {
		i.resize(this->width);
	}

	for (row = canvas.begin(); row < canvas.end(); row++) {
		for (column = row->begin(); column < row->end(); column++) {
			*column = false;
		}
	}

	this->square = Square(corner1, corner3); // Not sure if this is a memory leak or not
	this->circle = Circle(center_circle, radius);
}

int main() {
	ifstream f;
	f.open("input.txt");
	int n;

	f >> n;
	for (int i = 0; i < n; i++) {
		Canvas canvas(f);
		canvas.drawSquare();
		canvas.drawCircle();
		canvas.printCanvas();
	}


	return 0;
}



