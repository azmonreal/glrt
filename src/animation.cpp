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
	m_time = m_time + time * direction;

	switch(loopMode) {
		case LoopMode::ONCE:
			if(m_time > duration) {
				m_time = duration;
			}
			break;
		case LoopMode::LOOP:
			if(m_time > duration) {
				m_time = 0.0;
			}
			break;
		case LoopMode::PING_PONG:
			if(m_time > duration) {
				m_time = duration;
				direction = -1;
			} else if(m_time < 0.0) {
				m_time = 0.0;
				direction = 1;
			}
			break;
	}
}

Transform Animation::GetTransform() const {
	// find keyframe with time less then m_time
	size_t currentFrame = -1;
	size_t nextFrame = -1;
	for(size_t i = 0; i < m_keyframes.size(); i++) {
		if(m_keyframes[i].time > m_time) {
			break;
		}
		currentFrame = i;
	}

	if(currentFrame == -1) {
		return Transform{};
	}

	nextFrame = currentFrame + direction;
	if(nextFrame >= m_keyframes.size() || nextFrame < 0) {
		nextFrame = currentFrame - direction;
	}

	Transform result;

	switch(interpolationMode) {
		case InterpolationMode::STEP:
			return m_keyframes[currentFrame].transform;
		case InterpolationMode::LINEAR: {
			double t = (m_time - m_keyframes[currentFrame].time) / (m_keyframes[nextFrame].time - m_keyframes[currentFrame].time);
			return m_keyframes[currentFrame].transform.Lerp(m_keyframes[nextFrame].transform, t);
		}
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
