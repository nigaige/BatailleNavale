#include "GameUtils.h"

StartGameState::StartGameState(StateEnum val, StateMachine* Stm) : State(val, Stm)
{
	
}
void StartGameState::Start()
{
	cout << "====== Phase 1 : Place your boat ! ======" << endl;
}


void StartGameState::Update(string msg, int indexSock)
{
	cout << "-> Player : " << to_string(indexSock) << " is ready !" << endl;

	if (CheckIfReady(msg, indexSock))
	{
		stateMachine_->CurrentState(StateEnum::Game);
	}

}

void StartGameState::End()
{
	cout << "=> All Player was ready !\n" << endl;

	const char* msg = "P:2";
	char* chr = const_cast<char*>(msg);

	for (int i = 0; i < readyIndexSocket_.size(); i++)
	{
		stateMachine_->GetGameManager()->GetServer()->sendClientData(i, chr);
	}

}

bool StartGameState::CheckIfReady(string msg, int indexSock)
{
	string delimiter = ":";
	string MsgType = msg.substr(0, msg.find(delimiter));

	if (MsgType != "R")
		return false;

	msg.erase(0, msg.find(delimiter) + delimiter.length());

	delimiter = ",";
	int a = msg.find(delimiter);
	if (msg.find(delimiter) != -1)
		return false;

	if (msg == "0")
		return false;
	
	readyIndexSocket_.push_back(indexSock);

	if (readyIndexSocket_.size() != stateMachine_->GetGameManager()->GetServer()->GetNBClientConnect())
		return false;
	

	return true;
}
