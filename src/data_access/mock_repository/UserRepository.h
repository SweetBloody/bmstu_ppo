#ifndef SRC_USERREPOSITORY_H
#define SRC_USERREPOSITORY_H

#include <string>
#include <vector>

#include "repository_interface/IUserRepository.h"
//#include "business_logic/objects/user/User.h"

class UserRepository : public IUserRepository {
public:
//    UserRepository();
    User GetUserById(int id);
    User GetUserByLogin(std::string &login);
    bool UserExist(User &user) override;
    bool UserExist(std::string &login) override;
    int AddUser(User &user) override;
    bool CheckPassword(std::string &login, std::string &password) override;
    int UpdatePassword(User &user, std::string &new_password) override;
    int DeleteUser(User &user) override;

private:
    std::vector<User> _users;
};


#endif //SRC_USERREPOSITORY_H
