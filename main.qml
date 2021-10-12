import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.1

ApplicationWindow {
    minimumWidth: 1024
    minimumHeight: 768

    Material.theme:  Material.Light
    Material.accent: Material.Indigo

    visible: true
    title: qsTr("Sub Align")

    RowLayout {
        anchors.fill: parent

        ChartGrid {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        SideBar {
            Layout.fillHeight: true
            Layout.rightMargin: 5
            width: 200
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:768;width:1024}
}
##^##*/
