install(TARGETS clipsnap DESTINATION /usr/bin)

install(FILES ../packaging/clipsnap.desktop
        DESTINATION /usr/share/applications)

install(FILES ../packaging/clipsnap.svg
        DESTINATION /usr/share/icons/hicolor/scalable/apps)

install(FILES ../packaging/clipsnap.service
        DESTINATION /usr/lib/systemd/user)

install(FILES ../packaging/clipsnap-autostart.desktop
        DESTINATION /etc/xdg/autostart)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../gnome-extension/clipsnap@clipsnap.app")
    install(DIRECTORY ../gnome-extension/clipsnap@clipsnap.app
            DESTINATION /usr/share/clipsnap/gnome-extension)
endif()
