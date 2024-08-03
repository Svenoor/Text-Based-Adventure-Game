/**
 * @author Svenoor Josan[svenoor.josan@uleth.ca]
 * @author Sakib Islam[sakib.islam@uleth.ca]
 * @date 2023-12
 */

#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon {
public:
	Weapon(const std::string& name, int damage);
	std::string getName() const;
	int getDamage() const;

private:
	std::string name;
	int damage;
};

#endif // WEAPON_H
