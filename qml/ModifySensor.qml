import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Controls.Universal 2.2
import QtQuick.Layouts 1.3

import IoT 1.0

Window {
    id: modifySensor
    width: 550
    height: 540
    visible: false
    modality: Qt.WindowModal
    color: "#26282a"
    //// VARS --------------------------------->
    property Sensor sensor: Sensor{}
    property int deviceType: Device.ARDUINO
    property variant dataTypes: ["BOOL","BYTE","INT","FLOAT","DOUBLE","STRING","DATETIME"]
    property variant plcDataAreas: ["DB","MK","PE","PA","CT"]
    property variant gpioTypes: ["Input","Output","AnalogInput","AnalogOutput"]
    property string errorMsgNull: ""
    property string errorMsgName: "Sensor-Name: Need min. length (3-50)"
    property string errorMsgNameExists: "Sensor-Name: already exists"
    property string errorMsgNumberNeeded: "A Number is needed"
    //// VARS --------------------------------->

    Rectangle {
        id: rectMain
        visible: true
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
                modifySensor.close()
                sensor.update()
            }
        }
        // Remove
        DelayButton {
            id: remove
            text: qsTr("Remove")
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.rightMargin: 10
            delay: 1000
            onActivated:{
                modifySensor.close()
                sensorModel.remove(sensor)
            }

        }
        // Status
        Status {
            id: statusindicator
            visible: false
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 25
            anchors.bottomMargin: 100
            status.color: "green"
            messageText.text: ""
            messageText.font.pointSize: 10
        }
        // Details
        ListView{
            id: listViewSensor
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 100
            flickableDirection: Flickable.AutoFlickIfNeeded
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 120
            anchors.topMargin: 50
            model: sensor
            delegate:
                GridLayout{
                anchors.fill: parent
                columns: 2
                columnSpacing: 100
                rowSpacing: 30

                // Sensor-Name
                Label{
                    text: qsTr("Sensor-Name:")
                }
                TextField{
                    id: textFieldSensorName
                    Layout.fillWidth: true
                    text: model.name
                    validator: RegExpValidator {
                        regExp: /^.{3,50}$/
                    }
                    onTextChanged: acceptableInput ? isValid() : notValid(errorMsgName)
                    onEditingFinished: model.name = text
                }

                // Sensor-DataType
                Label{
                    text: qsTr("DataType:")

                }
                ComboBox{
                    id: comboBoxDataType
                    Layout.preferredWidth: 150
                    model: dataTypes
                    currentIndex: sensor.sensorDataType
                    onCurrentValueChanged: sensor.sensorDataType = currentIndex
                }

                //
                // PLC
                //

                // PLC-DataArea
                Label {
                    text: qsTr("PLC-DataArea:")
                    visible: deviceType > 1 && deviceType < 5
                }
                ComboBox{
                    id: comboBoxDataArea
                    Layout.preferredWidth: 150
                    visible: deviceType > 1 && deviceType < 5
                    model: plcDataAreas
                    currentIndex: sensor.plcDataArea.valueOf()
                    onCurrentValueChanged: sensor.plcDataArea = currentIndex
                }

                // PLC-DataArea --> DB-Number
                Label{
                    text: qsTr("DB-Number:")
                    visible: deviceType > 1 && deviceType < 5 && comboBoxDataArea.currentIndex == 0
                }
                TextField{
                    id: textFieldDBNumber
                    Layout.fillWidth: true
                    text: model.dbNum
                    visible: deviceType > 1 && deviceType < 5 && comboBoxDataArea.currentIndex == 0
                    validator: RegExpValidator {
                        regExp: /^[1-9]*[0-9]{1,6}$/
                    }
                    onTextChanged: acceptableInput ? isValid() : notValid("DB-Number: " + errorMsgNumberNeeded)
                    onEditingFinished: model.dbNum = text
                }

                // PLC-DataOffset
                Label{
                    text: qsTr("PLC-Data-Offset:")
                    visible: deviceType > 1 && deviceType < 5
                }
                TextField{
                    id:textFieldPLCOffset
                    Layout.fillWidth: true
                    text: model.dataOffset
                    visible: deviceType > 1 && deviceType < 5
                    validator: RegExpValidator {
                        regExp: /^[1-9]*[0-9]{1,6}$/
                    }
                    onTextChanged: acceptableInput ? isValid() : notValid("PLC-Data-Offset: " + errorMsgNumberNeeded)
                    onEditingFinished: model.dataOffset = text
                }

                // PLC-BoolIndex
                Label{
                    text: qsTr("PLC-Data-BoolIndex:")
                    visible: deviceType > 1 && deviceType < 5 && comboBoxDataType.currentIndex == 0
                }
                SpinBox{
                    id: spinBoxPLCBoolIndex
                    Layout.fillWidth: true
                    to: 7
                    value: model.boolIndex
                    visible: deviceType > 1 && deviceType < 5 && comboBoxDataType.currentIndex == 0
                    onValueModified: model.boolIndex = value
                }

                //
                // Arduino/RaspberryPi
                //

                // GPIONumber
                Label{
                    text: qsTr("GPIO-Number:")
                    visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                }
                TextField{
                    id: textFieldGPIONumber
                    Layout.fillWidth: true
                    visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                    text: model.gpioNum
                    validator: RegExpValidator {
                        regExp: /^[1-9]*[0-9]{1,6}$/
                    }
                    onTextChanged: acceptableInput ? isValid() : notValid("GPIO-Number: " +errorMsgNumberNeeded)
                    onEditingFinished: model.gpioNum = text
                }

                // GPIOType
                Label{
                    text: qsTr("GPIO-Type:")
                    visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                }
                ComboBox{
                    id: comboBoxGPIOType
                    Layout.preferredWidth: 150
                    visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                    model: gpioTypes
                    currentIndex: sensor.gpioType.valueOf()
                    onCurrentValueChanged: sensor.gpioType = currentIndex
                }

                // PullUp-Resistor
                Label{
                    text: qsTr("PullUp-Resistor:")
                    visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                }
                ComboBox{
                    id: comboBoxPULLUPResistor
                    Layout.preferredWidth: 150
                    visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                    model: ["False","True"]
                    currentIndex: sensor.pullUpResistor.valueOf()
                    onCurrentValueChanged: sensor.pullUpResistor = currentIndex
                }

                //
                // OPC
                //

                Label{
                    text: qsTr("NodeID:")
                    visible: deviceType == Device.OPC
                }
                TextField {
                    id: textFieldNodeID
                    Layout.fillWidth: true
                    visible: deviceType == Device.OPC
                    validator: RegExpValidator {
                        regExp: /^[0-9]{1,30}$/
                    }
                    text: model.nodeID
                    onTextChanged: acceptableInput ? isValid() : notValid("NodeID: " + errorMsgNumberNeeded)
                    onEditingFinished: model.nodeID = text
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
