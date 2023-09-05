#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <vector>

#define X 1280
#define Y 720
#define LEFT_BOUNDARY -10 // Левая граница экрана, после которой объект удаляется
#define NUMSTARS 10000
#define SPEED 30
#define RADIUS 3


using namespace sf;

class Star {
private:
    Clock clock;
    CircleShape a;
    float speed;
    float angle;

public:
    Star() {
        srand(time(NULL));
        speed = float(rand() % SPEED + 1);
        angle = 0;
        a.setRadius(float(rand() % RADIUS + 1));
        a.setPosition(float(rand() % X), float(rand() % Y));
        UpdateColor();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(a);
    }

    void Move() {
        if (clock.getElapsedTime().asMilliseconds() >= 16) {
            a.move(sf::Vector2f(-0.2f * speed, angle));
            clock.restart();
            if (a.getPosition().x <= LEFT_BOUNDARY) {
                a.setPosition(X - 5, Y - rand() % 720 + 1);
                UpdateColor();
            }
        }
    }

private:
    void UpdateColor() {
        if (a.getPosition().y <= float(Y/3))
        {
            a.setFillColor(Color::White);
        }
        else if(a.getPosition().y > float(Y/3) && a.getPosition().y < float(2*(Y/3)))
        {
            a.setFillColor(sf::Color::Blue);
        }
        else
        {
            a.setFillColor(sf::Color::Red);
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(X, Y), "SFML works!");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return 1;
    }

    sf::Text stars_num;
    stars_num.setFont(font);
    stars_num.setCharacterSize(24);
    stars_num.setFillColor(sf::Color::White);

    int colorIntensivity = 0;
    RectangleShape whiteColor;
    whiteColor.setSize(Vector2f(X,Y/3));
    whiteColor.setPosition(0,0);

    RectangleShape blueColor;
    blueColor.setSize(Vector2f(X,Y/3));
    blueColor.setPosition(0,Y/3);

    RectangleShape redColor;
    redColor.setSize(Vector2f(X,Y/3));
    redColor.setPosition(0,Y/3 + Y/3);

    std::vector<Star> stars;


    bool change = false;
    bool fin = false;
    Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Создаем новую звезду при каждой итерации цикла

        if(stars.size() < NUMSTARS) // Если количество звезд < 100, то продолжаем создавать звезды
        {
            stars.push_back(Star());
        }
        else if(!fin) // Если достигнуто нужное количество звезд и анимация еще не началась
        {
            fin = true; // Устанавливаем флаг, что можно начать анимацию
        }

        for (Star& star : stars) {
            star.Move();
            star.draw(window);
        }


        if( fin )
        {

            if(!change)
            {
                if(clock.getElapsedTime().asMilliseconds() > 20)
                {
                    ++colorIntensivity;
                    clock.restart();
                }
                if(colorIntensivity > 150)
                    change= true;
            }
            else
            {
                if(clock.getElapsedTime().asMilliseconds() > 20)
                {
                    --colorIntensivity;
                    clock.restart();
                }
                if(colorIntensivity <=50)
                    change= false;
            }

            blueColor.setFillColor(Color(0,0,200,colorIntensivity));
            whiteColor.setFillColor(Color(200,200,200,colorIntensivity));
            redColor.setFillColor(Color(200,0,0,colorIntensivity));
            window.draw(whiteColor);
            window.draw(blueColor);
            window.draw(redColor);

        }

        stars_num.setString("Number of Stars: " + std::to_string(stars.size()));

        window.draw(stars_num);

        window.display();
    }

    return 0;
}
