#pragma once

class Ship
{
private:
	int size_ = 0;
	bool orientation_ = false;		//TRUE = Vertical /FALSE = Horizontal
	int x_ = 0;
	int y_ = 0;
public:
	int size()						{ return size_; }
	void size(int size)				{ size_ = size; }
	bool orientation()				{ return orientation_; }
	void orientation(bool orient)	{ orientation_ = orient; }

	void pos(int x, int y) { x_ = x; y_ = y; }
	int x() { return x_; }
	int y() { return y_; }

	Ship();
	virtual ~Ship();
};

