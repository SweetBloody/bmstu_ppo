#ifndef SRC_PSQLMARKREPOSITORY_H
#define SRC_PSQLMARKREPOSITORY_H

#include "repository_interface/IMarkRepository.h"
#include "objects/connection/Connection.h"
#include "Query.h"
#include "logger/Logger.h"

class PSQLMarkRepository : public IMarkRepository {
public:
    PSQLMarkRepository(std::string &user, std::string &host, std::string &password, std::string &db_name, int port,
                       Logger &logger);
    std::vector<Mark> GetAllMarks();
    Mark GetMarkById(int id);
    bool MarkExist(Mark &mark);
    int AddMark(Mark &mark);
    int DeleteMark(int id);
    Mark UpdateMark(int id, Mark &mark);
private:
    pqxx::connection *_connection;
    Logger *_logger;
};


#endif //SRC_PSQLMARKREPOSITORY_H
