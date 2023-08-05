#include "user.h"

//получить логин
const std::string& User::getLogin() const {
	return _login;
}

//проверить логин
bool User::checkLogin(const std::string& login) const {
	return _login == login;
}

//проверить пароль
bool User::checkPassword(const std::string& password) const {
	return _password == password;
}

//установка авторизации
void User::setAuthUser() {
	_authUser = true;
}

//сброс авторизации
void User::resetAuthUser() {
	_authUser = false;
}

//авторизация
bool User::getAuthUser() const {
	return _authUser;
}
