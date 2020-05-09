#include "MainMenuScreen.h"
#include "ManagersInstance.h"
#include "SceneManager.h"
#include "SFML/Window/Event.hpp"
#include "Button.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "GameScreen.h"
#include "HighScoreScreen.h"




bool MainMenuScreen::handleEvent(const Event& aEvent) {
	if (aEvent.type == sf::Event::KeyPressed) {
		if (aEvent.key.code == sf::Keyboard::F4) {
			GET_SCENE_MANAGER()->popScene();
		}
	}
	exitButton->handleEvent(aEvent);
	highButton->handleEvent(aEvent);
	playButton->handleEvent(aEvent);
	return true;
}

void MainMenuScreen::draw(sf::RenderTarget& renderer) {
	renderer.draw(background);
	exitButton->draw(renderer);
	highButton->draw(renderer);
	playButton->draw(renderer);
	
}

MainMenuScreen::MainMenuScreen() {
	texture.loadFromFile("resources/mainmenu.png");
	background.setTexture(&texture);
	background.setSize({ 1280, 720 });
	background.setPosition({ 0.f, 0.f });

	playButton = new Button();
	playButton->setSize({ 90, 30 });
	playButton->setPosition(580, 280);
	playButton->setFillColor(Color::Transparent);
	playButton->setReleaseCallback([]() {
		GET_SCENE_MANAGER()->clearScenes();
		auto nextScene = new GameScreen();
		GET_SCENE_MANAGER()->pushScene(nextScene);
	});

	highButton = new Button();
	highButton->setSize({ 220, 30 });
	highButton->setPosition(520, 350);
	highButton->setFillColor(Color::Transparent);
	highButton->setReleaseCallback([]() {
		GET_SCENE_MANAGER()->clearScenes();
		auto nextScene = new HighScoreScreen();
		GET_SCENE_MANAGER()->pushScene(nextScene);
	});

	exitButton = new Button();
	exitButton->setSize({ 90, 30 });
	exitButton->setPosition(580, 410);
	exitButton->setFillColor(Color::Transparent);
	exitButton->setReleaseCallback([]() {
		GET_SCENE_MANAGER()->popScene();
	});
}

MainMenuScreen::~MainMenuScreen() {
	delete exitButton;
	delete highButton;
	delete playButton;
}