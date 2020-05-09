#include "Button.h"
#include "ManagersInstance.h"
#include "ResourceManager.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Event.hpp"

using namespace app;

Button::Button() {
	setFillColor(sf::Color::White);
	text.getTransform();
	text.setFont(GET_RESOURCE_MANAGER()->getFont());
	text.setFillColor(sf::Color::Yellow);
	releaseCallback = nullptr;
	pressCallback = nullptr;
}
Button::~Button() {

}
void Button::setLabel(const std::string& label) {
	text.setString(label);
}
void Button::draw(sf::RenderTarget& target) {
	target.draw(static_cast<sf::RectangleShape>(*this));
	text.setPosition(getGlobalBounds().left + getGlobalBounds().width / 2.f, getGlobalBounds().top + getGlobalBounds().height / 3.f);
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	target.draw(text);
}
bool Button::handleEvent(const sf::Event& ev) {
	if (ev.type == sf::Event::EventType::MouseButtonPressed) {
		if (getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y)) {
			if (pressCallback) {
				pressCallback();
			}
			return true;
		}
	}
	else if (ev.type == sf::Event::EventType::MouseButtonReleased) {
		if (getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y)) {
			if (releaseCallback) {
				releaseCallback();
			}
			return true;
		}
	}
	return false;
}
void Button::setPressCallback(const std::function<void(void)>& cb) {
	pressCallback = cb;
}
void Button::setReleaseCallback(const std::function<void(void)>& cb) {
	releaseCallback = cb;
}