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
import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15
import "../elements"

GridLayout {
    columns: 2

    Label {
        text: qsTr("start X")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 50
    }

    FloatSpinBox {
        units: qsTr("m")
        from: 0
        to: 100
        decimals: 2
        step: 1
        indicators: false
        Layout.fillWidth: true
        value: alignment.audience.start.x
        onValueChanged: alignment.audience.start.x = value;
    }

    Label {
        text: qsTr("start Y")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 50
    }

    FloatSpinBox {
        units: qsTr("m")
        from: 0
        to: 100
        decimals: 2
        step: 1
        indicators: false
        Layout.fillWidth: true
        value: alignment.audience.start.y
        onValueChanged: alignment.audience.start.y = value
    }

    Label {
        text: qsTr("stop X")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 50
    }

    FloatSpinBox {
        units: qsTr("m")
        from: 0
        to: 100
        decimals: 2
        step: 1
        indicators: false
        Layout.fillWidth: true
        value: alignment.audience.stop.x
        onValueChanged: alignment.audience.stop.x = value
    }

    Label {
        text: qsTr("stop Y")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 50
    }

    FloatSpinBox {
        units: qsTr("m")
        from: 0
        to: 100
        decimals: 2
        step: 1
        indicators: false
        Layout.fillWidth: true
        value: alignment.audience.stop.y
        onValueChanged: alignment.audience.stop.y = value;
    }
}
