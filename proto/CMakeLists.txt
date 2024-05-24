file(GLOB GEN_FILES "*.pb.h" "*.pb.cc")

foreach(generated_file ${GEN_FILES})
    set_property(SOURCE ${generated_file} PROPERTY SKIP_AUTOGEN ON)
endforeach()

find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS controls.proto common.proto)

add_library(protogen ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(protogen ${PROTOBUF_LIBRARIES})