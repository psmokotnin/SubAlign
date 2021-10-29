##########################################################################
#  SubAlign
#  Copyright (C) 2021  Pavel Smokotnin

#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
##########################################################################

QT += qml quick quickcontrols2
CONFIG += c++1z
CONFIG += sdk_no_version_check
CONFIG += qmltypes

QML_IMPORT_NAME = SubAlign
QML_IMPORT_MAJOR_VERSION = 1

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += qml/qml.qrc \
    resources.qrc

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

    QMAKE_ASSET_CATALOGS += AppIcons/Assets.xcassets

    app_launch_images.files = $$PWD/AppIcons/Launch.xib $$files($$PWD/AppIcons/LaunchImage*.png)
    QMAKE_BUNDLE_DATA += app_launch_images

    QMAKE_INFO_PLIST = $$PWD/ios.plist
}

INCLUDEPATH += \
        src \
        src/charts
HEADERS += \
        src/alignment.h \
        src/audience.h \
        src/charts/axis.h \
        src/charts/cursor.h \
        src/charts/padding.h \
        src/charts/item.h \
        src/charts/phaseoffset.h \
        src/charts/relativelevel.h \
        src/charts/spl.h \
        src/charts/splplane.h \
        src/environment.h \
        src/loudspeaker.h

SOURCES += \
        src/alignment.cpp \
        src/audience.cpp \
        src/charts/axis.cpp \
        src/charts/cursor.cpp \
        src/charts/item.cpp \
        src/charts/phaseoffset.cpp \
        src/charts/relativelevel.cpp \
        src/charts/spl.cpp \
        src/charts/splplane.cpp \
        src/environment.cpp \
        src/loudspeaker.cpp \
        src/main.cpp

DISTFILES += \
        style.astylerc

ICON = AppIcons/icon.icns
