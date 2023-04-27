#pragma once
class WaitPlayerState : public State
{
public:
	WaitPlayerState(StateEnum val, StateMachine* Stm = nullptr);

#ifdef DEBUG
	virtual void Start() override;
#endif // DEBUG

	virtual void Update() override;
	virtual void End() override;

	bool CheckIfGood();
};

