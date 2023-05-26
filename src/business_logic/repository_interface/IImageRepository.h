#ifndef SRC_IIMAGEREPOSITORY_H
#define SRC_IIMAGEREPOSITORY_H

#include <string>
#include <vector>

#include "objects/image/Image.h"

class IImageRepository {
public:
    virtual int AddImage(Image &image) = 0;
    virtual Image GetImageById(int id) = 0;
    virtual Image UpdateImageById(int id, Image &new_image) = 0;
    virtual std::vector<Image> GetAllImages() = 0;
    virtual int DeleteImage(int id) = 0;
};


#endif //SRC_IIMAGEREPOSITORY_H
