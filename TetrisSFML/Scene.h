#pragma once
#include "Updateable.h"
#include "Drawable.h"
#include "EventHandler.h"
#include <string>
namespace app {
	class Scene: public Updateable, public Drawable, public EventHandler {
	public:
		virtual ~Scene() = default;
		virtual void onPush() {};
		virtual void onPop() {};
		void setName(const std::string& name) { this->name = name; };
		const std::string& getName() { return name; };
	private:
		std::string name;
	};
}
