#pragma once

#include "Timer.h"
#include "ItemType.h"
#include <string>


//VERY rough draft on how items will work
class ItemBase
{
public:
	ItemBase(int ID, const std::string& name, ItemType type, int maxQuantity = 10, int quantity = 1, float cooldownLength = 1.0f);

	int getID() const { return m_ID; }
	const std::string& getName() const { return m_name; }
	ItemType getType() const { return m_type; }
	int getMaxQuantity() const { return m_maxQuantity; }
	int getQuantity() const { return m_quantity; }
	int getValue() const { return m_value; }
	bool fullyStacked() const {}

	void increaseQuantity(int& newItemQuantity);
	void decreaseQuantity(int& quantityToRemove);

	//Could possibly have items inheriting off of this.
	//Use to get the value of item
	//Such as damage, health potion amount/mana potiion amount
	virtual int use();

	void update(float deltaTime);
	
private:
	const int m_ID;
	const std::string m_name;
	const ItemType m_type;
	const int m_maxQuantity; //Item can only be stacked certain number of times
	int m_quantity;
	Timer m_cooldownTimer;
	int m_value; //Value like Damage for weapon, healing power for health potion ETC
};