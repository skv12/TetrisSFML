#pragma once
#include "Scene.h"
#include "Button.h"
#include <fstream>
#include <iostream>

using namespace sf;
using namespace app;

namespace app {
	class HighScoreScreen : public app::Scene {
	public:
		HighScoreScreen();
		~HighScoreScreen();
		bool handleEvent(const Event& aEvent);
		void draw(RenderTarget&) override;
	private:
		Font font;
		ifstream fin;
		Text rec[10];
		Texture texture;
		RectangleShape background;
		Button* menuButton;
		Button* playButton;
	};
}