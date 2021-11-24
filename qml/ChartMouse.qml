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
import QtQuick 2.15
import QtQuick.Layouts 1.12

MouseArea {
    id:control
    anchors.fill: parent
    hoverEnabled: true

    required property Item xItem
    required property Item yItem
    required property Item zItem

    onDoubleClicked: toggleOpen();

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

    function toggleOpen()
    {
        let wrap = control.parent.parent;
        let grid = control.parent.parent.parent;

        if (wrap.opened) {
            wrap.z = 1;
            wrap.Layout.preferredWidth = Layout.columnSpan
            wrap.Layout.preferredHeight = Layout.rowSpan
        } else {
            wrap.z = 3;
            wrap.Layout.preferredWidth = grid.width
            wrap.Layout.preferredHeight = grid.height
        }
        wrap.opened = !wrap.opened;
    }
}
