#ifndef SRC_APP_H
#define SRC_APP_H

#include  "managers/AccountManager.h"
#include  "managers/DataFileManager.h"
#include  "managers/ImageManager.h"
#include  "managers/LabelingManager.h"
#include  "managers/MarkManager.h"
#include "controller/Controller.h"
#include "request/Request.h"
#include "state/State.h"

const std::string MENU_ENTRIES = "\n\n\
0.  Выйти из программы.\n\
1.  Выйти из аккаунта.\n\
2.  Войти в аккаунт.\n\
3.  Зарегистрироваться.\n\
4.  Загрузить изображение.\n\
5.  Удалить изображение\n\
6.  Создать метку.\n\
7.  Создать файл с данными.\n\
8.  Вывести изображения.\n\
9.  Разметить изображение.\n\
10. Вывести все объекты изображения.\n\
11. Удалить размеченный объект на изображении.\n\
Введите команду: ";


const std::string NOT_COMMAND = "Такой команды не существует!\n\n";
const std::string NOT_ROLE = "Эту команду невозможно выполнить в текущем статусе!\n\n";

class App {
public:
    App(Controller &auth_controller, LabelingManager &labeling_manager,
        ImageManager &image_manager, MarkManager &mark_manager, DataFileManager &datafile_manager, Logger &logger);
    ~App() = default;
    void Menu();

private:
    REQUEST_KEYS GetRequestKey(std::string req);
    void PrintMenu();
    void PrintNotCommand();
    void PrintNotRole();
    void HandleReq(REQUEST_KEYS key);
    AppState _state;
    RequestHandler _req_handler;
    Controller *_controller;
    ImageManager *_image_manager;
    MarkManager *_mark_manager;
    DataFileManager *_datafile_manager;
    Logger *_logger;
};

#endif //SRC_APP_H
