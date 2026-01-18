import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PowderTrickler


Item {

    RunScreenView {
        id: runViewModel
    }

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
