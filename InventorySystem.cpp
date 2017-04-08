#include "InventorySystem.h"
#include "ItemBase.h"
#include "ItemType.h"
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <functional>
#include <unordered_map>


class InventorySystem::ItemFactory
{
public:
	ItemFactory(InventorySystem* inventorySystem)
	{
		registerItem("Fire Sword", ItemType::Weapon, 1);
		registerItem("Great Axe", ItemType::Weapon, 1);
		registerItem("Arrow", ItemType::Projectile, 25);
		registerItem("Healing Potion", ItemType::Consumable, 5);
		registerItem("Mana Potion", ItemType::Consumable, 5);
	}

	ItemBase& createItem(const std::string& name, int ID, int quantity = 1) const
	{
		auto cIter = m_items.find(name);
		if (cIter != m_items.cend())
		{
			return *cIter->second(ID, quantity);
		}
	}

private:
	std::unordered_map<std::string, std::function<ItemBase*(int ID, int quantity)>> m_items;

	void registerItem(const std::string& itemName, ItemType type, int maxQuantity, int quantity = 1)
	{
		//Potentially load from file item attributes here
		//Load in attributes to item constructor
		if (m_items.find(itemName) != m_items.cend()) { return; }
		m_items.emplace(itemName, [&itemName, type, quantity, maxQuantity](int ID, int quantity) -> ItemBase*
		{
			//Using raw pointers here because I am unsure on how to do this with smart pointers
			return new ItemBase(ID, itemName, type, quantity, maxQuantity);
		});
	}

};

InventorySystem::InventorySystem()
	: m_inventory(),
	m_currentItemEquipped(nullptr),
	m_maxInventorySize(static_cast<size_t>(8)),
	m_itemID(0)
{
}

InventorySystem::~InventorySystem()
{
	purgeItems();
}

void InventorySystem::addItem(const std::string & newItemName, int newItemQuantity)
{
	if (isInventoryFull()) { return; }
	if (newItemQuantity <= 0) { return; }
	//Attempt to stack new Item on already existing items in inventory
	increaseItemStackQuantity(newItemName, newItemQuantity);
	while (newItemQuantity)
	{
		//Create new Item in a new slot
		addItemToQueue(newItemName, newItemQuantity);
		//assignItemToNewSlot(newItemName, newItemQuantity);
		//Attempt to stack item with additional quantities
		increaseItemStackQuantity(newItemName, newItemQuantity);

		if (isInventoryFull()) { break; }
	}
}

void InventorySystem::removeItem(const std::string & itemName, int quantityToRemove)
{
	if (quantityToRemove <= 0) { return; } //Nothing to remove

	for (auto& item : m_inventory)
	{
		if (!quantityToRemove) { break; }
		if (item->getName() != itemName) { continue; }

		item->decreaseQuantity(quantityToRemove);
		if (!item->getQuantity())
		{
			removeItem(item->getID());
		}
	}
}

void InventorySystem::removeItem(int itemIDToRemove)
{
	//Check requested item to remove isn't already queue'd
	auto cIter = std::find_if(m_itemsToRemove.cbegin(), m_itemsToRemove.cend(), [itemIDToRemove](auto& itemID) {return itemID == itemIDToRemove; });
	if (cIter == m_itemsToRemove.cend())
	{
		m_itemsToRemove.push_back(itemIDToRemove);
	}
}

void InventorySystem::update(float deltaTime)
{
	for (auto& item : m_inventory)
	{
		item->update(deltaTime);
	}

	handleItemQueue();
	handleRemovals();
}

ItemBase * InventorySystem::getItemInInventory(const std::string & name)
{
	auto iter = std::find_if(m_inventory.begin(), m_inventory.end(), [&name](auto& item) { return item->m_name == name; });
	return (iter != m_inventory.end() ? *iter : nullptr);
}

ItemBase & InventorySystem::createItemFromFactory(const std::string & name)
{
	auto& item = m_itemFactory->createItem(name, m_itemID);
	++m_itemID;

	return item;
}

void InventorySystem::increaseItemStackQuantity(const std::string & itemName, int& itemQuantityToAdd)
{
	if (itemQuantityToAdd <= 0) { return; }
	for (auto& item : m_inventory)
	{
		if (!itemQuantityToAdd) { return; }
		if (item->getName() != itemName) { continue; }
	
		item->increaseQuantity(itemQuantityToAdd);
	}
}

void InventorySystem::decreaseItemStackQuantity(const std::string & itemName, int & itemQuantityToRemove)
{
	if (itemQuantityToRemove <= 0) { return; }
	for (auto& item : m_inventory)
	{
		if (!itemQuantityToRemove) { break; }
		if (item->getName() != itemName) { continue; }

		item->decreaseQuantity(itemQuantityToRemove);
		if (!item->getQuantity()) { removeItem(item->getID()); }
	}
}

void InventorySystem::assignItemToNewSlot(const std::string & newItemName, int & newItemQuantity)
{
	auto& item = createItemFromFactory(newItemName);
	if (m_inventory.size() < m_maxInventorySize)
	{	
		m_inventory.push_back(&item);
		--newItemQuantity;
	}
	else {
		std::cerr << "Inventory is full.\n";
	}
}

void InventorySystem::addItemFromQueue(const std::string & newItemName, int newItemQuantity)
{
	auto& item = m_itemFactory->createItem(newItemName, m_itemID);
	
}

void InventorySystem::handleItemQueue()
{
	for (const auto& item : m_itemQueue)
	{
		addItemFromQueue(item.m_name, item.m_quantity);
	}

	m_itemQueue.clear();
}

void InventorySystem::handleRemovals()
{
	for (const int itemID : m_itemsToRemove)
	{
		removeItem(itemID);
	}

	m_itemsToRemove.clear();
}

void InventorySystem::addItemToQueue(const std::string & itemName, int itemQuantity)
{
	m_itemQueue.emplace_back(itemName, itemQuantity);
}

void InventorySystem::removeItemFromInventory(int itemID)
{
	//Item must always be found to be erased
	auto iter = std::find_if(m_inventory.begin(), m_inventory.end(), [itemID](auto& item) { return item->m_ID == itemID; });
	if (iter != m_inventory.cend())
	{
		delete *iter;
		*iter = nullptr;
		m_inventory.erase(iter);
	}
}

int InventorySystem::getItemCount(const std::string & itemName) const
{
	//Get total number of items in inventory
	int itemCount = 0;
	for (const auto& item : m_inventory)
	{
		if (item->getName() == itemName)
		{
			++itemCount;
		}
	}

	return itemCount;
}

void InventorySystem::purgeItems()
{
	for (auto& item : m_inventory)
	{
		delete item;
		item = nullptr;
	}

	m_inventory.clear();
}
