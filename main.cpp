#include <iostream>
#include <vector>
#include "Character.h"
#include "Room.h"
#include "Weapon.h"
#include "Enemy.h"

void printMap(Character* character, const std::vector<Room*>& rooms);
void handleCombat(Character* character, Enemy* enemy);
void displayRoomInfo(Character* character);

int main() {
	// Create rooms
	Room bedroom("BEDROOM");
	Room club("CLUB");
	Room cafe("CAFE");
	Room laboratory("LABORATORY");
	Room theatre("THEATRE");
	Room bar("BAR");
	Room museum("MUSEUM");
	Room arcade("ARCADE");
	Room kfc("KFC");

	// Set adjacent rooms
	bedroom.setAdjacent(nullptr, &laboratory, &club, nullptr);
	club.setAdjacent(nullptr, &theatre, &cafe, &bedroom);
	cafe.setAdjacent(nullptr, &bar, nullptr, &club);
	laboratory.setAdjacent(&bedroom, &museum, &theatre, nullptr);
	theatre.setAdjacent(&club, &arcade, &bar, &laboratory);
	bar.setAdjacent(&cafe, &kfc, nullptr, &theatre);
	museum.setAdjacent(&laboratory, nullptr, &arcade, nullptr);
	arcade.setAdjacent(&theatre, nullptr, &kfc, &museum);
	kfc.setAdjacent(&bar, nullptr, nullptr, &arcade);

	// Create character
	Character mainCharacter("Player", &bedroom);

	// Create weapons
	Weapon sword("Sword", 10);
	Weapon gun("Gun", 20);
	Weapon knife("Knife", 5);
	Weapon axe("Axe", 15);

	// Place weapons in rooms
	bedroom.setWeapon(&sword);
	club.setWeapon(&gun);
	cafe.setWeapon(&knife);
	museum.setWeapon(&axe);

	// Create enemies
	Enemy enemy1("Devil", 30);
	Enemy enemy2("Zombie", 40);

	// Place enemies in rooms
	theatre.setEnemy(&enemy1);
	bar.setEnemy(&enemy2);

	// Game loop
	char direction;
	while (true) {
		printMap(&mainCharacter, { &bedroom, &club, &cafe, &laboratory, &theatre, &bar, &museum, &arcade, &kfc });
		displayRoomInfo(&mainCharacter);
		std::cout << "Enter direction (N/S/E/W), 'A' to attack, 'P' to pick up weapon, 'I' to view inventory or 'Q' to quit: ";
		std::cin >> direction;
		if (direction == 'Q' || direction == 'q') {
			break;
		}
		switch (toupper(direction)) {
		case 'N':
		case 'S':
		case 'E':
		case 'W':
			mainCharacter.move(direction);
			break;
		case 'A':
			if (mainCharacter.getCurrentRoom()->getEnemy()) {
				handleCombat(&mainCharacter, mainCharacter.getCurrentRoom()->getEnemy());
			}
			else {
				std::cout << "No enemies here!" << std::endl;
			}
			break;
		case 'P':
			if (mainCharacter.getCurrentRoom()->getWeapon()) {
				mainCharacter.pickUpWeapon(mainCharacter.getCurrentRoom()->getWeapon());
				mainCharacter.getCurrentRoom()->setWeapon(nullptr); // Remove weapon from room
			}
			else {
				std::cout << "No weapons here!" << std::endl;
			}
			break;
		case 'I':
			mainCharacter.displayInventory();
			break;
		default:
			std::cout << "Invalid option!" << std::endl;
		}
		// Check if the player is in a room with an enemy without having a weapon
		if (mainCharacter.getCurrentRoom()->getEnemy() && mainCharacter.getWeapons().empty()) {
			std::cout << "You encountered an enemy without having a weapon. Game over!" << std::endl;
			break;
		}
	}

	return 0;
}

void printMap(Character* character, const std::vector<Room*>& rooms) {
	std::string row16 = "|----------------------------------------------------|\n";
	std::string row15 = "|           |      |           |      |              |\n";
	std::string row14 = "| BEDROOM   |      |   CLUB    |      |     CAFE     |\n";
	std::string row13 = "|           |      |           |      |              |\n";
	std::string row12 = "|-----------|      |-----------|      |--------------|\n";
	std::string row11 = "|                                                    |\n";
	std::string row10 = "|-----------|      |-----------|      |--------------|\n";
	std::string row09 = "|           |      |           |      |              |\n";
	std::string row08 = "| LABORATORY|      |  THEATRE  |      |     BAR      |\n";
	std::string row07 = "|           |      |           |      |              |\n";
	std::string row06 = "|-----------|      |-----------|      |--------------|\n";
	std::string row05 = "|                                                    |\n";
	std::string row04 = "|-----------|      |-----------|      |--------------|\n";
	std::string row03 = "|           |      |           |      |              |\n";
	std::string row02 = "|  MUSEUM   |      |  ARCADE   |      |   KFC        |\n";
	std::string row01 = "|           |      |           |      |              |\n";
	std::string row00 = "|----------------------------------------------------|\n";

	Room* currentRoom = character->getCurrentRoom();
	std::string marker = "*";

	if (currentRoom->getName() == "BEDROOM") row14.replace(1, 1, marker);
	if (currentRoom->getName() == "CLUB") row14.replace(22, 1, marker);
	if (currentRoom->getName() == "CAFE") row14.replace(43, 1, marker);
	if (currentRoom->getName() == "LABORATORY") row08.replace(1, 1, marker);
	if (currentRoom->getName() == "THEATRE") row08.replace(22, 1, marker);
	if (currentRoom->getName() == "BAR") row08.replace(43, 1, marker);
	if (currentRoom->getName() == "MUSEUM") row02.replace(1, 1, marker);
	if (currentRoom->getName() == "ARCADE") row02.replace(22, 1, marker);
	if (currentRoom->getName() == "KFC") row02.replace(43, 1, marker);

	std::cout << row16 << row15 << row14 << row13 << row12 << row11 << row10 << row09 << row08 << row07 << row06 << row05 << row04 << row03 << row02 << row01 << row00;
}

void handleCombat(Character* character, Enemy* enemy) {
	character->attackEnemy(enemy);
	if (!enemy->isAlive()) {
		std::cout << enemy->getName() << " has been defeated!" << std::endl;
	}
	else {
		std::cout << enemy->getName() << " has " << enemy->getHealth() << " health left." << std::endl;
	}
}

void displayRoomInfo(Character* character) {
	Room* currentRoom = character->getCurrentRoom();
	std::cout << "You are in the " << currentRoom->getName() << "." << std::endl;

	if (currentRoom->getWeapon()) {
		std::cout << "There is a " << currentRoom->getWeapon()->getName() << " here." << std::endl;
	}
	else {
		std::cout << "There are no weapons here." << std::endl;
	}

	if (currentRoom->getEnemy()) {
		std::cout << "There is an enemy here: " << currentRoom->getEnemy()->getName() << "." << std::endl;
		if (character->getWeapons().empty()) {
			std::cout << "You have no weapons to fight with. Game over!" << std::endl;
			exit(0);
		}
	}
	else {
		std::cout << "There are no enemies here." << std::endl;
	}
}
