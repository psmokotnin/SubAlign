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
        text: qsTr("F")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 50
    }

    FloatSpinBox {
        units: qsTr("Hz")
        from: 20
        to: 20000
        decimals: 0
        step: 1
        indicators: false
        value: alignment.frequency
        Layout.fillWidth: true
        onValueChanged: alignment.frequency = value
    }

    Label {
        text: qsTr("max\noffset")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 50
    }

    FloatSpinBox {
        units: qsTr("º")
        from: -180
        to: 180
        decimals: 0
        step: 1
        indicators: false
        value:alignment.maxPhaseOffset
        onValueChanged: alignment.maxPhaseOffset = value
        Layout.fillWidth: true
    }
}
