cmake_minimum_required(VERSION 3.0)
project(IMAGINE_TOOL)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -std=c++11 -Wall -Werror")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

# 定义全局参数 IS_MAKE_PROJECT
# 若已定义，则当前project作为subModule
# 若未定义, 则当前project作为mainModule
# 若当前的任务是编译动态库, 则构建TARGET: init, prepare, build
# 若当前的任务是生成项目, 则不构建上述TARGET
if(NOT DEFINED IS_MAKE_PROJECT)

    message("[Constructing LIB][Imagine Tool]: Starting Imagine_Tool lib building, lib name is ${PROJECT_NAME}...")
    set(TARGET_LIB "Imagine_Tool")
    set(IS_MAKE_PROJECT false)
    set(IMAGINE_THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

    # init/prepare初始化thirdparty(yaml-cpp)
    add_custom_target(
        init
        echo "[Constructing LIB][Imagine Tool]: Starting Imagine_Tool lib target init building..."
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} # 在哪个目录下执行命令
    )
    add_dependencies(init tool_prepare)

    add_custom_target(
        prepare
        echo "[Constructing LIB][Imagine Tool]: Starting Imagine_Tool lib target preparing..."
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} # 在哪个目录下执行命令
    )
    add_dependencies(prepare tool_prepare)

    add_custom_target(
        build
        echo "[Constructing LIB][Imagine Tool]: Starting Imagine_Tool lib target build building..."
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} # 在哪个目录下执行命令
    )
    add_dependencies(build imagine_tool)

endif()

add_custom_target(
    tool_prepare
    COMMAND python3 init_thirdparty.py
    echo "[Constructing LIB][Imagine Tool]: Starting Imagine_Tool lib target preparing..."
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} # 在哪个目录下执行命令
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Imagine_Time)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Imagine_Log)

add_custom_target(
    imagine_tool
    echo "[Constructing LIB][Imagine Tool]: Starting Imagine_Tool target build building..."
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # 在哪个目录下执行命令
)

if(TARGET imagine_tool)
    add_dependencies(imagine_tool imagine_log imagine_time imagine_tool_thirdparty)
endif()