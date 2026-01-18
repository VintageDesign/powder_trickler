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
        id: viewModel
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
            text: viewModel.setpoint
            font.pixelSize: 32
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            background: Rectangle {
                color: "#333333"
                radius: 5
            }
            onEditingFinished: viewModel.setSetpointInput(text)
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 20

            Button {
                text: qsTr("-")
                font.pixelSize: 32
                implicitWidth: 80
                implicitHeight: 80
                onClicked: viewModel.decrement()
            }
            Button {
                text: qsTr("+")
                font.pixelSize: 32
                implicitWidth: 80
                implicitHeight: 80
                onClicked: viewModel.increment()
            }
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Dispense")
            font.pixelSize: 24
            implicitWidth: 200
            implicitHeight: 70
            onClicked: viewModel.dispense()
        }

    }
}
