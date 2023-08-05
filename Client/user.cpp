#include "user.h"

//Получить логин
const std::string& User::getLogin() const {
	return login_;
}

//Проверка логина
bool User::checkLogin(const std::string& login) const {
	return login_ == login;
}
