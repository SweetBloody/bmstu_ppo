#ifndef SRC_LABELINGMANAGER_H
#define SRC_LABELINGMANAGER_H

#include "ImageManager.h"
#include "exception/Exception.h"
#include "objects/dot/Dot.h"
#include "repository_interface/IMarkedObjectRepository.h"

class LabelingManager {
public:
    LabelingManager(ImageManager &image_manager, IMarkedObjectRepository &marked_object_repository);

    void SetImageManager(ImageManager &image_manager);
    void SetMarkedObjectRepository(IMarkedObjectRepository &marked_object_repository);
    Image LabelImagePolygon(Image &image, std::vector<Dot> &coords, Mark &mark);
    Image LabelImageCircle(Image &image, Dot &center, Dot &radius, Mark &mark);
    void DeleteMarkedObject(Image &image, MarkedObject &marked_object);
    void DeleteAllMarkedObjects(Image &image);
    void SaveImageInfo(Image &image);

private:
    ImageManager *_image_manager;
    IMarkedObjectRepository *_marked_object_repository;
};


#endif //SRC_LABELINGMANAGER_H
