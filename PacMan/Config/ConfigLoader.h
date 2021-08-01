#pragma once
#include "json/json.h"
#include <fstream>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

#define CONFIG_PATH "config.json"

class ConfigLoader{
public:
	static ConfigLoader& instance();
	// paths
	std::string getMapTxtPath();
	std::string getDynamicMapImgPath();
	std::string getPlayerImgPath();
	std::string getHeartImgPath();
	std::string getPointImgPath();
	std::string getMapElementVerticalImgPath();
	std::string getMapElementHorizontalImgPath();
	std::string getMapElementEmptyImgPath();
	std::string getMapElementCornerNEImgPath();
	std::string getMapElementCornerNWImgPath();
	std::string getMapElementCornerSEImgPath();
	std::string getMapElementCornerSWImgPath();

	std::vector<std::string> getOponentsImgPaths();

	// others
	Position getPlayerInitialPosition();
	int getAmoutOfOponents();
	int getAmountOfSpecialPoints();
	CoordType getPlayerSpeed();
	CoordType getOponentSpeed();
	int getMainWindowWidth();
	int getMainWindowHeight();



private:
	ConfigLoader();

	Json::Value root;
	Json::CharReaderBuilder builder;
};

