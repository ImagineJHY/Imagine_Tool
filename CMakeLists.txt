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
    set(IMAGINE_SYSTEM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/Imagine_System)
    set(IMAGINE_LIB_WORKER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/Imagine_System/worker)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

    # init初始化thirdparty(yaml-cpp)
    add_custom_target(
        init
        COMMAND python3 init.py
        echo "[Constructing LIB][Imagine Tool]: Starting Imagine_Tool lib target init building..."
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # 在哪个目录下执行命令
    )
    if(EXISTS ${IMAGINE_SYSTEM_DIR}/CMakeLists.txt)
        add_custom_target(
            prepare
            echo "[Constructing LIB][Imagine Tool]: thirdparty Imagine_System exists, Starting Imagine_Tool lib target prepare building..."
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # 在哪个目录下执行命令
        )
        add_dependencies(prepare prepare_thirdparty)
    else()
        message("[Constructing LIB][Imagine Tool]: thirdparty Imagine_System NOT exists, cin make init to init it!")
    endif()

    add_custom_target(
        build
        echo "[Constructing LIB][Imagine Tool]: Starting Imagine_Tool lib target build building..."
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # 在哪个目录下执行命令
    )
    add_dependencies(build imagine_log imagine_time)
    
    if(EXISTS ${IMAGINE_SYSTEM_DIR}/CMakeLists.txt)
        add_subdirectory(${IMAGINE_SYSTEM_DIR})
        message("[Constructing LIB][Imagine Tool]: thirdparty Imagine_System exists, add subModule...")
    else()
        message("[Constructing LIB][Imagine Tool]: thirdparty Imagine_System NOT exists, cin make init to init it!")
    endif()
else()
    message("[Constructing PROJECT][Imagine Tool]: Starting Imagine_Tool lib building, lib name is ${PROJECT_NAME}...")
endif()

add_subdirectory(./Imagine_Time)
add_subdirectory(./Imagine_Log)

add_custom_target(
    imagine_tool
    echo "[Constructing LIB][Imagine Tool]: Starting Imagine_Tool target build building..."
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # 在哪个目录下执行命令
)

add_dependencies(imagine_tool imagine_log imagine_time)