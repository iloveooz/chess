//
// Created by fahr on 04.03.19.
//

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
        -6, -6, -6, -6, -6, -6, -6, -6,
        -1, -2, -3, -4, -5, -3, -2, -1 };

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


int main() {
    sf::RenderWindow window(sf::VideoMode(453, 453), "The Chess");

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


    while (window.isOpen()) {

        sf::Vector2i pos = sf::Mouse::getPosition(window);

        sf::Event e;

        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

            // drag and drop
            if (e.type == sf::Event::MouseButtonPressed)
                if (e.key.code == sf::Mouse::Left)
                    if (s.getGlobalBounds().contains(pos.x, pos.y)) {
                        isMove = true;
                        dx = pos.x - s.getPosition().x;
                        dy = pos.y - s.getPosition().y;
                    }
            if (e.type == sf::Event::MouseButtonReleased)
                if (e.key.code == sf::Mouse::Left)
                    isMove = false;

        }

        if (isMove) s.setPosition(pos.x - dx, pos.y - dy);

        window.clear();
        window.draw(sBoard);

        for (int i = 0; i < 32; i++)
            window.draw(f[i]);

        window.display();

    }

    return 0;
}