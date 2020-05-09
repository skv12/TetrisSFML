#pragma once
#include "Drawable.h"
#include <string>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "EventHandler.h"
#include <functional>

namespace app {
	class Button: public sf::RectangleShape, public EventHandler, public Drawable {
	public:
		Button();
		~Button();
		void setLabel(const std::string& label);
		void setPressCallback(const std::function<void(void)> &cb);
		void setReleaseCallback(const std::function<void(void)> &cb);
		bool handleEvent(const sf::Event&);
		void draw(sf::RenderTarget& target) override;
	private:
		sf::Text text;
		std::function<void(void)> pressCallback;
		std::function<void(void)> releaseCallback;
	};
}