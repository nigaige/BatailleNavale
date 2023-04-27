#pragma once
class GameState : public State
{
	vector<int> playQueue_;

public:
	GameState(StateEnum val, StateMachine* Stm = nullptr);

	virtual void Update(string msg, int indexSock) override;
	virtual void End() override; 

	bool ProcessMessage(string msg, int indexSock);
	bool ProcessMessagePosition(string msg, int indexSock);
	bool ProcessMessageResult(string msg, int indexSock);
};

