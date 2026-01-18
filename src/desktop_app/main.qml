import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PowderTrickler

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: qsTr("Powder Trickler")

    color: "#1e1e1e"

    RunScreenView {
        id: runViewModel
    }

    SettingsView {
        id: settingsViewModel
        Component.onCompleted: refreshPorts()
    }

    header: TabBar {
        id: tabBar
        currentIndex: 0

        TabButton {
            text: qsTr("Run")
            font.pixelSize: 18
            implicitHeight: 50
        }
        TabButton {
            text: qsTr("Settings")
            font.pixelSize: 18
            implicitHeight: 50
        }
    }

    StackLayout {
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        // Run Tab
        Item {
            ColumnLayout {
                anchors.centerIn: parent
                spacing: 20

                Label {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Target:")
                    font.pixelSize: 32
                    color: "#aaaaaa"
                }
                TextField {
                    id: setpointInput
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 150
                    text: runViewModel.setpoint
                    font.pixelSize: 32
                    color: "#ffffff"
                    horizontalAlignment: Text.AlignHCenter
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    background: Rectangle {
                        color: "#333333"
                        radius: 5
                    }
                    onEditingFinished: runViewModel.setSetpointInput(text)
                }

                RowLayout {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: 20

                    Button {
                        text: qsTr("-")
                        font.pixelSize: 32
                        implicitWidth: 80
                        implicitHeight: 80
                        onClicked: runViewModel.decrement()
                    }
                    Button {
                        text: qsTr("+")
                        font.pixelSize: 32
                        implicitWidth: 80
                        implicitHeight: 80
                        onClicked: runViewModel.increment()
                    }
                }

                Button {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Dispense")
                    font.pixelSize: 24
                    implicitWidth: 200
                    implicitHeight: 70
                    onClicked: runViewModel.dispense()
                }
            }
        }

        // Settings Tab
        Item {
            ColumnLayout {
                anchors.centerIn: parent
                spacing: 20

                Label {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Serial Port")
                    font.pixelSize: 32
                    color: "#aaaaaa"
                }

                RowLayout {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: 10

                    ComboBox {
                        id: portComboBox
                        implicitWidth: 250
                        implicitHeight: 50
                        font.pixelSize: 18
                        model: settingsViewModel.availablePorts
                        currentIndex: settingsViewModel.availablePorts.indexOf(settingsViewModel.selectedPort)
                        onActivated: settingsViewModel.selectPort(currentText)
                    }

                    Button {
                        text: qsTr("Refresh")
                        font.pixelSize: 18
                        implicitWidth: 100
                        implicitHeight: 50
                        onClicked: settingsViewModel.refreshPorts()
                    }
                }

                Button {
                    Layout.alignment: Qt.AlignHCenter
                    text: settingsViewModel.isConnected ? qsTr("Disconnect") : qsTr("Connect")
                    font.pixelSize: 24
                    implicitWidth: 200
                    implicitHeight: 70
                    onClicked: {
                        if (settingsViewModel.isConnected) {
                            settingsViewModel.disconnect()
                        } else {
                            settingsViewModel.connectToPort()
                        }
                    }
                }

                Label {
                    Layout.alignment: Qt.AlignHCenter
                    text: settingsViewModel.isConnected ? qsTr("Connected to: ") + settingsViewModel.selectedPort : qsTr("Not connected")
                    font.pixelSize: 16
                    color: settingsViewModel.isConnected ? "#4CAF50" : "#aaaaaa"
                }
            }
        }
    }
}
