#ifndef SRC_LABELINGMANAGERTEST_H
#define SRC_LABELINGMANAGERTEST_H

#include "gtest/gtest.h"
#include "managers/LabelingManager.h"
#include "mock_repository/MarkedObjectRepository.h"

TEST(LabelingManagerTest, LabelImagePolygonTest) {
    ImageRepository image_repository;
    ImageManager image_manager(image_repository);
    MarkedObjectRepository marked_object_repository;
    LabelingManager labeling_manager(image_manager, marked_object_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 0);

    Dot dot1(1, 1), dot2(1, 5), dot3(34, 25);
    std::vector<Dot> coords{dot1, dot2, dot3};

    std::string name = "car";
    Mark mark(0, name);

    image = labeling_manager.LabelImagePolygon(image, coords, mark);
    std::vector<MarkedObject> marked_objects = image.GetAllMarkedObjects();
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

TEST(LabelingManagerTest, LabelImagePolygonCoordErrorTest) {
    ImageRepository image_repository;
    ImageManager image_manager(image_repository);
    MarkedObjectRepository marked_object_repository;
    LabelingManager labeling_manager(image_manager, marked_object_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 0);

    Dot dot1(1, 1), dot2(1, 5);
    std::vector<Dot> coords{dot1, dot2};

    std::string name = "car";
    Mark mark(0, name);

    EXPECT_THROW(labeling_manager.LabelImagePolygon(image, coords, mark), MarkedObjectCoordsException);
}

TEST(LabelingManagerTest, LabelImageCircleTest) {
    ImageRepository image_repository;
    ImageManager image_manager(image_repository);
    MarkedObjectRepository marked_object_repository;
    LabelingManager labeling_manager(image_manager, marked_object_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 0);

    Dot center(1, 1), radius(20, 20);
    std::vector<Dot> coords{center, radius};

    std::string name = "car";
    Mark mark(0, name);

    image = labeling_manager.LabelImageCircle(image, center, radius, mark);
    std::vector<MarkedObject> marked_objects = image.GetAllMarkedObjects();
    auto circle = marked_objects[0];
    EXPECT_EQ(circle.GetType(), CIRCLE);
    EXPECT_STREQ(circle.GetMark().GetName().c_str(), name.c_str());
    std::vector<Dot> coords_res = circle.GetCoords();
    EXPECT_EQ(coords_res[0].GetX(), 1);
    EXPECT_EQ(coords_res[0].GetY(), 1);
    EXPECT_EQ(coords_res[1].GetX(), 20);
    EXPECT_EQ(coords_res[1].GetY(), 20);
}

TEST(LabelingManagerTest, DeleteMarkedObjectTest) {
    ImageRepository image_repository;
    ImageManager image_manager(image_repository);
    MarkedObjectRepository marked_object_repository;
    LabelingManager labeling_manager(image_manager, marked_object_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 0);

    Dot center(1, 1), radius(20, 20);
    std::vector<Dot> coords_circ{center, radius};
    std::string name = "car";
    Mark mark(0, name);
    image = labeling_manager.LabelImageCircle(image, center, radius, mark);

    Dot dot1(1, 1), dot2(1, 5), dot3(34, 25);
    std::vector<Dot> coords_pol{dot1, dot2, dot3};
    std::string name2 = "house";
    Mark mark2(1, name2);
    image = labeling_manager.LabelImagePolygon(image, coords_pol, mark);

    std::vector<MarkedObject> marked_objects = image.GetAllMarkedObjects();

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
    image = image_manager.GetImageById(0);
    std::vector<MarkedObject> marked_objects_res = image.GetAllMarkedObjects();
    polygon = marked_objects_res[0];
    EXPECT_EQ(polygon.GetType(), POLYGON);
}

TEST(LabelingManagerTest, DeleteAllMarkedObjectTest) {
    ImageRepository image_repository;
    ImageManager image_manager(image_repository);
    MarkedObjectRepository marked_object_repository;
    LabelingManager labeling_manager(image_manager, marked_object_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 0);

    Dot center(1, 1), radius(20, 20);
    std::vector<Dot> coords_circ{center, radius};
    std::string name = "car";
    Mark mark(0, name);
    image = labeling_manager.LabelImageCircle(image, center, radius, mark);

    Dot dot1(1, 1), dot2(1, 5), dot3(34, 25);
    std::vector<Dot> coords_pol{dot1, dot2, dot3};
    std::string name2 = "house";
    Mark mark2(1, name2);
    image = labeling_manager.LabelImagePolygon(image, coords_pol, mark);

    std::vector<MarkedObject> marked_objects = image.GetAllMarkedObjects();

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
    image = image_manager.GetImageById(0);
    std::vector<MarkedObject> marked_objects_res = image.GetAllMarkedObjects();
    int res = marked_objects_res.empty();
    EXPECT_EQ(res, 1);
}

#endif //SRC_LABELINGMANAGERTEST_H
