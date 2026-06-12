cmake_minimum_required(VERSION 3.16)

project(TodoList VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Quick
    QuickControls2
    Test
    Sql
)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_library(TodoListCore STATIC
    backend/database/database.cpp
    backend/database/database.h
    backend/managers/taskmanager.cpp
    backend/managers/taskmanager.h
    backend/model/listModel.h
    backend/model/listModel.cpp
    backend/task/task.h
    backend/proxyModel/proxyModel.h
    backend/proxyModel/proxyModel.cpp
)

target_link_libraries(TodoListCore
    PUBLIC
        Qt6::Core
        Qt6::Sql

    )

target_include_directories(TodoListCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/backend
)

qt_add_executable(TodoListApp
    main.cpp
)

qt_add_qml_module(TodoListApp
    URI TodoList
    QML_FILES
        frontend/Main.qml
        frontend/pages/HomePage.qml
        frontend/components/CustomButton.qml
        frontend/components/TaskCard.qml
        frontend/components/TaskInput.qml
        frontend/components/Toast.qml
)

target_include_directories(TodoListApp PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/backend
   ${CMAKE_CURRENT_SOURCE_DIR}/backend/managers
   ${CMAKE_CURRENT_SOURCE_DIR}/backend/database
   ${CMAKE_CURRENT_SOURCE_DIR}/backend/model
   ${CMAKE_CURRENT_SOURCE_DIR}/backend/proxyModel
)

target_link_libraries(TodoListApp
    PRIVATE
        TodoListCore
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Test
        Qt6::Sql
)

qt_add_executable(TodoListTests
    test/database/databaseTest.cpp
    test/database/databaseTest.h
    test/manager/managerTest.cpp
    test/manager/managerTest.h
    test/listModel/listModelTest.cpp
    test/listModel/listModelTest.h
    test/proxyModel/proxyModelTest.cpp
    test/proxyModel/proxyModelTest.h
    test/main.cpp
)

target_link_libraries(TodoListTests
    PRIVATE
        TodoListCore
        Qt6::Test
)

set_target_properties(TodoListApp PROPERTIES

    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS TodoListApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
