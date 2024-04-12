#pragma once
#include "iStrategy.h"

class Player;
class HealStrategy : public iStrategy
{
public:
	HealStrategy(Player* owner);
	void execute(std::vector <std::unique_ptr<Object>>& objects) override;
};