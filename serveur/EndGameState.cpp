#include "GameUtils.h"

EndGameState::EndGameState(StateEnum val, StateMachine* Stm) : State(val, Stm)
{
}

void EndGameState::Start()
{
	cout << "====== Finish ! ======" << endl;
	//cout << "=> Player " << to_string() << endl;

	SendFinishMessage(stateMachine_->IndexWinner());
}


void EndGameState::SendFinishMessage(int winnerIndex)
{
	char win = 'F:1';
	stateMachine_->GetGameManager()->GetServer()->sendClientData(winnerIndex, &win);

	cout << "=> Player " << to_string(winnerIndex) << endl;

	char lose = 'F:0';
	if (winnerIndex == 1)
		stateMachine_->GetGameManager()->GetServer()->sendClientData(0, &lose);
	else
		stateMachine_->GetGameManager()->GetServer()->sendClientData(1, &lose);
}
