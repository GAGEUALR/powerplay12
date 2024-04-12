#pragma once
#include "iStrategy.h"

class Player;
class BasicAttackStrategy : public iStrategy
{
public:
	BasicAttackStrategy(Player* owner);
	void execute(std::vector <std::unique_ptr<Object>>& objects) override;
};