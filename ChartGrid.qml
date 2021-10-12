import QtQuick 2.12
import QtQuick.Layouts 1.12
import SubAlign 1.0

GridLayout {
    id: grid
    rows: 2
    columns: 3

    ChartWrap {
        color: "red"
    }

    ChartWrap {
        color: "blue"
        SplChart {
            anchors.fill: parent
        }
    }

    ChartWrap {
        color: "grey"
    }

    ChartWrap {
        color: "yellow"
    }

    ChartWrap {
        color: "green"
    }

    ChartWrap {
        color: "pink"
    }
}
