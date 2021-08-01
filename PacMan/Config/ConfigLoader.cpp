#include "ConfigLoader.h"

ConfigLoader& ConfigLoader::instance(){
    static ConfigLoader loader;
    return loader;
}

ConfigLoader::ConfigLoader() {
	Json::Value root;
	std::ifstream ifs;
	ifs.open(CONFIG_PATH);
	if (!ifs.is_open()) {
		std::cout << "Error: cannot open config file (broken or doesn't exist) - "<< CONFIG_PATH << std::endl;
		return;
	}

	Json::CharReaderBuilder builder;
	builder["collectComments"] = true;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, ifs, &root, &errs)) {
		std::cout << errs << std::endl;
	}
	else {
		std::cout << "Config file (" << CONFIG_PATH << ") sucessfully loded!" << std::endl;
	}
}
