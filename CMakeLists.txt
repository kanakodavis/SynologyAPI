cmake_minimum_required(VERSION 2.8.4)
project(SynologyAPI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    API/AudioStationAPI/AudioStationAPI.cpp
    API/AudioStationAPI/AudioStationAPI.h
    API/API.cpp
    API/API.h
    API/AuthAPI.cpp
    API/AuthAPI.h
    API/RequestManager.cpp
    API/RequestManager.h
    Data/Album.h
    Data/Audio.h
    Data/AudioInfo.h
    Data/ID3.h
    Data/Song.h
    JSONParser/ASParser.cpp
    JSONParser/ASParser.h
    JSONParser/JSONParser.cpp
    JSONParser/JSONParser.h
    main.cpp)

include_directories(
    ${CMAKE_SOURCE_DIR}/API
    ${CMAKE_SOURCE_DIR}/API/AudioStationAPI
    ${CMAKE_SOURCE_DIR}/Data
    ${CMAKE_SOURCE_DIR}/JSONParser
    ${CMAKE_SOURCE_DIR}/include
)

#Set Jansson lib path
set(JANSSON ${CMAKE_SOURCE_DIR}/lib/libjansson.a)

find_package(CURL)
if(CURL_FOUND)
    message(STATUS "cURL libraries found at: ${CURL_LIBRARIES}")
    message(STATUS "cURL includes found at: ${CURL_INCLUDE_DIRS}")
else()
    message(SEND_ERROR "Could not find cURL on your system")
endif(CURL_FOUND)

add_executable(SynologyAPI ${SOURCE_FILES})

target_link_libraries(SynologyAPI
    ${CURL_LIBRARIES}
    ${JANSSON}
)