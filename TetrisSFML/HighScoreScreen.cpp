#include "MainMenuScreen.h"
#include "ManagersInstance.h"
#include "SceneManager.h"
#include "SFML/Window/Event.hpp"
#include "Button.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "GameScreen.h"
#include "HighScoreScreen.h"


bool HighScoreScreen::handleEvent(const Event& aEvent) {
	if (aEvent.type == sf::Event::KeyPressed) {
		if (aEvent.key.code == sf::Keyboard::Q) {
			GET_SCENE_MANAGER()->popScene();
		}
	}
	menuButton->handleEvent(aEvent);
	playButton->handleEvent(aEvent);
	return true;
}

void HighScoreScreen::draw(RenderTarget& renderer) {
	renderer.draw(background);
	menuButton->draw(renderer);
	playButton->draw(renderer);
}

HighScoreScreen::HighScoreScreen() {
	fin.open("records.txt");
	vector<int> records(10);
	if (fin.is_open())
	{
		for (int j = 0; j < 10; j++) {
			fin >> records[j];

		}
			
	}
	fin.close();
	texture.loadFromFile("resources/records.png");
	background.setTexture(&texture);
	background.setSize({ 1280, 720 });
	background.setPosition({ 0.f, 0.f });
	playButton = new Button();
	playButton->setSize({ 130, 30 });
	playButton->setPosition(1000, 560);
	playButton->setLabel("play");
	playButton->setFillColor(Color::Transparent);
	playButton->setReleaseCallback([]() {
		GET_SCENE_MANAGER()->clearScenes();
		auto nextScene = new GameScreen();
		GET_SCENE_MANAGER()->pushScene(nextScene);
	});

	menuButton = new Button();
	menuButton->setSize({ 130, 30 });
	menuButton->setPosition(1000, 600);
	menuButton->setLabel("menu");
	menuButton->setFillColor(Color::Transparent);
	menuButton->setReleaseCallback([]() {
		GET_SCENE_MANAGER()->clearScenes();
		auto nextScene = new MainMenuScreen();
		GET_SCENE_MANAGER()->pushScene(nextScene);
	});
}

HighScoreScreen::~HighScoreScreen() {
	delete menuButton;
	delete playButton;
}