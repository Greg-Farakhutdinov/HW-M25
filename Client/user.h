#pragma once

#include <string>

class User {
	const std::string login_;							//поле для логина
public:
	User() : login_("UNKNOWN") {}
	explicit User(const std::string& login) : login_(login) {}
	~User() = default;

	const std::string& getLogin() const;				//Получить логин
	bool checkLogin(const std::string& login) const;	//Проверка логина	
};
