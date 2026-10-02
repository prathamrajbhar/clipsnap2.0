add_executable(TestHistory unit/TestHistory.cpp)
target_link_libraries(TestHistory PRIVATE
    Qt6::Core Qt6::Test Qt6::Sql Qt6::Gui SQLite::SQLite3
)
target_include_directories(TestHistory PRIVATE ../src)
target_sources(TestHistory PRIVATE
    ../src/history/HistoryItem.cpp
    ../src/history/HistoryRepository.cpp
    ../src/settings/Settings.cpp
)
add_test(NAME TestHistory COMMAND TestHistory)
