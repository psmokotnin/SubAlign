import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
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

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
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
        NumberAnimation {
            duration: 500
            easing.type: Easing.Linear
        }
    }

    Behavior on Layout.preferredWidth {
        NumberAnimation {
            duration: 500
            easing.type: Easing.Linear
        }
    }
}
