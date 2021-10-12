import QtQuick 2.0
import QtQuick.Layouts 1.12

Rectangle {
    property bool opened : false

    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.preferredWidth: Layout.columnSpan
    Layout.preferredHeight: Layout.rowSpan
    clip: true

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (parent.opened) {
                parent.z = 1;
                parent.Layout.preferredWidth = Layout.columnSpan
                parent.Layout.preferredHeight = Layout.rowSpan
            } else {
                parent.z = 3;
                parent.Layout.preferredWidth = grid.width
                parent.Layout.preferredHeight = grid.height
            }
            parent.opened = !parent.opened;
        }
    }

    Behavior on Layout.preferredHeight {
        NumberAnimation {duration: 500}
    }

    Behavior on Layout.preferredWidth {
        NumberAnimation {duration: 500}
    }
}
