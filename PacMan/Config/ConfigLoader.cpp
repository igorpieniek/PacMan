#include "ConfigLoader.h"

#define RETURN_IF_INVALID(X) if(!X) return false; 

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

	bool status = isJSONhaveRequiredFields();
	if (!status) exit(EXIT_FAILURE);
	std::cout << "Verification of the configuration file was successful! " << std::endl;

}



bool ConfigLoader::isJSONhaveRequiredFields(){
	RETURN_IF_INVALID( isSubsectionHaveRequiredFields(root, requiredMainHeaders, "MAIN"));
	RETURN_IF_INVALID(isSubsectionHaveRequiredFields(root["paths"], requiredPathsHeaders, "paths"));
	RETURN_IF_INVALID(isSubsectionHaveRequiredFields(root["paths"]["mapElementsImg"], requiredMapElementsHeaders, "paths->mapElementsImg"));
	RETURN_IF_INVALID(isSubsectionHaveRequiredFields(root["other"], requiredOtherHeaders, "other"));
	return true;
}

bool ConfigLoader::isSubsectionHaveRequiredFields(Json::Value sub, RequiredMap& required, std::string subName){

	for (auto& req : required) {
		if (!sub.isMember(req.first)) {
			std::cout << "Field <<" << req.first << ">> has to be defined in subsection <"<< subName<<"> json file!" << std::endl;
			return false;
		}
		else {
			if (!(sub[req.first].*(req.second))() ) {
				std::cout << "Field <<" << req.first << ">> exist in <" << subName << ">  , but value is not required type!" << std::endl;
				return false;
			}
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
	CoordType x = root["other"]["playerPosition"][0].asFloat();
	CoordType y = root["other"]["playerPosition"][1].asFloat();
	return Position(x,y);
}

int ConfigLoader::getAmoutOfOponents(){
	return root["other"]["amountOfOponents"].asInt();
}

int ConfigLoader::getAmountOfSpecialPoints(){
	return root["other"]["amoutOfSpecialPoints"].asInt();
}

CoordType ConfigLoader::getPlayerSpeed(){
	return root["other"]["playerSpeed"].asFloat();
}

CoordType ConfigLoader::getOponentSpeed(){
	return root["other"]["oponentSpeed"].asFloat();
}

int ConfigLoader::getMainWindowWidth(){
	return root["other"]["windowSize"][0].asInt();
}

int ConfigLoader::getMainWindowHeight(){
	return root["other"]["windowSize"][1].asInt();
}