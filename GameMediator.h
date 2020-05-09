#pragma once
class GameMediator
{
	// GameMediator counts turns and money, it doesn't have access to other objects, therefore, it must accept infos passed in so as for update
	// there will be only one GameMediator in each execution
public:
	int AMoney;
	int BMoney;
	bool isTurn;	// note: true means turn for A, false for B

	GameMediator();	// defaut is A's turn, both no money
	GameMediator(bool isTurn, int AMoney, int BMoney);	// used for recovering from savings

	int getMoney();	// returns AMoney or BMoney, based on the turn
	void setMoney(int money);	// can update money, also based on turn

	void accMoney(int AMoneyAcc, int BMoneyAcc);	// accumulate money, used after each round
	bool nextTurn();	// next turn, just do '!'
};