set(TARGET_NAME workers_widgets)

add_library(${TARGET_NAME} STATIC
    include/pointswidget.h
    src/pointswidget.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET_NAME}
    PUBLIC
        workers_core
        Qt${QT_VERSION_MAJOR}::Widgets
)