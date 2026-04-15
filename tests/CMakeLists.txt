set(TEST_SOURCES
    test_mypoint.cpp
    test_pointswidget.cpp
    test_worker.cpp
)

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
