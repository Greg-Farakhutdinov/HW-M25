#include "config.h"
#include <fstream>
#include <nlohmann/json.hpp>

//Прочитать конфигурации
void Config::readConfig() {
    std::ifstream f(namefile_);

    //Если файл не открыт
    if (!f.is_open()) {
        std::string str = "Ошибка при открытии файла конфигурации " + namefile_;
        throw str;
    }

    //Считать данные с файла
    nlohmann::json data;
    f >> data;

    port_ = data["port"];
    addressdb_ = data["addressdb"];
    logindb_ = data["logindb"];
    passworddb_ = data["passworddb"];
    namedb_ = data["namedb"];

    //Закрыть файл
    f.close();
}

//Получить порт
uint16_t Config::getPort() const {
    return port_;
}

//Получить адрес БД MySQL
const std::string& Config::getAddressDB() const {
    return addressdb_;
}

// Получить логин БД MySQL
const std::string& Config::getLoginDB() const {
    return logindb_;
}

//Получить пароль БД MySQL
const std::string& Config::getPasswordDB() const {
    return passworddb_;
}

// Получить имя БД
const std::string& Config::getNameDB() const {
    return namedb_;
}
