#pragma once
class EndGameState : public State
{
public:
	EndGameState(StateEnum val, StateMachine* Stm = nullptr);

	virtual void Start() override;

	void SendFinishMessage(int winnerIndex);
};

