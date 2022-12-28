#include "enemy.h"
#include <SFML/Graphics.hpp>
#include "map.h"
using namespace sf;

Enemy::Enemy(Image& image, float X, float Y, int W, int H, std::string Name)
:Entity(image, X, Y, W, H, Name)
{
sprite.setTextureRect(IntRect(0, 0, w, h));
direction = rand() % 10;
if (direction % 2 == 0) state = left;
else state = right;

speed = 0.1;//даем скорость.этот объект всегда двигается
dx = speed;
}

void Enemy::checkCollisionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой
{
for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
for (int j = x / 32; j < (x + w) / 32; j++)
{
if (TileMap[i][j] == '0')//если элемент - тайлик земли
{
if (Dy > 0) {
life = false;
}//по Y
if (Dy < 0) {
y = i * 32 + 32; dy = 0.1;
direction = 3;//Направление движения врага
}//столкновение с верхними краями
if (Dx > 0) {
x = j * 32 - w; dx = -0.1;
state = left;//Направление движения врага
}//с правым краем карты
if (Dx < 0) {
x = j * 32 + 32; dx = 0.1;
state = right; //Направление движения врага
}// с левым краем карты
}
if (TileMap[i][j] == '1')
{
if (Dy > 0) {
life = false;
}//по Y
}
}
if (startDeathAnim) state = dead;
}

void Enemy::update(float time)
{
static Clock clock;
static int destroyed = 0;
//std::cout « clock.getElapsedTime().asSeconds() « "\n";

if (name == "EasyEnemy") {//для персонажа с таким именем логика будет такой
if (startDeathAnim)
{
dy = 0;
dx = 0;
CurrentFrame += 0.005 * time;
if (CurrentFrame > 7) CurrentFrame -= 7;
sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
}
if (life) {//проверяем, жив ли герой

switch (state)//делаются различные действия в зависимости от состояния
{
case dead: {
dy = 0;
dx = 0;
CurrentFrame += 0.005 * time;
if (CurrentFrame > 7) life = false;
sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
break;

}
case right: {//состояние идти вправо
dx = speed;
dy = speed / 10;
CurrentFrame += 0.005 * time;
if (CurrentFrame > 2) CurrentFrame -= 2;
sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
break;
}
case left: {//состояние идти влево
dx = -speed;
dy = speed / 10;
CurrentFrame += 0.005 * time;
if (CurrentFrame > 2) CurrentFrame -= 2;
sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
break;
}
//case 2: {//идти вверх
// dy = -speed;
// CurrentFrame += 0.005 * time;
// if (CurrentFrame > 3) CurrentFrame -= 3;
// sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
// break;
//}
//case 3: {//идти вниз
// dy = speed;
// CurrentFrame += 0.005 * time;
// if (CurrentFrame > 3) CurrentFrame -= 3;
// sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
// break;
//}
}
x += dx * time; //движение по “X”
//x += 0;
checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
//y += cos(x/10); //движение по “Y”
if (clock.getElapsedTime().asSeconds() >= 5) y += 2;
checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
sprite.setPosition(x, y); //спрайт в позиции (x, y).
//если жизней меньше 0, либо равно 0, то умираем
}
}
}
