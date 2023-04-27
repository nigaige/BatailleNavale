#pragma once
class GameManager
{
	StateMachine* stateMachine_;

	vector<SOCKET> ClientSocket_;
	Server* server_;

	//TODO faire un process message pour traiter les messages du jeu



public:

	GameManager(Server* serv);
	virtual ~GameManager();

	StateMachine* GetStateMachine() { return stateMachine_; };
	Server* GetServer() { return server_; }

	void Update(string msg, int indexSock);


};

