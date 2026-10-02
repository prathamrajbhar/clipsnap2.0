file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(clipsnap ${SOURCES})

qt_add_resources(clipsnap "qml"
    PREFIX "/"
    FILES
        ../qml/main.qml
        ../qml/HistoryView.qml
        ../qml/HistoryItemDelegate.qml
        ../qml/HistoryCardDelegate.qml
        ../qml/FilterBar.qml
        ../qml/StatusBar.qml
        ../qml/CropWindow.qml
        ../qml/CropSelector.qml
        ../qml/SettingsWindow.qml
)

target_link_libraries(clipsnap PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::DBus
    Qt6::Sql
    Qt6::Concurrent
    SQLite::SQLite3
)

target_include_directories(clipsnap PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
