#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace app {
	class EventHandler {
	public:
		virtual ~EventHandler() = default;
		virtual bool handleEvent(const sf::Event&) { return false; };
	};
}
