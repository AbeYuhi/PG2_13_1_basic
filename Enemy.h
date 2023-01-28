#pragma once

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

class Enemy
{
public:

	Enemy(Vector2 pos, Vector2 speed, int radius);
	~Enemy();

	static bool isAlive;

	void Move();

	void Draw();

	inline Vector2 GetPos() { return pos; };
	inline int GetRadius() { return radius; };


private:

	Vector2 pos;
	Vector2 speed;
	int radius;

};
