#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Classes.h"
//#include "map.h" //подключили код с картой
#include <list>
#include <ctime>

//#include "Header.h"
using namespace sf;
int ENEMY_COUNT = 5;
int STAR_COUNT = 15;



int main()
{
    //TODO сделать лучи типо gas gas
    // ?чтобы враги отталкивались при встречи д с д
    // уровни
    // хп варгов и урон героя
    //
    //ЗАДАЕМ ПАРАМЕТРЫ ОКНА
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(800, 800, desktop.bitsPerPixel), "fabrica de estrellas");

    //ТЕКСТОВАЯ СТРОКА
    Font font;//шрифт
    font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта

    Text text("", font, 20);//создаем объект текст
    text.setColor(Color::Red);//покрасили текст в красный
    text.setStyle(Text::Bold);//жирный текст.

    Image map_image;//объект изображения для карты
    map_image.loadFromFile("images/map_last.png");//загружаем файл для карты
    Texture map;//текстура карты
    map.loadFromImage(map_image);//заряжаем текстуру картинкой
    Sprite s_map;//создаём спрайт для карты
    s_map.setTexture(map);//заливаем текстуру спрайтом

    Clock clock;
    Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры
    Clock shootingClock;
    Clock timerClock;
    int gameTime = 0;//объявили игровое время, инициализировали.

    Image heroImage;
    heroImage.loadFromFile("images/mainn.png"); // загружаем изображение игрока
    Image easyEnemyImage;
    easyEnemyImage.loadFromFile("images/enemyy.png"); // загружаем изображение врага
    Image BulletImage;//изображение для пули
    BulletImage.loadFromFile("images/bullets.png");//загрузили картинку в объект изображения
    Image starImage;
    starImage.loadFromFile("images/star.png");
    Player p(heroImage, 320, 400, 96, 96, "Player1");//объект класса игрока

    std::list<Entity*> enemies; //список врагов
    std::list<Entity*> Bullets; //список пуль
    std::list<Entity*> stars;
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator it2;//итератор чтобы проходить по элементам списка
    int playerScore = 0;
    //RectangleShape rect;
    /*rect.setSize(Vector2f(50, 50));
    rect.setPosition(150, 150);
    rect.setFillColor(Color::White);*/

    //const int ENEMY_COUNT = 1; //максимальное количество врагов в игре
    int enemiesCount = 0; //текущее количество врагов в игре
    int starsCount = 0;
    //Заполняем список объектами врагами
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        float xr = 150 + rand() % 500; // случайная координата врага на поле игры по оси “x”
        float yr = 40 + rand()%40; // случайная координата врага на поле игры по оси “y”
        enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 96, 96, "EasyEnemy"));
        enemiesCount += 1; //увеличили счётчик врагов
    }
    for (int i = 0; i < STAR_COUNT; i++)
    {
        float xr = 32 + rand() % 726;;
        float yr = 32 + rand() % 128;
        stars.push_back(new Star(starImage, xr, yr, 16, 16, "Star", p.state));
        starsCount += 1;
    }
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();//игровое время в
            clock.restart();
        time = time / 800;



        //автострельба раз в 1 сек.
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

        //оживляем звезды
        for (it = stars.begin(); it != stars.end(); it++)
        {
            //std::cout << clock.getElapsedTime().asMicroseconds() << "\n";
            (*it)->update(time); //запускаем метод update()
        }
        p.update(time);
        //оживляем врагов
        for (it = enemies.begin(); it != enemies.end(); it++)
        {
            //std::cout << clock.getElapsedTime().asMicroseconds() << "\n";
            (*it)->update(time); //запускаем метод update()
        }
        //оживляем пули
        for (it = Bullets.begin(); it != Bullets.end(); it++)
        {
            (*it)->update(time); //запускаем метод update()

            //if (((*it)->getRect()).top == 200) (*it)->life = false;
            //(*it)->getRect();
        }

        for (it = Bullets.begin(); it != Bullets.end(); it++)
        {
            for (it2 = enemies.begin(); it2 != enemies.end(); it2++)
            {
                if (p.state != p.dead)
                {
                    if ((*it)->getRect().intersects((*it2)->getRect()))
                    {
                        (*it2)->state = (*it2)->dead;
                        (*it)->life = false;
                        playerScore++;

                    }
                }


            }
            it2 = enemies.begin();
            while (it2 != enemies.end())
            {
                if ((*it2)->life == false)
                {
                    it2 = enemies.erase(it2);

                }
                else it2++;
            }
        }

        //коллизия пуль
        /*for (it = Bullets.begin(); it != Bullets.end(); it++)
        {
            it2 = enemies.begin();
            while (it2 != enemies.end())
            {
                if( (*it)->getRect().intersects((*it2)->getRect()) )
                {
                    it2 = enemies.erase(it2);
                    (*it)->life = false;
                    enemiesCount--;
                    playerScore++;
                }
                else it2++;
            }
        } */

        int died = 0;
        for (it = enemies.begin(); it != enemies.end(); it++)
        {
            if ((*it)->life == false)
            {
                died++;
            }
        }

        it = enemies.begin();
        while (it != enemies.end())
        {
            if ((*it)->life == false)
            {
                it = enemies.erase(it);
            }
            else it++;
        }
        Clock tmpTimer;
        int newLevelTime = 0;
        //std::cout << enemies.size();
        if ((enemies.size() == 0 || died == enemiesCount) && p.startDeathAnim == false && newLevelTime == 0)
        {
            LEVEL++;

            timerClock.restart();
            for (int i = 0; i < ENEMY_COUNT; i++)
            {
                float xr = 150 + rand() % 500; // случайная координата врага на поле игры по оси “x”
                float yr = 40 + rand() % 40; // случайная координата врага на поле игры по оси “y”
                //создаем врагов и помещаем в список
                enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 96, 96, "EasyEnemy"));
                enemiesCount += 1; //увеличили счётчик врагов
            }




        }//std::cout << "LEVEL";

        if (newLevelTime == 2)
        {

        }
        //Проверяем список на наличие "мертвых" пуль и удаляем их
        for (it = Bullets.begin(); it != Bullets.end(); )//говорим что проходимся от начала до конца
        {// если этот объект мертв, то удаляем его
            if ((*it)->life == false) { it = Bullets.erase(it); }
            else it++;//и идем курсором (итератором) к след объекту.
        }
        //Проверка пересечения игрока с врагами
        //Если пересечение произошло, то "health = 0", игрок обездвижевается и
        //выводится сообщение "you are lose"
        if (p.life == true) {//если игрок жив
            for (it = enemies.begin(); it != enemies.end(); it++) {//бежим по списку врагов
                if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
                {
                    p.startDeathAnim = true;


                }
            }
        }
        else {
            window.close();
            std::cout << "Game over. You are dead.\nYour score: " << playerScore;
        }
        window.clear();

            /////////////////////////////Рисуем карту/////////////////////
            for (int i = 0; i < HEIGHT_MAP; i++)
                for (int j = 0; j < WIDTH_MAP; j++)
                {
                    if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 0, 0));
                    if (TileMap[i][j] == '1') s_map.setTextureRect(IntRect(0, 0, 0, 0));
                    if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 64, 32, 32));
                    s_map.setPosition(j * 32, i * 32);
                    window.draw(s_map);
                }
        //объявили переменную здоровья и времени
        std::ostringstream playerHealthString, gameTimeString, playerScoreString;
        playerHealthString << p.health;
        playerScoreString << playerScore;
        gameTimeString << gameTime;//формируем строку
        text.setString("Здоровье: " + playerHealthString.str() + "\nВремя игры: " +	gameTimeString.str() + "\nСчет: " + playerScoreString.str());//задаем строку тексту
        text.setPosition(50, 700);//задаем позицию текста
        window.draw(text);//рисуем этот текст
        window.draw(p.sprite);//рисуем спрайт объекта “p” класса “Player”
        for (it = stars.begin(); it != stars.end(); it++)
        {
            if ((*it)->life) //если враги живы
                window.draw((*it)->sprite); //рисуем
        }
        //рисуем врагов
        for (it = enemies.begin(); it != enemies.end(); it++)
        {
            if ((*it)->life) //если враги живы
                window.draw((*it)->sprite); //рисуем
        }
        //рисуем пули
        for (it = Bullets.begin(); it != Bullets.end(); it++)
        {
            if ((*it)->life) //если пули живы
                window.draw((*it)->sprite); //рисуем объекты
        }
        window.display();
    }
    return 0;
}
