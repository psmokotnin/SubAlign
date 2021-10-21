import QtQuick 2.14
import QtQml.Models 2.2
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

GridLayout {
    columns: 1

    Component {
        id: delegateComponent

        RowLayout {
            Layout.leftMargin: 40
            Layout.rightMargin: 40

            Rectangle {
                color: model.color
                Layout.preferredHeight: 14
                Layout.minimumWidth: 14
                Layout.fillWidth: true
                visible: (model.color !== "transparent")
            }

            Label {
                text: (model.title ? model.title : "")
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }

    ListModel {
        id: model

        ListElement {
            title: qsTr("0 dB")
            color: "#FFFFFF"
        }

        ListElement {
            title: qsTr("-3 dB")
            color: "#982018"
        }

        ListElement {
            title: qsTr("-6 dB")
            color: "#E83626"
        }

        ListElement {
            title: qsTr("-9 dB")
            color: "#E96233"
        }

        ListElement {
            title: qsTr("-12 dB")
            color: "#F2AB4B"
        }

        ListElement {
            title: qsTr("-15 dB")
            color: "#FFFD6A"
        }

        ListElement {
            title: qsTr("-18 dB")
            color: "#DDFB68"
        }

        ListElement {
            title: qsTr("-21 dB")
            color: "#A4FA72"
        }

        ListElement {
            title: qsTr("-24 dB")
            color: "#82FAAF"
        }

        ListElement {
            title: qsTr("-27 dB")
            color: "#78FBFD"
        }

        ListElement {
            title: qsTr("-30 dB")
            color: "#357BEC"
        }

        ListElement {
            title: qsTr("-33 dB")
            color: "#0634E8"
        }

        ListElement {
            title: qsTr("-36 dB")
            color: "#001FE6"
        }

        ListElement {
            title: qsTr("-39 dB")
            color: "#0016B5"
        }

        ListElement {
            title: qsTr("-42 dB")
            color: "#000867"
        }

        ListElement {
            color: "transparent"
        }

        ListElement {
            title: qsTr("Combing")
            color: "#EB341C"
        }

        ListElement {
            title: qsTr("Transition")
            color: "#FBFB54"
        }

        ListElement {
            title: qsTr("Isolation")
            color: "#357C24"
        }

        ListElement {
            title: "Checkered coupled"
            color: "transparent"
        }
    }

    Repeater {
        model: model
        delegate: delegateComponent
    }
}
