#include "exercisefactory.h"

#include <cassert>

namespace aoc {
	void ExerciseFactory::prepare(const std::string& year, const std::string& day, const Builder& builder) {
		std::string key{ year + "/" + day };
		assert(!builders.contains(key));
		
		builders.emplace(key, builder);
	}

	std::unique_ptr<aoc::Exercise> ExerciseFactory::build(const std::string& year, const std::string& day, PosArgs& args, OptArgs& options) {
		std::string key{ year + "/" + day };
		assert(builders.contains(key));
		
		return builders[key](args, options);
	}
}
