#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "exercise.h"

namespace aoc {
	class ExerciseFactory {
	public:
		using PosArgs = std::vector<std::string>;
		using OptArgs = std::unordered_map<std::string, std::string>;
		using Builder = std::function<std::unique_ptr<aoc::Exercise>(PosArgs&, OptArgs&)>;
		
		void prepare(const std::string& year, const std::string& day, const Builder& builder);
		std::unique_ptr<aoc::Exercise> build(const std::string& year, const std::string& day, PosArgs& args, OptArgs& options);
	
	private:
		std::unordered_map<std::string, Builder> builders;
	};
}
