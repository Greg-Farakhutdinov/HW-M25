#include <iostream>
#include <string>
#include <mysql.h>
#include "config.h"

int main() {
	//объект для чтения конфигурации
	Config config("serverConfig.json");

	try {
		//считать конфигурации
		config.readConfig();
	}
	catch (const std::string& e) {
		std::cout << e << std::endl;
		return 1;
	}
	catch (const char* e) {
		std::cout << e << std::endl;
		return 1;
	}
	catch (...) {
		std::cout << "Неизвестное исключение." << std::endl;
		return 1;
	}

	MYSQL mysql;					//дескриптор соединения с MySQL

	//если дескриптор не получен
	if (!mysql_init(&mysql)) {
		std::cout << "Ошибка: дескриптор MySQL не создан." << std::endl;
		return 1;
	}

	//если нет подключения с БД
	if (!mysql_real_connect(&mysql, config.getAddressDb().c_str(), config.getLoginDb().c_str(), config.getPasswordDb().c_str(), "", 0, NULL, 0)) {
		std::cout << "Ошибка: не удается подключиться к базе данных. " << mysql_error(&mysql) << std::endl;
		return 1;
	}

	//сформировать запрос
	std::string q = "DROP DATABASE " + config.getNameDb();

	//удалить БД
	int r = mysql_query(&mysql, q.c_str());

	if (r == 0) {
		std::cout << "База данных " << config.getNameDb() << " удалена!" << std::endl;
	}
	else {
		std::cout << "Ошибка MySql: " << mysql_error(&mysql) << std::endl;
		return 1;
	}

	//закрыть дескриптор соединения
	mysql_close(&mysql);

	return 0;
}
