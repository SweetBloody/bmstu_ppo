#ifndef SRC_ACCOUNTMANAGER_H
#define SRC_ACCOUNTMANAGER_H

#include <string>

#include "exception/Exception.h"
#include "repository_interface/IUserRepository.h"

class AccountManager {
public:
    AccountManager(IUserRepository &user_repository);

    User CreateUser(std::string &login, std::string &password);
    User GetUserByLogin(std::string &login);
    bool UserExist(std::string &login);
    bool UserExist(User &user);
    bool CheckPassword(std::string &login, std::string &password);
    User UpdatePassword(std::string &login, std::string &old_password, std::string &new_password);
    User UpdatePassword(User &user, std::string &new_password);
    int DeleteUser(User &user);

private:
    IUserRepository *_user_repository;
};


#endif //SRC_ACCOUNTMANAGER_H
