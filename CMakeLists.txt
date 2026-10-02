cmake_minimum_required(VERSION 3.22)
project(clipsnap VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Qml Quick QuickControls2 DBus Sql Test Concurrent)
find_package(SQLite3 REQUIRED)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(packaging)

# -------------------------------------------------------------
# CPack Packaging Configuration (.deb, .tar.gz)
# -------------------------------------------------------------
set(CPACK_PACKAGE_NAME "clipsnap")
set(CPACK_PACKAGE_VENDOR "ClipSnap Team")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Intelligent Clipboard History & Screenshot Snipping Tool for Linux")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "support@clipsnap.app")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_STRIP_FILES TRUE)

# Debian (.deb) specific generator settings
set(CPACK_GENERATOR "DEB;TGZ")
set(CPACK_DEBIAN_PACKAGE_NAME "clipsnap")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "ClipSnap Team <support@clipsnap.app>")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/clipsnap/clipsnap")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt6core6, libqt6gui6, libqt6widgets6, libqt6qml6, libqt6quick6, libqt6quickcontrols2-6, libqt6dbus6, libqt6sql6, libqt6concurrent6, libsqlite3-0")
set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "qml6-module-qtquick, qml6-module-qtquick-controls, qml6-module-qtquick-layouts, qml6-module-qtquick-window")
set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")

set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
    "${CMAKE_CURRENT_SOURCE_DIR}/packaging/postinst"
    "${CMAKE_CURRENT_SOURCE_DIR}/packaging/prerm"
    "${CMAKE_CURRENT_SOURCE_DIR}/packaging/postrm"
)

include(CPack)
