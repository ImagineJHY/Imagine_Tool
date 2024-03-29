cmake_minimum_required(VERSION 3.0)
project(IMAGINE_TOOL)

if(NOT DEFINED IMAGINE_TARGET_LIB)

    set(IMAGINE_TARGET_LIB "Imagine_Tool")

    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -std=c++11 -Wall -Werror")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Werror")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

    string(ASCII 27 Esc)
    set(R "${Esc}[1;31m")
    set(G "${Esc}[0;32m")
    set(E "${Esc}[m")

    set(IS_MAKE_PROJECT false)
    set(IMAGINE_THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

    message("${G}[Imagine Tool]: Starting Imagine_Tool lib building, lib name is ${PROJECT_NAME}...${E}")

endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Imagine_Time)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Imagine_Log)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Imagine_StateMachine)

# add_custom_target(
#     imagine_tool
#     echo "[Imagine Tool]: Starting Imagine_Tool target build building..."
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # 在哪个目录下执行命令
# )
add_library(imagine_tool SHARED)

add_dependencies(imagine_tool imagine_statemachine imagine_log imagine_time imagine_tool_thirdparty)
target_link_libraries(imagine_tool imagine_statemachine imagine_log imagine_time imagine_tool_thirdparty)