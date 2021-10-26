import QtQuick 2.0

MouseArea {
    anchors.fill: parent
    hoverEnabled: true

    required property Item xItem
    required property Item yItem
    required property Item zItem

    onPositionChanged: function(position) {
        let chart = parent;
        let point = chart.point(Qt.point(position.x, position.y));

        if (isNaN(point.x) || isNaN(point.x)) {
            return ;
        }

        xItem.text =
                point.x.toFixed(1) +
                chart.x.unit;
        yItem.text =
                point.y.toFixed(1) +
                chart.y.unit
                ;

        let value = chart.value(Qt.point(position.x, position.y));
        zItem.text = value + chart.unit;

        chart.cursor.x = point.x;
        chart.cursor.y = point.y;
    }

    onExited: {
        xItem.text = "";
        yItem.text = "";
        zItem.text = "";
        parent.cursor.x = NaN;
        parent.cursor.y = NaN;
    }
}
