set(TARGET_NAME lab4_threads_2_app)

set(APP_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
)

set(APP_HEADERS
    include/mainwindow.h
)

add_executable(${TARGET_NAME}
    ${APP_SOURCES}
    ${APP_HEADERS}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET_NAME}
    PRIVATE
        workers_core
        workers_widgets
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
)

if(WIN32 AND QT_VERSION_MAJOR EQUAL 5)
    target_link_libraries(${TARGET_NAME}
        PRIVATE
            Qt5::WinMain
    )
endif()