set(TARGET_NAME workers_core)

add_library(${TARGET_NAME} STATIC
    include/mypoint.h
    include/worker.h
    include/workersrunsettings.h
    src/mypoint.cpp
    src/worker.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET_NAME}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
)