#include <random>
#include <iostream>
#include "Player.h"
#include "Monster.h"
#include "StrategyList.h"


Player::Player(const Player& src) noexcept :
	Object(src.name, src.strength, src.health, src.level),
	SP{ src.SP }
{
	for (const auto& currItem : src.inventory)
	{
		inventory[currItem.first] =
			std::make_unique<Item>
			(currItem.second->getClassification(), currItem.second->getBonusValue());
	}
}

Player::Player(Player&& src) noexcept :
	Object(src.name, src.strength, src.health, src.level),
	inventory{ std::move(src.inventory) },
	SP{ src.SP }
{
}

Player& Player::operator=(const Player& src) noexcept
{
	inventory.clear();
	for (const auto& currItem : src.inventory)
	{
		inventory[currItem.first] =
			std::make_unique<Item>
			(currItem.second->getClassification(), currItem.second->getBonusValue());
	}
	name = src.name;
	strength = src.strength;
	health = src.health;
	level = src.level;
	SP = src.SP;
	return *this;
}

Player& Player::operator=(Player&& src) noexcept
{
	inventory.clear();
	name = src.name;
	strength = src.strength;
	health = src.health;
	level = src.level;
	inventory = std::move(src.inventory);
	SP = src.SP;
	return *this;

}

Player::Player() :Object(Object::Type::player, 0, 1, 0)
{
	levelUp();
}



void Player::levelUp()
{
	level++;
	switch (level)
	{
	case 1:
		abilities.emplace(std::make_unique<BasicAttackStrategy>(this));
		break;
	case 2:
		abilities.emplace(std::make_unique<HealStrategy>(this));
		break;
	case 3:
		abilities.emplace(std::make_unique<FuryStrategy>(this));
		break;
	}
	std::normal_distribution<double> randomHealth(20.0 + (long long)level * 5, 5.0);
	health += std::max(1, (int)randomHealth(engine));

	std::normal_distribution<double> randomStrength(3.0 + level, 1.0);
	strength += std::max(1, (int)randomStrength(engine));
	SP += std::max(1, (int)randomStrength(engine));

	//grab new item.
	std::uniform_int_distribution<int> randomItem(0, (int)Item::Type::numTypes - 1);
	std::normal_distribution<double> randomBonus((double)level, (double)level / 2);
	std::unique_ptr<Item> found{ std::make_unique<Item>((Item::Type)randomItem(engine), std::max(1, (int)randomBonus(engine)))} ;

	std::cout << "You found a " << *found << "!!!!" << std::endl;
	if (
		auto haveOne{ inventory.find(found->getClassification()) };
		haveOne == inventory.end()
		|| (*inventory[found->getClassification()]) < *found
		)
	{
		std::cout << "You keep the shiny new toy!" << std::endl;
		inventory.insert_or_assign(found->getClassification(), std::move(found));

	}
	else
	{
		std::cout << "You toss aside the ugly old thing!" << std::endl;
	}
}

void Player::update(std::vector<std::unique_ptr<Object>>& objects)
{
	
	if (objects.size() == 1)
	{
		levelUp();
		return;
	}
	std::cout << "What do you do? ";

	for (const auto& ability : abilities)
	{
		std::cout << ability->actionName;
		std::cout << " ";
	}
	std::cout << " : ";
	char command{ 'x' };
	std::cin >> command;
	for (auto& ability : abilities)
	{
		if (ability->commandToActivate == command)
		{
			ability->execute(objects);
		}
	}
	
}


int Player::attack() const
{
	if (auto sword{ inventory.find(Item::Type::sword) }; sword != inventory.end())
	{
		return damageDone(sword->second->getBonusValue());
	}
	else
	{
		return damageDone(0);
	}
}

void Player::defend(int damage)
{
	int AC{ 0 };
	if (auto armor{ inventory.find(Item::Type::armor) }; armor != inventory.end())
	{
		AC += *(armor->second);
	}
	if (auto shield{ inventory.find(Item::Type::shield) }; shield != inventory.end())
	{
		AC += *(shield->second);
	}
	damageTaken(damage, AC);
}


void Player::print(std::ostream& o) const
{
	if (nameOnly) Object::print(o);
	else
	{
		o << "L:" << getLevel() << " ";
		Object::print(o);
		o << " h:" << getHealth() << ", SP:" << SP << std::endl;
		o << inventory;
	}
}

bool Player::cast(int cost)
{
	if (cost < SP)
	{
		SP -= cost;
		return true;
	}
	else
	{
		std::cout << "Not enough SP!!!" << std::endl;
		return false;
	}
}

std::ostream& operator<<(std::ostream& o, const std::map<Item::Type, std::unique_ptr<Item>>& src)
{
	for(const auto& itemIter : src )
		{
			o << "  " << *itemIter.second << std::endl;
		};
	return o;
}


