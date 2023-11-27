#pragma once

#include <vector>

#include "keyframe.hpp"
#include "transform.hpp"

namespace GLRT {
class Animation {
   public:
	Animation();
	Animation(double duration, const std::vector<Keyframe>& keyframes);
	Animation(double duration, std::initializer_list<Keyframe> keyframes);
	~Animation();

	void Update(double time);
	Transform GetTransform() const;
	double GetTime() const;

	void AddKeyFrame(Keyframe keyframe);

   private:
	std::vector<Keyframe> m_keyframes;
	double m_time = 0;
	double duration = 0;
};

}  // namespace GLRT
