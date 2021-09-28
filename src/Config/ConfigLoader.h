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

	std::vector<std::string> getOpponentsImgPaths();
	std::string getDisabledOpponentImgPath();
	std::string getDefeatedOpponentImgPath();
	std::string getGhostBaseImgPath();

	std::string get2DFragmentShaderPath();
	std::string get2DVertexShaderPath();


	// others
	Position getPlayerInitialPosition();
	int getAmountOfOpponents();
	int getAmountOfSpecialPoints();
	int getMainWindowWidth();
	int getMainWindowHeight();
	int getStartDelay_s();
	Position getGhostBasePosition();



private:
	ConfigLoader();
	using JsonVal = Json::Value;
	typedef bool (JsonVal::*JsonCheckerMeth)(void) const ;
	using RequiredMap = std::map<std::string, JsonCheckerMeth>;

	Json::Value root{};
	Json::CharReaderBuilder builder{};

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
		{"ghostsImg",       &JsonVal::isArray},
		{"disabledGhostImg",&JsonVal::isString},
		{"defeatedGhostImg",&JsonVal::isString},
		{"ghostBaseImg",    &JsonVal::isString},
		{"2DfragmentShader",&JsonVal::isString},
		{"2DvertexShader",  &JsonVal::isString}
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
		{"playerPosition",		 &JsonVal::isArray},
		{"amountOfOpponents",	 &JsonVal::isUInt},
		{"amountOfSpecialPoints",&JsonVal::isUInt},
		{"windowSize",			 &JsonVal::isUInt}, //isArray (x,y) if scale problem will be resolved
		{"startDelay_s",         &JsonVal::isUInt},
		{"ghostBasePosition",    &JsonVal::isArray},
	};

	bool isJSONhaveRequiredFields();

	bool isSubsectionHaveRequiredFields(Json::Value sub, RequiredMap& required, std::string subName);

};

