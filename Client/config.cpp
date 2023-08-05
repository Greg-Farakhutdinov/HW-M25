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

    //Считать данные
    nlohmann::json data;
    f >> data;

    address_ = data["address"];
    port_ = data["port"];

    f.close();
}

//Получить адрес сервера
const std::string& Config::getAddress() const {
    return address_;
}

//Получить порт
uint16_t Config::getPort() const {
    return port_;
}
