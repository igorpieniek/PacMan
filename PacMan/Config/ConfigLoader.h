#pragma once
#include "json/json.h"
#include <fstream>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Player.h"


#define CONFIG ConfigLoader::instance()

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
	int getAmountOfOponents();
	int getAmountOfSpecialPoints();
	CoordType getPlayerSpeed();
	CoordType getOponentSpeed();
	int getMainWindowWidth();
	int getMainWindowHeight();
	int getStartDelay_s();



private:
	ConfigLoader();
	using JsonVal = Json::Value;
	typedef bool (JsonVal::*JsonCheckerMeth)(void) const ;
	using RequiredMap = std::map<std::string, JsonCheckerMeth>;

	RequiredMap requiredMainHeaders{
		{"paths", &JsonVal::isObject},
		{"other", &JsonVal::isObject}
	};

	RequiredMap requiredPathsHeaders{
		{"mapTxt",			&JsonVal::isString},
		{"dynamicMapImg",   &JsonVal::isString},
		{"playerImg",		&JsonVal::isString},
		{"heartImg",		&JsonVal::isString},
		{"pointImg",		&JsonVal::isString},
		{"mapElementsImg",  &JsonVal::isObject},
		{"ghostsImg",       &JsonVal::isArray}
	};
	RequiredMap requiredMapElementsHeaders{
		{"vertical",	&JsonVal::isString},
		{"horizontal",	&JsonVal::isString},
		{"empty",		&JsonVal::isString},
		{"cornerNE",	&JsonVal::isString},
		{"cornerSE",	&JsonVal::isString},
		{"cornerSW",	&JsonVal::isString},
		{"cornerNW",	&JsonVal::isString}
	};
	RequiredMap requiredOtherHeaders{
		{"playerPosition",		&JsonVal::isArray},
		{"amountOfOponents",	&JsonVal::isUInt},
		{"amountOfSpecialPoints",&JsonVal::isUInt},
		{"playerSpeed",			&JsonVal::isDouble},
		{"oponentSpeed",		&JsonVal::isDouble},
		{"windowSize",			&JsonVal::isArray},
		{"startDelay_s",        &JsonVal::isUInt},	
	};

	bool isJSONhaveRequiredFields();

	bool isSubsectionHaveRequiredFields(Json::Value sub, RequiredMap& required, std::string subName);
	

	Json::Value root;
	Json::CharReaderBuilder builder;
};

