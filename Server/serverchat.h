#pragma once

#include "tcpserver.h"
#include "sha256.h"
#include "config.h"
#include "dbmysql.h"
#include <memory>
#include <vector>

class ServerChat {
    std::unique_ptr<IServer> server_;                   //указатель для работы с сервером
    std::vector<User> users_;                           //вектор пользователей
    Config config_;                                     //объект для чтения конфигураций
    std::shared_ptr<IDatabase> database_;               //указатель для работы с базой данных

public:
    ServerChat() :users_(), config_("serverConfig.json") {
        //прочитать конфигурации
        config_.readConfig();
        //создать указатель для работы с сервером
        server_ = std::make_unique<TcpServer>(config_.getPort());
        //создать указатель для работы с БД
        database_ = DbMysql::getInstance(config_.getAddressDB(), config_.getLoginDB(), config_.getPasswordDB(), config_.getNameDB());
    }
    ~ServerChat() = default;

    void setColor(const std::string& color) const;      //установить цвет текста
    int working();                                      //работа чата

    //авторизация пользователя
    bool authorizationUser(const std::string& login, const std::string& password);

    //отправить сообщения на клиент
    void sendMessages(const std::string& login, const size_t amount);

    //выход пользователя
    void outUser(const std::string& login);

    //добавить пользователя
    int addUser(const std::string& login, const std::string& password);

    //добавить сообщение
    int addMessage(const std::string& from, const std::string& to, const std::string& text);

    //отправить список пользователей
    void sendUsers();
};
