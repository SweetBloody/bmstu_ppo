#ifndef SRC_CONNECTION_H
#define SRC_CONNECTION_H

#include <string>
#include <pqxx/pqxx>
#include "exception/Exception.h"


class Connection {
public:
    Connection(std::string &user, std::string &host, std::string &password, std::string &db_name, int port);
    void CreateConnection();

private:
    std::string _user;
    std::string _host;
    std::string _password;
    std::string _db_name;
    int _port;
    pqxx::connection *_connection;
};



#endif //SRC_CONNECTION_H
