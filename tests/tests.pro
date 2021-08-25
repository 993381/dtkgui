TEMPLATE = app
QT += dtkcore gui gui-private dbus network testlib
CONFIG += thread testcase no_testcase_installs
CONFIG -= app_bundle

load(dtk_testcase)
LIBS += -lgmock

INCLUDEPATH += \
    $$PWD/../src/ \
    $$PWD/../src/filedrag \
    $$PWD/../src/kernel \
    $$PWD/../src/util \
    $$OUT_PWD/../src \
    $$PWD/../src/private

# 指定moc文件生成目录和src一样
MOC_DIR=$$OUT_PWD/../src

DEPENDPATH += $$PWD/../src
unix:QMAKE_RPATHDIR += $$OUT_PWD/../src
unix:LIBS += -L$$OUT_PWD/../src/ -ldtkgui -lgtest -lglib-2.0

include($$PWD/../src/filedrag/filedrag.pri)
include($$PWD/../src/kernel/kernel.pri)
include($$PWD/../src/util/util.pri)

linux* {
    # don't link library
    QMAKE_CXXFLAGS += $$system(pkg-config --cflags-only-I librsvg-2.0)

    dbus_monitor.files += $$PWD/../src/dbus/com.deepin.api.XEventMonitor.xml
    dbus_monitor.header_flags += -i ../src/dbus/arealist.h
    DBUS_INTERFACES += dbus_monitor
}

SOURCES += \
    main.cpp \
    #src/ut_dguiapplicationhelper.cpp \
    src/ut_dforeignwindow.cpp \
    src/ut_dpalette.cpp \
    src/ut_dplatformhandle.cpp \
#    src/ut_dplatformtheme.cpp \
    src/ut_dwindowmanagerhelper.cpp \
    src/ut_dwindowgroupleader.cpp \
#    src/ut_dfontmanager.cpp \
    src/ut_dsvgrenderer.cpp \
    src/ut_dtaskbarcontrol.cpp \
    src/ut_dthumbnailprovider.cpp

RESOURCES += \
    res.qrc


