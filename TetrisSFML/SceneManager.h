#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <string>

using namespace sf;
using namespace std;

namespace app {
	class Scene;

	class SceneManager {
	public:
		SceneManager();
		~SceneManager();

		void update(const Time &);
		void draw(RenderTarget &);
		void handleEvent(const Event &);

		bool isEmpty();
		void pushScene(Scene*);
		void popScene();
		void clearScenes();
		Scene* getScene(const string& name);
	private:
		enum class eSceneActionType {
			POP = 0,
			PUSH,
			CLEAR
		};
		struct SceneAction {
			Scene* scene;
			eSceneActionType type;
			SceneAction(eSceneActionType type, Scene* scene = nullptr) : type(type), scene(scene) {};
		};
		vector<SceneAction> actionQueue;
		vector<Scene*> scenes;

		void applyActions();
	};
}
