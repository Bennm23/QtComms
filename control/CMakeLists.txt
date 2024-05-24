include_directories(${PROJECT_ROOT_DIR}/comms/zeromq)

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        ControlWindow.cpp
        ControlWindow.h
        ControlWindow.ui
)

add_executable(controlGui ${PROJECT_SOURCES} )

target_include_directories(controlGui PRIVATE 
    ${PROJECT_ROOT_DIR}/comms/zeromq 
    ${PROJECT_ROOT_DIR}/proto
    ${ZMQ_INCLUDE_DIRS}
)

target_link_libraries(controlGui 
    ${ZMQ_LIBRARIES}
    Qt5::Widgets
    Qt5::Core
    zmqComms
    protogen
)
include(GNUInstallDirs)
install(TARGETS controlGui RUNTIME DESTINATION bin)
