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
        Run_screen {}

        // Settings Tab
        Settings_tab {}

    }
}
