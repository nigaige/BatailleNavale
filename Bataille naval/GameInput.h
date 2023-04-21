#pragma once
class GameInput
{
private:
	int x_;
	int y_;
	bool rightClick_;

public:
    GameInput ();
	void x(int x) { x_ = x; };
	int x() { return x_; };
	void y(int y) { y_ = y; };
	int y() { return y_; };
    void swapClick(){rightClick_ = !rightClick_;}
	void rightClick(bool rightClick) { rightClick_ = rightClick; };
	bool rightClick() { return rightClick_; };
	void windowInput(int x, int y, int WinX = WINDOWSIZE_X, int winY = WINDOWSIZE_Y);
};
