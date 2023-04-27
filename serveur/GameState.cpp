#include "GameUtils.h"

GameState::GameState(StateEnum val, StateMachine* Stm) : State(val, Stm)
{
	for (int i = 0; i < stateMachine_->GetGameManager()->GetServer()->GetNBClientConnect(); i++)
	{
		playQueue_.push_back(i);
	}
}

void GameState::Update(string msg, int indexSock)
{
}

void GameState::End()
{
	char msg = 'P:3';

	for (int i = 0; i < stateMachine_->GetGameManager()->GetServer()->GetNBClientConnect(); i++)
	{
		stateMachine_->GetGameManager()->GetServer()->sendClientData(i, &msg);
	}
}

bool GameState::ProcessMessage(string msg, int indexSock)
{
	string delimiter = ":";
	string MsgType = msg.substr(0, msg.find(delimiter));

	msg.erase(0, msg.find(delimiter) + delimiter.length());

	if (MsgType != "S")
		ProcessMessagePosition(msg, indexSock);

	if (MsgType != "R")
		ProcessMessageResult(msg, indexSock);

	return true;
}

bool GameState::ProcessMessagePosition(string msg, int indexSock)
{
	return true;
}

bool GameState::ProcessMessageResult(string msg, int indexSock)
{
	return true;
}
