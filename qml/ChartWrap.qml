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
import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    id: control
    property bool opened : false
    property string title : "Text value"

    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.preferredWidth: Layout.columnSpan
    Layout.preferredHeight: Layout.rowSpan
    clip: true

    Label {
        text: title
        horizontalAlignment: Qt.AlignHCenter
        font.pixelSize: (opened ? 14 : 12)
        font.weight: Font.Bold
        topPadding: 10
        bottomPadding: 10
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
    }
}
