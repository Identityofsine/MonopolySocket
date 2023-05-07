#pragma once
#include <functional>

//std::function<void(Player* player, int spaces)> engine_move
namespace Monopoly {
	template<typename ...args>
	struct EngineMethod {
		std::function<void(args...)> method;
		std::string name;
		EngineMethod(std::string name, std::function<void(args...)> method) {
			this->method = method;
			this->name = name;
		};
	};

}
