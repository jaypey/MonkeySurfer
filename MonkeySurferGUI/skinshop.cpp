#include "skinshop.h"
#include <QGraphicsGridLayout>

SkinShop::SkinShop()
{
	setupUI();
	loadSkins();
	displaySkins();
}
SkinShop::~SkinShop() {}

int SkinShop::getSelectedSkin()
{
	return m_selectedSkinIndex;
}

void SkinShop::setupUI() {
	layout = new QVBoxLayout(this);
	view = new QGraphicsView(this);
	scene = new QGraphicsScene(this);
	

	layout->addWidget(view);
	

	view->setScene(scene);

}

//void SkinShop::createSkinItem() {
	//skin1 = new QGraphics
//}

void SkinShop::loadSkins() {

}

void SkinShop::displaySkins() {

}