#ifndef ANIMATEDPIXMAP_H
#define ANIMATEDPIXMAP_H

#include <chrono>
#include <vector>
#include <QGraphicsPixmapItem>

typedef std::vector<QString> FrameSet;

class AnimatedPixmap : public QGraphicsPixmapItem {
public:
	AnimatedPixmap(long long nextFrameDelay);
	void setFrameSetsSize(size_t capacity);
	void selectedSet(size_t setIndex);
	void addFrame(QString filename, size_t setIndex);
	void setFrame(size_t index);
	void setLoops(int loops);
	void animate();
private:
	size_t _frameIndex;
	long long _nextFrameDelay;
	int _loops;
	std::chrono::steady_clock::time_point _lastFrameUpdate;
	std::vector<FrameSet> _sets;
	size_t _selectedSet;
};

#endif // !ANIMATEDPIXMAP_H
