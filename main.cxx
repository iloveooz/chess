//
// Created by fahr on 04.03.19.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

int size = 56;

sf::Sprite f[32];

int board[8][8] = {
        -1, -2, -3, -4, -5, -3, -2, -1,
        -6, -6, -6, -6, -6, -6, -6, -6,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         6,  6,  6,  6,  6,  6,  6,  6,
         1,  2,  3,  4,  5,  3,  2,  1 };

std::string position = "";

void loadPosition() {
    int k = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            int n = board[i][j];
            if (!n) continue;

            int x = abs(n) - 1;
            int y = n > 0 ? 1 : 0;
            f[k].setTextureRect(sf::IntRect(size * x, size * y, size, size));
            f[k].setPosition(size * j, size * i);
            k++;
        }
}

std::string toChessNote(sf::Vector2f p) {
    std::string s = "";
    s += char(p.x / size + 97);
    s += char(7 - p.y / size + 49);
    return s;
}

sf::Vector2f toCoord(char a, char b) {
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    return sf::Vector2f(x * size, y * size);
}

void move (std::string str) {
    sf::Vector2f oldPos = toCoord(str[0], str[1]);
    sf::Vector2f newPos = toCoord(str[2], str[3]);

    for (int i = 0; i < 32; i++) {
        if (f[i].getPosition() == newPos)
            f[i].setPosition(-100, -100);
    }

    for (int i = 0; i < 32; i++) {
        if (f[i].getPosition() == oldPos)
            f[i].setPosition(newPos);
    }

}

int main() {
    sf::RenderWindow window(sf::VideoMode(453, 454), "The Chess");

    sf::Texture t1, t2;
    t1.loadFromFile("images/figures.png");
    t2.loadFromFile("images/board0.png");

    sf::Sprite s(t1);
    sf::Sprite sBoard(t2);

    for (int i = 0; i < 32; i++)
        f[i].setTexture(t1);

    loadPosition();

    bool isMove = false;
    float dx = 0;
    float dy = 0;

    sf::Vector2f oldPos, newPos;
    std::string str;

    int n = 0;


    while (window.isOpen()) {

        sf::Vector2i pos = sf::Mouse::getPosition(window);

        sf::Event e;

        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

            // drag and drop
            if (e.type == sf::Event::MouseButtonPressed)
                if (e.key.code == sf::Mouse::Left)
                    for (int i = 0; i < 32; i++)
                        if (f[i].getGlobalBounds().contains(pos.x, pos.y)) {
                            isMove = true;
                            n = i;
                            dx = pos.x - f[i].getPosition().x;
                            dy = pos.y - f[i].getPosition().y;
                            oldPos = f[i].getPosition();
                        }
            if (e.type == sf::Event::MouseButtonReleased)
                if (e.key.code == sf::Mouse::Left) {
                    isMove = false;
                    sf::Vector2f p = f[n].getPosition() + sf::Vector2f(size / 2, size / 2);
                    sf::Vector2f newPos = sf::Vector2f(size * int(p.x / size), size *int(p.y / size));

                    str = toChessNote(oldPos) + toChessNote(newPos);
                    move(str);
                    std::cout << str << std::endl;
                    f[n].setPosition(newPos);
                }

        }

        if (isMove) f[n].setPosition(pos.x - dx, pos.y - dy);

        window.clear();
        window.draw(sBoard);

        for (int i = 0; i < 32; i++)
            window.draw(f[i]);

        window.display();

    }

    return 0;
}