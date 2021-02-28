#pragma once

class Point
{
public:
	Point(int x, int y);

public:
	int getX();
	int getY();

	void setX(int x);
	void setY(int y);

private:
	int x = 0;
	int y = 0;
};