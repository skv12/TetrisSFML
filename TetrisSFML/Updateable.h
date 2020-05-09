#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;

namespace app {
	class Updateable {
	public:
		virtual ~Updateable() = default;
		virtual bool update(const sf::Time& deltaTime) { return false; };
	};
}
