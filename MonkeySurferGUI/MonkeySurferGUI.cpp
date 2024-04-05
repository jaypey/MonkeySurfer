#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

int main(int argv, char** args)
{
	QApplication app(argv, args);

	QGraphicsScene* scene = new QGraphicsScene;
	scene->setSceneRect(0, 0, 800, 600);

	QGraphicsView* view = new QGraphicsView;
	view->setScene(scene);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setFixedSize(800, 600);

	// Singe
	QGraphicsRectItem* player = new QGraphicsRectItem;
	player->setRect(350, 250, 100, 100);
	scene->addItem(player);

	view->show();
	app.exec();
}
