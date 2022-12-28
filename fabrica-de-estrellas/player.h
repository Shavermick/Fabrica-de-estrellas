#ifndef PLAYER
#define PLAYER
#include "entity.h"

using namespace sf;

class Player :public Entity {
public:

int playerScore;//эта переменная может быть только у игрока
Player(Image& image, float X, float Y, int W, int H, std::string Name);
void control();
//Метод проверки столкновений с элементами карты
void checkCollisionWithMap(float Dx, float Dy);
void update(float time);
};
#endif // PLAYER
