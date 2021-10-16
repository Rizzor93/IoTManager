import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3
import IoT 1.0

Item{
    id: recordBox
    width: 460
    height: 320
    visible: true
    //// VARS --------------------------------->
    property Record record : Record{}
    property variant boolValues: ["False","True"]
    //// VARS --------------------------------->

    Rectangle{
        id: rectMain
        color: "#26282a"
        radius: 15
        border.color: "#ffffff"
        anchors.topMargin: 0
        anchors.fill: parent
        clip: true

        // Record-Name Label
        RowLayout{
            id: rowlayoutRecordName
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 25
            anchors.topMargin: 25
            // Name
            Label{
                text: qsTr("Record-Name:")
            }
            Label{
                Layout.fillWidth: true
                text: record.name
            }
        }

        // Record-Running Label
        RowLayout{
            id: rowlayoutRecordRunning
            anchors.left: parent.left
            anchors.top: rowlayoutRecordName.bottom
            anchors.leftMargin: 25
            anchors.topMargin: 10
            // Running
            Label{
                text: qsTr("Record-Running:")
            }
            Switch{
                id: switchRecordRunning
                text: "Yes"
                checked: record.running
                onCheckedChanged: record.running = checked
            }
        }

        // Record-SensorList Label
        RowLayout{ anchors.left: parent.left
            anchors.top: rowlayoutRecordRunning.bottom
            anchors.leftMargin: 25
            anchors.topMargin: 10
            // RecordSensorList
            Label{text: qsTr("Record-Sensorlist:")}
        }

        // RecordSensorList
        ListView{
            id: listViewRecordList
            anchors.left: parent.left
            anchors.right: buttonModify.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: 0
            anchors.leftMargin: 50
            anchors.bottomMargin: 30
            anchors.topMargin: 145
            flickableDirection: Flickable.AutoFlickIfNeeded
            clip: true
            spacing: 15
            model: RecordSensorModel{
                list: record.recordSensorList
            }
            delegate:
                Rectangle{
                width: 250
                height: 130
                color: "#26282a"
                radius: 15
                border.color: "#ffffff"
                clip: true

                GridLayout{
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    columns: 2
                    columnSpacing: 30
                    rowSpacing: 5
                    clip: true
                    // Sensor-Name
                    Label{
                        text: qsTr("Sensor-Name:")

                    }
                    Label{
                        Layout.fillWidth: true
                        text: model.name
                    }

                    // RecordType
                    Label{
                        text: qsTr("RecordType:")
                    }
                    Label{
                        Layout.fillWidth: true
                        text: model.recordTypeName
                    }

                    // TriggerValue
                    Label{
                        text: qsTr("TriggerValue:")
                        visible: model.recordType != RecordSensor.ALWAYS
                    }
                    Label{
                        Layout.fillWidth: true
                        visible: model.recordType != RecordSensor.ALWAYS
                        text:
                            if(model.recordType == RecordSensor.RANGE){
                                return model.triggerValueMin + " - " + model.triggerValueMax
                            }else if(model.recordType == RecordSensor.ALWAYS){
                                return ""
                            }
                            else if(model.sensorDataType == Sensor.BOOL){
                                return boolValues[model.triggerValueMin]
                            }
                            else return model.triggerValueMin
                    }

                    // Interval
                    Label{
                        text: qsTr("Interval:")
                    }
                    Label{
                        Layout.fillWidth: true
                        text: model.interval + " seconds"
                    }

                }

            }

        }
        // Modify
        Button{
            id: buttonModify
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.rightMargin: 15
            text: qsTr("Modify")
            onClicked: modifyRecord.visible = true

        }
        // Data
        Button{
            id: buttonData
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            anchors.rightMargin: 15
            text: qsTr("Data")
            onClicked:{
                console.log("TODO!")
            }

        }
    }

    ModifyRecord{
        id: modifyRecord
        visible: false
        record: recordBox.record

    }
}
