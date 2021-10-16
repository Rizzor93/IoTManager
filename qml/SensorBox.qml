import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3
import IoT 1.0
import QtQml.Models 2.3
Item{
    id: sensorBox
    width: 460
    height: 300
    visible: true
    //// VARS --------------------------------->
    property Sensor sensor: Sensor{}
    property int deviceType: Device.ARDUINO
    //// VARS --------------------------------->

    Rectangle{
        id: rectMain
        color: "#26282a"
        radius: 15
        border.color: "#ffffff"
        anchors.topMargin: 0
        anchors.fill: parent
        clip: true

        ListView{
            id: listViewSensorBox
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 40
            flickableDirection: Flickable.AutoFlickIfNeeded
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 120
            anchors.topMargin: 25
            model: sensor
            delegate:
                GridLayout{
                anchors.fill: parent
                columns: 2
                columnSpacing: 30
                rowSpacing: 30

                // Sensor-Name
                Label{
                    text: qsTr("Sensor-Name:")
                }
                Label{
                    Layout.fillWidth: true
                    text: model.name
                }

                // Sensor-DataType
                Label{
                    text: qsTr("DataType:")

                }
                Label{
                    Layout.fillWidth: true
                    text: model.sensorDataType
                }

                //
                // PLC
                //

                // PLC-DataArea
                Label {
                    text: qsTr("PLC-DataArea:")
                    visible: deviceType > 1 && deviceType < 5
                }
                Label{
                    Layout.fillWidth: true
                    visible: deviceType > 1 && deviceType < 5
                    text: model.plcDataArea
                }

                // PLC-DataArea --> DB-Number
                Label{
                    text: qsTr("DB-Number:")
                    visible: deviceType > 1 && deviceType < 5 && model.plcDataArea == Sensor.DB
                }
                Label{
                    Layout.fillWidth: true
                    visible: deviceType > 1 && deviceType < 5 && model.plcDataArea == Sensor.DB
                    text: model.dbNum
                }

                // PLC-DataOffset
                Label{
                    text: qsTr("PLC-Data-Offset:")
                    visible: deviceType > 1 && deviceType < 5
                }
                Label{
                    Layout.fillWidth: true
                    visible: deviceType > 1 && deviceType < 5
                    text: model.dataOffset
                }

                // PLC-BoolIndex
                Label{
                    text: qsTr("PLC-Data-BoolIndex:")
                    visible: deviceType > 1 && deviceType < 5 && model.sensorDataType == Sensor.BOOL
                }
                Label{
                    Layout.fillWidth: true
                    visible: deviceType > 1 && deviceType < 5 && model.sensorDataType == Sensor.BOOL
                    text: model.boolIndex
                }

                //
                // Arduino/RaspberryPi
                //

                // GPIONumber
                Label{
                    text: qsTr("GPIO-Number:")
                    visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                }
                Label{
                    Layout.fillWidth: true
                    visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                    text: model.gpioNum
                }

                // GPIOType
                Label{
                    text: qsTr("GPIO-Type:")
                    visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                }
                Label{
                    Layout.fillWidth: true
                    visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                    text: model.gpioType
                }

                // PullUp-Resistor
                Label{
                    text: qsTr("PullUp-Resistor:")
                    visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                }
                Label{
                    Layout.fillWidth: true
                    visible: (deviceType == Device.ARDUINO || deviceType == Device.RASPBERRYPI)
                    text: model.pullUpResistor
                }

                //
                // OPC
                //

                Label{
                    text: qsTr("NodeID:")
                    visible: deviceType == Device.OPC
                }
                Label {
                    Layout.fillWidth: true
                    visible: deviceType == Device.OPC
                    text: model.nodeID
                }

            }

        }

        Button{
            id: buttonModify
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.rightMargin: 15
            text: qsTr("Modify")
            onClicked: modifySensor.visible = true
        }

        ModifySensor{
            id: modifySensor
            visible: false
            sensor: sensorBox.sensor
            deviceType: sensorBox.deviceType
        }

    }

}
