#include "animation.hpp"

#include <iostream>

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
			if(m_time < 0.0) {
				m_time = 0.0;
			} else if(m_time > duration) {
				m_time = duration;
			}
			break;
		case LoopMode::LOOP:
			if(m_time < 0.0) {
				m_time = duration;
			} else if(m_time > duration) {
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
	if(m_keyframes.size() == 0) {
		return Transform{};
	} else if(m_keyframes.size() == 1) {
		return m_keyframes[0].transform;
	}

	size_t current_index, next_index;

	if(direction == 1) {
		current_index = -1;
		for(size_t i = 0; i < m_keyframes.size(); i++) {
			if(m_keyframes[i].time > m_time) {
				break;
			}
			current_index = i;
		}
	} else {
		current_index = m_keyframes.size();
		for(size_t i = m_keyframes.size() - 1; i >= 0; i--) {
			if(m_keyframes[i].time < m_time) {
				break;
			}
			current_index = i;
		}
	}

	if(current_index == -1) {
		return Transform{};
	}

	next_index = current_index + direction;
	if(next_index >= m_keyframes.size() || next_index < 0) {
		next_index = current_index - direction;
	}

	if(direction == -1) {
		// std::swap(current_index, next_index);
	}

	auto current_frame = m_keyframes[current_index];
	auto next_frame = m_keyframes[next_index];

	Transform result;

	switch(current_frame.interpolationMode) {
		case Keyframe::InterpolationMode::STEP:
			return m_keyframes[current_index].transform;
		case Keyframe::InterpolationMode::LINEAR: {
			double t = (m_time - m_keyframes[current_index].time) / (m_keyframes[next_index].time - m_keyframes[current_index].time);
			return m_keyframes[current_index].transform.Lerp(m_keyframes[next_index].transform, t);
		}
		case Keyframe::InterpolationMode::BEZIER: {
			double t = (m_time - m_keyframes[current_index].time) / (m_keyframes[next_index].time - m_keyframes[current_index].time);

			int cp1 = 0, cp2 = 1;
			if(direction == -1) {
				cp1 = 0, cp2 = 1;
			}

			return m_keyframes[current_index].transform.BezierInterpolation(m_keyframes[next_index].transform, current_frame.controlPoints[cp1], current_frame.controlPoints[cp2], t);
		}
	}

	return m_keyframes[current_index].transform;
}

double Animation::GetTime() const {
	return m_time;
}

void Animation::AddKeyFrame(Keyframe keyframe) {
	m_keyframes.push_back(keyframe);
}
}  // namespace GLRT
