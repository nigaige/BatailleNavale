#include "GameUtils.h"

StateMachine::StateMachine(GameManager* gm)
{
	gameManager_ = gm;
	initState();
	CurrentState(StateEnum::Null);

	indexWinner_ = -1;

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

void StateMachine::Update(string msg, int indexSock)
{
	if (msg == "")
	{
		GetState(currentState_)->Update();
		return;
	}

	GetState(currentState_)->Update(msg, indexSock);
}

void StateMachine::initState() 
{
	stateList_.push_back(new State(StateEnum::Null));
	stateList_.push_back(new WaitPlayerState(StateEnum::WaitPlayer, this));
	stateList_.push_back(new StartGameState(StateEnum::StartGame, this));
	stateList_.push_back(new StartGameState(StateEnum::Game, this));
	stateList_.push_back(new StartGameState(StateEnum::EndGame, this));
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


void StateMachine::Finish(int indexWinner)
{
	indexWinner_ = indexWinner;
	CurrentState(StateEnum::EndGame);

}