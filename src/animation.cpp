#include "animation.hpp"

namespace GLRT {
Animation::Animation() : m_keyframes(), m_time(0.0) {
	m_keyframes.emplace_back(Transform(), 0.0);
	duration = 0.0;
}

Animation::Animation(double duration, const std::vector<Keyframe>& keyframes) : m_keyframes(), m_time(0.0), duration(duration) {
	for(const Keyframe& keyframe : keyframes) {
		m_keyframes.push_back(keyframe);
	}
}

Animation::Animation(double duration, std::initializer_list<Keyframe> keyframes) : m_keyframes(), m_time(0.0), duration(duration) {
	for(const Keyframe& keyframe : keyframes) {
		m_keyframes.push_back(keyframe);
	}
}

Animation::~Animation() {}

void Animation::Update(double time) {
	m_time = m_time + time;

	if(m_time > duration) {
		m_time = m_time - duration;
	}
}

Transform Animation::GetTransform() const {
	// find keyframe with time less then m_time
	size_t currentFrame = -1;
	for(size_t i = 0; i < m_keyframes.size(); i++) {
		if(m_keyframes[i].time > m_time) {
			break;
		}
		currentFrame = i;
	}

	if(currentFrame == -1) {
		return Transform{};
	}

	return m_keyframes[currentFrame].transform;
}

double Animation::GetTime() const {
	return m_time;
}

void Animation::AddKeyFrame(Keyframe keyframe) {
	m_keyframes.push_back(keyframe);
}
}  // namespace GLRT
