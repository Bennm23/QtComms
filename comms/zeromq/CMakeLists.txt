# set(
#     SOURCES
#     ZeroClient.cpp ZeroChannel.cpp
# )
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(
    HEADERS
    ZeroClient.h ZeroChannel.h ZeroClientQt.h
)

add_library(zmqComms ${HEADERS})


target_include_directories(zmqComms PUBLIC
    ${ZMQ_INCLUDE_DIRS}
    ${PROJECT_ROOT_DIR}/proto
 )
target_link_libraries(zmqComms PUBLIC 
    ${ZMQ_LIBRARIES} 
    Qt5::Core
    Qt5::Widgets
    protogen
)

include(GNUInstallDirs)