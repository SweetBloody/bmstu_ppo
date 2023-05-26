#ifndef SRC_PSQLMARKEDOBJECTREPOSITORY_H
#define SRC_PSQLMARKEDOBJECTREPOSITORY_H

#include "repository_interface/IMarkedObjectRepository.h"
#include "repository_interface/IMarkRepository.h"
#include "objects/connection/Connection.h"
#include "Query.h"
#include "logger/Logger.h"

class PSQLMarkedObjectRepository : public IMarkedObjectRepository {
public:
    PSQLMarkedObjectRepository(std::string &user, std::string &host, std::string &password, std::string &db_name,
                               int port, Logger &logger);
    void SetMarkRepository(IMarkRepository &mark_repository);

    std::vector<MarkedObject> GetAllMarkedObjects();
    std::vector<MarkedObject> GetAllMarkedObjectsOfImage(int image_id);
    std::vector<Dot> GetAllCoords();
    int AddMarkedObject(MarkedObject &marked_object);
    int AddAllMarkedObjectsOfImage(std::vector<MarkedObject> &marked_objects);
    int DeleteMarkedObject(int id);
    int DeleteAllMarkedObjectsOfImage(int image_id);

    std::vector<Dot> GetCoordsOfMarkedObject(int id);
    int DeleteCoordsOfMarkedObject(int id);

private:
    pqxx::connection *_connection;
    IMarkRepository *_mark_repository;
    Logger *_logger;
};


#endif //SRC_PSQLMARKEDOBJECTREPOSITORY_H
