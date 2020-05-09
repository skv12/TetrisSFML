#pragma once
#include "Scene.h"
#include "Button.h"
using namespace app;

namespace app {
	class MainMenuScreen : public app::Scene {
	public:
		MainMenuScreen();
		~MainMenuScreen();
		bool handleEvent(const sf::Event& aEvent);
		void draw(sf::RenderTarget& renderer);
	private:
		Texture texture;
		RectangleShape background;
		Button* exitButton;
		Button* highButton;
		Button* playButton;
	};
}