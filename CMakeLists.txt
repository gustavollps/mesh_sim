cmake_minimum_required(VERSION 2.8.3)
project(mesh_sim)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

add_message_files(
  FILES
  msg.msg
)
add_service_files(
  FILES
  msg_request.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)


catkin_package()

set(CPP_FILES
    src/node.cpp
    src/libs/node_mesh.cpp
    )

set(H_FILES
    include/node_mesh.h
    )


include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(node src/node.cpp ${CPP_FILES})
target_link_libraries(node ${catkin_LIBRARIES})
add_dependencies(node std_msgs ${catkin_EXPORTED_TARGETS})


