#ifndef PLAYER
#define PLAYER
#include "entity.h"

using namespace sf;

class Player :public Entity {
public:

int playerScore;//��� ���������� ����� ���� ������ � ������
Player(Image& image, float X, float Y, int W, int H, std::string Name);
void control();
//����� �������� ������������ � ���������� �����
void checkCollisionWithMap(float Dx, float Dy);
void update(float time);
};
#endif // PLAYER
