/**
 *  SubAlign
 *  Copyright (C) 2021  Pavel Smokotnin

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.1

ApplicationWindow {
    minimumWidth: 1024
    minimumHeight: 768

    Material.theme:  Material.Light
    Material.accent: Material.Indigo

    visible: true
    title: qsTr("Sub Align")

    RowLayout {
        anchors.fill: parent

        ChartGrid {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        SideBar {
            Layout.fillHeight: true
            Layout.rightMargin: 5
            width: 200
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:768;width:1024}
}
##^##*/
