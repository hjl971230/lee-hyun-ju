#include<iostream>

using namespace std;

class Point
{
	int x;
	int y;
public:
	Point(int _x = 0, int _y = 0) :x(_x), y(_y) {}
	void Print();
	Point operator +(Point);
	Point operator -(Point);
	Point operator *(Point);
	Point operator /(Point);
	bool operator <(Point);
	bool operator <=(Point);
	void operator +();
	void operator -();
	bool operator !();
	Point& operator &();
	Point* operator *();
};

void Point::Print()
{
	cout << "x : " << x << ", y : " << y << endl;
}

Point Point::operator+(Point p)
{
	Point _point;
	_point.x = this->x + p.x;
	_point.y = this->y + p.y;
	return _point;
}

Point Point::operator-(Point p)
{
	Point _point;
	_point.x = this->x - p.x;
	_point.y = this->y - p.y;
	return _point;
}

Point Point::operator*(Point p)
{
	Point _point;
	_point.x = this->x * p.x;
	_point.y = this->y * p.y;
	return _point;
}

Point Point::operator/(Point p)
{
	Point _point;
	if(this->x > 0) _point.x = this->x / p.x;
	if(this->y > 0) _point.y = this->y / p.y;
	return _point;
}

bool Point::operator <(Point p)
{
	if (this->x < p.x && this->y < p.y) return true;
	else return false;
}

bool Point::operator <=(Point p)
{
	if (this->x <= p.x && this->y <= p.y) return true;
	else return false;
}

void Point::operator +()
{
	this->x *= 1;
	this->y *= 1;
}

void Point::operator -()
{
	this->x *= -1;
	this->y *= -1;
}

bool Point::operator !()
{
	if (this == EMPTY)
		return true;
	else return false;
}

Point& Point::operator &()
{
	return (*this);
}

Point* Point::operator *()
{
	return this;
}

void main()
{
	Point p1(10, 20);
	Point p2(5, 5);
	Point p3;

	p3 = p1 + p2;
	p3.Print();

	-p1;
	+p2;

	p1.Print();
	p2.Print();

	Point& pp1 = &p1;
	Point* pp2 = *p2;
	Point* pp3 = EMPTY;

	cout << !pp3 << endl;

	pp1.Print();
	pp2->Print();
}