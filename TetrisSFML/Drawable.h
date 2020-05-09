#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;

namespace app {
	class Drawable {
	public:
		virtual ~Drawable() = default;
		virtual void draw(sf::RenderTarget&) = 0;
	};
}
