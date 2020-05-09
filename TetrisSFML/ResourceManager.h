#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <string>

using namespace sf;
using namespace std;

namespace app {
	class ResourceManager {
	private:
		map<string, Font> fonts;
		map<string, Texture> textures;
	public:
		ResourceManager();
		~ResourceManager();
		void loadFont(const string& aPath, const string& aKey);
		Font& getFont(const string& aKey = "default");
		Texture& getTexture(const string& aPath);
	};
}