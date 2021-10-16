import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Controls.Universal 2.2
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2

import IoT 1.0

Item{
    id: deviceBox
    width: 320
    height: 200
    visible: true
    //// VARS --------------------------------->
    property Device device: Device{}
    //// VARS --------------------------------->

    Rectangle{
        id: rectMain
        color: "#26282a"
        radius: 15
        border.color: "#ffffff"
        anchors.topMargin: 0
        anchors.fill: parent
        clip: true

        Button{
            id: buttonOption
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            anchors.rightMargin: 15
            text: qsTr("Option")
            onClicked:deviceOption.visible = true
        }

        DeviceOption{
            id: deviceOption
            device: deviceBox.device
            visible: false
        }

        ListView{
            id: listViewDeviceBox
            anchors.fill: parent
            anchors.bottomMargin: 80
            anchors.topMargin: 10
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            clip: true
            model: device
            delegate:
                GridLayout{
                width: parent.width
                height: parent.height
                rowSpacing: 20
                columns: 2
                clip: true
                //DeviceName
                Label{
                    text: "Device Name: "
                }
                Label{
                    Layout.fillWidth: true
                    text: model.name
                }
                // DeviceType
                Label{
                    text: "Device Type: "
                }
                Label{
                    Layout.fillWidth: true
                    text: model.deviceType
                }
                // DeviceLocation
                Label{
                    text: "Device Location: "
                }
                Label{
                    Layout.fillWidth: true
                    text: model.location
                }

            }

        }

    }

}
