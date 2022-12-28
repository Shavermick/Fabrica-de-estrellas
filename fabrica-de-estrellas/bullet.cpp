#include "bullet.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Bullet::Bullet(Image& image, float X, float Y, int W, int H, std::string Name, int dir)
:Entity(image, X, Y, W, H, Name)
{
    x = X;
    y = Y;
    direction = dir;
    speed = 0.8;
    w = h = 16;
    life = true;

}

void Bullet::update(float time)
    {
        dx = 0; dy = -speed;
        //switch (direction)
        //{
        //case 0: dx = -speed; dy = 0; break;// state = left
        //case 1: dx = speed; dy = 0; break;// state = right
        //case 2: dx = 0; dy = -speed; break;// state = up
        //case 3: dx = 0; dy = speed; break;// state = down
        //}
        if (life) {
            x += dx * time;//само движение пули по х
            y += dy * time;//по у
            if (x <= 0) x = 20;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки(сервер может тормозить!)
            if (y <= 0) y = 20;
            if (x >= 800) x = 780;// задержка пули в правой стене, чтобы при проседании	кадров она случайно не вылетела за предел карты и не было ошибки(сервер может тормозить!)
            if (y >= 640) y = 620;
            for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
                for (int j = x / 32; j < (x + w) / 32; j++)
                {
                    if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
                        life = false;// то пуля умирает
                }
            CurrentFrame += 0.005 * time;
            if (CurrentFrame > 4) CurrentFrame = 4;
            sprite.setTextureRect(IntRect(10 * int(CurrentFrame), 0, 10, 20));
            sprite.setPosition(x + w / 2, y + h / 2);//задается позицию пули
            //checkCollisionsWithEnemies(entityList);
        }
    }

FloatRect Bullet::getRect() {
        FloatRect FR(x, y, w, h);

        return FR;
    }
