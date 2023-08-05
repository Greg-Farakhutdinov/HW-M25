#include "dbmysql.h"

#include <iostream>

//Объявление статического поля класса
std::shared_ptr<DbMysql> DbMysql::singleton_ = nullptr;

DbMysql::DbMysql() : mysql_(), address_(), login_(), password_(), namedb_() {}
DbMysql::DbMysql(const std::string& address, const std::string& login, const std::string& password, const std::string& namedb) : mysql_(), address_(address), login_(login), password_(password), namedb_(namedb) {}

//Получить экземпляр класса
std::shared_ptr<DbMysql> DbMysql::getInstance(const std::string& address, const std::string& login, const std::string& password, const std::string& namedb) {
    if (singleton_ == nullptr) {
        singleton_ = std::shared_ptr<DbMysql>(new DbMysql(address, login, password, namedb));
    }
    return singleton_;
}

//Подключиться к серверу
void DbMysql::connect() {
    // Получить дескриптор соединения
    mysql_init(&mysql_);
    if (&mysql_ == nullptr) {               // Если дескриптор не получен
        throw "Ошибка: не удается создать MySQL-дескриптор";
    }

    // Если нет соединения с БД вывести сообщение об ошибке
    if (!mysql_real_connect(&mysql_, address_.c_str(), login_.c_str(), password_.c_str(), namedb_.c_str(), 0, NULL, 0)) {
        std::string str = "Ошибка: не удается подключиться к базе данных. " + std::string(mysql_error(&mysql_));
        throw str;
    }

    //Настроить кодировку
    mysql_set_character_set(&mysql_, "utf8");
}

//Отключиться от сервера
void DbMysql::disconnect() {
    // Закрыть соединение с сервером БД
    mysql_close(&mysql_);
}

//Прочитать список всех пользователей
void DbMysql::readAllUsers(std::vector<User>& vUsers) {
    MYSQL_RES* res;
    MYSQL_ROW row;
    //Отправить запрос к таблице на сервер
    mysql_query(&mysql_, "SELECT login, password FROM users");

    //Добавить все, что есть в таблице, в вектор vUsers
    if ((res = mysql_store_result(&mysql_))) {
        while ((row = mysql_fetch_row(res))) {
            for (unsigned i = 0; i < mysql_num_fields(res) - 1; ++i) {
                vUsers.emplace_back(row[i], row[i + 1]);
            }
        }
    }
    else {
        std::string str = "Ошибка MySql: " + std::string(mysql_error(&mysql_));
        throw str;
    }
}

//Прочитать сообщения, отправленные определенному пользователю
void DbMysql::readMessages(const std::string& login, std::vector<Message>& vMessages) {
    MYSQL_RES* res;
    MYSQL_ROW row;

    //Сформировать запрос
    std::string q = "SELECT u1.login as 'from' , u2.login as 'to', `text` FROM messages \
                     INNER JOIN users AS u1 ON u1.id = messages.from \
                     INNER JOIN users AS u2 ON u2.id = messages.to \
                     WHERE u2.login = '" + login + "' OR u2.login = 'all'";
    //Отправить запрос на сервер
    mysql_query(&mysql_, q.c_str());

    //Добавить все, что есть в таблице, в вектор vMessages
    if ((res = mysql_store_result(&mysql_))) {
        while ((row = mysql_fetch_row(res))) {
            for (unsigned i = 0; i < mysql_num_fields(res) - 2; ++i) {
                vMessages.emplace_back(row[i], row[i + 1], row[i + 2]);
            }
        }
    }
    else {
        std::string str = "Ошибка MySql: " + std::string(mysql_error(&mysql_));
        throw str;
    }
}

//Добавить пользователя в БД
void DbMysql::addUser(const std::string& login, const std::string& pass) {
    //Сформировать и отправить запрос
    std::string q = "INSERT INTO users(login, password) values('" + login + "', '" + pass + "')";
    mysql_query(&mysql_, q.c_str());
}

//Добавить сообщение в БД
void DbMysql::addMessage(const std::string& from, const std::string& to, const std::string& text) {
    //Сформировать и отправить запрос
    std::string q = "INSERT INTO messages(`from`, `to`, `text`) values((SELECT id FROM users WHERE login = '" + from + "'), (SELECT id FROM users WHERE login = '" + to + "'), '" + text + "')";
    mysql_query(&mysql_, q.c_str());
}
