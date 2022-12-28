#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>


using namespace sf;


class Entity {
public:
enum { left, right, up, down, stay, dead } state;//
float dx, dy, x, y, speed, moveTimer;
int w, h, health;
bool life;
bool startDeathAnim = false;

Texture texture;//сфмл текстура
Sprite sprite;//сфмл спрайт
float CurrentFrame;//хранит текущий кадр
std::string name;//враги могут быть разные, врагов можно различать по именам

Entity(Image& image, float X, float Y, int W, int H, std::string Name);
FloatRect getRect();
virtual void update(float time) = 0;

};

#endif // ENTITY_H