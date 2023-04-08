#include "gif.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <sstream>

// Window shit
std::vector<sf::RenderWindow*> window;
sf::Event event;
sf::Sound amung;
sf::SoundBuffer buffer;
sf::SoundBuffer buffer2;
sf::SoundBuffer buffer3;
std::vector<sf::Sound> sound;
std::vector<int> xv;
std::vector<int> yv;
const int SCREEN_WIDTH = sf::VideoMode().getDesktopMode().width;
const int SCREEN_HEIGHT = sf::VideoMode().getDesktopMode().height;
bool isRunning = true;
int windows;

// Cat shit
std::vector<AnimatedGIF> gif;
std::vector<sf::Sprite> sprite;
std::vector<int> gifID;

void spawnWindow() {
	// Create path to selected gif
	std::stringstream _ss;
	_ss << "data/" << gifID[windows] << ".gif";
	std::string _path = _ss.str();

	// Load selected gif
	gif.push_back(AnimatedGIF(_path.c_str()));
	sprite.push_back(sf::Sprite());

	// Create borderless window
	window.push_back(new sf::RenderWindow(sf::VideoMode(gif[windows].getSize().x, gif[windows].getSize().y), "АМОГУС", sf::Style::None));
	window[windows]->setFramerateLimit(60);
	int _x = rand() % SCREEN_WIDTH;
	int _y = rand() % SCREEN_HEIGHT;
	int _xv = rand() % 2 - 1; if (_xv == 0) { _xv++; }
	int _yv = rand() % 2 - 1; if (_yv == 0) { _yv++; }
	int _rand = rand() % 15 + 5;
	_xv *= _rand;
	_yv *= _rand;
	xv.push_back(_xv);
	yv.push_back(_yv);
	window[windows]->setPosition(sf::Vector2i(_x, _y));
	sound.push_back(sf::Sound());
	if (gifID[windows] == 43)
		sound[windows].setBuffer(buffer3);
	else {
		sound[windows].setBuffer(buffer);
		float _pitch = rand() % 199 + 1;
		_pitch /= 100;
		sound[windows].setPitch(_pitch);
		sound[windows].setVolume(40);
	}

	windows++;
}

int main() {
	
	// Randomizing gifs
	for (int i = 0; i < 44; i++)
		gifID.push_back(i);
	srand(time(NULL));
	std::random_shuffle(gifID.begin(), gifID.end());

	// Setting the sound buffer
	buffer.loadFromFile("data/yippi.ogg");
	buffer2.loadFromFile("data/amogus.ogg");
	buffer3.loadFromFile("data/bone.ogg");
	amung.setBuffer(buffer2);

	// The first window
	spawnWindow();

	int t = 0;
	while (isRunning) {
		if (t > 100) {
			spawnWindow();
			t = 0;
		}

		for (int i = 0; i < window.size(); i++) {
			// Poll events
			while (window[i]->pollEvent(event)) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::RAlt)
						isRunning = false;
					else
						spawnWindow();
				}
				if (event.type == sf::Event::MouseButtonPressed)
					spawnWindow();
			}

			// Bounce windows
			bool bounceX = false, bounceY = false;
			int _x = window[i]->getPosition().x;
			int _y = window[i]->getPosition().y;
			if (_x > SCREEN_WIDTH * 2 - window[i]->getSize().x - 1 or _x < 1) {
				xv[i] *= -1;
				bounceX = true;
				sound[i].play();
			}
			if (_y > SCREEN_HEIGHT - window[i]->getSize().y - 1 or _y < 31) {
				yv[i] *= -1;
				bounceY = true;
				sound[i].play();
			}
			window[i]->setPosition(sf::Vector2i(_x + xv[i], _y + yv[i]));
			if (bounceX and bounceY) {
				amung.play();
				printf("edge hit!!!!\n");
			}

			// Draw funny cat
			gif[i].update(sprite[i]);
			window[i]->clear();
			window[i]->draw(sprite[i]);
			window[i]->display();
		}
		t++;
	}

	// Memory management shit
	for (int i = 0; i < window.size(); i++) { delete window[i]; }
	return 0;
}