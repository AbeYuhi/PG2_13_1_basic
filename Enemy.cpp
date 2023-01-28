#include "Enemy.h"
#include <Novice.h>

Enemy::Enemy(Vector2 pos, Vector2 speed, int radius)
{
	this->pos = pos;
	this->speed = speed;
	this->radius = radius;
}

Enemy::~Enemy()
{

}

void Enemy::Move() {
	pos.x += speed.x;
	pos.y += speed.y;


	if (pos.x < radius) {
		pos.x = radius;
		speed.x *= -1;
	}
	if (pos.x > 1280 - radius) {
		pos.x = 1280 - radius;
		speed.x *= -1;
	}
	if (pos.y < radius) {
		pos.y = radius;
		speed.y *= -1;
	}
	if (pos.y > 1280 - radius) {
		pos.y = 1280 - radius;
		speed.y *= -1;
	}
}

void Enemy::Draw() {
	if (isAlive) {
		Novice::DrawEllipse(pos.x, pos.y,radius, radius, 0, RED, kFillModeSolid);
	}
}