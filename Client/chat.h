#pragma once

#include "message.h"
#include "sha256.h"
#include "tcpclient.h"
#include "iclient.h"
#include "config.h"
#include "user.h"
#include <memory>
#include <vector>

class Chat {
	Config config_;											//объект для чтения настроек из файла
	std::string login_;										//логин
	std::vector<User> users_;								//вектор пользователей
	std::vector<Message> messages_;							//вектор сообщений
	std::unique_ptr<IClient> client_;						//клиент

public:
	Chat() : config_("clientConfig.json"), login_(), users_(), messages_(), client_(new TcpClient) {
		config_.readConfig();
	}
	virtual ~Chat() = default;

	void setColor(const std::string& color) const;			//установить цвет текста в терминале
	void working();											//работа чата
	bool authorizationUser(std::string login, std::string password);		//авторизация пользователя
	void receiveUsers();									//получить список пользователей
	void receiveMessages(const std::string& login);			//получить сообщения от сервера
	void showAllChat();										//показать общий чат
	void showSelfChat();									//показать чат с личными сообщениями
	void showUserMenu();									//показать меню пользователя
	int calculateAllMessages() const;						//подсчитать количество общих сообщений
	int calculateSelfMessages() const;						//подсчитать количество личных сообщений
	void outUser();											//выход пользователя
	void writeMessage();									//написать сообщения
	void userRegistration();								//регистрация пользователя
	void chatEntry();										//вход в чат
};
