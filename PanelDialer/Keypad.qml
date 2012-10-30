import QtQuick 2.0
import Ubuntu.Components 0.1

Item {
    id: keypad

    width: keys.width
    height: keys.height

    signal keyPressed(int keycode, string label)

    BorderImage {
        id: background

        anchors.fill: keys
        anchors.leftMargin: units.dp(-2)
        anchors.rightMargin: units.dp(-2)
        anchors.bottomMargin: units.dp(-1)
        source: "../assets/keypad_background.png"
        border {left: units.dp(15); right: units.dp(15); top: units.dp(2); bottom: units.dp(15)}
        horizontalTileMode: BorderImage.Stretch
        verticalTileMode: BorderImage.Stretch
    }

    Image {
        id: separators

        anchors.fill: keys
        source: "../assets/keypad_div_tile.png"
        fillMode: Image.Tile
        verticalAlignment: Image.AlignTop
    }

    Grid {
        id: keys

        rows: 4
        columns: 3
        spacing: units.dp(1)

        KeypadButton {
            label: "1"
            keycode: Qt.Key_1
            onClicked: keypad.keyPressed(keycode, label)
            onPressAndHold: telephony.callVoicemail()
        }

        KeypadButton {
            label: "2"
            sublabel: "ABC"
            keycode: Qt.Key_2
            onClicked: keypad.keyPressed(keycode, label)
        }

        KeypadButton {
            label: "3"
            sublabel: "DEF"
            keycode: Qt.Key_3
            onClicked: keypad.keyPressed(keycode, label)
        }

        KeypadButton {
            label: "4"
            sublabel: "GHI"
            keycode: Qt.Key_4
            onClicked: keypad.keyPressed(keycode, label)
        }

        KeypadButton {
            label: "5"
            sublabel: "JKL"
            keycode: Qt.Key_5
            onClicked: keypad.keyPressed(keycode, label)
        }

        KeypadButton {
            label: "6"
            sublabel: "MNO"
            keycode: Qt.Key_6
            onClicked: keypad.keyPressed(keycode, label)
        }

        KeypadButton {
            label: "7"
            sublabel: "PQRS"
            keycode: Qt.Key_7
            onClicked: keypad.keyPressed(keycode, label)
        }

        KeypadButton {
            label: "8"
            sublabel: "TUV"
            keycode: Qt.Key_8
            onClicked: keypad.keyPressed(keycode, label)
        }

        KeypadButton {
            label: "9"
            sublabel: "WXYZ"
            keycode: Qt.Key_9
            onClicked: keypad.keyPressed(keycode, label)
        }

        KeypadButton {
            isCorner: true
            corner: Qt.BottomLeftCorner
            label: "*"
            keycode: Qt.Key_Asterisk
            onClicked: keypad.keyPressed(keycode, label)
        }

        KeypadButton {
            label: "0"
            sublabel: "+"
            keycode: Qt.Key_0
            onClicked: keypad.keyPressed(keycode, label)
        }

        KeypadButton {
            isCorner: true
            corner: Qt.BottomRightCorner
            label: "#"
            keycode: Qt.Key_ssharp
            onClicked: keypad.keyPressed(keycode, label)
        }
    }
}
