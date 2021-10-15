
QT += qml quick quickcontrols2
CONFIG += c++1z
CONFIG += sdk_no_version_check
CONFIG += qmltypes

QML_IMPORT_NAME = SubAlign
QML_IMPORT_MAJOR_VERSION = 1

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ios: {
    QMAKE_IOS_DEPLOYMENT_TARGET = 12.0
    QMAKE_APPLE_TARGETED_DEVICE_FAMILY = 2 #iPad
    QMAKE_IOS_DEVICE_ARCHS = "arm64"
    DEFINES += SUPPORT_64_BIT_IOS
}

INCLUDEPATH += charts

HEADERS += \
    alignment.h \
    audience.h \
    charts/axis.h \
    charts/padding.h \
    charts/item.h \
    charts/phaseoffset.h \
    charts/spl.h \
    environment.h \
    loudspeaker.h

SOURCES += \
        alignment.cpp \
        audience.cpp \
        charts/axis.cpp \
        charts/item.cpp \
        charts/phaseoffset.cpp \
        charts/spl.cpp \
        environment.cpp \
        loudspeaker.cpp \
        main.cpp

DISTFILES += \
        style.astylerc
