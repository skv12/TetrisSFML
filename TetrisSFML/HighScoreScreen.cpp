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
vector<int> records(10);
void HighScoreScreen::draw(RenderTarget& renderer) {
	

	renderer.draw(background);
	for (int j = 0; j < 10; j++) {
		rec[j].setFont(font);
		rec[j].setFillColor(Color::Yellow);
		rec[j].setCharacterSize(32);
		rec[j].setStyle(Text::Bold);
		rec[j].setString(to_string(records[j]));
		rec[j].setPosition(800.f, 100.f + j * 30.f);
		renderer.draw(rec[j]);
	}
	menuButton->draw(renderer);
	playButton->draw(renderer);
}

HighScoreScreen::HighScoreScreen() {

	
	texture.loadFromFile("resources/records.png");
	background.setTexture(&texture);
	background.setSize({ 1280, 720 });
	background.setPosition({ 0.f, 0.f });
	font.loadFromFile("resources/VCR_OSD_MONO_1.001.ttf");
	
	fin.open("records.txt");
	if (fin.is_open())
	{
		for (int j = 0; j < 10; j++) {
			fin >> records[j];
		}

	}
	fin.close();
	
	playButton = new Button();
	playButton->setSize({ 130, 30 });
	playButton->setPosition(1000, 560);
	playButton->setLabel("play");
	playButton->setFillColor(Color::Transparent);
	playButton->setReleaseCallback([]() {
		//GET_SCENE_MANAGER()->clearScenes();
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