import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PowderTrickler

Item {

    SettingsView {
        id: settingsViewModel
        Component.onCompleted: refreshPorts()
    }

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
