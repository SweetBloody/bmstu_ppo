#ifndef SRC_PSQLUSERREPOSITORY_H
#define SRC_PSQLUSERREPOSITORY_H

#include "repository_interface/IUserRepository.h"
#include "objects/connection/Connection.h"
#include "Query.h"
#include "logger/Logger.h"

class PSQLUserRepository : public IUserRepository {
public:
    PSQLUserRepository(std::string &user, std::string &host, std::string &password, std::string &db_name, int port,
                       Logger &logger);
    User GetUserById(int id);
    User GetUserByLogin(std::string &login);
    bool UserExist(User &user);
    bool UserExist(std::string &login);
    int AddUser(User &user);
    bool CheckPassword(std::string &login, std::string &password);
    int UpdatePassword(User &user, std::string &new_password);
    int DeleteUser(User &user);

private:
    pqxx::connection *_connection;
    Logger *_logger;
};


#endif //SRC_PSQLUSERREPOSITORY_H
