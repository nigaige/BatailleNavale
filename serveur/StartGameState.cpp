#include "GameUtils.h"

StartGameState::StartGameState(StateEnum val, StateMachine* Stm) : State(val, Stm)
{
	
}

void StartGameState::Update(string msg, int indexSock)
{
	if (CheckIfReady(msg, indexSock))
		stateMachine_->CurrentState(StateEnum::StartGame);

}

void StartGameState::End()
{
	char msg('P:2');

	for (int i = 0; i < readyIndexSocket_.size(); i++)
	{
		stateMachine_->GetGameManager()->GetServer()->sendClientData(i, &msg);
	}

}

bool StartGameState::CheckIfReady(string msg, int indexSock)
{
	if (readyIndexSocket_.size() > 0 || find(readyIndexSocket_.begin(), readyIndexSocket_.end(), indexSock) != readyIndexSocket_.end())
		return false;

	string delimiter = ":";
	string MsgType = msg.substr(0, msg.find(delimiter));

	if (MsgType != "R")
		return false;

	msg.erase(0, msg.find(delimiter) + delimiter.length());

	delimiter = ",";
	if (msg.find(delimiter) == -1)
		return false;

	if (msg == "0")
		return false;
	
	readyIndexSocket_.push_back(indexSock);

	if (readyIndexSocket_.size() != stateMachine_->GetGameManager()->GetServer()->GetNBClientConnect())
		return false;
	

	return true;
}
