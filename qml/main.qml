import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import IoT 1.0


ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: qsTr("IoT Manager")
    id: mainWindow
    //// VARS --------------------------------->
    //// VARS --------------------------------->

    Rectangle {
        id: mainRectangle
        color: "#26282a"
        anchors.fill: parent

        TabBar {
            id: mainBar
            width: mainRectangle.width

            Repeater {
                model: ["Dashboard", "Data","Option"]

                TabButton {
                    text: modelData
                    width: Math.max(100, mainBar.width / 3)
                }
            }
        }

        StackLayout {
            id: stackLayoutMain
            width: mainRectangle.width
            height: mainRectangle.height - mainBar.height
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: mainBar.bottom
            anchors.bottom: parent.bottom
            currentIndex: mainBar.currentIndex
            //currentIndex: 2

            Rectangle {
                id: dashboardTab
                width: stackLayoutMain.width
                height: stackLayoutMain.height
                color: "#26282a"

                Button {
                    id: addMachine
                    text: qsTr("add Device")
                    anchors.right: parent.right
                    anchors.top: parent.top
                    clip: false
                    anchors.topMargin: 10
                    anchors.rightMargin: 10
                    onClicked: addDevice.visible = true
                }

                AddDevice{
                    id: addDevice
                    visible: false
                }

                GridView {
                    id: gridMachineBox
                    width: parent.width
                    height: parent.height
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.leftMargin: 50
                    anchors.topMargin: 75
                    flow: Grid.LeftToRight
                    clip: true
                    cellWidth: 330
                    cellHeight: 230
                    model:DeviceModel{
                        id: deviceModel
                        list: Devices
                    }
                    delegate:
                        DeviceBox{
                        device: model.device
                    }

                }

            }

            // TODO
            Rectangle {
                id: dataTab
                width: stackLayoutMain.width
                height: stackLayoutMain.height
                color: "#26282a"
                Text {
                    text: qsTr("data")
                }
            }

            Rectangle {
                id: optionTab
                width: stackLayoutMain.width
                height: stackLayoutMain.height
                color: "#26282a"
                // Text
                RowLayout{
                    anchors.top: parent.top
                    anchors.topMargin: 25
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text {
                        color: "orange"
                        text: qsTr("Configure connection to 'IoT_Service':\nafter changed you must restart the application")
                        font.pointSize: 16
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                }

                // Status
                Status {
                    id: statusindicator
                    visible: false
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.leftMargin: 25
                    anchors.bottomMargin: 50
                    status.color: "green"
                    messageText.text: ""
                    messageText.font.pointSize: 10
                }

                // Restart Application
                Button{
                    id: buttonRestartApp
                    x: 596
                    y: 466
                    text: "Restart"
                    enabled: false
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    anchors.rightMargin: 10
                    onClicked: ConfigSingleTon.restartApplication()
                }

                // Show Options
                ListView{
                    id: listViewOption
                    width: 400
                    height: 400
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 100
                    anchors.horizontalCenter: parent.horizontalCenter
                    flickableDirection: Flickable.AutoFlickIfNeeded
                    anchors.bottomMargin: 60
                    model: ConfigModel{
                        id:configModel
                    }
                    delegate:

                        Rectangle{
                        id: rectangle
                        //anchors.fill: parent
                        width: 300
                        height: 150
                        color: "#00000000"
                        anchors.horizontalCenter: parent.horizontalCenter
                        radius: 15
                        border.color: "#ffffff"
                        clip: true

                        GridLayout{
                            anchors.fill: parent
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.rightMargin: 15
                            anchors.leftMargin: 15
                            anchors.bottomMargin: 15
                            anchors.topMargin: 15
                            columns: 2
                            columnSpacing: 30
                            rowSpacing: 5
                            // Host
                            Label {
                                text: "Host:"
                            }
                            TextField {
                                Layout.fillWidth: true
                                text: model.host
                                validator: RegExpValidator {
                                    regExp: /^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/
                                }
                                onTextChanged: acceptableInput ? isValid() : notValid("Host: Need a valid Address e.g. '192.168.1.212'")
                                onEditingFinished: model.host = text
                            }
                            // Port
                            Label{
                                text: qsTr("Port:")
                            }
                            TextField{
                                Layout.fillWidth: true
                                text: model.port
                                validator: RegExpValidator {
                                    regExp: /^[1-9]*[0-9]{1,6}$/
                                }
                                onTextChanged: acceptableInput ? isValid() : notValid("Port: Need a valid Number")
                                onEditingFinished: model.port = text
                            }

                        }

                    }

                }


            }
        }
    }

    // is valid --> reset Status
    function isValid(){
        statusindicator.messageText.text = ""
        statusindicator.status.color = "green"
        statusindicator.visible = false
        buttonRestartApp.enabled = true
    }
    // not valid --> restartButton false and show status
    function notValid(msg){
        statusindicator.messageText.text = msg
        statusindicator.status.color = "red"
        statusindicator.visible = true
        buttonRestartApp.enabled = false

    }




}


