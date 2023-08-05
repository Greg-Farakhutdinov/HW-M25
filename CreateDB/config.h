#pragma once

#include <string>
#include <iostream>

class Config {
	std::string namefile_;			//имя файла конфигурации
	std::string addressdb_;			//адрес БД MySQL
	std::string logindb_;			//логин БД MySQL
	std::string passworddb_;		//пароль БД MySQL
	std::string namedb_;			//имя БД
public:

	Config() : namefile_("serverConfig.json"), addressdb_(), logindb_(), passworddb_(), namedb_() {}
	explicit Config(const std::string& namefile) : namefile_(namefile), addressdb_(), logindb_(), passworddb_(), namedb_() {}
	~Config() = default;

	//Прочитать конфигурации
	void readConfig();

	//Получить адрес БД
	const std::string& getAddressDb() const;

	//Получить логин БД
	const std::string& getLoginDb() const;

	//Получить пароль БД
	const std::string& getPasswordDb() const;

	//Получить имя БД
	const std::string& getNameDb() const;
};
