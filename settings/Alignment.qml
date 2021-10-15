import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15
import "../elements"
//import SubAlign 1.0

GridLayout {
    columns: 2

    Label {
        text: qsTr("frequency")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 80
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
        text: qsTr("max offset")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 80
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
