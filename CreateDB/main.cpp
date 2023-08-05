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
		std::cout << "Ошибка: дескриптор MySQL не создан " << std::endl;
		return 1;
	}

	//если нет подключения с БД
	if (!mysql_real_connect(&mysql, config.getAddressDb().c_str(), config.getLoginDb().c_str(), config.getPasswordDb().c_str(), "", 0, NULL, 0)) {
		std::cout << "Ошибка: не удается подключиться к БД. " << mysql_error(&mysql) << std::endl;
		return 1;
	}

	//сформировать запрос
	std::string q = "CREATE DATABASE " + config.getNameDb();

	//создать БД
	int res = mysql_query(&mysql, q.c_str());

	if (res == 0) {
		std::cout << "База данных " << config.getNameDb() << " добавлена!" << std::endl;
	}
	else {
		std::cout << "Ошибка MySql: " << mysql_error(&mysql) << std::endl;
		return 1;
	}

	//выбрать БД
	q = "USE " + config.getNameDb();
	mysql_query(&mysql, q.c_str());

	//создать таблицу
	res = mysql_query(&mysql, "CREATE TABLE users(id INT AUTO_INCREMENT PRIMARY KEY, login VARCHAR(8) UNIQUE, password VARCHAR(100))");

	if (res == 0) {
		std::cout << "Таблица users создана!" << std::endl;
	}
	else {
		std::cout << "Ошибка MySql: " << mysql_error(&mysql) << std::endl;
		return 1;
	}

	//добавить данные в таблицу users
	res = mysql_query(&mysql, "INSERT INTO users(login, password) values('all', 'UNKNOWN')");
	int r1 = mysql_query(&mysql, "INSERT INTO users(login, password) values('admin', '7c04837eb356565e28bb14e5a1dedb240a5ac2561f8ed318c54a279fb6a9665e')");

	if (res == 0 && r1 == 0) {
		std::cout << "В таблицу users добавлены изначальные значения." << std::endl;
	}
	else {
		std::cout << "Ошибка MySql при добавлении данных в таблицу users: " << mysql_error(&mysql) << std::endl;
		return 1;
	}
	//создать таблицу messages
	res = mysql_query(&mysql, "CREATE TABLE messages(id INT AUTO_INCREMENT PRIMARY KEY, `from` INT NOT NULL, `to` INT NOT NULL, `text` VARCHAR(500))");

	if (res == 0) {
		std::cout << "Таблица messages создана!" << std::endl;
	}
	else {
		std::cout << "Ошибка MySql: " << mysql_error(&mysql) << std::endl;
		return 1;
	}

	//закрыть дескриптор соединения
	mysql_close(&mysql);

	return 0;
}
