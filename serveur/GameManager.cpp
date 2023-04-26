#include "GameUtils.h"

GameManager::GameManager() 
{
	stateMachine_ = new StateMachine();

}

GameManager::~GameManager() 
{
	stateMachine_ = nullptr;
}

void GameManager::Update()
{
	stateMachine_->Update();
}

void GameManager::ProcessMessage(string msg)
{
	switch (msg)
	{
	default:
		break;
	}
}


