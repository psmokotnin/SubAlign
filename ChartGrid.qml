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

        PhaseOffsetChart {
           anchors.fill: parent
           alignment: source
           color: Material.color(Material.Red)
       }
    }

    ChartWrap {
        id: splPlane
        color: grid.chartBackground

        SplPlaneChart {
            anchors.fill: parent
            alignment: source
            plane: SplPlaneChart.XY
        }
    }

    ChartWrap {
        id: splSection
        color: grid.chartBackground

        SplPlaneChart {
            anchors.fill: parent
            alignment: source
            plane: SplPlaneChart.XZ
        }
    }

    ChartWrap {
        id: splChart
        color: grid.chartBackground

        SplChart {
            anchors.fill: parent
            alignment: source

            mainsColor: Material.color(Material.Blue)
            subwooferColor: Material.color(Material.Green)
            sumColor: Material.color(Material.Red)
        }
    }

    ChartWrap {
        color: grid.chartBackground
    }

    ChartWrap {
        color: grid.chartBackground
    }
}
