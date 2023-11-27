#pragma once

#include <vector>
namespace GLRT {
class Face {
   public:
	Face();
	~Face();

	std::vector<int> indices;
};
}  // namespace GLRT
