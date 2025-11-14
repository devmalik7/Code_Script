cmake_minimum_required(VERSION 3.21)
project(pathfinding_visualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Enable Qt automatic processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

qt_add_executable(pathfinding_visualizer
    src/main.cpp
    src/MainWindow.cpp
    src/Grid.cpp
    src/Node.cpp
    src/Algorithms/AlgorithmWorker.cpp

    # Headers (needed for AUTOMOC)
    include/MainWindow.hpp
    include/Grid.hpp
    include/Node.hpp
    include/Algorithms/AlgorithmWorker.hpp

    # UI + Resources
    ui/MainWindow.ui
)

target_include_directories(pathfinding_visualizer PRIVATE include)

target_link_libraries(pathfinding_visualizer PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)
