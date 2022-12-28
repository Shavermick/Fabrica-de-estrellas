#include "player.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Player::Player(Image& image, float X, float Y, int W, int H, std::string Name):
Entity(image, X, Y, W, H, Name)
{
playerScore = 0;
state = stay;
if (name == "Player1")
{
sprite.setTextureRect(IntRect(0, 0, w, h));
}
}

void Player::control() {
if (Keyboard::isKeyPressed(Keyboard::Left)) {
state = left;
speed = 0.1;
}
if (Keyboard::isKeyPressed(Keyboard::Right)) {
state = right;
speed = 0.1;
}
if (Keyboard::isKeyPressed(Keyboard::Up)) {
state = up;
speed = 0.1;
}
if (Keyboard::isKeyPressed(Keyboard::Down)) {
state = down;
speed = 0.1;
}
if (Keyboard::isKeyPressed(Keyboard::Left) == false &&
Keyboard::isKeyPressed(Keyboard::Right) == false &&
Keyboard::isKeyPressed(Keyboard::Up) == false &&
Keyboard::isKeyPressed(Keyboard::Down) == false)
{
state = stay;
}
if (startDeathAnim) state = dead;
}

void Player::checkCollisionWithMap(float Dx, float Dy) {
for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
for (int j = x / 32; j < (x + w) / 32; j++)
{
if (TileMap[i][j] == '0')//���� ������� ������ �����
{
if (Dy > 0) { y = i * 32 - h; dy = 0; }//�� Y
if (Dy < 0) { y = i * 32 + 32; dy = 0; }//������������ � �������� ������
if (Dx > 0) { x = j * 32 - w; dx = 0; }//� ������ ����� �����
if (Dx < 0) { x = j * 32 + 32; dx = 0; }// � ����� ����� �����
}
if (TileMap[i][j] == 's') {
playerScore++; //���� ����� ������
TileMap[i][j] = ' ';
}
if (TileMap[i][j] == 'f') {
health -= 40;//���� ����� �������� ������
TileMap[i][j] = ' ';//������ ������
}
if (TileMap[i][j] == 'h') {
health += 20;//���� ����� ��������
TileMap[i][j] = ' ';//������ ��������
}
}
}

void Player::update(float time) //����� "���������/����������" ������� ������.
{
if (life) {//���������, ��� �� �����
control();//������� ���������� ����������
switch (state)//�������� ��������� �������� � ����������� �� ���������
{
case right: {//��������� ���� ������
dx = speed;
CurrentFrame += 0.005 * time;
if (CurrentFrame > 2) CurrentFrame -= 2;
sprite.setTextureRect(IntRect(96*int(CurrentFrame), 96, 96, 96));

break;
}
case left: {//��������� ���� �����
dx = -speed;
CurrentFrame += 0.005 * time;
if (CurrentFrame > 2) CurrentFrame -= 2;
sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
break;
}
case stay: {//�����
dy = speed;
dx = speed;
CurrentFrame += 0.005 * time;
if (CurrentFrame > 3) CurrentFrame -= 3;
sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
break;

}
case dead: {
life = false;
}
}
x += dx * time; //�������� �� �X�
checkCollisionWithMap(dx, 0);//������������ ������������ �� �
y += dy * time; //�������� �� �Y�
checkCollisionWithMap(0, dy);//������������ ������������ �� Y
speed = 0; //�������� ��������, ����� �������� �����������.
//state = stay; //��������� - �����
sprite.setPosition(x, y); //������ � ������� (x, y).
if (health <= 0) { life = false; }//���� ������ ������ 0, ���� ����� 0, �� �������
}

}
