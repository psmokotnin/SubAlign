import QtQuick 2.12
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

    ChartWrap {
        id: phaseOffsetChart
        color: grid.chartBackground
        title: "Phase offset"

        PhaseOffsetChart {
           anchors.fill: parent
           anchors.topMargin: 20
           alignment: source
           color: Material.color(Material.Red)
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
        }
    }
}
