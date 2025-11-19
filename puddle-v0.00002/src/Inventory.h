#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <array>
#include <cstdint>

enum Slot {
	WEAPON,
	OTHER
};

struct ItemComponent;

constexpr int g_inventoryCapacity = 100;

class Inventory {
public:
	Inventory();
	~Inventory();

	bool equip(int index);

	bool unequip(int slot);

	bool add(ItemComponent* item);

	void drop(ItemComponent* item);

	ItemComponent* getEquipped(int slot) const;

	ItemComponent* getWeapon();

	void dbgPrint() const;

private:
	std::map<uint8_t, ItemComponent*> m_equipped;
	std::array<ItemComponent*, g_inventoryCapacity> m_items{ nullptr };

	uint8_t m_numItems;
};

#endif