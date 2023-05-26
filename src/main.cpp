#include <iostream>
//#include "managers/AccountManager.h"
//#include "mock_repository/UserRepository.h"
//
//int main() {
//    UserRepository userRepositoryMock;
//    AccountManager accountManager = AccountManager(userRepositoryMock);
//    std::string login = "Alexey", password = "525";
//    accountManager.CreateUser(login, password);

//    accountManager.CreateUser((std::string &) "Slava", (std::string &) "763456");
//    accountManager.CreateUser((std::string &) "Nikolay", (std::string &) "123453");
//    std::cout << accountManager.UserExist((std::string &) "Slava") << std::endl;
//    std::cout << accountManager.CheckPassword((std::string &) "Nikolay", (std::string &) "123453");

//    std::vector<int> vec;
//    std::cout << vec.empty();
//    return 0;
//}

//#include <iostream>
//#include <opencv2/opencv.hpp>
//using namespace cv;

//include "business_logic/managers/DataFileManager.h"
//#include "data_access/mock_repository/CoordRepository.h"
//#include "gtest/gtest.h"
//#include "objects/image/Image.h"

//#include "objects/image/Image.h"
//#include "objects/connection/Connection.h"
//#include "data_access/psql_repository/PSQLUserRepository.h"
//#include <pqxx/pqxx>


//int main(int argc, char** argv )
//{

//    std::string parameters = "username=postgres"
//                             " host=localhost"
//                             " password=poatgres"
//                             " dbname=ppo"
//                             " port=5259";
//    pqxx::connection conn = pqxx::connection(parameters);
//    if ( argc != 2 )
//    {
//        printf("usage: DisplayImage.out <Image_Path>\n");
//        return -1;
//    }
//    std::string path = "tests/img/map_ryba.jpg";
//    Image image(0, path);
//    std::string username = "postgres", host = "localhost", password = "poatgres", dbname = "ppo";
//    std::string newname = "korsar", newpassword = "123456";
//    int port = 5259;
//    Connection connection(username, host, password, dbname , port);
//    connection.CreateConnection();
//    PSQLUserRepository user_rep(username, host, password, dbname, port);
//    User new_user(0, newname, newpassword, USER);
//    user_rep.AddUser(new_user);

//    User user = user_rep.GetUserById(3);
//    std::cout << user.GetLogin() << user.GetPassword();

//    image = cv::imread( "tests/img/map.jpg");
//    std::vector<uchar> data;

//    if ( !image.data )
//    {
//        printf("No image data \n");
//        return -1;
//    }
//    cv::imencode(".jpg", image, data);
//    for (int i = 0; i < data.size(); i++) {
//        std::cout << data[i] << " ";
//    }
//    cv::Mat image2 = cv::imdecode(data, 1);
//    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
//    cv::imshow("Display Image", image.GetImage());
//    cv::waitKey(0);
//    CoordRepository coord_repository;
//    std::vector<Dot> coords, coords2;
//    coords.emplace_back(1, 2);
//    coords.emplace_back(3, 0);
//    coords.emplace_back(134, 201);
//    coords.emplace_back(0, 3);
//    coord_repository.AddAllCoords(coords);
//
//    DataFileManager dataFileManager;
//    dataFileManager.SetCoordRepository(coord_repository);
//    std::string path = "coords.csv";
//    dataFileManager.CreateCoordFile(path);


//    return 0;
//}

//TEST(TTest, PositiveNos) {
//    ASSERT_EQ(6, 6);
//}
//
//
//int main(int argc, char **argv) {
////    testing::InitGoogleTest(&argc, argv);
////    return RUN_ALL_TESTS();
//    std::cout << "Hello";
//    return 0;
//}

#include "app/App.h"
#include "psql_repository/PSQLMarkRepository.h"
#include "psql_repository/PSQLMarkedObjectRepository.h"
#include "psql_repository/PSQLUserRepository.h"
#include "psql_repository/PSQLImageRepository.h"
#include "managers/MarkManager.h"
#include "managers/DataFileManager.h"
#include "managers/AccountManager.h"
#include "managers/LabelingManager.h"
#include "managers/ImageManager.h"
#include "controller/Controller.h"
#include "logger/Logger.h"
#include "config_reader/ConfigReader.h"

///home/alexey/Documents/University/semester_6/ppo/src/img

int main(int argc, char** argv)
{
    Logger logger("log/log.txt");
    logger.Log(INFO, "Application started");
    DatabaseConfig dbconfig = ReadDatabaseConfig(logger, "config.json");
//    Connection connection(username, host, password, dbname , port);
    std::string username = dbconfig.username, host = dbconfig.host, password = dbconfig.password, dbname = dbconfig.dbname;
    int port = dbconfig.port;

    PSQLMarkedObjectRepository marked_object_repository = PSQLMarkedObjectRepository(username, host, password, dbname,port, logger);
    PSQLMarkRepository mark_repository = PSQLMarkRepository(username, host, password, dbname, port, logger);
    PSQLImageRepository image_repository = PSQLImageRepository(username, host, password, dbname, port, logger);
    PSQLUserRepository user_repository = PSQLUserRepository(username, host, password, dbname, port, logger);

    marked_object_repository.SetMarkRepository(mark_repository);
    image_repository.SetMarkedObjectRepository(marked_object_repository);

    ImageManager image_manager = ImageManager(image_repository, marked_object_repository);
    MarkManager mark_manager = MarkManager(mark_repository);
    DataFileManager data_file_manager = DataFileManager(image_repository, mark_repository, marked_object_repository);
    AccountManager account_manager = AccountManager(user_repository);
    LabelingManager labeling_manager = LabelingManager(image_manager, marked_object_repository);

    Controller auth_controller = Controller(account_manager, labeling_manager, mark_manager, logger);

    App app(auth_controller, labeling_manager, image_manager, mark_manager, data_file_manager, logger);

    for (;;)
        app.Menu();
}