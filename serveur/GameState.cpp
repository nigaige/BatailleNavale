#include "GameUtils.h"

GameState::GameState(StateEnum val, StateMachine* Stm) : State(val, Stm)
{

}

void GameState::Start()
{
	cout << "====== Phase 2 : Lets play ! ======" << endl;


	for (int i = 0; i < stateMachine_->GetGameManager()->GetServer()->GetNBClientConnect(); i++)
	{
		playQueue_.push_back(i);
	}

	cout << "->" << to_string(playQueue_.size()) << "player was connect" << endl;

	for (size_t i = 0; i < playQueue_.size(); i++)
	{
		cout << "=> Player "<< to_string(i) << " is index : " << to_string(playQueue_[i]) << endl;
	}


	SendPlayerTurn();
}

void GameState::Update(string msg, int indexSock)
{
	//cout << "-> Player <<Message enter : " << << endl;

	ProcessMessage(msg, indexSock);
}

void GameState::End()
{
	const char* msg = "P:3";
	char* chr = const_cast<char*>(msg);


	for (int i = 0; i < stateMachine_->GetGameManager()->GetServer()->GetNBClientConnect(); i++)
	{
		stateMachine_->GetGameManager()->GetServer()->sendClientData(i, chr);
	}
}

bool GameState::ProcessMessage(string msg, int indexSock)
{
	string delimiter = ":";

	if (msg.find(delimiter) == -1 )
		return false; // TODO => s'occuper des messages d'erreur (Format non pris en charge)


	string MsgType = msg.substr(0, msg.find(delimiter));

	msg.erase(0, msg.find(delimiter) + delimiter.length());

	if (MsgType == "S" && indexSock == playQueue_[0])
		return ProcessMessagePosition(msg);

	if (MsgType == "R" && indexSock == playQueue_[1])
		return ProcessMessageResult(msg);

	if (MsgType == "T")
		return PlayerTurn();

	if (MsgType == "F")
		return ProcessMessageFinish(msg, indexSock);

	return false; // TODO => s'occuper des messages d'erreur (type de message non reconnu / ce n'est pas au tour de ce joueur)
}

bool GameState::ProcessMessagePosition(string msg)
{
	string delimiter = ",";
	int secu = 0;
	/*
	while (msg.find(delimiter) != -1)
	{
		secu++;
		msg.erase(0, msg.find(delimiter) + delimiter.length());

		if (secu >= 100)
			return false; // TODO => s'occuper des messages d'erreur (boucle infini detecter)
	}*/
	if (secu > 2)
			return false; // TODO => s'occuper des messages d'erreur (Taille de message incorrect)
	msg = "S:" + msg;
	const char* message =  msg.c_str();
	char* chr = const_cast<char*>(message);

	stateMachine_->GetGameManager()->GetServer()->sendClientData(playQueue_[1], chr);

	return true;
}

bool GameState::ProcessMessageResult(string msg)
{
	if (msg.length() > 1)
		return false; // TODO => s'occuper des messages d'erreur (Taille de message incorrect)

	if (msg != "0" && msg != "1")
		return false; // TODO => s'occuper des messages d'erreur (Valeur Incorrect)
	msg = "R:" + msg;

	const char* message = msg.c_str();
	char* chr = const_cast<char*>(message);

	stateMachine_->GetGameManager()->GetServer()->sendClientData(playQueue_[0], chr);
	PlayerTurn();

	return true;
}

bool GameState::ProcessMessageFinish(string msg, int indexSock)
{

	if (msg.length() > 1)
		return false; // TODO => s'occuper des messages d'erreur (Taille de message incorrect)

	if (msg != "-1" && msg != "0" && msg != "1")
		return false; // TODO => s'occuper des messages d'erreur (Valeur Incorrect)

	if (msg == "1") 
	{
		stateMachine_->Finish(indexSock);
		return true;
	}

	if (msg == "0")
	{
		if (indexSock == 0)
		{
			stateMachine_->Finish(1);
			return true;
		}
		else
		{
			stateMachine_->Finish(0);
			return true;
		}
	}
	return true;
}

bool GameState::PlayerTurn()
{
	int lastPlayer = playQueue_[0];
	playQueue_.erase(playQueue_.begin());
	playQueue_.push_back(lastPlayer);

	//SendPlayerTurn();
	return true;
}

void GameState::SendPlayerTurn()
{
	//P1
	const char* msg = "T:1";
	char* chr = const_cast<char*>(msg);

	stateMachine_->GetGameManager()->GetServer()->sendClientData(playQueue_[0], chr);
	
	//P2
	const char* msg2 = "T:0";
	char* chr2 = const_cast<char*>(msg2);
	stateMachine_->GetGameManager()->GetServer()->sendClientData(playQueue_[1], chr2);
}


