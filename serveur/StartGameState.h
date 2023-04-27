#pragma once
class StartGameState : public State
{
	vector<int> readyIndexSocket_;
public:
	StartGameState(StateEnum val, StateMachine* Stm = nullptr);

	virtual void Update(string msg, int indexSock) override;
	virtual void End() override;

	bool CheckIfReady(string msg, int indexSock);
	
};

