#include "GameUtils.h"

State::State(StateEnum val)
{
	statevalue_ = val;
	isActive_ = false;
}

void State::Start()
{
}

void State::Update()
{
}


void State::End()
{
}
