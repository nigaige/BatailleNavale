#include "GameUtils.h"

WaitPlayerState::WaitPlayerState(StateEnum val, StateMachine* Stm) : State(val, Stm)
{
}

#ifdef DEBUG
	void WaitPlayerState::Start()
	{
		cout << "====== WAIT CONNECTION ======" << endl;
	}
#endif // DEBUG

void WaitPlayerState::Update()
{
	if (CheckIfGood()) 
	{
#ifdef DEBUG
		cout << "-> A Player was connect !" << endl;
#endif // DEBUG
		stateMachine_->CurrentState(StateEnum::StartGame);
	}
}

void WaitPlayerState::End()
{
#ifdef DEBUG
	cout << "=> Lobby is full ! \n" << endl;
#endif // DEBUG

	const char* msg = "P:1";
	char* chr = const_cast<char*>(msg);


	for (int i = 0; i < stateMachine_->GetGameManager()->GetServer()->GetNBClientConnect(); i++)
	{
		stateMachine_->GetGameManager()->GetServer()->sendClientData(i, chr);
	}

}

bool WaitPlayerState::CheckIfGood()
{
	int nbMaxClient = stateMachine_->GetGameManager()->GetServer()->maxClient();
	int nbClientConnect = stateMachine_->GetGameManager()->GetServer()->GetNBClientConnect();

	return nbMaxClient == nbClientConnect;
}
