#pragma once
enum StateEnum
{
	Null,
	WaitPlayer,
	StartGame,
	Game,
	EndGame
};


class StateMachine
{
	StateEnum currentState_;
	vector<State*> stateList_;
	GameManager* gameManager_;


public:
	StateMachine(GameManager* gm = nullptr);
	virtual ~StateMachine();

	StateEnum CurrentState() { return currentState_; }
	bool CurrentState(StateEnum t_stateEnum);

	GameManager* GetGameManager() { return gameManager_; }

	void Update(string msg = "", int indexSock = -1);

private:
	void initState();
	
	State* GetState(StateEnum val);
};

