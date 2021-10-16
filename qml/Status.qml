import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
//import QtQuick.Controls.Material 2.2
import QtQuick.Controls.Universal 2.2
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3

Item {
    property alias messageText: messageText
    property alias status: status
    // Status
    RowLayout {
        id: rowLayout
        anchors.fill: parent
        spacing: 10

        StatusIndicator {
            id: status
            height: 48
            color: "red"
            active: true
            visible: true
        }

        Label {
            id: messageText
            text: "Message: "
            visible: true
            verticalAlignment: Text.AlignVCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            font.pointSize: 16
        }
    }
}
