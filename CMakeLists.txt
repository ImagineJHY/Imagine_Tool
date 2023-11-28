cmake_minimum_required(VERSION 3.0)
project(IMAGINE_TOOL)

message("[Imagine Tool]: Starting Imagine_Tool lib building, lib name is ${PROJECT_NAME}...")

if(NOT DEFINED IMAGINE_TARGET_LIB)

    message("[Imagine Tool]: IMAGINE_TARGET_LIB Is Not Defined")

    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -std=c++11 -Wall -Werror")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Werror")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

    set(IMAGINE_TARGET_LIB "Imagine_Tool")

    set(IS_MAKE_PROJECT false)
    set(IMAGINE_THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Imagine_Time)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Imagine_Log)

add_custom_target(
    imagine_tool
    echo "[Imagine Tool]: Starting Imagine_Tool target build building..."
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # 在哪个目录下执行命令
)

add_dependencies(imagine_tool imagine_log imagine_time imagine_tool_thirdparty)