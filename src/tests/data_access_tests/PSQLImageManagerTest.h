#ifndef SRC_IMAGEMANAGERTEST_H
#define SRC_IMAGEMANAGERTEST_H

#include "gtest/gtest.h"
#include "managers/ImageManager.h"
#include "psql_repository/PSQLMarkRepository.h"
#include "psql_repository/PSQLMarkedObjectRepository.h"
#include "psql_repository/PSQLImageRepository.h"
#include "const.h"

class PSQLImageManagerTest: public ::testing::Test {
private:
    pqxx::connection *_connection;

public:
    PSQLImageManagerTest( ) {
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
                std::string sql = "drop table if exists Image cascade;\n"
                                  "create table public.Image(\n"
                                  "    id serial primary key,\n"
                                  "    image_path text not null\n"
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

    ~PSQLImageManagerTest( )  {}
};

TEST_F(PSQLImageManagerTest, LoadImageTest) {
    PSQLImageRepository image_repository(username, host, password, dbname, port);
    PSQLMarkedObjectRepository marked_object_repository(username, host, password, dbname, port);
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    marked_object_repository.SetMarkRepository(mark_repository);
    image_repository.SetMarkedObjectRepository(marked_object_repository);
    ImageManager image_manager(image_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 1);

    Image image2 = image_manager.GetImageById(1);
    EXPECT_EQ(image2.GetImageId(), 1);
}

//TEST(ImageManagerTest, LoadImageErrorTest) {
//    ImageRepository image_repository;
//    ImageManager image_manager(image_repository);
//    std::string path = "mock_repository/img/image.png";
//
//    Image image = image_manager.LoadImage(path);
//    EXPECT_THROW(Image image(path), LoadImageException);
//}

TEST_F(PSQLImageManagerTest, UpdateImageTest) {
    PSQLImageRepository image_repository(username, host, password, dbname, port);
    PSQLMarkedObjectRepository marked_object_repository(username, host, password, dbname, port);
    image_repository.SetMarkedObjectRepository(marked_object_repository);
    ImageManager image_manager(image_repository);
    std::string path = "img/circle_color.png",
                path2 = "img/map_ryba.jpg";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 1);

    Image image2(0, path2);
    image = image_manager.UpdateImageById(image.GetImageId(), image2);
    EXPECT_EQ(image.GetImageId(), 1);
}

TEST_F(PSQLImageManagerTest, DeleteImageTest) {
    PSQLImageRepository image_repository(username, host, password, dbname, port);
    PSQLMarkedObjectRepository marked_object_repository(username, host, password, dbname, port);
    image_repository.SetMarkedObjectRepository(marked_object_repository);
    ImageManager image_manager(image_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 1);

    image_manager.DeleteImage(1);
    Image image2 = image_manager.GetImageById(1);
    EXPECT_THROW(image_manager.GetImageById(1), NoDataException);
}


#endif //SRC_IMAGEMANAGERTEST_H
