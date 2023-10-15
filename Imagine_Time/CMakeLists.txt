cmake_minimum_required(VERSION 3.0)
project(IMAGINE_TIME)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -std=c++11 -Wall -Werror")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

file(GLOB IMAGINE_TIME_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
message(${IMAGINE_TIME_SRC_LIST})
add_library(imagine_time SHARED ${IMAGINE_TIME_SRC_LIST})
target_include_directories(imagine_time PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)