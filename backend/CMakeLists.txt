include_directories(${PROJECT_ROOT_DIR}/comms/zeromq)

set(PROJECT_SOURCES
        main.cpp
        RadarController.cpp
        RadarController.h
)

add_executable(backend ${PROJECT_SOURCES} )


target_include_directories(backend PRIVATE 
    ${PROJECT_ROOT_DIR}/comms/zeromq 
    ${PROJECT_ROOT_DIR}/proto
    ${ZMQ_INCLUDE_DIRS}
)

target_link_libraries(backend 
    ${ZMQ_LIBRARIES}
    protogen
)

install(TARGETS backend RUNTIME DESTINATION bin)
