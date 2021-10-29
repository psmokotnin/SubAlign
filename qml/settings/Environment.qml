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
