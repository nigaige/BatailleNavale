#pragma once
class GameManager
{
	StateMachine* stateMachine_;

	//TODO faire un process message pour traiter les messages du jeu



public:
	GameManager();
	virtual ~GameManager();

	StateMachine* GetStateMachine() { return stateMachine_; };

	void Update();

	void ProcessMessage(string msg);
};

