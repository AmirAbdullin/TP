cmake_minimum_required(VERSION 3.10)
project(QuantumVisualizer)

# Указываем, что проект будет использовать C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим пакеты Qt5, необходимые для проекта
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

# Включаем автоматическую обработку MOC, UIC и RCC файлов
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_C_COMPILER "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.16.27023\bin\HostX64\x64/cl.exe")
set(CMAKE_CXX_COMPILER "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.16.27023\bin\HostX64\x64/cl.exe")


# Добавляем исполняемый файл проекта
add_executable(${PROJECT_NAME}
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    QuantumSimulator.cpp
    QuantumSimulator.h
    HelpDialog.h
    HelpDialog.ui
)

# Включаем директории include для Qt модулей
target_include_directories(${PROJECT_NAME} PRIVATE ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} )

# Связываем исполняемый файл с необходимыми библиотеками
target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    )
