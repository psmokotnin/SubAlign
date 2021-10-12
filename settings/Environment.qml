import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15
import "../elements"

GridLayout {
    columns: 2

    Label {
        text: qsTr("frequency")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 80
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
            speed.value = speedOfSound();
        }
    }

    Label {
        text: qsTr("phase span")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 80
    }

    FloatSpinBox {
        id: speed
        units: qsTr("m/s")
        decimals: 0
        from: 0
        to: 1000

        indicators: false
        value: speedOfSound()
        Layout.fillWidth: true
        enabled: false
    }

    function speedOfSound() {
        return 20.05 * Math.sqrt(273.15 + temp.value);
    }
}
