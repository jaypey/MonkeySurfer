#ifndef ANIMATEDPIXMAP_H
#define ANIMATEDPIXMAP_H

#include <chrono>
#include <vector>
#include <QGraphicsPixmapItem>

class AnimatedPixmap : public QGraphicsPixmapItem {
public:
	AnimatedPixmap(long long nextFrameDelay);
	void addFrame(QString filename);
	void setFrame(size_t index);
	void setLoops(int loops);
	void animate();
private:
	size_t _frameIndex;
	long long _nextFrameDelay;
	int _loops;
	std::chrono::steady_clock::time_point _lastFrameUpdate;
	std::vector<QString> _frames;
};

#endif // !ANIMATEDPIXMAP_H
