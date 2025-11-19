#include "Inventory.h"

#include "Entity.h"
#include "ItemComponent.h"

#include "Log.h"

Inventory::Inventory() :
	m_numItems ( 0 )
{
	m_equipped[Slot::WEAPON] = nullptr;
}

Inventory::~Inventory()
{}

bool Inventory::equip(int index) {
	if (index < 0 || index > m_numItems || !m_items.at(index)) {
		return false;
	}

	auto item = m_items.at(index);

	if (!unequip(item->m_slot)) {
		return false;
	}


	m_equipped[item->m_slot] = item;
	m_items.at(index) = nullptr;
	--m_numItems;

	if (item->m_slot == Slot::WEAPON) {
		item->show();
	}
	else {
		item->hide();
	}

	return true;
}

bool Inventory::unequip(int slot) {
	if (m_equipped.find(slot) == m_equipped.end()) {
		return true;
	}
	else if (m_numItems >= m_items.size()) {
		return false;
	}


	auto item = m_equipped[slot];
	
	if (!item) {
		return true;
	}

	if (item->m_slot == Slot::WEAPON) {
		item->hide();
	}

	m_items.at(m_numItems++) = item;
	m_equipped[slot] = nullptr;
	return true;
}

bool Inventory::add(ItemComponent* item) {
	if (m_numItems < m_items.size()) {
		item->hide();
		m_items.at(m_numItems++) = item;
		return true;
	}
	return false;
}

void Inventory::drop(ItemComponent* item) {
	// idk
}

ItemComponent* Inventory::getEquipped(int slot) const {
	auto item = m_equipped.find(slot);

	return (item == m_equipped.end()) ? nullptr : item->second;
}

void Inventory::dbgPrint() const {
	Log::get().write(L_DEBUG, "-----Equipped Items-----");
	for (auto it = m_equipped.begin(); it != m_equipped.end(); ++it) {
		if (it->second) {
			Log::get().write(L_DEBUG, (int)it->first, ": ", it->second->m_entity->getName(), " ", it->second->m_entity->getId());
		}
		else {
			Log::get().write(L_DEBUG, (int)it->first, ": ", "null", " ", "null");
		}
	}

	Log::get().write(L_DEBUG, "-----Inventory-----");
	int index = 0;
	for (auto item : m_items) {
		if (item) {
			Log::get().write(L_DEBUG, index, " ", item->m_entity->getName(), " ", item->m_entity->getId());
		}
		++index;
	}
}

ItemComponent* Inventory::getWeapon() {
	return m_equipped[Slot::WEAPON];
}