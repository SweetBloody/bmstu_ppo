#ifndef SRC_MARKMANAGERTEST_H
#define SRC_MARKMANAGERTEST_H

#include "gtest/gtest.h"
#include "managers/MarkManager.h"
#include "psql_repository/PSQLMarkRepository.h"
#include "const.h"

class PSQLMarkManagerTest: public ::testing::Test {
private:
    pqxx::connection *_connection;

public:
    PSQLMarkManagerTest( ) {
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
                std::string sql = "drop table if exists Mark cascade;\n"
                                  "create table public.Mark(\n"
                                  "    id serial primary key,\n"
                                  "    name text not null\n"
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

    ~PSQLMarkManagerTest( )  {}
};

TEST_F(PSQLMarkManagerTest, CreateMarkTest) {
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    MarkManager mark_manager(mark_repository);
    std::string name = "car";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 1);

    int res = mark_repository.MarkExist(mark);
    EXPECT_EQ(res, 1);
    EXPECT_STREQ(mark.GetName().c_str(), name.c_str());
}

TEST_F(PSQLMarkManagerTest, CreateMarkAlreadyExistTest) {
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    MarkManager mark_manager(mark_repository);
    std::string name = "car";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 1);

    EXPECT_THROW(mark_manager.CreateMark(name), AlreadyExistException);
}

TEST_F(PSQLMarkManagerTest, GetAllMarksTest) {
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    MarkManager mark_manager(mark_repository);
    std::string name = "car", name2 = "house", name3 = "hfhghg";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 1);
    Mark mark2 = mark_manager.CreateMark(name2);
    EXPECT_EQ(mark2.GetMarkId(), 2);
    Mark mark3 = mark_manager.CreateMark(name3);
    EXPECT_EQ(mark3.GetMarkId(), 3);

    std::vector<Mark> marks = mark_manager.GetAllMarks();
    EXPECT_STREQ(marks[0].GetName().c_str(), name.c_str());
    EXPECT_STREQ(marks[1].GetName().c_str(), name2.c_str());
    EXPECT_STREQ(marks[2].GetName().c_str(), name3.c_str());
}

TEST_F(PSQLMarkManagerTest, GetAllMarksNoDataTest) {
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    MarkManager mark_manager(mark_repository);

    EXPECT_THROW(mark_manager.GetAllMarks(), NoDataException);
}

TEST_F(PSQLMarkManagerTest, GetMarkByIdTest) {
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    MarkManager mark_manager(mark_repository);
    std::string name = "car", name2 = "house", name3 = "hfhghg";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 1);
    Mark mark2 = mark_manager.CreateMark(name2);
    EXPECT_EQ(mark2.GetMarkId(), 2);
    Mark mark3 = mark_manager.CreateMark(name3);
    EXPECT_EQ(mark3.GetMarkId(), 3);

    Mark mark_res = mark_manager.GetMarkById(2);
    EXPECT_STREQ(mark_res.GetName().c_str(), name2.c_str());
    Mark mark_res2 = mark_manager.GetMarkById(3);
    EXPECT_STREQ(mark_res2.GetName().c_str(), name3.c_str());
}

TEST_F(PSQLMarkManagerTest, GetMarkByIdNoDataTest) {
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    MarkManager mark_manager(mark_repository);
    std::string name = "car", name2 = "house", name3 = "hfhghg";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 1);
    Mark mark2 = mark_manager.CreateMark(name2);
    EXPECT_EQ(mark2.GetMarkId(), 2);
    Mark mark3 = mark_manager.CreateMark(name3);
    EXPECT_EQ(mark3.GetMarkId(), 3);

    EXPECT_THROW(mark_manager.GetMarkById(5), NoDataException);
}

TEST_F(PSQLMarkManagerTest, DeleteMarkTest) {
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    MarkManager mark_manager(mark_repository);
    std::string name = "car", name2 = "house", name3 = "hfhghg";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 1);
    Mark mark2 = mark_manager.CreateMark(name2);
    EXPECT_EQ(mark2.GetMarkId(), 2);
    Mark mark3 = mark_manager.CreateMark(name3);
    EXPECT_EQ(mark3.GetMarkId(), 3);

    mark_manager.DeleteMark(3);
    EXPECT_THROW(mark_manager.GetMarkById(3), NoDataException);
}

TEST_F(PSQLMarkManagerTest, UpdateMarkTest) {
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    MarkManager mark_manager(mark_repository);
    std::string name = "car", name2 = "house", name3 = "hfhghg",
                new_name = "car2";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 1);
    Mark mark2 = mark_manager.CreateMark(name2);
    EXPECT_EQ(mark2.GetMarkId(), 2);
    Mark mark3 = mark_manager.CreateMark(name3);
    EXPECT_EQ(mark3.GetMarkId(), 3);

    mark_manager.UpdateMark(1, new_name);
    Mark mark_upd = mark_manager.GetMarkById(1);
    EXPECT_STREQ(mark_upd.GetName().c_str(), new_name.c_str());
}

#endif //SRC_MARKMANAGERTEST_H
