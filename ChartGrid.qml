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
        color: grid.chartBackground

        PhaseOffsetChart {
           anchors.fill: parent
           alignment: source
           color: Material.color(Material.Red)
       }
    }

    ChartWrap {
        color: grid.chartBackground

    }

    ChartWrap {
        color: grid.chartBackground
    }

    ChartWrap {
        color: grid.chartBackground

        SplChart {
            anchors.fill: parent
        }
    }

    ChartWrap {
        color: grid.chartBackground
    }

    ChartWrap {
        color: grid.chartBackground
    }
}
