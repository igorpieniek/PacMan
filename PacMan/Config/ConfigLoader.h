#pragma once
#include "json/json.h"
#include <fstream>
#include <exception>
#include <iostream>

#define CONFIG_PATH "config.json"

class ConfigLoader{
public:
	static ConfigLoader& instance();

private:
	ConfigLoader();

	Json::Value root;
	Json::CharReaderBuilder builder;
};

