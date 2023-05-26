#ifndef SRC_IMAGE_H
#define SRC_IMAGE_H

#include <string>
#include <vector>

#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/opencv.hpp>

#include "exception/Exception.h"
#include "objects/marked_object/MarkedObject.h"

class Image {
public:
    Image() = default;
    Image(int id, const std::string &path);
    Image(int id, const std::string &path, std::vector<MarkedObject> &marked_object);

    int GetImageId();
    void SetImageId(int id);
    cv::Mat GetImage();
    std::string GetPath();
    void SetPath(std::string &path);
    std::vector<MarkedObject> GetMarkedObjects();
    void SetMarkedObjects(std::vector<MarkedObject> marked_objects);

    int AddMarkedObject(MarkedObject &object);
    int DeleteMarkedObjectById(int id);
    int DeleteAllMarkedObjects();
    int UpdateMarkedObject(int id, MarkedObject &new_object);

private:
    int _id;
    std::string _path;
    cv::Mat _image;
    std::vector<MarkedObject> _marked_objects;
};


#endif //SRC_IMAGE_H
