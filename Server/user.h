#pragma once

#include <string>

class User {
	const std::string _login;							//логин пользователя
	std::string _password;								//пароль пользователя
	bool _authUser;										//пользователь авторизирован
public:
	User() : _login("UNKNOWN"), _password("UNKNOWN"), _authUser(false) {}
	User(const std::string& login, const std::string& password)
		: _login(login), _password(password), _authUser(false) {}
	~User() = default;

	const std::string& getLogin() const;				//получить логин
	bool checkLogin(const std::string& login) const;	//проверить логин
	bool checkPassword(const std::string& password) const;	//проверить пароль
	void setAuthUser();									//установка авторизации
	void resetAuthUser();								//сброс авторизации
	bool getAuthUser() const;							//авторизация
};
