/**
 * @author Sakib Islam[sakib.islam@uleth.ca]
 * @date 2023-12
 */
#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <unordered_map>
#include "Weapon.h"
#include "Enemy.h"

class Room {
public:
	Room(const std::string& name);
	std::string getName() const;
	void setAdjacent(Room* north, Room* south, Room* east, Room* west);
	Room* moveNorth() const;
	Room* moveSouth() const;
	Room* moveEast() const;
	Room* moveWest() const;

	void setWeapon(Weapon* weapon);
	Weapon* getWeapon() const;
	void setEnemy(Enemy* enemy);
	Enemy* getEnemy() const;

private:
	std::string name;
	std::unordered_map<std::string, Room*> adjacentRooms;
	Weapon* weapon;
	Enemy* enemy;
};

#endif // ROOM_H
