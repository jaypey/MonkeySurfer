#include "animatedpixmap.h"

AnimatedPixmap::AnimatedPixmap(long long nextFrameDelay) : _frameIndex(0), _nextFrameDelay(nextFrameDelay), _loops(0) {
	_lastFrameUpdate = std::chrono::steady_clock::now();
	_selectedSet = 0;
}

void AnimatedPixmap::setFrameSetsSize(size_t capacity) {
	_sets.resize(capacity);
}

void AnimatedPixmap::selectedSet(size_t setIndex) {
	_selectedSet = setIndex;
	setPixmap(QPixmap(_sets[_selectedSet][_frameIndex]));
}

void AnimatedPixmap::addFrame(QString filename, size_t setIndex) {
	_sets[setIndex].push_back(filename);
}

void AnimatedPixmap::setFrame(size_t index) {
	_frameIndex = index;
	setPixmap(QPixmap(_sets[_selectedSet][_frameIndex]));
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
	_frameIndex = (_frameIndex + 1) % _sets[_selectedSet].size();
	setPixmap(QPixmap(_sets[_selectedSet][_frameIndex]));
	
	if (_frameIndex == 0)
		_loops--;
}
