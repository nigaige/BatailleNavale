#include "GameUtils.h"

WaitPlayerState::WaitPlayerState(StateEnum val, StateMachine* Stm) : State(val, Stm)
{
}

void WaitPlayerState::Update()
{
	if (CheckIfGood())
		stateMachine_->CurrentState(StateEnum::StartGame);
}

void WaitPlayerState::End()
{
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
