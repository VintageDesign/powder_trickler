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
        Label {
            Layout.alignment: Qt.AlignHCenter
            text: viewModel.setpoint
            font.pixelSize: 32
            color: "#aaaaaa"
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
