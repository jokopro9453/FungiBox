cmake_minimum_required(VERSION 3.19)
project(Interfaz_Fb_v1 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Charts Sql)

qt_standard_project_setup()

qt_add_executable(Interfaz_Fb_v1
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    sql.h sql.cpp
    simulador_sensor.cpp
    simulador_sensor.h
    graficas.h graficas.cpp


)

target_link_libraries(Interfaz_Fb_v1
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Charts
        Qt::Sql
)

install(TARGETS Interfaz_Fb_v1
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Interfaz_Fb_v1
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
