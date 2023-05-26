#ifndef SRC_IMAGEMANAGER_H
#define SRC_IMAGEMANAGER_H

#include <vector>

#include "exception/Exception.h"
#include "repository_interface/IImageRepository.h"
#include "repository_interface/IMarkedObjectRepository.h"
#include "objects/image/Image.h"
#include "objects/marked_object/MarkedObject.h"

class ImageManager {
public:
    ImageManager() = default;
    ImageManager(IImageRepository &image_repository, IMarkedObjectRepository &marked_object_repository);

    std::vector<Image> GetAllImages();
    Image GetImageById(int id);
    Image LoadImage(std::string &path);
    Image UpdateImageById(int id, Image &new_image);
    int DeleteImage(int id);
    int AddMarkedObjectToImage(Image &image, MarkedObject &marked_object);
    int DeleteMarkedObjectFromImage(Image &image, int id);
    int DeleteMarkedObject(int id);
    std::vector<MarkedObject> GetAllMarkedObjectsOfImage(Image &image);

private:
    IImageRepository *_image_repository;
    IMarkedObjectRepository *_marked_object_repository;
};


#endif //SRC_IMAGEMANAGER_H
