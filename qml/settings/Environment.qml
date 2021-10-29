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
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 50
    }

    FloatSpinBox {
        id: temp
        units: qsTr("ºC")
        from: -50
        to: 100
        decimals: 0
        step: 1
        indicators: false
        value: alignment.environment.temperature
        Layout.fillWidth: true

        onValueChanged: {
            alignment.environment.temperature = value
            speed.value = alignment.environment.speedOfSound;
        }
    }

    Label {
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 50
    }

    FloatSpinBox {
        id: speed
        units: qsTr("m/s")
        decimals: 0
        from: 0
        to: 1000

        indicators: false
        value: alignment.environment.speedOfSound
        Layout.fillWidth: true
        enabled: false
    }
}
