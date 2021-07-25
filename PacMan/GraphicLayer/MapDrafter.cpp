#include "MapDrafter.h"



MapDrafter::MapDrafter(){
	calculateScale();

	MapCreator creator;
	creator.create();
}

void MapDrafter::draw(){
	Render2D::instance().addToDraw(text, trans);

}

void MapDrafter::addImage(std::string path, Direction dir){
	filePath = path;

	text = std::make_shared<Texture>(filePath);
	trans.setTranslation(0, -0.03f);
	trans.setRotationAxis(Transformation::Axis::X);
	trans.setRotation(180.0f);
	trans.setScale(2.05f, 0.7f, 1.0f);
}


