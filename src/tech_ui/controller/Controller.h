#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <iostream>
#include "managers/AccountManager.h"
#include "managers/LabelingManager.h"
#include "managers/MarkManager.h"
#include "logger/Logger.h"


const std::string CHOOSE_SHAPE = "\n\n\
Выберите форму для выделения\n\
0.  Круг\n\
1.  Прямоугольник\n\
2.  Многоугольник\n\
Введите форму: ";

enum SHAPE {
    CIRC,
    SQUARE,
    POLYG
};
class Controller {
public:
    Controller(AccountManager &account_manager, LabelingManager &labeling_manager, MarkManager &mark_manager, Logger &logger);
    Controller();
    ~Controller() = default;
    bool IsAuthorized(std::string login);
    PrivilegeLvl TryToAuthorize();
    PrivilegeLvl TryToRegister();
    int ChooseShape();
    Mark ChooseMark();
    void OutpuImages(std::vector<Image> &images);
    void OutputImage(Image &image);
    void OutputMarkedObjectsOfImage(Image &image);
    void LabelImage(Image &image);
    std::string GetLogin();
private:
    std::string _login;
    std::string _password;
    AccountManager *_account_manager;
    LabelingManager *_labeling_manager;
    MarkManager *_mark_manager;
    Logger *_logger;
};

#endif // AUTHMANAGER_H
