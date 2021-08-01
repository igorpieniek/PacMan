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
