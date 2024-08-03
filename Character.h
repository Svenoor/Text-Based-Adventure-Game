/**
 * @author Sakib Islam[sakib.islam@uleth.ca]
 * @date 2023-12
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "Room.h"
#include "Weapon.h"
#include "Enemy.h"

class Character {
public:
	Character(const std::string& name, Room* startingRoom);
	std::string getName() const;
	Room* getCurrentRoom() const;
	void move(char direction);
	void pickUpWeapon(Weapon* weapon);
	void displayInventory() const;
	void attackEnemy(Enemy* enemy);
	const std::vector<Weapon*>& getWeapons() const;

private:
	std::string name;
	Room* currentRoom;
	std::vector<Weapon*> weapons;
};

#endif // CHARACTER_H
