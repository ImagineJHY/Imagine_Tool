cmake_minimum_required(VERSION 3.0)
project(IMAGINE_LOG)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -std=c++11 -Wall -Werror")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

file(GLOB IMAGINE_LOG_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(imagine_log SHARED ${IMAGINE_LOG_SRC_LIST})
target_include_directories(imagine_log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(imagine_log yaml-cpp imagine_time)