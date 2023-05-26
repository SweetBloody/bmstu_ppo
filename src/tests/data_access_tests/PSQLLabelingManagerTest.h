#ifndef SRC_LABELINGMANAGERTEST_H
#define SRC_LABELINGMANAGERTEST_H

#include "gtest/gtest.h"
#include "managers/LabelingManager.h"
#include "psql_repository/PSQLMarkedObjectRepository.h"
#include "psql_repository/PSQLImageRepository.h"
#include "psql_repository/PSQLMarkRepository.h"
#include "const.h"

class PSQLLabelingManagerTest: public ::testing::Test {
private:
    pqxx::connection *_connection;

public:
    PSQLLabelingManagerTest( ) {
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
                std::string sql = "drop table if exists MarkedObject cascade;\n"
                                  "create table public.MarkedObject(\n"
                                  "    id serial primary key,\n"
                                  "    type int not null check (type = 0 or type = 1),\n"
                                  "    mark_id int not null,\n"
                                  "    image_id int not null\n"
                                  ");\n"
                                  "\n"
                                  "drop table if exists Coord cascade;\n"
                                  "create table public.Coord(\n"
                                  "    id serial primary key,\n"
                                  "    marked_object_id int not null,\n"
                                  "    x_coord int not null,\n"
                                  "    y_coord int not null\n"
                                  ");\n"
                                  "drop table if exists Image cascade;\n"
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

    ~PSQLLabelingManagerTest( )  {}
};

TEST_F(PSQLLabelingManagerTest, LabelImagePolygonTest) {
    PSQLImageRepository image_repository(username, host, password, dbname, port);
    ImageManager image_manager(image_repository);
    PSQLMarkedObjectRepository marked_object_repository(username, host, password, dbname, port);
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    marked_object_repository.SetMarkRepository(mark_repository);
    image_repository.SetMarkedObjectRepository(marked_object_repository);
    LabelingManager labeling_manager(image_manager, marked_object_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 1);

    Dot dot1(1, 1), dot2(1, 5), dot3(34, 25);
    std::vector<Dot> coords{dot1, dot2, dot3};

    std::string name = "car";
    Mark mark(0, name);

    image = labeling_manager.LabelImagePolygon(image, coords, mark);
    std::vector<MarkedObject> marked_objects = image.GetMarkedObjects();
    auto polygon = marked_objects[0];
    EXPECT_EQ(polygon.GetType(), POLYGON);
    EXPECT_STREQ(polygon.GetMark().GetName().c_str(), name.c_str());
    std::vector<Dot> coords_res = polygon.GetCoords();
    EXPECT_EQ(coords_res[0].GetX(), 1);
    EXPECT_EQ(coords_res[0].GetY(), 1);
    EXPECT_EQ(coords_res[1].GetX(), 1);
    EXPECT_EQ(coords_res[1].GetY(), 5);
    EXPECT_EQ(coords_res[2].GetX(), 34);
    EXPECT_EQ(coords_res[2].GetY(), 25);
}

TEST_F(PSQLLabelingManagerTest, LabelImagePolygonCoordErrorTest) {
    PSQLImageRepository image_repository(username, host, password, dbname, port);
    ImageManager image_manager(image_repository);
    PSQLMarkedObjectRepository marked_object_repository(username, host, password, dbname, port);
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    marked_object_repository.SetMarkRepository(mark_repository);
    image_repository.SetMarkedObjectRepository(marked_object_repository);
    LabelingManager labeling_manager(image_manager, marked_object_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 1);

    Dot dot1(1, 1), dot2(1, 5);
    std::vector<Dot> coords{dot1, dot2};

    std::string name = "car";
    Mark mark(0, name);

    EXPECT_THROW(labeling_manager.LabelImagePolygon(image, coords, mark), MarkedObjectCoordsException);
}

TEST_F(PSQLLabelingManagerTest, LabelImageCircleTest) {
    PSQLImageRepository image_repository(username, host, password, dbname, port);
    ImageManager image_manager(image_repository);
    PSQLMarkedObjectRepository marked_object_repository(username, host, password, dbname, port);
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    marked_object_repository.SetMarkRepository(mark_repository);
    image_repository.SetMarkedObjectRepository(marked_object_repository);
    LabelingManager labeling_manager(image_manager, marked_object_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 1);

    Dot center(1, 1), radius(20, 20);
    std::vector<Dot> coords{center, radius};

    std::string name = "car";
    Mark mark(0, name);

    image = labeling_manager.LabelImageCircle(image, center, radius, mark);
    std::vector<MarkedObject> marked_objects = image.GetMarkedObjects();
    auto circle = marked_objects[0];
    EXPECT_EQ(circle.GetType(), CIRCLE);
    EXPECT_STREQ(circle.GetMark().GetName().c_str(), name.c_str());
    std::vector<Dot> coords_res = circle.GetCoords();
    EXPECT_EQ(coords_res[0].GetX(), 1);
    EXPECT_EQ(coords_res[0].GetY(), 1);
    EXPECT_EQ(coords_res[1].GetX(), 20);
    EXPECT_EQ(coords_res[1].GetY(), 20);
}

TEST_F(PSQLLabelingManagerTest, DeleteMarkedObjectTest) {
    PSQLImageRepository image_repository(username, host, password, dbname, port);
    ImageManager image_manager(image_repository);
    PSQLMarkedObjectRepository marked_object_repository(username, host, password, dbname, port);
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    marked_object_repository.SetMarkRepository(mark_repository);
    image_repository.SetMarkedObjectRepository(marked_object_repository);
    LabelingManager labeling_manager(image_manager, marked_object_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 1);

    Dot center(1, 1), radius(20, 20);
    std::vector<Dot> coords_circ{center, radius};
    std::string name = "car";
    Mark mark(0, name);
    image = labeling_manager.LabelImageCircle(image, center, radius, mark);

    Dot dot1(1, 1), dot2(1, 5), dot3(34, 25);
    std::vector<Dot> coords_pol{dot1, dot2, dot3};
    std::string name2 = "house";
    Mark mark2(0, name2);
    image = labeling_manager.LabelImagePolygon(image, coords_pol, mark);

    std::vector<MarkedObject> marked_objects = image.GetMarkedObjects();

    auto circle = marked_objects[0];
    EXPECT_EQ(circle.GetType(), CIRCLE);
    EXPECT_STREQ(circle.GetMark().GetName().c_str(), name.c_str());
    std::vector<Dot> coords_cir = circle.GetCoords();
    EXPECT_EQ(coords_cir[0].GetX(), 1);
    EXPECT_EQ(coords_cir[0].GetY(), 1);
    EXPECT_EQ(coords_cir[1].GetX(), 20);
    EXPECT_EQ(coords_cir[1].GetY(), 20);

    auto polygon = marked_objects[1];
    EXPECT_EQ(polygon.GetType(), POLYGON);
    EXPECT_STREQ(polygon.GetMark().GetName().c_str(), name.c_str());
    std::vector<Dot> coords_res = polygon.GetCoords();
    EXPECT_EQ(coords_res[0].GetX(), 1);
    EXPECT_EQ(coords_res[0].GetY(), 1);
    EXPECT_EQ(coords_res[1].GetX(), 1);
    EXPECT_EQ(coords_res[1].GetY(), 5);
    EXPECT_EQ(coords_res[2].GetX(), 34);
    EXPECT_EQ(coords_res[2].GetY(), 25);

    labeling_manager.DeleteMarkedObject(image, circle);
    image = image_manager.GetImageById(1);
    std::vector<MarkedObject> marked_objects_res = image.GetMarkedObjects();
    polygon = marked_objects_res[0];
    EXPECT_EQ(polygon.GetType(), POLYGON);
}

TEST_F(PSQLLabelingManagerTest, DeleteAllMarkedObjectTest) {
    PSQLImageRepository image_repository(username, host, password, dbname, port);
    ImageManager image_manager(image_repository);
    PSQLMarkedObjectRepository marked_object_repository(username, host, password, dbname, port);
    PSQLMarkRepository mark_repository(username, host, password, dbname, port);
    marked_object_repository.SetMarkRepository(mark_repository);
    image_repository.SetMarkedObjectRepository(marked_object_repository);
    LabelingManager labeling_manager(image_manager, marked_object_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 1);

    Dot center(1, 1), radius(20, 20);
    std::vector<Dot> coords_circ{center, radius};
    std::string name = "car";
    Mark mark(0, name);
    image = labeling_manager.LabelImageCircle(image, center, radius, mark);

    Dot dot1(1, 1), dot2(1, 5), dot3(34, 25);
    std::vector<Dot> coords_pol{dot1, dot2, dot3};
    std::string name2 = "house";
    Mark mark2(0, name2);
    image = labeling_manager.LabelImagePolygon(image, coords_pol, mark);

    std::vector<MarkedObject> marked_objects = image.GetMarkedObjects();

    auto circle = marked_objects[0];
    EXPECT_EQ(circle.GetType(), CIRCLE);
    EXPECT_STREQ(circle.GetMark().GetName().c_str(), name.c_str());
    std::vector<Dot> coords_cir = circle.GetCoords();
    EXPECT_EQ(coords_cir[0].GetX(), 1);
    EXPECT_EQ(coords_cir[0].GetY(), 1);
    EXPECT_EQ(coords_cir[1].GetX(), 20);
    EXPECT_EQ(coords_cir[1].GetY(), 20);

    auto polygon = marked_objects[1];
    EXPECT_EQ(polygon.GetType(), POLYGON);
    EXPECT_STREQ(polygon.GetMark().GetName().c_str(), name.c_str());
    std::vector<Dot> coords_res = polygon.GetCoords();
    EXPECT_EQ(coords_res[0].GetX(), 1);
    EXPECT_EQ(coords_res[0].GetY(), 1);
    EXPECT_EQ(coords_res[1].GetX(), 1);
    EXPECT_EQ(coords_res[1].GetY(), 5);
    EXPECT_EQ(coords_res[2].GetX(), 34);
    EXPECT_EQ(coords_res[2].GetY(), 25);

    labeling_manager.DeleteAllMarkedObjects(image);
    image = image_manager.GetImageById(1);
    std::vector<MarkedObject> marked_objects_res = image.GetMarkedObjects();
    int res = marked_objects_res.empty();
    EXPECT_EQ(res, 1);
}

#endif //SRC_LABELINGMANAGERTEST_H
