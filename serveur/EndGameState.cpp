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
	const char* msg = "F:1";
	char* chr = const_cast<char*>(msg);

	stateMachine_->GetGameManager()->GetServer()->sendClientData(winnerIndex, chr);

	cout << "=> Player " << to_string(winnerIndex) << endl;

	const char* msg2 = "F:0";
	char* chr2 = const_cast<char*>(msg2);

	if (winnerIndex == 1)
		stateMachine_->GetGameManager()->GetServer()->sendClientData(0, chr2);
	else
		stateMachine_->GetGameManager()->GetServer()->sendClientData(1, chr2);
}
