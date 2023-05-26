#include "PSQLMarkedObjectRepository.h"

PSQLMarkedObjectRepository::PSQLMarkedObjectRepository(std::string &user, std::string &host, std::string &password,
                                                       std::string &db_name,
                                                       int port, Logger &logger) {
    std::string parameters = "user=" + user +
                             " host=" + host +
                             " password=" + password +
                             " dbname=" + db_name +
                             " port=" + std::to_string(port);
    _logger = &logger;
    try {
        _connection = new pqxx::connection(parameters);
        std::cout << "fobvsbvbnsv";
        if (!_connection->is_open()) {
            std::string msg = "connection is not opened";
            _logger->Log(ERROR, msg);
            throw ConnectException(msg);
        }
    }
    catch (Exception const &e) {
        std::string msg = "Error with creating connect";
        _logger->Log(ERROR, msg);
        throw ConnectException(msg);
    }
}

void PSQLMarkedObjectRepository::SetMarkRepository(IMarkRepository &mark_repository) {
    _mark_repository = &mark_repository;
}

std::vector<MarkedObject> PSQLMarkedObjectRepository::GetAllMarkedObjects() {
    std::vector<MarkedObject> marked_objects;
    try
    {
        if (_connection->is_open()) {
            std::string sql_mo = Query::GetAllMarkedObjects();
            pqxx::work curConnect(*_connection);
            pqxx::result result_mo = curConnect.exec(sql_mo);
            _logger->Log(INFO, "GetAllMarkedObjects repo query");
            if (!result_mo.empty()) {
                for (const auto & i : result_mo) {
//                    std::vector<Dot> coords = PSQLMarkedObjectRepository::GetCoordsOfMarkedObject(i[0].as<int>());

//                    std::string sql_c = Query::GetCoordsOfMarkedObject(result_mo[i][0].as<int>());
//                    pqxx::result result_c = curConnect.exec(sql_c);
//                    std::vector<Dot> coords;
//                    if (!result_c.empty()) {
//                        for (int j = 0; j < result_c.size(); j++) {
//                            coords[j] = Dot(result_c[j][0].as<int>(), result_c[j][2].as<int>(), result_c[j][3].as<int>(), result_c[j][1].as<int>());
//                        }
//                    }

//                    std::string sql_m = Query::GetMarkById(result_mo[i][2].as<int>());
//                    pqxx::result result_m = curConnect.exec(sql_m);
//                    Mark mark;
//                    if (!result_m.empty()) {
//                        mark = Mark(result_m[0][0].as<int>(), result_m[0][1].as<std::string>());
//                    }

//                    Mark mark = _mark_repository->GetMarkById(i[2].as<int>());
                    marked_objects.emplace_back(i[0].as<int>(), i[3].as<int>(),
                                                     i[1].as<int>());
                }
            }
            else {
                std::string msg = "No marked objects";
                _logger->Log(ERROR, msg);
                throw NoDataException(msg);
            }
            curConnect.commit();

            if (!result_mo.empty()) {
                for (int i = 0; i < marked_objects.size(); i++) {
                    Mark mark = _mark_repository->GetMarkById(result_mo[i][2].as<int>());
                    std::vector<Dot> coords = GetCoordsOfMarkedObject(marked_objects[i].GetMarkedObjectId());
                    marked_objects[i].SetMark(mark);
                    marked_objects[i].SetCoords(coords);
                }
            }
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
    return marked_objects;
}

std::vector<MarkedObject> PSQLMarkedObjectRepository::GetAllMarkedObjectsOfImage(int image_id) {
    std::vector<MarkedObject> marked_objects;
    try
    {
        if (_connection->is_open()) {
            std::string sql_mo = Query::GetAllMarkedObjectsOfImage(image_id);
            pqxx::work curConnect(*_connection);
            pqxx::result result_mo = curConnect.exec(sql_mo);
            _logger->Log(INFO, "GetAllMarkedObjectsOfImage repo query");
            if (!result_mo.empty()) {
                for (const auto & i : result_mo) {
//                    std::vector<Dot> coords = GetCoordsOfMarkedObject(i[0].as<int>());
//                    Mark mark = _mark_repository->GetMarkById(i[2].as<int>());
                    marked_objects.emplace_back(i[0].as<int>(),i[3].as<int>(),
                                                     i[1].as<int>());
                }
            }
            else {
                std::string msg = "No marked objects";
                _logger->Log(ERROR, msg);
                throw NoDataException(msg);
            }
            curConnect.commit();
            if (!result_mo.empty()) {
                for (int i = 0; i < marked_objects.size(); i++) {
                    Mark mark = _mark_repository->GetMarkById(result_mo[i][2].as<int>());
                    std::vector<Dot> coords = GetCoordsOfMarkedObject(marked_objects[i].GetMarkedObjectId());
                    marked_objects[i].SetMark(mark);
                    marked_objects[i].SetCoords(coords);
                }
            }
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
    return marked_objects;
}

int PSQLMarkedObjectRepository::AddMarkedObject(MarkedObject &marked_object) {
    int id = 0;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::AddMarkedObject(marked_object.GetType(),
                                                     marked_object.GetMark().GetMarkId(),
                                                     marked_object.GetImageId());
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "AddMarkedObject repo query");
            id = result[0][0].as<int>();
            std::vector<Dot> coords = marked_object.GetCoords();
            for (auto & coord : coords) {
                sql = Query::AddCoord(id, coord.GetX(), coord.GetY());
                curConnect.exec(sql);
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
    return id;
}

int PSQLMarkedObjectRepository::AddAllMarkedObjectsOfImage(std::vector<MarkedObject> &marked_objects) {
    for (auto & marked_object : marked_objects) {
        AddMarkedObject(marked_object);
    }
}

int PSQLMarkedObjectRepository::DeleteMarkedObject(int id) {
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::DeleteCoordsOfMarkedObject(id);
            pqxx::work curConnect(*_connection);
            curConnect.exec(sql);

            sql = Query::DeleteMarkedObject(id);
            curConnect.exec(sql);
            _logger->Log(INFO, "DeleteMarkedObject repo query");

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

int PSQLMarkedObjectRepository::DeleteAllMarkedObjectsOfImage(int image_id) {
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::DeleteAllMarkedObjectsOfImage(image_id);
            pqxx::work curConnect(*_connection);
            curConnect.exec(sql);
            _logger->Log(INFO, "DeleteMarkedObjectsOfImage repo query");
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

std::vector<Dot> PSQLMarkedObjectRepository::GetAllCoords() {
    std::vector<Dot> coords;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::GetAllCoords();
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "GetAllCoords repo query");
            if (!result.empty()) {
                for (const auto & i : result) {
                    coords.emplace_back(i[0].as<int>(), i[2].as<int>(),
                            i[3].as<int>(), i[1].as<int>());
                }
            }
            else {
                std::string msg = "No coords";
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
    return coords;
}

std::vector<Dot> PSQLMarkedObjectRepository::GetCoordsOfMarkedObject(int id) {
    std::vector<Dot> coords;
    try
    {
        if (_connection->is_open()) {
            std::string sql_c = Query::GetCoordsOfMarkedObject(id);
            pqxx::work curConnect(*_connection);
            pqxx::result result_c = curConnect.exec(sql_c);
            _logger->Log(INFO, "GetCoordsOfMarkedObject repo query");
            if (!result_c.empty()) {
                for (const auto & j : result_c) {
                    coords.emplace_back(j[0].as<int>(), j[2].as<int>(), j[3].as<int>(), j[1].as<int>());
                }
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
    return coords;
}

int PSQLMarkedObjectRepository::DeleteCoordsOfMarkedObject(int id) {
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::DeleteCoordsOfMarkedObject(id);
            pqxx::work curConnect(*_connection);
            curConnect.exec(sql);
            _logger->Log(INFO, "DeleteCoordsOfMarkedObject repo query");
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
