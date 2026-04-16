# test_mypoint
add_executable(test_mypoint
    test_mypoint.cpp
)

target_link_libraries(test_mypoint
    PRIVATE
        workers_core
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Test
)

add_test(NAME test_mypoint COMMAND test_mypoint)

# test_pointswidget
add_executable(test_pointswidget
    test_pointswidget.cpp
)

target_link_libraries(test_pointswidget
    PRIVATE
        workers_core
        workers_widgets
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Test
)

add_test(NAME test_pointswidget COMMAND test_pointswidget)

# test_worker
add_executable(test_worker
    test_worker.cpp
)

target_link_libraries(test_worker
    PRIVATE
        workers_core
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Test
)

add_test(NAME test_worker COMMAND test_worker)

# test_mainwindow
add_executable(test_mainwindow
    test_mainwindow.cpp
    ${CMAKE_SOURCE_DIR}/app/include/mainwindow.h
    ${CMAKE_SOURCE_DIR}/app/src/mainwindow.cpp
    ${CMAKE_SOURCE_DIR}/app/src/mainwindow.ui
)

target_include_directories(test_mainwindow
    PRIVATE
        ${CMAKE_SOURCE_DIR}/app/include
)

target_link_libraries(test_mainwindow
    PRIVATE
        workers_core
        workers_widgets
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Test
)

add_test(NAME test_mainwindow COMMAND test_mainwindow)

if(UNIX AND NOT APPLE)
    set_tests_properties(test_mainwindow PROPERTIES
        ENVIRONMENT "QT_QPA_PLATFORM=offscreen"
    )
endif()
