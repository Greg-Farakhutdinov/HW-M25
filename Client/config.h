#pragma once

#include <string>

class Config {
	std::string namefile_;					//имя файла откуда считывается конфигурация
	std::string address_;					//адрес сервера
	uint16_t port_;							//порт

public:
	Config() : namefile_("clientConfig.json"), port_(55555) {}
	explicit Config(const std::string& namefile) : namefile_(namefile), port_(55555) {}
	~Config() = default;

	void readConfig();						//Прочитать конфигурации	
	const std::string& getAddress() const;	//Получить адрес сервера	
	uint16_t getPort() const;				//Получить адрес порта
};
