import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Controls.Universal 2.2
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3
import IoT 1.0

Window {
    id: addSensor
    width: 500
    height: 450
    modality: Qt.WindowModal
    color: "#26282a"
    //// VARS --------------------------------->
    property int deviceType: Device.ARDUINO
    property int deviceID: 0
    property Sensor newSensor: Sensor{}
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
                addSensor.close()
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

                newSensor.name = textFieldSensorName.text
                newSensor.sensorDataType = comboBoxDataType.currentIndex

                // PLC
                if(deviceType > 1 && deviceType < 5){
                    newSensor.plcDataArea = comboBoxPLCDataArea.currentIndex
                    //newSensor.dataOffset = qmlBridge.qStringToDouble(textFieldPLCOffset.text)
                    newSensor.dataOffset = textFieldPLCOffset.text
                    newSensor.boolIndex = spinBoxPLCBoolIndex.value
                    //newSensor.dbNum = qmlBridge.qStringToDouble(textFieldDBNumber.text)
                    newSensor.dbNum = textFieldDBNumber.text
                }
                // Arduino/RaspberryPi
                if(deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI){
                    //newSensor.gpioNum = qmlBridge.qStringToDouble(textFieldGPIONumber.text)
                    newSensor.gpioNum = textFieldGPIONumber.text
                    newSensor.gpioType = comboBoxGPIOType.currentIndex
                    newSensor.pullUpResistor = comboBoxPULLUPResistor.currentIndex
                }
                // OPC
                if(deviceType == Device.OPC){
                    newSensor.nodeID = textFieldNodeID.text
                }

                sensorModel.add(newSensor)
                addSensor.close()
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

            // Sensor-Name
            Label{
                text: qsTr("Sensor-Name:")

            }
            TextField{
                id: textFieldSensorName
                width: 200
                placeholderText: qsTr("Name")
                validator: RegExpValidator {
                    regExp: /^.{3,50}$/
                }
                onTextChanged: sensorNameCheck(textFieldSensorName.text.toString())
            }
            // Data-Type
            Label{
                text: qsTr("DataType:")
            }
            ComboBox{
                id: comboBoxDataType
                model: dataTypes
                width: 200
            }
            //
            // PLC
            //
            // PLC-DataArea
            Label{
                text: qsTr("PLC-DataArea:")
                visible: deviceType > 1 && deviceType < 5

            }
            ComboBox{
                id: comboBoxPLCDataArea
                width: 200
                model: plcDataAreas
                visible: deviceType > 1 && deviceType < 5
            }
            // PLC-DataArea --> DB
            Label{
                text: qsTr("DB-Number:")
                visible: deviceType > 1 && deviceType < 5 && comboBoxPLCDataArea.currentIndex == Sensor.DB
            }
            TextField{
                id: textFieldDBNumber
                width: 100
                placeholderText: qsTr("1")
                visible: deviceType > 1 && deviceType < 5 && comboBoxPLCDataArea.currentIndex == Sensor.DB
                validator: RegExpValidator {
                    regExp: /^[1-9]*[0-9]{1,6}$/
                }
                onTextChanged: acceptableInput ? isValid() : notValid("DB-Number: " + errorMsgNumberNeeded)
            }
            // PLC-DataOffset
            Label{
                text: qsTr("PLC-Data-Offset:")
                visible: deviceType > 1 && deviceType < 5
            }
            TextField{
                id:textFieldPLCOffset
                width: 100
                placeholderText: qsTr("0")
                visible: deviceType > 1 && deviceType < 5
                validator: RegExpValidator {
                    regExp: /^[1-9]*[0-9]{1,6}$/
                }
                onTextChanged: acceptableInput ? isValid() : notValid("PLC-Data-Offset: " + errorMsgNumberNeeded)

            }
            // PLC-BoolIndex
            Label{
                text: qsTr("PLC-Data-BoolIndex:")
                visible: deviceType > 1 && deviceType < 5 && comboBoxDataType.currentIndex == Sensor.BOOL
            }
            SpinBox{
                id: spinBoxPLCBoolIndex
                to: 7
                visible: deviceType > 1 && deviceType < 5 && comboBoxDataType.currentIndex == Sensor.BOOL
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
                width: 100
                visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                placeholderText: qsTr("1")
                validator: RegExpValidator {
                    regExp: /^[1-9]*[0-9]{1,6}$/
                }
                onTextChanged: acceptableInput ? isValid() : notValid("GPIO-Number: " +errorMsgNumberNeeded)
            }
            // GPIOType
            Label{
                text: qsTr("GPIO-Type:")
                visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
            }
            ComboBox{
                id: comboBoxGPIOType
                visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                model: gpioTypes
                width: 200
            }
            // PullUp-Resistor
            Label{
                visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                text: qsTr("PullUp-Resistor:")
            }
            ComboBox{
                id: comboBoxPULLUPResistor
                width: 200
                visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                model: ["False","True"]
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
                width: 200
                visible: deviceType === Device.OPC
                placeholderText: qsTr("100")
                validator: RegExpValidator {
                    regExp: /^[0-9]{1,30}$/
                }
                onTextChanged: acceptableInput ? isValid() : notValid("NodeID: " + errorMsgNumberNeeded)
            }

        }

    }

    // validation all Inputs and show saveButton
    function validation(){

        if(!sensorModel.nameExists(textFieldSensorName.text)){
            if(textFieldSensorName.acceptableInput){
                // PLC
                if(deviceType > 1 && deviceType < 5){
                    // DB
                    if(comboBoxPLCDataArea.currentIndex == Sensor.DB){
                        if(textFieldDBNumber.text === "0")
                            notValid("DB-Number: '0' is not allowed")

                        if(textFieldDBNumber.acceptableInput && textFieldPLCOffset.acceptableInput && textFieldDBNumber.text !== "0")
                            save.visible = true
                    } // Other DataArea
                    else if(comboBoxPLCDataArea.currentIndex != Sensor.DB){
                        if(textFieldPLCOffset.acceptableInput && textFieldPLCOffset.acceptableInput)
                            save.visible = true
                    }
                }
                // Arduino RaspberryPi
                if(deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI){
                    if(textFieldGPIONumber.acceptableInput)
                        save.visible = true
                }
                // OPC
                if(deviceType == Device.OPC){
                    if(textFieldNodeID.acceptableInput)
                        save.visible = true
                }
            }

        }else{
            notValid(errorMsgNameExists)
        }

    }

    // reset hide saveButton reset Inputs
    function reset(){
        textFieldSensorName.text = ""
        comboBoxDataType.currentIndex = 0
        comboBoxPLCDataArea.currentIndex = 0
        textFieldDBNumber.text = ""
        textFieldPLCOffset.text = ""
        spinBoxPLCBoolIndex.value = 0
        textFieldGPIONumber.text = ""
        comboBoxGPIOType.currentIndex = 0
        comboBoxPULLUPResistor.currentIndex = 0

        save.visible = false
    }

    // is valid --> reset Status
    function isValid(){
        statusindicator.messageText.text = ""
        statusindicator.status.color = "green"
        statusindicator.visible = false
        validation()
    }

    // not valid --> save visible false and show status
    function notValid(msg){
        save.visible = false
        statusindicator.messageText.text = msg
        statusindicator.status.color = "red"
        statusindicator.visible = true

    }

    // sensorNameCheck
    function sensorNameCheck(text){
        if(text.length < 3){
            notValid(errorMsgName)
        }else{
            if(sensorModel.nameExists(text)){
                notValid(errorMsgNameExists)
            }else{
                isValid()
            }
        }

    }

    // set ModelData
    Connections{
        target: addSensor
        function onVisibleChanged(){
            newSensor.deviceID = deviceID
            reset()
        }

    }

}
