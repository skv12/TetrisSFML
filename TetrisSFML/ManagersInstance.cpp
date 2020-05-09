#include "ManagersInstance.h"
#include "SceneManager.h"
#include "ResourceManager.h"

using namespace app;

ManagersInstance* ManagersInstance::getInstance() {
	static ManagersInstance _instance;
	return &_instance;
}
SceneManager* ManagersInstance::getSceneManager() {
	return sceneManager;
}
ResourceManager* ManagersInstance::getResourceManager() {
	return resourceManager;
}
ManagersInstance::ManagersInstance() {
	sceneManager = new SceneManager();
	resourceManager = new ResourceManager();
}
ManagersInstance::~ManagersInstance() {
	delete sceneManager;
	delete resourceManager;
}