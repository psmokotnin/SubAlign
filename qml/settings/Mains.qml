import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15
import "../elements"

GridLayout {
    columns: 2

    Label {
        text: qsTr("X")
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
        value: alignment.mains.x
        onValueChanged: alignment.mains.x = value
    }

    Label {
        text: qsTr("Y")
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
        value: alignment.mains.y
        onValueChanged: alignment.mains.y = value
    }

    Label {
        text: qsTr("Level")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 50
    }

    FloatSpinBox {
        units: qsTr("dB")
        from: -100
        to: 100
        decimals: 1
        step: 1
        indicators: false
        Layout.fillWidth: true
        value: alignment.mains.dB
        onValueChanged: alignment.mains.dB = value
    }
}
