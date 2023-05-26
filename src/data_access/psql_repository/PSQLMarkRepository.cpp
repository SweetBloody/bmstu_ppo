#include "PSQLMarkRepository.h"

PSQLMarkRepository::PSQLMarkRepository(std::string &user, std::string &host, std::string &password,
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

std::vector<Mark> PSQLMarkRepository::GetAllMarks() {
    std::vector<Mark> marks;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::GetAllMarks();
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "GetAllMarks repo query");
            if (!result.empty()) {
                for (const auto & i : result) {
                    marks.emplace_back(i[0].as<int>(), i[1].as<std::string>());
                }
            }
            else {
                std::string msg = "No marks";
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
    return marks;
}

Mark PSQLMarkRepository::GetMarkById(int id) {
    Mark mark;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::GetMarkById(id);
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "GetMarkById repo query");
            if (!result.empty()) {
                mark = Mark(result[0][0].as<int>(), result[0][1].as<std::string>());
            }
            else {
                std::string msg = "No such mark";
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
    return mark;
}

bool PSQLMarkRepository::MarkExist(Mark &mark) {
    bool flag = false;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::GetMarkByName(mark.GetName());
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "MarkExist repo query");
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

int PSQLMarkRepository::AddMark(Mark &mark) {
    int id = 0;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::AddMark(mark.GetName());
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "AddMark repo query");
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
    return  id;
}

int PSQLMarkRepository::DeleteMark(int id) {
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::DeleteMark(id);
            pqxx::work curConnect(*_connection);
            curConnect.exec(sql);
            _logger->Log(INFO, "DeleteMark repo query");
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

Mark PSQLMarkRepository::UpdateMark(int id, Mark &mark) {
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::UpdateMark(id, mark.GetName());
            pqxx::work curConnect(*_connection);
            curConnect.exec(sql);
            _logger->Log(INFO, "UpdateMark repo query");
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
    mark.SetMarkId(id);
    return mark;
}