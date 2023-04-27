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
	char msg = 'P:1';

	for (int i = 0; i < stateMachine_->GetGameManager()->GetServer()->GetNBClientConnect(); i++)
	{
		stateMachine_->GetGameManager()->GetServer()->sendClientData(i, &msg);
	}

}

bool WaitPlayerState::CheckIfGood()
{
	int nbMaxClient = stateMachine_->GetGameManager()->GetServer()->maxClient();
	int nbClientConnect = stateMachine_->GetGameManager()->GetServer()->GetNBClientConnect();

	return nbMaxClient == nbClientConnect;
}
