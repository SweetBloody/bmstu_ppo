#ifndef SRC_IMAGEREPOSITORY_H
#define SRC_IMAGEREPOSITORY_H

#include <vector>

#include "repository_interface/IImageRepository.h"

class ImageRepository : public IImageRepository {
public:
//    Image LoadImage(std::string &path);
    int AddImage(Image &image) override;
    Image GetImageById(int id) override;
    Image UpdateImageById(int id, Image &new_image) override;
    std::vector<Image> GetAllImages() override;
    int DeleteImage(int id) override;


private:
    std::vector<Image> _images;
};


#endif //SRC_IMAGEREPOSITORY_H
