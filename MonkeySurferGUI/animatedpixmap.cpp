#include "animatedpixmap.h"

AnimatedPixmap::AnimatedPixmap(long long nextFrameDelay) : _frameIndex(0), _nextFrameDelay(nextFrameDelay), _loops(0) {
	_lastFrameUpdate = std::chrono::steady_clock::now();
}

void AnimatedPixmap::addFrame(QString filename) {
	_frames.push_back(filename);
}

void AnimatedPixmap::setFrame(size_t index) {
	_frameIndex = index;
	setPixmap(QPixmap(_frames[_frameIndex]));
}

void AnimatedPixmap::setLoops(int loops) {
	_loops = loops;
}

void AnimatedPixmap::animate() {
	auto now = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastFrameUpdate);

	if (duration.count() < _nextFrameDelay || _loops <= 0)
		return; // Prochaine frame pas prete

	_lastFrameUpdate = std::chrono::steady_clock::now();
	_frameIndex = (_frameIndex + 1) % _frames.size();
	setPixmap(QPixmap(_frames[_frameIndex]));
	
	if (_frameIndex == 0)
		_loops--;
}
