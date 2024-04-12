#include "HealStrategy.h"
#include "Player.h"
#include <iostream>
HealStrategy::HealStrategy(Player* owner)
	:iStrategy(owner, 'h', "(h)eal")
{
}

void HealStrategy::execute(std::vector<std::unique_ptr<Object>>& objects)
{
	system("CLS");
	Object::nameOnly = true;
	if (owner->cast(2))
	{
		std::normal_distribution<double> randomHeal(owner->getStrength() * 2.0, 20.0 * (1.0 / owner->getLevel()));
		int  amountHealed{ std::max(1, (int)randomHeal(Object::engine)) };

		std::cout << *owner << " is healed by " << amountHealed << "hp!" << std::endl;
		owner->heal(amountHealed);
	}

}
