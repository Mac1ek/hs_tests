cmake_minimum_required(VERSION 3.16)
project(hs_tests VERSION 0.0.1 LANGUAGES CXX)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable(hs_test WIN32 main.cpp MainWindow.cpp QuestionWidget.cpp SingleQuestionWidget.cpp MultipleQuestionWidget.cpp MultipleQuestionImageWidget.cpp TestWidget.cpp LangTranslation.cpp resources/resources.qrc)

target_link_libraries(hs_test PRIVATE Qt6::Core)
target_link_libraries(hs_test PRIVATE Qt6::Widgets)