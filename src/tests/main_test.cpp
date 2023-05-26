//#include "business_logic_tests/AccountManagerTest.h"
//#include "business_logic_tests/ImageManagerTest.h"
//#include "business_logic_tests/MarkManagerTest.h"
//#include "business_logic_tests/LabelingManagerTest.h"

#include "data_access_tests/PSQLAccountManagerTest.h"
#include "data_access_tests/PSQLImageManagerTest.h"
#include "data_access_tests/PSQLMarkManagerTest.h"
#include "data_access_tests/PSQLLabelingManagerTest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}