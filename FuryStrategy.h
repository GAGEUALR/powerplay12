#pragma once
#include "iStrategy.h"

class Player;
class FuryStrategy : public iStrategy
{
public:
	FuryStrategy(Player* owner);
	void execute(std::vector <std::unique_ptr<Object>>& objects) override;
};