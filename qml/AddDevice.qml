import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

import QtQuick.Controls.Universal 2.2
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3

import IoT 1.0

Window {
    id: addDevice
    width: 500
    height: 480
    visible: true
    modality: Qt.WindowModal
    //// VARS --------------------------------->
    property Device newDevice: Device{}
    property variant deviceTypes: ["Arduino", "RaspberryPi", "PLC_Siemens", "PLC_Beckhoff", "PLC_WAGO", "OPC"]
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
                addDevice.close()
            }
        }
        // Save
        Button {
            id: save
            x: 552
            y: 424
            text: qsTr("Save")
            visible: false
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.rightMargin: 10
            onClicked: {

                newDevice.name = textFieldDeviceName.text
                newDevice.location = textFieldLocationName.text
                newDevice.deviceType = comboBoxDeviceType.currentIndex
                newDevice.opcUrl = textFieldOPCUrl.text
                newDevice.ipAddress = textFieldIPAddress.text
                newDevice.gateway = textFieldGateWay.text
                newDevice.subnetMask = textFieldNetmask.text

                deviceModel.add(newDevice)

                addDevice.close()
            }
        }
        // Status
        Status {
            id: statusindicator
            visible: false
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 100
            anchors.bottomMargin: 50
            status.color: "green"
            messageText.text: ""
            messageText.font.pointSize: 10
        }
        // Input
        Grid {
            id: gridMain
            width: parent.width
            height: parent.height
            anchors.fill: parent
            clip: true
            verticalItemAlignment: Grid.AlignVCenter
            horizontalItemAlignment: Grid.AlignLeft
            spacing: 15
            columns: 2
            anchors.rightMargin: 50
            anchors.leftMargin: 50
            anchors.bottomMargin: 55
            anchors.topMargin: 20

            // Device-Type
            Label {
                text: "Device-Type:"
            }
            ComboBox {
                id: comboBoxDeviceType
                width: 200
                model: deviceTypes
            }
            // Device-Name
            Label{
                text: qsTr("Device-Name:")

            }
            TextField{
                id: textFieldDeviceName
                width: 250
                placeholderText: qsTr("Name")
                validator: RegExpValidator {
                    regExp: /^.{3,50}$/
                }
            }
            // Device-Location
            Label{
                text: qsTr("Location:")

            }
            TextField{
                id: textFieldLocationName
                width: 250
                placeholderText: qsTr("Location")
                validator: RegExpValidator {
                    regExp: /^.{3,50}$/
                }
                onTextChanged: acceptableInput ? isValid() : notValid(errorMsgLocation)
            }
            // IP-Address
            Label{
                text: qsTr("IP-Address:")
            }
            TextField{
                id: textFieldIPAddress
                placeholderText: qsTr("192.168.1.212")
                width: 250
                validator: RegExpValidator {
                    regExp: /^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/
                }
                onTextChanged: acceptableInput ? isValid() : notValid(errorMsgIpAddress)
            }
            // Netmask-Address
            Label{
                text: qsTr("Netmask-Address:")
            }
            TextField{
                id: textFieldNetmask
                placeholderText: qsTr("255.255.255.0")
                width: 250
                validator: RegExpValidator {
                    regExp: /^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/
                }
                onTextChanged: acceptableInput ? isValid() : notValid(errorMsgNetmaskAddress)
            }
            // Gateway-Address
            Label{
                text: qsTr("Gateway-Address:")
            }
            TextField{
                id: textFieldGateWay
                placeholderText: qsTr("192.168.1.1")
                width: 250
                validator: RegExpValidator {
                    regExp: /^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/
                }
                onTextChanged: acceptableInput ? isValid() : notValid(errorMsgGatewayAddress)
            }
            // OPC-Url
            Label{
                text: qsTr("OPC-Url:")
                visible: comboBoxDeviceType.currentIndex == 5
            }
            TextField{
                id: textFieldOPCUrl
                width: 250
                visible: comboBoxDeviceType.currentIndex == 5
                placeholderText: qsTr("opc.tcp://IP-Address:Port")
                validator: RegExpValidator {
                    regExp: /(opc.tcp):\/\/((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?):\d+/
                }
                onTextChanged: acceptableInput ? isValid() : notValid(errorMsgOPCUrl)
            }

        }
    }

    // validation all Inputs and show saveButton
    function validation(){
        // DeviceName
        if(textFieldDeviceName.acceptableInput && textFieldLocationName.acceptableInput &&
                textFieldIPAddress.acceptableInput && textFieldNetmask.acceptableInput &&
                textFieldGateWay.acceptableInput){
            // OPC
            if(comboBoxDeviceType.currentIndex == Device.OPC && textFieldOPCUrl.acceptableInput){
                save.visible = true
            }else if(comboBoxDeviceType.currentIndex != Device.OPC){
                save.visible = true
            }
        }

    }

    // reset --> hide saveButton reset Inputs
    function reset(){
        textFieldDeviceName.text = ""
        textFieldLocationName.text = ""
        comboBoxDeviceType.currentIndex = 0
        textFieldOPCUrl.text = ""
        textFieldIPAddress.text = ""
        textFieldGateWay.text = ""
        textFieldNetmask.text = ""

        save.visible = false
    }

    // is valid --> reset Status
    function isValid(){
        statusindicator.messageText.text = ""
        statusindicator.status.color = "green"
        statusindicator.visible = false
        validation()
    }
    // not valid --> save false and show status
    function notValid(msg){
        save.visible = false
        statusindicator.messageText.text = msg
        statusindicator.status.color = "red"
        statusindicator.visible = true

    }

    // DeviceName check
    Connections{
        target: textFieldDeviceName

        function onTextChanged(){

            if(textFieldDeviceName.text.length < 3){
                notValid(errorMsgName)
            }else{
                if(deviceModel.nameExists(textFieldDeviceName.text)){
                    notValid(errorMsgNameExists)
                }else{
                    isValid()
                }
            }
        }

    }

    // Reset Inputs
    Connections{
        target: addDevice

        function onVisibleChanged(){
            reset()
        }
    }
}
