add_subdirectory(layers)

set(PROJECT_SOURCES
    ${PROJECT_SOURCES}

    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui
    PARENT_SCOPE
)
