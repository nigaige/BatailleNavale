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

	int indexWinner_;


public:
	StateMachine(GameManager* gm = nullptr);
	virtual ~StateMachine();

	StateEnum CurrentState() { return currentState_; }
	bool CurrentState(StateEnum t_stateEnum);

	GameManager* GetGameManager() { return gameManager_; }

	int IndexWinner() { return indexWinner_; }

	void Update(string msg = "", int indexSock = -1);

	void Finish(int indexWinner);


private:
	void initState();
	
	State* GetState(StateEnum val);
};

