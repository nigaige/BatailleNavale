#pragma once
enum StateEnum
{
	Null,
	WaitPlayer,
	StartGame,
};


class StateMachine
{
	StateEnum currentState_;
	vector<State*> stateList_;

public:
	StateMachine();
	virtual ~StateMachine();

	StateEnum CurrentState() { return currentState_; }
	bool CurrentState(StateEnum t_stateEnum);

	void Update();

private:
	void initState();
	
	State* GetState(StateEnum val);
};

