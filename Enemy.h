/**
 * @author Svenoor Josan[svenoor.josan@uleth.ca]
 * @author Sakib Islam[sakib.islam@uleth.ca]
 * @date 2023-12
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
	Enemy(const std::string& name, int health);
	std::string getName() const;
	int getHealth() const;
	void takeDamage(int damage);
	bool isAlive() const;

private:
	std::string name;
	int health;
};

#endif // ENEMY_H
