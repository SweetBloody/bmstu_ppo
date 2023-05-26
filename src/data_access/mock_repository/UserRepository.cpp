#include "UserRepository.h"

//UserRepository::UserRepository() {
//    _users = std::vector<User>();
//}

User UserRepository::GetUserById(int id) {
    if (_users.empty()) {
        std::string msg = "No data";
        throw NoDataException(msg);
    }
    User user(0, (std::string &) "", (std::string &) "");

    for (auto & _user : _users)
        if (_user.GetUserId() == id) {
            user = _user;
            break;
        }

    if (user.GetLogin().empty()) {
        std::string msg = "No user";
        throw UserNotExistException(msg);
    }
    return user;
}

User UserRepository::GetUserByLogin(std::string &login) {
    if (_users.empty()) {
        std::string msg = "No data";
        throw NoDataException(msg);
    }
    std::string login1, password;
    User user(0, login1, password);

    for (auto & _user : _users)
        if (_user.GetLogin() == login) {
            user = _user;
            break;
        }

    if (user.GetLogin().empty()) {
        std::string msg = "No user";
        throw UserNotExistException(msg);
    }
    return user;
}


int UserRepository::AddUser(User &user) {
    _users.push_back(user);
    return _users.size() - 1;
}

bool UserRepository::UserExist(User &user) {
//    std::find_if(_users.begin(), _users.end(), [])
    for (auto & _user : _users)
        if (_user.GetLogin() == user.GetLogin())
            return true;
    return false;

//    std::find_if(_users.begin(), _users.end(), User::UserCompareByLogin);
//    return (user == _login);
}

bool UserRepository::UserExist(std::string &login) {
    for (auto & _user : _users)
        if (_user.GetLogin() == login)
            return true;
    return false;
}


bool UserRepository::CheckPassword(std::string &login, std::string &password) {
    for (auto & _user : _users)
        if (_user.GetLogin() == login && _user.GetPassword() == password)
            return true;
    return false;
}

int UserRepository::UpdatePassword(User &user, std::string &new_password) {
    for (auto & _user : _users)
        if (_user.GetLogin() == user.GetLogin()) {
            _user.SetPassword(new_password);
            return 0;
        }
    return 1;
}

int UserRepository::DeleteUser(User &user) {
    _users.erase(_users.begin() + user.GetUserId());
    return 0;
}