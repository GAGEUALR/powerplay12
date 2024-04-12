#include "BasicAttackStrategy.h"
#include <iostream>
#include "Player.h"
BasicAttackStrategy::BasicAttackStrategy(Player* owner)
	:iStrategy(owner, 'a', "(a)ttack")
{
}

void BasicAttackStrategy::execute(std::vector<std::unique_ptr<Object>>& objects)
{

	int monsterNum{ 1 };
	if (objects.size() > 2)
	{
		std::cout << "Which Monster? (";
		for (unsigned int i = 1; i < objects.size(); i++)
		{
			std::cout << i;
			if (i < objects.size() - 1) std::cout << ", ";
		}
		std::cout << "): ";
		std::cin >> monsterNum;
	}
	if (monsterNum >= 1 && monsterNum < objects.size())
	{
		Object::nameOnly = true;
		system("CLS");
		std::cout << "**************FIGHT*****************" << std::endl;
		std::cout << *owner << " Attacks ";
		std::cout << *objects.at(monsterNum) << "!!\n";
		objects[monsterNum]->defend(owner->attack());
	}
}
