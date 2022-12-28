#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Classes.h"
//#include "map.h" //���������� ��� � ������
#include <list>
#include <ctime>

//#include "Header.h"
using namespace sf;
int ENEMY_COUNT = 5;




int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(800, 800, desktop.bitsPerPixel), "fabrica de estrellas");

    //��������� ������
    Font font;//�����
    font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������

    Text text("", font, 20);//������� ������ �����
    text.setColor(Color::Red);//��������� ����� � �������
    text.setStyle(Text::Bold);//������ �����.

    Image map_image;//������ ����������� ��� �����
    map_image.loadFromFile("images/map_last.png");//��������� ���� ��� �����
    Texture map;//�������� �����
    map.loadFromImage(map_image);//�������� �������� ���������
    Sprite s_map;//������ ������ ��� �����
    s_map.setTexture(map);//�������� �������� ��������

    Clock clock;
    Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ����
    Clock shootingClock;
    Clock timerClock;
    int gameTime = 0;//�������� ������� �����, ����������������.

    Image heroImage;
    heroImage.loadFromFile("images/mainn.png"); // ��������� ����������� ������
    Image easyEnemyImage;
    easyEnemyImage.loadFromFile("images/enemyy.png"); // ��������� ����������� �����
    Image BulletImage;//����������� ��� ����
    BulletImage.loadFromFile("images/bullets.png");//��������� �������� � ������ �����������
    Image starImage;
    starImage.loadFromFile("images/star.png");
    Player p(heroImage, 320, 400, 96, 96, "Player1");//������ ������ ������

    std::list<Entity*> enemies; //������ ������
    std::list<Entity*> Bullets; //������ ����
    std::list<Entity*> stars;
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator it2;//�������� ����� ��������� �� ��������� ������
    int playerScore = 0;

    //const int ENEMY_COUNT = 1; //������������ ���������� ������ � ����
    int enemiesCount = 0; //������� ���������� ������ � ����

    //��������� ������ ��������� �������
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        float xr = 150 + rand() % 500; // ��������� ���������� ����� �� ���� ���� �� ��� �x�
        float yr = 40 + rand()%40; // ��������� ���������� ����� �� ���� ���� �� ��� �y�
        enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 96, 96, "EasyEnemy"));
        enemiesCount += 1; //��������� ������� ������
    }
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();//������� ����� �
            clock.restart();
        time = time / 800;
        int shootingTime = shootingClock.getElapsedTime().asSeconds();
        int timerTime = timerClock.getElapsedTime().asSeconds();
        if (shootingTime == 1 && p.life && timerTime < 5)
        {
            Bullet* ptrBullet = new Bullet(BulletImage, p.x + 40, p.y, 10, 20, "Bullet", p.state);
            Bullets.push_back(ptrBullet);
            shootingClock.restart();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        p.update(time);
        //�������� ������
        for (it = enemies.begin(); it != enemies.end(); it++)
        {
            //std::cout << clock.getElapsedTime().asMicroseconds() << "\n";
            (*it)->update(time); //��������� ����� update()
        }
        //�������� ����
        for (it = Bullets.begin(); it != Bullets.end(); it++)
        {
            (*it)->update(time); //��������� ����� update()


        }


        //��������� ������ �� ������� "�������" ���� � ������� ��
        for (it = Bullets.begin(); it != Bullets.end(); )//������� ��� ���������� �� ������ �� �����
        {// ���� ���� ������ �����, �� ������� ���
            if ((*it)->life == false) { it = Bullets.erase(it); }
            else it++;//� ���� �������� (����������) � ���� �������.
        }
        //�������� ����������� ������ � �������
        //���� ����������� ���������, �� "health = 0", ����� ��������������� �
        //��������� ��������� "you are lose"
        if (p.life == true) {//���� ����� ���
            for (it = enemies.begin(); it != enemies.end(); it++) {//����� �� ������ ������
                if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
                {
                    p.startDeathAnim = true;


                }
            }
        }
        else {

        }
        window.clear();


            for (int i = 0; i < HEIGHT_MAP; i++)
                for (int j = 0; j < WIDTH_MAP; j++)
                {
                    if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 0, 0));
                    if (TileMap[i][j] == '1') s_map.setTextureRect(IntRect(0, 0, 0, 0));
                    if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 64, 32, 32));
                    s_map.setPosition(j * 32, i * 32);
                    window.draw(s_map);
                }
        //�������� ���������� �������� � �������
        std::ostringstream playerHealthString, gameTimeString, playerScoreString;
        playerHealthString << p.health;
        playerScoreString << playerScore;
        gameTimeString << gameTime;//��������� ������
        text.setString("��������: " + playerHealthString.str() + "\n����� ����: " +	gameTimeString.str() + "\n����: " + playerScoreString.str());//������ ������ ������
        text.setPosition(50, 700);//������ ������� ������
        window.draw(text);//������ ���� �����
        window.draw(p.sprite);//������ ������ ������� �p� ������ �Player�
        for (it = stars.begin(); it != stars.end(); it++)
        {
            if ((*it)->life) //���� ����� ����
                window.draw((*it)->sprite); //������
        }
        //������ ������
        for (it = enemies.begin(); it != enemies.end(); it++)
        {
            if ((*it)->life) //���� ����� ����
                window.draw((*it)->sprite); //������
        }
        //������ ����
        for (it = Bullets.begin(); it != Bullets.end(); it++)
        {
            if ((*it)->life) //���� ���� ����
                window.draw((*it)->sprite); //������ �������
        }
        window.display();
    }
    return 0;
}
