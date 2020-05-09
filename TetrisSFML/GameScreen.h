#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <string>
#include "Scene.h"
#include "Button.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <Algorithm>


using namespace app;

namespace app{
	class GameScreen : public app::Scene {
	public:
		GameScreen();
		~GameScreen();
		bool handleEvent(const Event& aEvent);
		void draw (RenderTarget&) override;
	private:
		sf::RectangleShape background;
		sf::Texture tiles;
	};
}