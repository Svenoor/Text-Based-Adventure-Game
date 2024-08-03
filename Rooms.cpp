/**
 * @author Sakib Islam[sakib.islam@uleth.ca]
 * @date 2023-12
 */

#include "Room.h"

Room::Room(const std::string& name) : name(name), weapon(nullptr), enemy(nullptr) {}

std::string Room::getName() const {
	return name;
}

void Room::setAdjacent(Room* north, Room* south, Room* east, Room* west) {
	adjacentRooms["N"] = north;
	adjacentRooms["S"] = south;
	adjacentRooms["E"] = east;
	adjacentRooms["W"] = west;
}

Room* Room::moveNorth() const {
	return adjacentRooms.at("N");
}

Room* Room::moveSouth() const {
	return adjacentRooms.at("S");
}

Room* Room::moveEast() const {
	return adjacentRooms.at("E");
}

Room* Room::moveWest() const {
	return adjacentRooms.at("W");
}

void Room::setWeapon(Weapon* weapon) {
	this->weapon = weapon;
}

Weapon* Room::getWeapon() const {
	return weapon;
}

void Room::setEnemy(Enemy* enemy) {
	this->enemy = enemy;
}

Enemy* Room::getEnemy() const {
	return enemy;
}
