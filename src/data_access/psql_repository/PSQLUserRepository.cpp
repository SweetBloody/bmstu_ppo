#include "PSQLUserRepository.h"
#include "logger/Logger.h"

PSQLUserRepository::PSQLUserRepository(std::string &user, std::string &host, std::string &password,
                                       std::string &db_name, int port,
                                       Logger &logger) {
    std::string parameters = "user=" + user +
                             " host=" + host +
                             " password=" + password +
                             " dbname=" + db_name +
                             " port=" + std::to_string(port);
    _logger = &logger;
    try {
        _connection = new pqxx::connection(parameters);

        if (!_connection->is_open()) {
            std::string msg = "connection is not opened";
            _logger->Log(ERROR, msg);
            throw ConnectException(msg);
        }
    }
    catch (Exception) {
        std::string msg = "Error with creating connect";
        _logger->Log(ERROR, msg);
        throw ConnectException(msg);
    }
}

User PSQLUserRepository::GetUserById(int id) {
    User user;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::GetUserById(id);
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "GetUserById repo query");
            if (!result.empty()) {
                user = User(result[0][0].as<int>(), result[0][1].as<std::string>(), result[0][2].as<std::string>(),
                                 PrivilegeLvl((result[0][3].as<int>())));
            }
            else {
                std::string msg = "No such user";
                _logger->Log(ERROR, msg);
                throw NoDataException(msg);
            }
            curConnect.commit();
        }
        else {
            std::string msg = "Error with creating connect";
            _logger->Log(ERROR, msg);
            throw ConnectException(msg);
        }
    }
    catch (const std::exception &e)
    {
        _logger->Log(ERROR, e.what());
        std::cout << e.what() << std::endl;
    }
    return user;
}

User PSQLUserRepository::GetUserByLogin(std::string &login) {
    User user;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::GetUserByLogin(login);
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "GetUserByLogin repo query");
            if (!result.empty()) {
                user = User(result[0][0].as<int>(), result[0][1].as<std::string>(), result[0][2].as<std::string>(),
                            PrivilegeLvl((result[0][3].as<int>())));
            }
            else {
                std::string msg = "No such user";
                _logger->Log(ERROR, msg);
                throw NoDataException(msg);
            }
            curConnect.commit();
        }
        else {
            std::string msg = "Error with creating connect";
            _logger->Log(ERROR, msg);
            throw ConnectException(msg);
        }
    }
    catch (const std::exception &e)
    {
        _logger->Log(ERROR, e.what());
    }
    return user;
}


int PSQLUserRepository::AddUser(User &user) {
    int id = 0;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::AddUser(user.GetLogin(), user.GetPassword(), user.GetPrivilegeLvl());
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "AddUser repo query");
            id = result[0][0].as<int>();
            curConnect.commit();
        }
        else {
            std::string msg = "Error with creating connect";
            _logger->Log(ERROR, msg);
            throw ConnectException(msg);
        }
    }
    catch (const std::exception &e)
    {
        _logger->Log(ERROR, e.what());
        std::cout << e.what() << std::endl;
    }
    return id;
}

bool PSQLUserRepository::UserExist(User &user) {
    bool flag = false;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::GetUserByLogin(user.GetLogin());
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "UserExist repo query");
            if (!result.empty()) {
                flag = true;
            }
            curConnect.commit();
        }
        else {
            std::string msg = "Error with creating connect";
            _logger->Log(ERROR, msg);
            throw ConnectException(msg);
        }
    }
    catch (const std::exception &e)
    {
        _logger->Log(ERROR, e.what());
        std::cout << e.what() << std::endl;
    }
    return flag;
}

bool PSQLUserRepository::UserExist(std::string &login) {
    bool flag = false;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::GetUserByLogin(login);
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "UserExist repo query");
            if (!result.empty()) {
                flag = true;
            }
            curConnect.commit();
        }
        else {
            std::string msg = "Error with creating connect";
            _logger->Log(ERROR, msg);
            throw ConnectException(msg);
        }
    }
    catch (const std::exception &e)
    {
        _logger->Log(ERROR, e.what());
        std::cout << e.what() << std::endl;
    }
    return flag;
}


bool PSQLUserRepository::CheckPassword(std::string &login, std::string &password) {
    User user;
    bool flag = false;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::GetUserByLogin(login);
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "CheckPassword repo query");
            if (!result.empty() && result[0][2].as<std::string>() == password) {
                flag = true;
            }
            curConnect.commit();
        }
        else {
            std::string msg = "Error with creating connect";
            _logger->Log(ERROR, msg);
            throw ConnectException(msg);
        }
    }
    catch (const std::exception &e)
    {
        _logger->Log(ERROR, e.what());
        std::cout << e.what() << std::endl;
    }
    return flag;
}

int PSQLUserRepository::UpdatePassword(User &user, std::string &new_password) {
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::UpdatePassword(user.GetLogin(), new_password);
            pqxx::work curConnect(*_connection);
            curConnect.exec(sql);
            _logger->Log(INFO, "UpdatePassword repo query");
            curConnect.commit();
        }
        else {
            std::string msg = "Error with creating connect";
            _logger->Log(ERROR, msg);
            throw ConnectException(msg);
        }
    }
    catch (const std::exception &e)
    {
        _logger->Log(ERROR, e.what());
        std::cout << e.what() << std::endl;
    }
}

int PSQLUserRepository::DeleteUser(User &user) {
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::DeleteUser(user.GetLogin());
            pqxx::work curConnect(*_connection);
            curConnect.exec(sql);
            _logger->Log(INFO, "DeleteUser repo query");
            curConnect.commit();
        }
        else {
            std::string msg = "Error with creating connect";
            _logger->Log(ERROR, msg);
            throw ConnectException(msg);
        }
    }
    catch (const std::exception &e)
    {
        _logger->Log(ERROR, e.what());
        std::cout << e.what() << std::endl;
    }
}