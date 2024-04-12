#include "iStrategy.h"
#include "Player.h"
iStrategy::iStrategy(Player* owner, char commandToActivate, std::string actionName)
	:owner(owner), commandToActivate(commandToActivate), actionName(actionName)
{
}