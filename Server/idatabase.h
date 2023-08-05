#pragma once

#include <vector>
#include <string>
#include "user.h"
#include "message.h"

//Интерфейс БД для паттерна strategy
class IDatabase {
public:
	virtual ~IDatabase() = default;

	//Подключиться к серверу
	virtual void connect() = 0;

	//Отключиться от сервера
	virtual void disconnect() = 0;

	//Прочитать список всех пользователей
	virtual void readAllUsers(std::vector<User>& v) = 0;

	//Прочитать сообщения, отправленные определенному пользователю
	virtual void readMessages(const std::string& login, std::vector<Message>& v) = 0;

	//Добавить пользователя в БД
	virtual void addUser(const std::string& login, const std::string& pass) = 0;

	//Добавить сообщение в БД
	virtual void addMessage(const std::string& from, const std::string& to, const std::string& text) = 0;
};
