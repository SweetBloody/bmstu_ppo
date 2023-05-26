#ifndef SRC_PSQLACCOUNTMANAGERTEST_H
#define SRC_PSQLACCOUNTMANAGERTEST_H

#include "gtest/gtest.h"
#include "managers/AccountManager.h"
#include "psql_repository/PSQLUserRepository.h"
#include "const.h"

class PSQLAccountManagerTest: public ::testing::Test {
private:
    pqxx::connection *_connection;

public:
    PSQLAccountManagerTest( ) {
        std::string parameters = "user=" + username +
                                 " host=" + host +
                                 " password=" + password +
                                 " dbname=" + dbname +
                                 " port=" + std::to_string(port);
        try {
            _connection = new pqxx::connection(parameters);

            if (!_connection->is_open()) {
                std::string msg = "connection is not opened";
                throw ConnectException(msg);
            }
        }
        catch (Exception) {
            std::string msg = "Error with creating connect";
            throw ConnectException(msg);
        }
    }

    void SetUp( ) {
        try
        {
            if (_connection->is_open()) {
                std::string sql = "drop table if exists Users cascade;\n"
                                  "create table public.Users(\n"
                                  "    id serial primary key,\n"
                                  "    login varchar(15) not null,\n"
                                  "    password text not null,\n"
                                  "    privilege_lvl int not null\n"
                                  ");";
                pqxx::work curConnect(*_connection);
                curConnect.exec(sql);
                curConnect.commit();
            }
            else {
                std::string msg = "Error with creating connect";
                throw ConnectException(msg);
            }
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    void TearDown( ) {}

    ~PSQLAccountManagerTest( )  {}
};

TEST_F(PSQLAccountManagerTest, CreateUserTest) {
    PSQLUserRepository user_repository(username, host, password, dbname, port);
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";

    User user = account_manager.CreateUser(login, password);

    EXPECT_STREQ(user.GetLogin().c_str(), login.c_str());
    EXPECT_STREQ(user.GetPassword().c_str(), password.c_str());
    EXPECT_EQ(user.GetUserId(), 1);
}

TEST_F(PSQLAccountManagerTest, CreateExistedUserTest) {
    PSQLUserRepository user_repository(username, host, password, dbname, port);
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";
    User user1(0, login, password);

    int id = user_repository.AddUser(user1);
    user1.SetUserId(id);

    ASSERT_THROW(account_manager.CreateUser(login, password), AlreadyExistException);
}

TEST_F(PSQLAccountManagerTest, UserExistedTest) {
    PSQLUserRepository user_repository(username, host, password, dbname, port);
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";

    User user = account_manager.CreateUser(login, password);
    int res1 = account_manager.UserExist(login);
    int res2 = account_manager.UserExist(user);

    EXPECT_EQ(res1, 1);
    EXPECT_EQ(res2, 1);
}

TEST_F(PSQLAccountManagerTest, CheckPasswordCorrectTest) {
    PSQLUserRepository user_repository(username, host, password, dbname, port);
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";

    User user = account_manager.CreateUser(login, password);
    int res1 = account_manager.CheckPassword(login, password);

    EXPECT_EQ(res1, 1);
}

TEST_F(PSQLAccountManagerTest, CheckPasswordUserNotExistTest) {
    PSQLUserRepository user_repository(username, host, password, dbname, port);
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";
    std::string login2 = "Userr";

    User user = account_manager.CreateUser(login, password);

    ASSERT_THROW(account_manager.CheckPassword(login2, password), UserNotExistException);
}

TEST_F(PSQLAccountManagerTest, CheckPasswordWrongPasswordTest) {
    PSQLUserRepository user_repository(username, host, password, dbname, port);
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";
    std::string password2 = "321";

    User user = account_manager.CreateUser(login, password);

    ASSERT_THROW(account_manager.CheckPassword(login, password2), WrongPasswordException);
}

TEST_F(PSQLAccountManagerTest, UpdatePasswordCorrectTest) {
    PSQLUserRepository user_repository(username, host, password, dbname, port);
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", old_password = "123", new_password = "321";

    User user = account_manager.CreateUser(login, old_password);
    account_manager.UpdatePassword(login, old_password, new_password);

    User user_res = user_repository.GetUserByLogin(login);

    EXPECT_STREQ(user_res.GetLogin().c_str(), login.c_str());
    EXPECT_STREQ(user_res.GetPassword().c_str(), new_password.c_str());
}

TEST_F(PSQLAccountManagerTest, UpdatePasswordUserNotExistTest) {
    PSQLUserRepository user_repository(username, host, password, dbname, port);
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", login2 = "Userr",
            old_password = "123", new_password = "321";

    User user = account_manager.CreateUser(login, old_password);

    ASSERT_THROW(account_manager.UpdatePassword(login2, old_password, new_password), UserNotExistException);
}

TEST_F(PSQLAccountManagerTest, UpdatePasswordWrongOldPasswordTest) {
    PSQLUserRepository user_repository(username, host, password, dbname, port);
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", old_password = "123",
            old_password2 = "12333", new_password = "321";

    User user = account_manager.CreateUser(login, old_password);

    ASSERT_THROW(account_manager.UpdatePassword(login, old_password2, new_password), WrongPasswordException);
}

TEST_F(PSQLAccountManagerTest, DeleteUserCorrectTest) {
    PSQLUserRepository user_repository(username, host, password, dbname, port);
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";

    User user = account_manager.CreateUser(login, password);
    int res1 = account_manager.UserExist(user);
    EXPECT_EQ(res1, 1);

    account_manager.DeleteUser(user);
    int res2 = account_manager.UserExist(user);
    EXPECT_EQ(res2, 0);
}

TEST_F(PSQLAccountManagerTest, DeleteUserUserNotExistTest) {
    PSQLUserRepository user_repository(username, host, password, dbname, port);
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123",
            login2 = "Userr", password2 = "321";

    User user = account_manager.CreateUser(login, password);
    int res1 = account_manager.UserExist(user);
    EXPECT_EQ(res1, 1);

    User user2(1, login2, password2);
    ASSERT_THROW(account_manager.DeleteUser(user2), UserNotExistException);
}


#endif //SRC_PSQLACCOUNTMANAGERTEST_H
