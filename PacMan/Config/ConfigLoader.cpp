#include "ConfigLoader.h"

ConfigLoader& ConfigLoader::instance(){
    static ConfigLoader loader;
    return loader;
}



ConfigLoader::ConfigLoader() {

	std::ifstream ifs;
	ifs.open(CONFIG_PATH);
	if (!ifs.is_open()) {
		std::cout << "Error: cannot open config file (broken or doesn't exist) - "<< CONFIG_PATH << std::endl;
		return;
	}
	builder["collectComments"] = true;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, ifs, &root, &errs)) {
		std::cout << errs << std::endl;
	}
	else {
		std::cout << "Config file (" << CONFIG_PATH << ") sucessfully loded!" << std::endl;
	}

	bool status = isPathSectionOK();

}

bool ConfigLoader::isPathSectionOK(){
	bool status = isSubsectionHaveRequiredFields(root["paths"], requiredPathsHeaders, "paths");
	if (!status) return status;
	status &= isMapElementsOK();
	return status;


}

bool ConfigLoader::isMapElementsOK(){
	return  isSubsectionHaveRequiredFields(root["paths"]["mapElementsImg"], requiredMapElementsHeaders, "paths->mapElementsImg");
}

bool ConfigLoader::isSubsectionHaveRequiredFields(Json::Value sub, std::vector<std::string>& required, std::string subName){
	for (auto& req : required) {
		if (!sub.isMember(req)) {
			std::cout << "Field <<" << req << ">> has to be defined in subsection <"<< subName<<"> json file!" << std::endl;
			return false;
		}
		else {
			//if (!sub[req].isString()) {
			//	std::cout << "Field <<" << req << ">> exist in <" << subName << ">  , but value is not a string type!" << std::endl;
			//	return false;
			//}
		}
	}
	return true;
}

 //----------------------GETTERS--------------------------------------------------
std::string ConfigLoader::getMapTxtPath(){
	return root["paths"]["mapTxt"].asString();
}

std::string ConfigLoader::getDynamicMapImgPath(){
	return root["paths"]["dynamicMapImg"].asString();
}

std::string ConfigLoader::getPlayerImgPath(){
	return root["paths"]["playerImg"].asString();
}

std::string ConfigLoader::getHeartImgPath(){
	return root["paths"]["heartImg"].asString();
}

std::string ConfigLoader::getPointImgPath(){
	return root["paths"]["pointImg"].asString();
}

std::string ConfigLoader::getMapElementVerticalImgPath(){
	return root["paths"]["mapElementsImg"]["vertical"].asString();
}

std::string ConfigLoader::getMapElementHorizontalImgPath(){
	return root["paths"]["mapElementsImg"]["horizontal"].asString();
}

std::string ConfigLoader::getMapElementEmptyImgPath(){
	return root["paths"]["mapElementsImg"]["empty"].asString();
}

std::string ConfigLoader::getMapElementCornerNEImgPath(){
	return root["paths"]["mapElementsImg"]["cornerNE"].asString();
}

std::string ConfigLoader::getMapElementCornerNWImgPath(){
	return root["paths"]["mapElementsImg"]["cornerNW"].asString();
}

std::string ConfigLoader::getMapElementCornerSEImgPath(){
	return root["paths"]["mapElementsImg"]["cornerSE"].asString();
}

std::string ConfigLoader::getMapElementCornerSWImgPath(){
	return root["paths"]["mapElementsImg"]["cornerSW"].asString();
}

std::vector<std::string> ConfigLoader::getOponentsImgPaths(){
	return std::vector<std::string>();
}

Position ConfigLoader::getPlayerInitialPosition(){
	return Position();
}

int ConfigLoader::getAmoutOfOponents(){
	return 0;
}

int ConfigLoader::getAmountOfSpecialPoints(){
	return 0;
}

CoordType ConfigLoader::getPlayerSpeed(){
	return CoordType();
}

CoordType ConfigLoader::getOponentSpeed(){
	return CoordType();
}

int ConfigLoader::getMainWindowWidth(){
	return 0;
}

int ConfigLoader::getMainWindowHeight(){
	return 0;
}