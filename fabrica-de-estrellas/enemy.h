#ifndef ENEMY
#define ENEMY

#include "entity.h"

using namespace sf;
class Enemy :public Entity {
public:
int direction;//направление движения врага
Enemy(Image& image, float X, float Y, int W, int H, std::string Name);
void checkCollisionWithMap(float Dx, float Dy);
void update(float time);



};//класс Enemy закрыт

#endif // ENEMY
