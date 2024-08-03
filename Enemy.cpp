#include "Enemy.h"

Enemy::Enemy(const std::string& name, int health) : name(name), health(health) {}

std::string Enemy::getName() const {
	return name;
}

int Enemy::getHealth() const {
	return health;
}

void Enemy::takeDamage(int damage) {
	health -= damage;
}

bool Enemy::isAlive() const {
	return health > 0;
}
