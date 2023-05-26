#include "PSQLImageRepository.h"
#include "logger/Logger.h"


PSQLImageRepository::PSQLImageRepository(std::string &user, std::string &host, std::string &password,
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
    catch (Exception const &e) {
        std::string msg = "Error with creating connect";
        _logger->Log(ERROR, msg);
        throw ConnectException(msg);
    }
}

void PSQLImageRepository::SetMarkedObjectRepository(IMarkedObjectRepository &marked_object_repository) {
    _marked_object_repository = &marked_object_repository;
}

int PSQLImageRepository::AddImage(Image &image) {
    int id = 0;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::AddImage(image.GetPath());
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "AddImage repo query");
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

Image PSQLImageRepository::GetImageById(int id) {
    Image image;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::GetImageById(id);
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "GetImageById repo query");
            if (!result.empty()) {
                image = Image(result[0][0].as<int>(), result[0][1].as<std::string>());
            }
            else {
                std::string msg = "No such image";
                _logger->Log(ERROR, msg);
                throw NoDataException(msg);
            }
            curConnect.commit();

            if(!result.empty()) {
                std::vector<MarkedObject> marked_objects = _marked_object_repository->GetAllMarkedObjectsOfImage(result[0][0].as<int>());
                if (!marked_objects.empty()) {
                    image.SetMarkedObjects(marked_objects);
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
    return image;
}

Image PSQLImageRepository::UpdateImageById(int id, Image &new_image) {
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::UpdateImageById(id, new_image.GetPath());
            pqxx::work curConnect(*_connection);
            curConnect.exec(sql);
            _logger->Log(INFO, "UpdateImageById repo query");
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
    new_image.SetImageId(id);
    return new_image;
}

std::vector<Image> PSQLImageRepository::GetAllImages() {
    std::vector<Image> images;
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::GetAllImages();
            pqxx::work curConnect(*_connection);
            pqxx::result result = curConnect.exec(sql);
            _logger->Log(INFO, "GetAllImages repo query");
            if (!result.empty()) {
                for (const auto & i : result) {
                    images.emplace_back(i[0].as<int>(), i[1].as<std::string>());
                }
            }
            else {
                std::string msg = "No such image";
                _logger->Log(ERROR, msg);
                throw NoDataException(msg);
            }
            curConnect.commit();

            if (!result.empty()) {
                for (auto & image : images) {
                    std::vector<MarkedObject> marked_objects = _marked_object_repository->GetAllMarkedObjectsOfImage(image.GetImageId());
                    image.SetMarkedObjects(marked_objects);
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
    return images;
}

int PSQLImageRepository::DeleteImage(int id) {
    try
    {
        if (_connection->is_open()) {
            std::string sql = Query::DeleteImage(id);
            pqxx::work curConnect(*_connection);
            curConnect.exec(sql);
            _logger->Log(INFO, "DeleteImage repo query");
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