//#include <SFML/Graphics.hpp>
#include "Application.h"
#include "ManagersInstance.h"
#include "SceneManager.h"

#include "MainMenuScreen.h"
using namespace app;
using namespace sf;

Application::Application() {
	window = new RenderWindow(VideoMode(1280, 720), "Tetris", Style::Close);
}
Application::~Application() {
	delete window;
}

static const Time TimePerFrame = seconds(1.f / 60.f);
void Application::run(){
	Clock clock;
	Time Timer = Time::Zero; 
	auto nextScene = new MainMenuScreen();
	GET_SCENE_MANAGER()->pushScene(nextScene);
	while (window->isOpen())
	{
		Time tick = clock.restart();
		Timer += tick;
		while (Timer > TimePerFrame)
		{
			Timer -= TimePerFrame;
			processInput();
			update(TimePerFrame);

			if (GET_SCENE_MANAGER()->isEmpty()) {
				window->close();
			}
		}
		render();
	}
}

void Application::processInput() {
	Event currentEvent;
	while (window->pollEvent(currentEvent))
	{
		GET_SCENE_MANAGER()->handleEvent(currentEvent);
		if (currentEvent.type == Event::Closed) {
			window->close();
		}
	}
}
void Application::update(const Time& tick) {
	GET_SCENE_MANAGER()->update(tick);
}
void Application::render() {
	window->clear();
	GET_SCENE_MANAGER()->draw(*window);
	window->setView(window->getDefaultView());
	window->display();
}