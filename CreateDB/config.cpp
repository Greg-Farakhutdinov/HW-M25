#include "config.h"
#include <fstream>
#include <nlohmann/json.hpp>

//Прочитать конфигурации
void Config::readConfig() {
	std::ifstream f(namefile_);

	//если файл не открыт
	if (!f.is_open()) {
		std::string str = " Ошибка при открытии файла конфигурации " + namefile_;
		throw str;
	}

	//считывание данных из файла
	nlohmann::json data;
	f >> data;

	addressdb_ = data["addressdb"];
	logindb_ = data["logindb"];
	passworddb_ = data["passworddb"];
	namedb_ = data["namedb"];

	f.close();
}

//Получить адрес БД
const std::string& Config::getAddressDb() const {
	return addressdb_;
}

//Получить логин БД
const std::string& Config::getLoginDb() const {
	return logindb_;
}

//Получить пароль БД
const std::string& Config::getPasswordDb() const {
	return passworddb_;
}

//Получить имя БД
const std::string& Config::getNameDb() const {
	return namedb_;
}
