#ifndef SRC_MARKMANAGERTEST_H
#define SRC_MARKMANAGERTEST_H

#include "gtest/gtest.h"
#include "managers/MarkManager.h"
#include "mock_repository/MarkRepository.h"

TEST(MarkManagerTest, CreateMarkTest) {
    MarkRepository mark_repository;
    MarkManager mark_manager(mark_repository);
    std::string name = "car";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 0);

    int res = mark_repository.MarkExist(mark);
    EXPECT_EQ(res, 1);
    EXPECT_STREQ(mark.GetName().c_str(), name.c_str());
}

TEST(MarkManagerTest, CreateMarkAlreadyExistTest) {
    MarkRepository mark_repository;
    MarkManager mark_manager(mark_repository);
    std::string name = "car";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 0);

    EXPECT_THROW(mark_manager.CreateMark(name), AlreadyExistException);
}

TEST(MarkManagerTest, GetAllMarksTest) {
    MarkRepository mark_repository;
    MarkManager mark_manager(mark_repository);
    std::string name = "car", name2 = "house", name3 = "hfhghg";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 0);
    Mark mark2 = mark_manager.CreateMark(name2);
    EXPECT_EQ(mark2.GetMarkId(), 1);
    Mark mark3 = mark_manager.CreateMark(name3);
    EXPECT_EQ(mark3.GetMarkId(), 2);

    std::vector<Mark> marks = mark_manager.GetAllMarks();
    EXPECT_STREQ(marks[0].GetName().c_str(), name.c_str());
    EXPECT_STREQ(marks[1].GetName().c_str(), name2.c_str());
    EXPECT_STREQ(marks[2].GetName().c_str(), name3.c_str());
}

TEST(MarkManagerTest, GetAllMarksNoDataTest) {
    MarkRepository mark_repository;
    MarkManager mark_manager(mark_repository);

    EXPECT_THROW(mark_manager.GetAllMarks(), NoDataException);
}

TEST(MarkManagerTest, GetMarkByIdTest) {
    MarkRepository mark_repository;
    MarkManager mark_manager(mark_repository);
    std::string name = "car", name2 = "house", name3 = "hfhghg";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 0);
    Mark mark2 = mark_manager.CreateMark(name2);
    EXPECT_EQ(mark2.GetMarkId(), 1);
    Mark mark3 = mark_manager.CreateMark(name3);
    EXPECT_EQ(mark3.GetMarkId(), 2);

    Mark mark_res = mark_manager.GetMarkById(1);
    EXPECT_STREQ(mark_res.GetName().c_str(), name2.c_str());
    Mark mark_res2 = mark_manager.GetMarkById(2);
    EXPECT_STREQ(mark_res2.GetName().c_str(), name3.c_str());
}

TEST(MarkManagerTest, GetMarkByIdNoDataTest) {
    MarkRepository mark_repository;
    MarkManager mark_manager(mark_repository);
    std::string name = "car", name2 = "house", name3 = "hfhghg";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 0);
    Mark mark2 = mark_manager.CreateMark(name2);
    EXPECT_EQ(mark2.GetMarkId(), 1);
    Mark mark3 = mark_manager.CreateMark(name3);
    EXPECT_EQ(mark3.GetMarkId(), 2);

    EXPECT_THROW(mark_manager.GetMarkById(4), NoDataException);
}

TEST(MarkManagerTest, DeleteMarkTest) {
    MarkRepository mark_repository;
    MarkManager mark_manager(mark_repository);
    std::string name = "car", name2 = "house", name3 = "hfhghg";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 0);
    Mark mark2 = mark_manager.CreateMark(name2);
    EXPECT_EQ(mark2.GetMarkId(), 1);
    Mark mark3 = mark_manager.CreateMark(name3);
    EXPECT_EQ(mark3.GetMarkId(), 2);

    mark_manager.DeleteMark(2);
    EXPECT_THROW(mark_manager.GetMarkById(2), NoDataException);
}

TEST(MarkManagerTest, UpdateMarkTest) {
    MarkRepository mark_repository;
    MarkManager mark_manager(mark_repository);
    std::string name = "car", name2 = "house", name3 = "hfhghg",
                new_name = "car2";

    Mark mark = mark_manager.CreateMark(name);
    EXPECT_EQ(mark.GetMarkId(), 0);
    Mark mark2 = mark_manager.CreateMark(name2);
    EXPECT_EQ(mark2.GetMarkId(), 1);
    Mark mark3 = mark_manager.CreateMark(name3);
    EXPECT_EQ(mark3.GetMarkId(), 2);

    mark_manager.UpdateMark(0, new_name);
    Mark mark_upd = mark_manager.GetMarkById(0);
    EXPECT_STREQ(mark_upd.GetName().c_str(), new_name.c_str());
}

#endif //SRC_MARKMANAGERTEST_H
