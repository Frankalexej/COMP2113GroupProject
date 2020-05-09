#include "GameMediator.h"

GameMediator::GameMediator() :isTurn(true), AMoney(0), BMoney(0) {}
GameMediator::GameMediator(bool isTurn, int AMoney, int BMoney) :isTurn(isTurn), AMoney(AMoney), BMoney(BMoney) {}
int GameMediator::getMoney()
{
	return this->isTurn ? this->AMoney : this->BMoney;
}
void GameMediator::setMoney(int money)
{
	(this->isTurn ? this->AMoney : this->BMoney) = money;
}

void GameMediator::accMoney(int AMoneyAcc, int BMoneyAcc)
{
	this->AMoney += AMoneyAcc;
	this->BMoney += BMoneyAcc;
}

bool GameMediator::nextTurn()
{
	this->isTurn = !this->isTurn;
	return this->isTurn;
}
