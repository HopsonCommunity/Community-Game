#include "ItemBase.h"
#include "InventorySystem.h"

ItemBase::ItemBase(int ID, const std::string & name, ItemType type, int maxQuantity, int quantity, float cooldownLength)
	:	m_ID(ID),
	m_name(name),
	m_type(type),
	m_quantity(quantity),
	m_maxQuantity(maxQuantity),
	m_cooldownTimer()
{
	m_cooldownTimer.setExpirationTime(cooldownLength);
}


int ItemBase::use()
{
	if (m_cooldownTimer.isActive()) { return 0; }
	m_cooldownTimer.activate();
	return m_value;
}

void ItemBase::update(float deltaTime)
{
	if (m_cooldownTimer.isActive())
	{
		m_cooldownTimer.update(deltaTime);
		if (m_cooldownTimer.isFinished())
		{
			m_cooldownTimer.deactivate();
		}
	}
}

void ItemBase::increaseQuantity(int& newItemQuantity)
{
	while (newItemQuantity)
	{
		if (m_quantity >= m_maxQuantity) { break; }
		++m_quantity;
		--newItemQuantity;
	}
}

void ItemBase::decreaseQuantity(int& quantityToRemove)
{
	while (!quantityToRemove)
	{
		if (!m_quantity) { break; }

		--m_quantity;
		--quantityToRemove;
	}
}