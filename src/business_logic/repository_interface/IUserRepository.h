#ifndef PPO_IUSERREPOSITORY_H
#define PPO_IUSERREPOSITORY_H

#include <string>
#include <vector>

#include "objects/user/User.h"

class IUserRepository {
public:
    virtual User GetUserById(int id) = 0;
    virtual User GetUserByLogin(std::string &login) = 0;
    virtual bool UserExist(User &user) = 0;
    virtual bool UserExist(std::string &login) = 0;
    virtual int AddUser(User &user) = 0;
    virtual bool CheckPassword(std::string &login, std::string &password) = 0;
    virtual int UpdatePassword(User &user, std::string &new_password) = 0;
    virtual int DeleteUser(User &user) = 0;

};


#endif //PPO_IUSERREPOSITORY_H
