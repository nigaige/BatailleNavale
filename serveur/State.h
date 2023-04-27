#pragma once
class State
{
protected:
	StateEnum statevalue_;
	bool isActive_;

	StateMachine* stateMachine_;

public:
	State(StateEnum val, StateMachine* Stm = nullptr);

	StateEnum StateValue() { return statevalue_; }
	void StateValue(StateEnum val) { statevalue_ = val; }

	bool isActive() { return isActive_; }
	void isActive(bool val) { isActive_ = val; }



	virtual void Start();
	virtual void Update();
	virtual void Update(string msg, int indexSock);
	virtual void End();
};

