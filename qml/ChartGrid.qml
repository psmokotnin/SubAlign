/**
 *  SubAlign
 *  Copyright (C) 2021  Pavel Smokotnin

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import SubAlign 1.0

GridLayout {
    id: grid

    property int spacing : 10
    property string chartBackground : "white"// "#c7d4a1"
    property Alignment source : alignment
    rows: 2
    columns: 3

    columnSpacing: spacing
    rowSpacing: spacing

    Rectangle {
        Layout.columnSpan: 3
        Layout.preferredHeight: 50
        Layout.fillWidth: true
        color: chartBackground

        RowLayout {
            id: cursorRow
            readonly property int itemWidth : (width - spacing * 3) / 4

            anchors.fill: parent
            spacing: 0

            Text {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: (parent.width - grid.spacing * 2) / 3
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

                text: qsTr("XO: %1").arg(phaseOffsetChart.xo.toFixed(2))
                color: Material.color(Material.Red)
                font.bold: true
            }

            Rectangle {
                Layout.preferredWidth: grid.spacing
            }

            Text {
                id: cursorX
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: (parent.width - grid.spacing * 2) / 6
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                rightPadding: 5
            }

            Text {
                id: cursorY
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: (parent.width - grid.spacing * 2) / 6
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                leftPadding: 5
            }

            Rectangle {
                Layout.preferredWidth: grid.spacing
            }

            Text {
                id: cursorZ
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: (parent.width - grid.spacing * 2) / 3
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: Material.color(Material.Red)
                font.bold: true
            }
        }
    }

    ChartWrap {
        color: grid.chartBackground
        title: "Phase offset"

        PhaseOffsetChart {
            id: phaseOffsetChart
            anchors.fill: parent
            anchors.topMargin: 20
            alignment: source
            color: Material.color(Material.Red)

            ChartMouse {
                xItem: cursorX
                yItem: cursorY
                zItem: cursorZ
            }
       }
    }

    ChartWrap {
        id: splPlane
        color: grid.chartBackground
        title: "SPL Plane"

        SplPlaneChart {
            anchors.fill: parent
            anchors.topMargin: 20
            alignment: source
            plane: SplPlaneChart.XY

            ChartMouse {
                xItem: cursorX
                yItem: cursorY
                zItem: cursorZ
            }
        }
    }

    ChartWrap {
        id: splSection
        color: grid.chartBackground
        title: "SPL Section"

        SplPlaneChart {
            anchors.fill: parent
            anchors.topMargin: 20
            alignment: source
            plane: SplPlaneChart.XZ

            ChartMouse {
                xItem: cursorX
                yItem: cursorY
                zItem: cursorZ
            }
        }
    }

    ChartWrap {
        id: splChart
        color: grid.chartBackground
        title: "SPL"

        SplChart {
            anchors.fill: parent
            anchors.topMargin: 20
            alignment: source
            mainsColor: Material.color(Material.Blue)
            subwooferColor: Material.color(Material.Green)
            sumColor: Material.color(Material.Red)

            ChartMouse {
                xItem: cursorX
                yItem: cursorY
                zItem: cursorZ
            }
        }
    }

    ChartWrap {
        color: grid.chartBackground
        title: "Relative Level Difference Plane"

        RelativeLevelChart {
            anchors.fill: parent
            anchors.topMargin: 20
            alignment: source
            plane: RelativeLevelChart.XY

            ChartMouse {
                xItem: cursorX
                yItem: cursorY
                zItem: cursorZ
            }
        }
    }

    ChartWrap {
        color: grid.chartBackground
        title: "Relative Level Difference Section"

        RelativeLevelChart {
            anchors.fill: parent
            anchors.topMargin: 20
            alignment: source
            plane: RelativeLevelChart.XZ

            ChartMouse {
                xItem: cursorX
                yItem: cursorY
                zItem: cursorZ
            }
        }
    }

    Rectangle {
        Layout.fillWidth: true
        Layout.preferredWidth: Layout.columnSpan
        Layout.preferredHeight: 50
        clip: true
        color: chartBackground

        RowLayout {
            anchors.fill: parent

            Image {
                source: "qrc:/images/resources/PavelLogo.png"
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                Layout.margins: 5
            }

            Text {
                textFormat: Text.RichText
                onLinkActivated: Qt.openUrlExternally(link)
                text: qsTr(
                        "<a style='color:%1' href=\"https://opensoundmeter.com?utm_source=tools&utm_medium=subalign&utm_campaign=promo\">Pavel Smokotnin</a>"
                    ).arg(Material.accentColor)
            }
        }
    }

    Rectangle {
        Layout.fillWidth: true
        Layout.preferredWidth: Layout.columnSpan
        Layout.preferredHeight: 50
        clip: true
        color: chartBackground

        RowLayout {
            anchors.fill: parent

            Image {
                source: "qrc:/images/resources/MerlijnLogo.png"
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                Layout.margins: 5
            }

            Text {
                textFormat: Text.RichText
                onLinkActivated: Qt.openUrlExternally(link)
                text: qsTr(
                        "Original calculator was created<br/>
                        by <a style='color:%1' href=\"https://www.merlijnvanveen.nl\">Merlijn Van Veen</a>"
                    ).arg(Material.accentColor)
            }
        }
    }

    Rectangle {
        Layout.fillWidth: true
        Layout.preferredWidth: Layout.columnSpan
        Layout.preferredHeight: 50
        clip: true
        color: chartBackground

            Text {
                anchors.fill: parent
                textFormat: Text.RichText
                onLinkActivated: Qt.openUrlExternally(link)
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                text: qsTr(
                        "<a style='color:%1' href=\"https://opensoundmeter.com/tools?utm_source=tools&utm_medium=subalign&utm_campaign=promo\">more tools</a>"
                    ).arg(Material.accentColor)
            }
    }
}
