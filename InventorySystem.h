#pragma once

#include <string>
#include <vector>
#include <utility>
#include <memory>

struct QueuedItem
{
	QueuedItem(const std::string& name, int quantity)
		: m_name(name),
		m_quantity(quantity)
	{}

	const std::string& m_name;
	const int m_quantity;
};

class ItemBase;
class InventorySystem
{
public:
	InventorySystem();
	~InventorySystem();
	InventorySystem(const InventorySystem&) = delete;
	InventorySystem& operator=(const InventorySystem) = delete;

	void addItem(const std::string& name, int newItemQuantity = 1);
	void removeItem(const std::string& itemName, int quantityToRemove = 1);
	void removeItem(int itemID);
	void update(float deltaTime);


private:
	class ItemFactory;
	const ItemFactory* m_itemFactory;

	std::vector<ItemBase*> m_inventory;
	std::vector<QueuedItem> m_itemQueue;
	std::vector<int> m_itemsToRemove;
	ItemBase* m_currentItemEquipped;
	size_t m_maxInventorySize;
	int m_itemID; //Assign to new items as ID

	ItemBase* getItemInInventory(const std::string& name);
	ItemBase& createItemFromFactory(const std::string& name);
	
	void increaseItemStackQuantity(const std::string& itemName, int& itemQuantityToAdd);
	void decreaseItemStackQuantity(const std::string& itemName, int& itemQuantityToRemove);
	void assignItemToNewSlot(const std::string& newItemName, int& newItemQuantity);
	
	void addItemToQueue(const std::string& itemName, int itemQuantity = 1);
	void addItemFromQueue(const std::string& newItemName, int newItemQuantity);
	void handleItemQueue();
	void handleRemovals();

	void removeItemFromInventory(int itemIDToRemove);

	int getItemCount(const std::string& itemName) const;
	int getTotalItemCount() const { return static_cast<int>(m_maxInventorySize - m_inventory.size()); }
	bool isInventoryFull() const { return m_inventory.size() == m_maxInventorySize; }


	void purgeItems();
};
