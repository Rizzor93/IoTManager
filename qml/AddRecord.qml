import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Controls.Universal 2.2
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3
import IoT 1.0
import QtQml.Models 2.15
Window {
    id: addRecord
    width: 880
    height: 540
    visible: true
    modality: Qt.WindowModal
    color: "#26282a"
    //// VARS --------------------------------->
    property variant sensorList: []
    property Sensor currentSensor : Sensor{}
    property RecordSensor newRecordSensor: RecordSensor{}
    property RecordSensorList newRecordSensorList: RecordSensorList{}
    property Record newRecord: Record{recordSensorList: newRecordSensorList}

    property variant recordTypes: ["EQUAL","ODD","SMALLER_THEN","BIGGER_THEN","RANGE","ALWAYS"]
    property variant boolValues: ["False","True"]
    property variant recordTypesOther: ["EQUAL","ODD","ALWAYS"]

    property string errorMsgNull: ""
    property string errorMsgName: "Record-Name: Need min. length (3-50)"
    property string errorMsgNameExists: "Record-Name: already exists"
    property string errorMsgNumberNeeded: "A Number is needed"
    property string errorMsgValueNeeded: "A Value is needed"
    property string errorMsgMissingRecordSensor: "A new Record need min. 1 RecordSensor in list"

    property RegExpValidator regExByte: RegExpValidator{regExp:/(?:0[xX])?[0-9a-fA-F]+/}
    property RegExpValidator regExDouble:RegExpValidator {regExp: /^(\d*\.)?\d+$/}
    property RegExpValidator regExInt: RegExpValidator {regExp: /^[0-9]{1,30}$/}
    property RegExpValidator regExString: RegExpValidator{regExp: /^.{3,50}$/}
    //// VARS --------------------------------->

    Rectangle {
        id: rectMain
        color: "#26282a"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
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
                addRecord.close()
                recordSensorModel.modelReset()
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
                // add running
                newRecord.running = switchRecordRunning.checked
                // add name
                newRecord.name = textFieldRecordName.text
                recordModel.add(newRecord)

                recordSensorModel.modelReset()
                addRecord.close()
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


        // RecordName
        // RecordRunning
        RowLayout{
            id: rowLayoutRecordName
            anchors.top: parent.top
            spacing: 30
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            // Record-Name
            Label{
                text: "Record-Name:"

            }
            TextField{
                id: textFieldRecordName
                width: 200
                placeholderText: "Name"
                validator: regExString
                onTextChanged: recordNameCheck(textFieldRecordName.text)
            }

            // Record-Start
            Label{
                text: "Record-Start:"
            }
            Switch{
                id: switchRecordRunning
                text: "Yes"
            }
        }

        // Sensors to Record
        Rectangle {
            id: rectlistViewSensorsRecord
            width: 760
            color: "#00000000"
            radius: 15
            border.color: "#ffffff"
            anchors.top: rowLayoutRecordName.bottom
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 240
            anchors.topMargin: 15

            ListView {
                id: listviewSensorsRecord
                anchors.fill: parent
                highlightRangeMode: ListView.ApplyRange
                anchors.bottomMargin: 10
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.topMargin: 10
                clip: true
                focus: true

                model: RecordSensorModel{id: recordSensorModel
                    list: newRecordSensorList
                    onListChanged: isValid()
                }
                delegate:

                    Item {
                    id: item1
                    width: listviewSensorsRecord.width
                    height: 80

                    GridLayout{
                        id: gridLayoutOutput
                        anchors.fill: parent
                        anchors.rightMargin: removeSensor.width + 10
                        anchors.leftMargin: 10
                        anchors.bottomMargin: 5
                        anchors.topMargin: 5
                        columns: {
                            if (model.recordType === RecordSensor.RANGE){
                                return 5
                            }else if (model.recordType === RecordSensor.ALWAYS){
                                return 3
                            }
                            else{
                                return 4
                            }
                        }
                        columnSpacing: 10
                        rowSpacing: 2

                        // Sensor
                        Label{
                            text: "Sensor"
                            horizontalAlignment: Text.AlignHCenter
                            color: "#ffffff"
                        }
                        // TriggerType
                        Label{
                            text: "TriggerType"
                            horizontalAlignment: Text.AlignHCenter
                            color: "#ffffff"
                        }
                        // TriggerValueMin
                        Label{
                            text: {
                                if(model.recordType === RecordSensor.RANGE){
                                    return "TriggerValueMin"
                                }else{
                                    return "TriggerValue"
                                }

                            }
                            horizontalAlignment: Text.AlignHCenter
                            color: "#ffffff"
                            visible: model.recordType !== RecordSensor.ALWAYS

                        }
                        // TriggerValueMax
                        Label{
                            text: "TriggerValueMax"
                            horizontalAlignment: Text.AlignHCenter
                            color: "#ffffff"
                            visible: model.recordType == RecordSensor.RANGE
                        }

                        // Interval
                        Label{
                            text: "Interval (seconds)"
                            horizontalAlignment: Text.AlignHCenter
                            color: "#ffffff"
                        }


                        // Sensor
                        Text{
                            color: "#ff9800"
                            text: model.name
                        }
                        // TriggerType
                        Text{
                            color: "#ff9800"
                            text: recordTypes[model.recordType]
                        }
                        // TriggerValue_min
                        Text{
                            color: "#ff9800"
                            text: {
                                if(model.sensorDataType !== Sensor.BOOL){
                                    return model.triggerValueMin
                                }else{
                                    return boolValues[model.triggerValueMin]
                                }

                            }
                            visible: model.recordType !== RecordSensor.ALWAYS
                        }
                        // TriggerValue_max
                        Text{
                            color: "#ff9800"
                            text: model.triggerValueMax
                            visible: model.recordType === RecordSensor.RANGE
                        }

                        // Interval
                        Text{
                            color: "#ff9800"
                            text: model.interval
                        }
                    }

                    MouseArea {
                        id:mouseArea
                        anchors.fill: parent
                        anchors.rightMargin: removeSensor.width
                        onClicked: listviewSensorsRecord.currentIndex = index
                    }

                    Button{
                        id: removeSensor
                        text: "Remove"
                        anchors.verticalCenter: item1.verticalCenter
                        anchors.right: item1.right
                        anchors.rightMargin: 5
                        onClicked: {
                            listviewSensorsRecord.currentIndex = index
                            removeRecordSensor()
                        }
                    }
                }
            }
        }

        // Add Element
        Rectangle{
            id: rectAddRecord
            height: 80
            color: "#00000000"
            radius: 15
            border.color: "#ffffff"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.bottomMargin: 100

            GridLayout{
                id: gridLayoutInput
                anchors.fill: parent
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.bottomMargin: 5
                anchors.topMargin: 5
                columns: 6
                columnSpacing: 4
                rowSpacing: 2

                // Sensor
                Label{
                    id: labelSensor
                    text: "Sensor"}
                // TriggerType
                Label{
                    id: labelTriggerType
                    text: "TriggerType"}
                // TriggerValueMin
                Label{
                    id: labelTriggerValueMin
                    text: "TriggerValueMin"}
                // TriggerValueMax
                Label{
                    id: labelTriggerValueMax
                    text: "TriggerValueMax"}
                // TriggerValueBool
                Label{
                    id: labelTriggerValueBool
                    text: "TriggerValue"
                }
                // Interval
                Label{
                    id: labelInterval
                    text: "Interval (seconds)"}


                // SensorList
                ComboBox{
                    id: comboBoxSensorList
                    font.pointSize: 13
                    implicitWidth: 200
                    onCurrentIndexChanged: sensorChanged()
                }
                // TriggerType
                ComboBox{
                    id: comboBoxTriggerType
                    font.pointSize: 13
                    implicitWidth: 180
                    onCurrentIndexChanged: inputMethodRecordSensor()
                    onModelChanged: inputMethodRecordSensor()
                }
                // TriggerValue_min
                TextField{
                    id: textFieldTriggerValueMin
                    placeholderText: "Value"
                    onTextChanged: acceptableInput ? inputValidationRecordSensor() : notValidSensor("TriggerValue: " + errorMsgValueNeeded)
                }
                // TriggerValue_max
                TextField{
                    id: textFieldTriggerValueMax
                    placeholderText: "Value"
                    onTextChanged: acceptableInput ? inputValidationRecordSensor() : notValidSensor("TriggerValue: " + errorMsgValueNeeded)
                }

                // TriggerValueBool
                ComboBox{
                    id: comboBoxTriggerValueBool
                    font.pointSize: 13
                    model: ["False","True"]
                }
                // Interval
                TextField{
                    id: textFieldInterval
                    placeholderText: "Interval"
                    validator: regExInt
                    onTextChanged: acceptableInput ? inputValidationRecordSensor() : notValidSensor("Interval: " + errorMsgNumberNeeded)
                }
            }

        }

        // Add Button
        Button{
            id: buttonAddSensor
            text: "ADD"
            anchors.top: rectAddRecord.bottom
            anchors.topMargin: 15
            anchors.horizontalCenter: rectAddRecord.horizontalCenter
            enabled: false
            onClicked: addRecordSensor()
        }

    }


    // validation all Inputs and show saveButton // ready for save Record
    function validation(){
        if(!textFieldRecordName.text < 3 && !textFieldRecordName.text == "" ){
            if(!recordModel.nameExists(textFieldRecordName.text)){
                // check recordName
                if(textFieldRecordName.acceptableInput){
                    // check count recordSensorList
                    if(recordSensorModel.rowCount() != 0){
                        save.visible = true
                    }else{
                        notValidRecord(errorMsgMissingRecordSensor)
                    }
                }

            }else{
                notValidRecord(errorMsgNameExists)
            }
        }else{
            notValidRecord(errorMsgName)
        }

    }

    // reset --> save visible false
    function reset(){
        textFieldRecordName.text = ""
        textFieldInterval.text = "0"
        textFieldTriggerValueMin.text = "0"
        textFieldTriggerValueMax.text = "0"
        switchRecordRunning.checked = false

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
    function notValidRecord(msg){
        save.visible = false
        statusindicator.messageText.text = msg
        statusindicator.status.color = "red"
        statusindicator.visible = true
    }
    // not valid --> buttonAddSensor disable and show status
    function notValidSensor(msg){
        buttonAddSensor.enabled = false
        statusindicator.messageText.text = msg
        statusindicator.status.color = "red"
        statusindicator.visible = true
    }
    // recordNameCheck
    function recordNameCheck(text){
        if(text.length < 3){
            notValidRecord(errorMsgName)
        }else{
            if(recordModel.nameExists(text)){
                notValidRecord(errorMsgNameExists)
            }else{
                isValid()
            }
        }

    }

    // add RecordSensor
    function addRecordSensor(){
        // add sensorID
        newRecordSensor.sensorID = currentSensor.sensorID
        // add sensorDataType
        newRecordSensor.sensorDataType = currentSensor.sensorDataType
        // add recordType
        newRecordSensor.recordType = comboBoxTriggerType.currentIndex
        // add correct the index from model --> if comboBoxTriggerType.model == recordTypesOther
        if(newRecordSensor.sensorDataType == Sensor.STRING ||
                newRecordSensor.sensorDataType == Sensor.DATETIME ||
                newRecordSensor.sensorDataType == Sensor.BOOL){
            if(comboBoxTriggerType.currentIndex == 2)
                newRecordSensor.recordType = comboBoxTriggerType.currentIndex + 3
        }

        // add trigger_values
        // BOOL
        if(newRecordSensor.sensorDataType == Sensor.BOOL){
            newRecordSensor.triggerValueMin = comboBoxTriggerValueBool.currentIndex
            newRecordSensor.triggerValueMax = ""
        }
        // OTHERS
        else{
            newRecordSensor.triggerValueMin = textFieldTriggerValueMin.text
            newRecordSensor.triggerValueMax = textFieldTriggerValueMax.text
        }

        // if recordType == ALWAYS remove triggerValues
        if(newRecordSensor.recordType == RecordSensor.ALWAYS){
            newRecordSensor.triggerValueMin = ""
            newRecordSensor.triggerValueMax = ""
        }

        // add interval
        newRecordSensor.interval = textFieldInterval.text
        // add to recordSensorModel
        recordSensorModel.add(newRecordSensor)
    }

    // remove RecordSensor
    function removeRecordSensor(){
        recordSensorModel.remove(recordSensorModel.at(listviewSensorsRecord.currentIndex))
    }

    // ComboBoxSensorList changed currentSensor
    function sensorChanged(){
        // update currentSensor
        currentSensor = sensorModel.at(comboBoxSensorList.currentIndex)
        // update inputMethods
        inputMethodRecordSensor()
    }

    // Show InputMethods
    function inputMethodRecordSensor(){
        // Resize gridLayoutInput.columns
        // Change comboBoxTriggerType model

        // Input for STRING DATETIME BOOL
        if(currentSensor.sensorDataType == Sensor.STRING || currentSensor.sensorDataType == Sensor.DATETIME ||
                currentSensor.sensorDataType == Sensor.BOOL){

            comboBoxTriggerType.model = recordTypesOther

            // ["EQUAL" "ODD"]
            if(comboBoxTriggerType.currentIndex <= 1 ){
                // BOOL
                if(currentSensor.sensorDataType == Sensor.BOOL){
                    gridLayoutInput.columns = 4
                    labelTriggerValueMin.text = "TriggerValue"
                    textFieldTriggerValueMin.visible = false
                    labelTriggerValueMin.visible = false

                    labelTriggerValueMax.visible = false
                    textFieldTriggerValueMax.visible = false

                    labelTriggerValueBool.visible = true
                    comboBoxTriggerValueBool.visible = true

                    labelInterval.visible = true
                    textFieldInterval.visible = true
                }
                // STRING DATETIME
                else{
                    gridLayoutInput.columns = 4

                    labelTriggerValueMin.text = "TriggerValue"
                    textFieldTriggerValueMin.visible = true
                    labelTriggerValueMin.visible = true

                    labelTriggerValueMax.visible = false
                    textFieldTriggerValueMax.visible = false

                    labelTriggerValueBool.visible = false
                    comboBoxTriggerValueBool.visible = false

                    labelInterval.visible = true
                    textFieldInterval.visible = true
                }


            }
            // ["ALWAYS"]
            else if(comboBoxTriggerType.currentIndex == 2){
                gridLayoutInput.columns = 3

                labelTriggerValueMin.text = "TriggerValueMin"
                textFieldTriggerValueMin.visible = false
                labelTriggerValueMin.visible = false

                labelTriggerValueMax.visible = false
                textFieldTriggerValueMax.visible = false

                labelTriggerValueBool.visible = false
                comboBoxTriggerValueBool.visible = false

                labelInterval.visible = true
                textFieldInterval.visible = true
            }
        }
        // Input for OTHER
        else{
            // ["EQUAL" "ODD" "SMALLER_THEN" "BIGGER_THEN"]
            if(comboBoxTriggerType.currentIndex < 4 ){
                comboBoxTriggerType.model = recordTypes
                gridLayoutInput.columns = 4

                labelTriggerValueMin.text = "TriggerValue"
                labelTriggerValueMin.visible = true
                textFieldTriggerValueMin.visible = true


                labelTriggerValueMax.visible = false
                textFieldTriggerValueMax.visible = false

                labelTriggerValueBool.visible = false
                comboBoxTriggerValueBool.visible = false

                labelInterval.visible = true
                textFieldInterval.visible = true
            }
            // ["RANGE"]
            else if(comboBoxTriggerType.currentIndex == 4){
                gridLayoutInput.columns = 5

                labelTriggerValueMin.text = "TriggerValueMin"
                textFieldTriggerValueMin.visible = true
                labelTriggerValueMin.visible = true

                labelTriggerValueMax.visible = true
                textFieldTriggerValueMax.visible = true

                labelTriggerValueBool.visible = false
                comboBoxTriggerValueBool.visible = false

                labelInterval.visible = true
                textFieldInterval.visible = true
            }
            // ["ALWAYS"]
            else if(comboBoxTriggerType.currentIndex == 5){
                gridLayoutInput.columns = 3

                labelTriggerValueMin.text = "TriggerValueMin"
                textFieldTriggerValueMin.visible = false
                labelTriggerValueMin.visible = false

                labelTriggerValueMax.visible = false
                textFieldTriggerValueMax.visible = false

                labelTriggerValueBool.visible = false
                comboBoxTriggerValueBool.visible = false

                labelInterval.visible = true
                textFieldInterval.visible = true
            }
        }


        // Change validationInput
        changeRegExValidation()
        // check inputValidation
        buttonAddSensor.enabled = false
        inputValidationRecordSensor()
    }

    // Change validationInput(RegExp)
    function changeRegExValidation(){
        // BYTE
        if(currentSensor.sensorDataType == Sensor.BYTE){
            textFieldTriggerValueMin.validator = regExByte
            textFieldTriggerValueMax.validator = regExByte

        }
        // INT
        if(currentSensor.sensorDataType == Sensor.INT){
            textFieldTriggerValueMin.validator = regExInt
            textFieldTriggerValueMax.validator = regExInt
        }
        // FLOAT DOUBLE
        if(currentSensor.sensorDataType == Sensor.FLOAT || currentSensor.sensorDataType == Sensor.DOUBLE){
            textFieldTriggerValueMin.validator = regExDouble
            textFieldTriggerValueMax.validator = regExDouble
        }
        // STRING
        if(currentSensor.sensorDataType == Sensor.STRING){
            textFieldTriggerValueMin.validator = regExString
            textFieldTriggerValueMax.validator = regExString
        }
        // DATETIME
        if(currentSensor.sensorDataType == Sensor.DATETIME){
            textFieldTriggerValueMin.validator = regExString
            textFieldTriggerValueMax.validator = regExString
        }
    }

    // Input validation for newRecordSensor
    function inputValidationRecordSensor(){
        // STRING // DATETIME // BOOL
        if(comboBoxTriggerType.count == 3){
            // ALWAYS
            if(comboBoxTriggerType.currentIndex == 2){
                // Check interval
                if(textFieldInterval.acceptableInput){
                    buttonAddSensor.enabled = true
                    isValid()
                    return
                }
            }
            // OTHER
            else{
                if(currentSensor.sensorDataType != Sensor.BOOL){
                    // Check TriggerValue
                    if(textFieldTriggerValueMin.acceptableInput){
                        buttonAddSensor.enabled = true
                        isValid()
                        return
                    }
                }else{
                    buttonAddSensor.enabled = true
                    isValid()
                    return
                }
            }


        }

        // OTHER
        if(comboBoxTriggerType.count == 6){
            // ALWAYS
            if(comboBoxTriggerType.currentIndex == 5){
                // Check Interval
                if(textFieldInterval.acceptableInput){
                    buttonAddSensor.enabled = true
                    isValid()
                    return
                }
            }
            // RANGE
            else if(comboBoxTriggerType.currentIndex == 4){
                // Check TriggerValueMin
                // Check TriggerValueMax
                // Check Interval
                if(textFieldTriggerValueMin.acceptableInput && textFieldTriggerValueMax.acceptableInput && textFieldInterval.acceptableInput){
                    buttonAddSensor.enabled = true
                    isValid()
                    return
                }
            }
            // OTHER
            else{
                if(textFieldTriggerValueMin.acceptableInput && textFieldInterval.acceptableInput){
                    buttonAddSensor.enabled = true
                    isValid()
                    return
                }
            }
        }

    }


    // set ModelData
    Connections{
        target: addRecord
        function onVisibleChanged(){
            sensorList = sensorModel.nameList()
            comboBoxSensorList.model = sensorList

            newRecord.deviceID = sensorModel.at(comboBoxSensorList.currentIndex).deviceID
            newRecordSensor.deviceID = sensorModel.at(comboBoxSensorList.currentIndex).deviceID

            currentSensor = sensorModel.at(comboBoxSensorList.currentIndex)
            comboBoxTriggerType.model = recordTypes

            reset()
        }
    }

}
