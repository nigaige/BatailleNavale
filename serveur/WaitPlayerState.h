#pragma once
class WaitPlayerState : public State
{
public:
	WaitPlayerState(StateEnum val, StateMachine* Stm = nullptr);

	virtual void Start() override;

	virtual void Update() override;
	virtual void End() override;

	bool CheckIfGood();
};

