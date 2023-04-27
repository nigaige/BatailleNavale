#pragma once
class GameManager
{
	StateMachine* stateMachine_;

	vector<SOCKET> ClientSocket_;
	Server* server_;

	//TODO faire un process message pour traiter les messages du jeu



public:
	GameManager(){
		stateMachine_ = new StateMachine(this);
	};
	GameManager(Server* serv);
	virtual ~GameManager();

	StateMachine* GetStateMachine() { return stateMachine_; };
	Server* GetServer() { return server_; }
	void setServer(Server* serv) { server_ = serv; }

	void Update(string msg, int indexSock);


};

