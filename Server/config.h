#pragma once

#include <string>

class Config {
	std::string namefile_;						//имя файла конфигурации
	uint16_t port_;								//порт
	std::string addressdb_;						//адрес БД MySQL
	std::string logindb_;						//логин БД MySQL
	std::string passworddb_;					//пароль БД MySQL
	std::string namedb_;						//имя БД
public:

	Config() : namefile_("serverConfig.json"), port_(55555), addressdb_(), logindb_(), passworddb_(), namedb_() {}
	explicit Config(const std::string& namefile) : namefile_(namefile), port_(55555), addressdb_(), logindb_(), passworddb_(), namedb_() {}
	~Config() = default;

	void readConfig();							//Прочитать конфигурации	
	uint16_t getPort() const;					//Получить порт	
	const std::string& getAddressDB() const;	//Получить адрес БД MySQL	
	const std::string& getLoginDB() const;		//Получить логин БД MySQL	
	const std::string& getPasswordDB() const;	//Получить пароль БД MySQL
	const std::string& getNameDB() const;		//Получить имя БД
};
