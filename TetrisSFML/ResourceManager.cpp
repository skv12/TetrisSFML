#include "ResourceManager.h"
#include "SFML/Graphics/Font.hpp"

using namespace app;
using namespace sf;

ResourceManager::ResourceManager() {
	loadFont("resources/VCR_OSD_MONO_1.001.ttf", "default");
}
ResourceManager::~ResourceManager() {
}
Texture& ResourceManager::getTexture(const string& aPath) {
	auto found = textures.find(aPath);
	if (found == textures.end()) {
		Texture newTexture;
		newTexture.loadFromFile(aPath);
		found = textures.insert(make_pair(aPath, newTexture)).first;
	}
	return found->second;
}
void ResourceManager::loadFont(const string& aPath, const string& aKey) {
	Font newFont;
	if (newFont.loadFromFile(aPath)) {
		auto found = fonts.find(aKey);
		if (found != fonts.end()) {
			fonts.erase(found);
		}
		fonts[aKey] = newFont;
	}
}
Font& ResourceManager::getFont(const std::string& aKey) {
	return fonts[aKey];
}
