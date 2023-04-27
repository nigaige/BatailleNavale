#pragma once
class GameState : public State
{
	vector<int> playQueue_;

public:
	GameState(StateEnum val, StateMachine* Stm = nullptr);

	virtual void Start();
	virtual void Update(string msg, int indexSock) override;
	virtual void End() override; 

	bool ProcessMessage(string msg, int indexSock);
	bool ProcessMessagePosition(string msg);
	bool ProcessMessageResult(string msg);
	bool ProcessMessageFinish(string msg, int indexSock);
	
	bool PlayerTurn();
	void SendPlayerTurn();



};

