cmake_minimum_required(VERSION 3.0)
project(IMAGINE_TOOL_THIRDPARTY)

# add_custom_target(
#     imagine_tool_thirdparty
#     echo "[Constructing LIB][Imagine Tool]: Starting Imagine_Tool_Thirdparty lib target init building..."
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} # 在哪个目录下执行命令
# )
add_library(imagine_tool_thirdparty SHARED)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/CMakeLists.txt)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp)
    add_dependencies(imagine_tool_thirdparty yaml-cpp)
    target_link_libraries(imagine_tool_thirdparty yaml-cpp)
else()
    message("${R}[Constructing LIB][Imagine Tool]: add thirdparty FAIL! Please cin make init or clone yaml-cpp here yourself${E}")
endif()
