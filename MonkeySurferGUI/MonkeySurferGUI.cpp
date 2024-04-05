#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600
#define ESPACEMENT_LIANES 100

int main(int argv, char** args)
{
	QApplication app(argv, args);

	// Scene (infos GUI)
	QGraphicsScene* scene = new QGraphicsScene;
	scene->setSceneRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);

	// View (affichage GUI)
	QGraphicsView* view = new QGraphicsView;
	view->setScene(scene);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);

	// Singe
	QGraphicsRectItem* singe = new QGraphicsRectItem;
	singe->setRect(350, 400, 100, 100);
	scene->addItem(singe);

	// Lianes
	QGraphicsRectItem* lianes[5];
	for (int i = 0; i < 5; i++) {
		int posXLiane = ((WINDOW_SIZE_X / 2) - 10) - (ESPACEMENT_LIANES * (i - 2));

		lianes[i] = new QGraphicsRectItem;
		lianes[i]->setRect(posXLiane, 0, 20, WINDOW_SIZE_Y);
		scene->addItem(lianes[i]);
	}

	view->show();
	app.exec();
}
