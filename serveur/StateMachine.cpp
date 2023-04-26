#include "GameUtils.h"

StateMachine::StateMachine() 
{
	initState();
	CurrentState(StateEnum::Null);
}

StateMachine::~StateMachine() 
{
}


bool StateMachine::CurrentState(StateEnum t_stateEnum)
{
	State* curState = GetState(currentState_);
	if (!curState)
	{
		return false;
	}
	curState->End();

	curState = GetState(t_stateEnum);
	if (!curState)
	{
		return false;
	}

	currentState_ = t_stateEnum;
	curState->Start();

	return true;
}

void StateMachine::Update()
{
	GetState(currentState_)->Update();
}

void StateMachine::initState() 
{
	stateList_.push_back(new State(StateEnum::Null));
	stateList_.push_back(new WaitPlayerState(StateEnum::WaitPlayer));
	stateList_.push_back(new StartGameState(StateEnum::StartGame));
}

State* StateMachine::GetState(StateEnum val)
{
	for (int i = 0; i < stateList_.size(); i++)
	{
		if (stateList_[i]->StateValue() == val)
		{
			return stateList_[i];
		}
	}
	cout << "State not found ! " << endl;
	return nullptr;
}
