#include "gif.h"

#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <sstream>

// Window shit
std::vector<sf::RenderWindow*> window;
sf::Event event;
std::vector<int> xv;
std::vector<int> yv;
const int SCREEN_WIDTH = sf::VideoMode().getDesktopMode().width;
const int SCREEN_HEIGHT = sf::VideoMode().getDesktopMode().height;
bool isRunning = true;

// Cat shit
std::vector<AnimatedGIF> gif;
std::vector<sf::Sprite> sprite;

int main() {

	std::vector<int> _gifID;
	for (int i = 0; i < 13; i++)
		_gifID.push_back(i);
	srand(time(NULL));
	std::random_shuffle(_gifID.begin(), _gifID.end());

	for (int i = 0; i < 5; i++) {
		// Create path to selected gif
		std::stringstream _ss;
		_ss << "data/" << _gifID[i] << ".gif";
		std::string _path = _ss.str();

		// Load selected gif
		gif.push_back(AnimatedGIF(_path.c_str()));
		sprite.push_back(sf::Sprite());

		// Create borderless window
		window.push_back(new sf::RenderWindow(sf::VideoMode(gif[i].getSize().x, gif[i].getSize().y), "АМОГУС", sf::Style::None));
		window[i]->setFramerateLimit(60);
		int _x = rand() % SCREEN_WIDTH;
		int _y = rand() % SCREEN_HEIGHT;
		int _xv = rand() % 2 - 1; if (_xv == 0) { _xv++; }
		int _yv = rand() % 2 - 1; if (_yv == 0) { _yv++; }
		int _rand = rand() % 9 + 1;
		_xv *= _rand;
		_yv *= _rand;
		xv.push_back(_xv);
		yv.push_back(_yv);
		window[i]->setPosition(sf::Vector2i(_x, _y));
	}

	while (isRunning) {
		for (int i = 0; i < window.size(); i++) {
			// Bounce windows
			int _x = window[i]->getPosition().x;
			int _y = window[i]->getPosition().y;
			if (_x > SCREEN_WIDTH * 2 - window[i]->getSize().x - 1 or _x < 1)
				xv[i] *= -1;
			if (_y > SCREEN_HEIGHT - window[i]->getSize().y - 1 or _y < 31)
				yv[i] *= -1;
			window[i]->setPosition(sf::Vector2i(_x + xv[i], _y + yv[i]));

			// Draw funny cat
			gif[i].update(sprite[i]);
			window[i]->clear();
			window[i]->draw(sprite[i]);
			window[i]->display();
		}
	}

	// Memory management shit
	for (int i = 0; i < window.size(); i++) { delete window[i]; }
	return 0;
}