import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Controls.Universal 2.2
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3

import IoT 1.0

Window {
    id: deviceOption
    width: 800
    height: 600
    visible: true
    modality: Qt.WindowModal
    color: "#26282a"
    //// VARS --------------------------------->
    property Device device: Device{}
    property SensorModel sensorModel: SensorModel{id:sensorModel; list:device.sensorList}
    property RecordModel recordModel: RecordModel{id:recordModel;list:device.recordList}
    //// VARS --------------------------------->
    Rectangle {
        id: rectMain
        color: "#26282a"
        anchors.fill: parent
        clip: false
        anchors.bottomMargin: 0
        visible: true
        // Close
        Button {
            id: close
            y: 424
            text: qsTr("Close")
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            clip: true
            anchors.leftMargin: 10
            anchors.bottomMargin: 10
            onClicked: deviceOption.close()
        }
        // Status
        Status {
            id: statusindicator
            visible: false
            clip: true
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 100
            anchors.bottomMargin: 50
            status.color: "green"
            messageText.text: ""
            messageText.font.pointSize: 10
        }

        TabBar {
            id: mainBar
            width: rectMain.width
            position: TabBar.Header

            Repeater {
                model: ["Device", "Sensor", "Record"]

                TabButton {
                    text: modelData
                    width: Math.max(100, mainBar.width / 3)
                }
            }
        }

        StackLayout {
            id: stackLayoutMain
            width: rectMain.width
            height: rectMain.height - mainBar.height
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: mainBar.bottom
            anchors.bottom: parent.bottom
            currentIndex: mainBar.currentIndex
            clip: true
            anchors.bottomMargin: 50

            Rectangle{
                id: deviceTab
                width: parent.width
                height: parent.height
                color: "#26282a"
                clip: true
                Button{
                    id: buttonDeviceModify
                    text: qsTr("Modify")
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.rightMargin: 10
                    onClicked: modifyDevice.visible = true
                }

                ListView{
                    id: listViewDevice
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.rightMargin: 50
                    anchors.leftMargin: 50
                    flickableDirection: Flickable.AutoFlickIfNeeded
                    anchors.bottomMargin: 0
                    anchors.topMargin: 60
                    model: device
                    delegate:

                        Rectangle{
                        id: rectangle
                        width: 400
                        height: 400
                        color: "#00000000"
                        anchors.horizontalCenter: parent.horizontalCenter
                        radius: 15
                        border.color: "#ffffff"
                        clip: true

                        GridLayout{
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            columns: 2

                            columnSpacing: 30
                            rowSpacing: 10
                            // Device-Type
                            Label {
                                text: "Device-Type:"
                            }
                            Label {
                                id: labeldeviceType
                                Layout.fillWidth: true
                                text: model.deviceType
                            }
                            // Device-Name
                            Label{
                                text: qsTr("Device-Name:")
                            }
                            Label{
                                id: labelDeviceName
                                Layout.fillWidth: true
                                text: model.name
                            }

                            // Device-Location
                            Label{
                                text: qsTr("Location:")

                            }
                            Label{
                                id: labelLocationName
                                Layout.fillWidth: true
                                text: model.location
                            }
                            // IP-Address
                            Label{
                                text: qsTr("IP-Address:")
                            }
                            Label{
                                id: labelIPAddress
                                Layout.fillWidth: true
                                text: model.ipAddress
                            }
                            // Netmask-Address
                            Label{
                                text: qsTr("Netmask-Address:")
                            }
                            Label{
                                id: labelNetmask
                                Layout.fillWidth: true
                                text: model.subnetMask
                            }
                            // Gateway-Address
                            Label{
                                text: qsTr("Gateway-Address:")
                            }
                            Label{
                                id: labelGateWay
                                Layout.fillWidth: true
                                text: model.gateway
                            }
                            // OPC-Url
                            Label{
                                text: qsTr("OPC-Url:")
                                visible: model.deviceType == Device.OPC
                            }
                            Label{
                                id: labelOPCUrl
                                Layout.fillWidth: true
                                visible: model.deviceType == Device.OPC
                                text: model.opcUrl
                            }

                        }

                    }

                }

                ModifyDevice{
                    id: modifyDevice
                    visible: false
                    device: deviceOption.device
                }

            }
            Rectangle{
                id: sensorTab
                width: parent.width
                height: parent.height
                color: "#26282a"


                Button{
                    id: buttonAddSensor
                    text: qsTr("Add Sensor")
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.rightMargin: 10
                    onClicked: addSensor.visible = true
                }

                ListView{
                    id: listViewSensor
                    visible: true
                    width: parent.width
                    height: parent.height
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottomMargin: 0
                    anchors.topMargin: 80
                    clip: true
                    spacing: 30
                    model:sensorModel

                    delegate:
                        SensorBox{
                        sensor: model.sensor
                        deviceType: deviceOption.device.deviceType
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                }


                AddSensor{
                    id: addSensor
                    visible: false
                    deviceType: deviceOption.device.deviceType
                    deviceID: deviceOption.device.deviceID
                }
            }

            // TODO
            Rectangle{
                id: recordTab
                width: stackLayoutMain.width
                height: stackLayoutMain.height
                color: "#26282a"
                Button{
                    id: buttonAddRecord
                    text: qsTr("Add Record")
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.rightMargin: 10
                    onClicked: addRecord.visible = true
                }

                ListView{
                    id: listViewRecord
                    visible: true
                    width: parent.width
                    height: parent.height
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottomMargin: 0
                    anchors.topMargin: 80
                    clip: true
                    spacing: 30
                    model:recordModel

                    delegate:
                        RecordBox{
                        record: model.record
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                }

                AddRecord{
                    id: addRecord
                    visible: false
                }
            }

        }

    }



}
