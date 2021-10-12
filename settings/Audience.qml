import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15
import "../elements"

GridLayout {
    columns: 2

    Label {
        text: qsTr("start X")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 80
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
        onValueChanged: alignment.audience.start.x = value
    }

    Label {
        text: qsTr("start Y")
        horizontalAlignment: Qt.AlignRight
        Layout.preferredWidth: 80
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
        Layout.preferredWidth: 80
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
        Layout.preferredWidth: 80
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
