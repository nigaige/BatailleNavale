#pragma once
class State
{
protected:
	StateEnum statevalue_;
	bool isActive_;

public:
	State(StateEnum val);

	StateEnum StateValue() { return statevalue_; }
	void StateValue(StateEnum val) { statevalue_ = val; }

	bool isActive() { return isActive_; }
	void isActive(bool val) { isActive_ = val; }



	virtual void Start();
	virtual void Update();
	virtual void End();
};

