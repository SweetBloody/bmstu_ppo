#include "Connection.h"

Connection::Connection(std::string &user, std::string &host, std::string &password, std::string &db_name, int port) {
    _user = user;
    _host = host;
    _password = password;
    _db_name = db_name;
    _port = port;
}

void Connection::CreateConnection() {
    std::string parameters = "user=" + _user +
                             " host=" + _host +
                             " password=" + _password +
                             " dbname=" + _db_name +
                             " port=" + std::to_string(_port);
    try {
        _connection = new pqxx::connection(parameters);

        if (!_connection->is_open()) {
            std::string msg = "connection is not opened";
            throw ConnectException(msg);
        }
    }
    catch (Exception) {
        std::string msg = "Error with creating connect";
        throw ConnectException(msg);
    }
}

