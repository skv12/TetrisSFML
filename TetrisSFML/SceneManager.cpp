#include "SceneManager.h"
#include "Scene.h"
#include <iostream>

#include "SFML/Window/Event.hpp"

using namespace app;
SceneManager::SceneManager() {
	
}
SceneManager::~SceneManager() {
	for (auto& scene : scenes) {
		delete scene;
	}
	scenes.clear();
}
void SceneManager::update(const sf::Time& deltaTime) {
	for (auto it = scenes.rbegin(); it != scenes.rend(); it++) {
		if (it.operator*()->update(deltaTime)) {
			break;
		}
	}
	applyActions();
}
void SceneManager::draw(sf::RenderTarget& renderTarget) {
	for (auto& scene : scenes) {
		scene->draw(renderTarget);
	}
}
bool SceneManager::isEmpty() {
	return scenes.empty();
}
void SceneManager::pushScene(Scene* newScene) {
	actionQueue.push_back(SceneAction(eSceneActionType::PUSH, newScene));
}
void SceneManager::popScene() {
	actionQueue.push_back(SceneAction(eSceneActionType::POP));

}
void SceneManager::clearScenes() {
	actionQueue.push_back(SceneAction(eSceneActionType::CLEAR));
}
void SceneManager::handleEvent(const sf::Event& aEvent) {
	for (auto it = scenes.rbegin(); it != scenes.rend(); it++) {
		if (it.operator*()->handleEvent(aEvent)) {
			break;
		}
	}
	applyActions();
}
void SceneManager::applyActions() {
	for (auto& action : actionQueue) {
		switch (action.type) {
		case eSceneActionType::CLEAR:
			for (auto it = scenes.rbegin(); it != scenes.rend(); it++) {
				delete *it;
			}
			scenes.clear();
			break;
		case eSceneActionType::POP:
			if (scenes.empty()) {
				std::cout << "no one scenes in manager" << std::endl;
			}
			else {
				Scene* poppingScene = scenes.back();
				scenes.pop_back();
				poppingScene->onPop();
				delete poppingScene;
			}
			break;
		case eSceneActionType::PUSH:
			scenes.push_back(action.scene);
			scenes.back()->onPush();
			break;
		}
	}
	actionQueue.clear();
}
Scene* SceneManager::getScene(const std::string& name) {
	for (auto it = scenes.rbegin(); it != scenes.rend(); it++) {
		Scene* scene = *it;
		if (scene->getName() == name) {
			return scene;
		}
	}
	return nullptr;
}