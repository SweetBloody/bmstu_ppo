#ifndef SRC_IMAGEMANAGERTEST_H
#define SRC_IMAGEMANAGERTEST_H

#include "gtest/gtest.h"
#include "managers/ImageManager.h"
#include "mock_repository/ImageRepository.h"
#include "objects/marked_object/circle_marked_object/CircleMarkedObject.h"
#include "objects/marked_object/polygon_marked_object/PolygonMarkedObject.h"

TEST(ImageManagerTest, LoadImageTest) {
    ImageRepository image_repository;
    ImageManager image_manager(image_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 0);

    Image image2 = image_manager.GetImageById(0);
    EXPECT_EQ(image2.GetImageId(), 0);
}

//TEST(ImageManagerTest, LoadImageErrorTest) {
//    ImageRepository image_repository;
//    ImageManager image_manager(image_repository);
//    std::string path = "mock_repository/img/image.png";
//
//    Image image = image_manager.LoadImage(path);
//    EXPECT_THROW(Image image(path), LoadImageException);
//}

TEST(ImageManagerTest, UpdateImageTest) {
    ImageRepository image_repository;
    ImageManager image_manager(image_repository);
    std::string path = "img/circle_color.png",
                path2 = "img/map_ryba.jpg";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 0);

    Image image2(0, path2);
    image = image_manager.UpdateImageById(image.GetImageId(), image2);
    EXPECT_EQ(image.GetImageId(), 0);
}

TEST(ImageManagerTest, DeleteImageTest) {
    ImageRepository image_repository;
    ImageManager image_manager(image_repository);
    std::string path = "img/circle_color.png";

    Image image = image_manager.LoadImage(path);
    EXPECT_EQ(image.GetImageId(), 0);

    image_manager.DeleteImage(0);
    EXPECT_THROW(image_manager.GetImageById(0), NoDataException);
}

//TEST(ImageManagerTest, AddMarkedObjectTest) {
//    ImageRepository image_repository;
//    ImageManager image_manager(image_repository);
//    std::string path = "img/circle_color.png";
//
//    Image image = image_manager.LoadImage(path);
//    EXPECT_EQ(image.GetImageId(), 0);
//
//    CircleMarkedObject circle_mo(0, 12, &Dot(3, 4), &Mark((std::string &) "car"));
//
//    image_manager.DeleteImage(0);
//    EXPECT_THROW(image_manager.GetImageById(0), NoDataException);
//}

#endif //SRC_IMAGEMANAGERTEST_H
