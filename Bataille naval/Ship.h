#pragma once

class Ship
{
private:
	int size_;
	bool orientation_;		//TRUE = Vertical /FALSE = Horizontal
	int x_;
	int y_;
public:
	int size()						{ return size_; }
	void size(int size)				{ size_ = size; }
	bool orientation()				{ return orientation_; }
	void orientation(bool orient)	{ orientation_ = orient; }

	void pos(int x, int y) { x_ = x; y_ = y; }
	int x() { return x_; }
	int y() { return y_; }

	Ship(int size);
	virtual ~Ship();
};

