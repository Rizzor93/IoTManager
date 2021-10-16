import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Controls.Universal 2.2
import QtQuick.Layouts 1.3

import IoT 1.0

Window {
    id: modifyDevice
    width: 500
    height: 600
    visible: true
    modality: Qt.WindowModal
    color: "#26282a"
    //// VARS --------------------------------->
    property Device device: Device{}
    property string errorMsgNull: ""
    property string errorMsgName: "Device-Name: Need min. length (3-50)"
    property string errorMsgNameExists: "Device-Name: already exists"
    property string errorMsgLocation: "Device-Location: Need min. length (3-50)"
    property string errorMsgIpAddress: "IP-Address: Need a valid Address e.g. '192.168.1.212' "
    property string errorMsgNetmaskAddress: "Netmask-Address: Need a valid Address e.g. '255.255.255.0' "
    property string errorMsgGatewayAddress: "Gateway-Address: Need a valid Address e.g. '192.168.1.1' "
    property string errorMsgOPCUrl: "OPC-Url: Need a valid Address e.g. 'opc.tcp://192.168.1.212:4840' "
    //// VARS --------------------------------->

    Rectangle {
        id: rectMain
        color: "#26282a"
        anchors.fill: parent
        visible: true
        // Close
        Button {
            id: close
            y: 424
            text: qsTr("Close")
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 10
            anchors.bottomMargin: 10
            onClicked: {
                modifyDevice.close()
                device.update()
            }
        }
        // Remove
        DelayButton{
            id: remove
            text: qsTr("Remove")
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 10
            anchors.bottomMargin: 10
            delay: 1000
            onActivated:{
                modifyDevice.destroy()
                deviceOption.destroy()
                deviceModel.remove(device)
            }
        }
        // Status
        Status {
            id: statusindicator
            visible: false
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 15
            anchors.bottomMargin: 105
            clip: false
            status.color: "green"
            messageText.text: ""
            messageText.font.pointSize: 10
        }
        // Input
        ListView{
            id: listViewDeviceModify
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 80
            flickableDirection: Flickable.AutoFlickIfNeeded
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 120
            anchors.topMargin: 50
            model: device
            delegate:
                GridLayout{
                anchors.fill: parent
                columns: 2
                columnSpacing: 30
                rowSpacing: 25
                // Device-Type
                Label {
                    text: "Device-Type:"
                }
                Label {
                    Layout.fillWidth: true
                    text: model.deviceType
                }
                // Device-Name
                Label{
                    text: qsTr("Device-Name:")
                }
                TextField{
                    Layout.fillWidth: true
                    text: model.name
                    validator: RegExpValidator {
                        regExp: /^.{3,50}$/
                    }
                    onTextChanged: acceptableInput ? isValid() : notValid(errorMsgName)
                    onEditingFinished: model.name = text
                }

                // Device-Location
                Label{
                    text: qsTr("Location:")

                }
                TextField{
                    Layout.fillWidth: true
                    text: model.location
                    validator: RegExpValidator {
                        regExp: /^.{3,50}$/
                    }
                    onTextChanged: acceptableInput ? isValid() : notValid(errorMsgLocation)
                    onEditingFinished: model.location = text
                }

                // IP-Address
                Label{
                    text: qsTr("IP-Address:")
                }
                TextField{
                    text: model.ipAddress
                    Layout.fillWidth: true
                    validator: RegExpValidator {
                        regExp: /^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/
                    }
                    onTextChanged: acceptableInput ? isValid() : notValid(errorMsgIpAddress)
                    onEditingFinished: model.ipAddress = text
                }

                // Netmask-Address
                Label{
                    text: qsTr("Netmask-Address:")
                }
                TextField{
                    text: model.subnetMask
                    Layout.fillWidth: true
                    validator: RegExpValidator {
                        regExp: /^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/
                    }
                    onTextChanged: acceptableInput ? isValid() : notValid(errorMsgNetmaskAddress)
                    onEditingFinished: model.subnetMask = text
                }

                // Gateway-Address
                Label{
                    text: qsTr("Gateway-Address:")
                }
                TextField{
                    text: model.gateway
                    Layout.fillWidth: true
                    validator: RegExpValidator {
                        regExp: /^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/
                    }
                    onTextChanged: acceptableInput ? isValid() : notValid(errorMsgGatewayAddress)
                    onEditingFinished: model.gateway = text
                }

                // OPC-Url
                Label{
                    text: qsTr("OPC-Url:")
                    visible: model.deviceType == Device.OPC
                }
                TextField{
                    Layout.fillWidth: true
                    visible: model.deviceType == Device.OPC
                    text: model.opcUrl
                    validator: RegExpValidator {
                        regExp: /(opc.tcp):\/\/((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?):\d+/
                    }
                    onTextChanged: acceptableInput ? isValid() : notValid(errorMsgOPCUrl)
                    onEditingFinished: model.opcUrl = text
                }

            }

        }

    }


    // is valid --> reset Status
    function isValid(){
        statusindicator.messageText.text = ""
        statusindicator.status.color = "green"
        statusindicator.visible = false
    }
    // not valid --> save false and show status
    function notValid(msg){
        statusindicator.messageText.text = msg
        statusindicator.status.color = "red"
        statusindicator.visible = true

    }


}
