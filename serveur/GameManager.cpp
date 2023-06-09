#include "Utils.h"
#include "GameUtils.h"

GameManager::GameManager(Server* serv)
{
	server_ = serv;
	stateMachine_ = new StateMachine(this);
	//server_->socketEvent(Update);
}

GameManager::~GameManager() 
{
	delete stateMachine_;
}

void GameManager::Update(string msg, int indexSock)
{
	stateMachine_->Update(msg, indexSock);
}


