#include "GameUtils.h"

State::State(StateEnum val, StateMachine* Stm)
{
	stateMachine_ = Stm;
	statevalue_ = val;
	isActive_ = false;
}

void State::Start()
{
}

void State::Update()
{
}


void State::Update(string msg, int indexSock)
{
}

void State::End()
{
}
