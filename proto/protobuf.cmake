INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})

list(APPEND dependency_libraries ${PROTOBUF_LIBRARIES})

file(GLOB_RECURSE common_proto "proto/*.proto")
PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER ${common_proto})

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(proto ${PROTO_HEADER} ${PROTO_SRC})
