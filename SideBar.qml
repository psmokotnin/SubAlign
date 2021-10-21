import QtQuick 2.0
import QtQml.Models 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12

import "settings" as Settings

Item {

    ListModel {
        id: model

        ListElement {
            title: qsTr("Alignment")
            component: "alignmentSettings"
        }

        ListElement {
            title: qsTr("Mains")
            component: "mainsSettings"
            materialColor: Material.Blue
        }

        ListElement {
            title: qsTr("Subwoofer")
            component: "subwooferSettings"
            materialColor: Material.Green
        }

        ListElement {
            title: qsTr("Audience")
            component: "audienceSettings"
        }

        ListElement {
            title: qsTr("Environment")
            component: "environmentSettings"
        }

        ListElement {
            title: qsTr("Legend")
            component: "legend"
            opened: true
        }
    }

    Component {
        id: alignmentSettings
        Settings.Alignment {}
    }

    Component {
        id: mainsSettings
        Settings.Mains {}
    }

    Component {
        id: subwooferSettings
        Settings.Subwoofer {}
    }

    Component {
        id: audienceSettings
        Settings.Audience {}
    }

    Component {
        id: environmentSettings
        Settings.Environment {}
    }

    Component {
        id: legend
        Legend {}
    }

    Component {
        id: delegateComponent

        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            property bool opened: (model.opened ? model.opened : false)

            Label {
                text: model.title
                font.bold: true
                font.pixelSize: 14
                horizontalAlignment: Qt.AlignHCenter
                Layout.fillWidth: true
                Layout.topMargin: 5
                color: (model.materialColor ? Material.color(model.materialColor) : "")

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        opened = !opened;
                    }
                }
            }

            Item {
                clip: true
                Layout.fillWidth: true
                Layout.preferredHeight: opened ? loaded.item.height : 0

                Behavior on Layout.preferredHeight {
                    NumberAnimation {duration: 100}
                }

                Loader {
                    id: loaded
                    sourceComponent: switch(model.component) {
                         case "environmentSettings": return environmentSettings;
                         case "audienceSettings": return audienceSettings;
                         case "subwooferSettings": return subwooferSettings;
                         case "mainsSettings": return mainsSettings;
                         case "alignmentSettings": return alignmentSettings;
                         case "legend": return legend;
                         default: console.error("unknown component", model.component);
                    }
                }
            }

            MenuSeparator {}
        }
    }

    ListView {
        anchors.fill: parent

        model: model
        delegate: delegateComponent
        ScrollIndicator.vertical: ScrollIndicator {}
    }
}
