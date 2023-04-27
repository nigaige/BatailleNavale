#pragma once
class GameInput
{
private:
	int x_;
	int y_;

	int mouseX_;
	int mouseY_;
	bool rightClick_;

	bool leftClick_;

	int currentGrid_;

public:
    GameInput ();
	void x(int x) { x_ = x; };
	int x() { return x_; };
	void y(int y) { y_ = y; };
	int y() { return y_; };
    void swapClick(){rightClick_ = !rightClick_;}
	void rightClick(bool rightClick) { rightClick_ = rightClick; };
	bool rightClick() { return rightClick_; };
	void leftClick(bool leftClick) { leftClick_ = leftClick; }
	bool leftClick() { return leftClick_; }
	int currentGrid() { return currentGrid_; }


	void windowInput();
	void mousePos(sf::RenderWindow* window);

	void checkCurrentGrid();

};
