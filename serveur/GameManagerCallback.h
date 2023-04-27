#pragma once
class ServerCallBack;
class GameManager;
class GameManagerCallback:public ServerCallBack
{
public:
	GameManager* gm_;
	GameManagerCallback(GameManager* gm) { gm_ = gm; }
	void callBack(string msg, int socketEvent) { gm_->Update(msg, socketEvent); }
};

