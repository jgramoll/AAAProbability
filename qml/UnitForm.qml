import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    id: unitForm

    ScrollView {
        anchors.fill: parent

        GridLayout {
            id: gridLayout
            width: parent.width

            columns: 3
            columnSpacing: 10
            rowSpacing: 10

            Label {
                text: ""
            }
            Label {
                text: "Attacker"
                font {
                    pointSize: 20
                }
            }
            Label {
                text: "Defender"
                font {
                    pointSize: 20
                }
            }

            Label {
                text: "Infantry"
                font {
                    pointSize: 16
                }
            }
            SpinBox {
                Layout.preferredWidth: unitForm.width / 3
                minimumValue: 0
                value: aaaProbability.attacker.infantryCount
                onEditingFinished: aaaProbability.attacker.infantryCount = value
            }
            SpinBox {
                Layout.preferredWidth: unitForm.width / 3
                minimumValue: 0
                value: aaaProbability.defender.infantryCount
                onEditingFinished: aaaProbability.defender.infantryCount = value
            }

            Label {
                text: "Tank"
                font {
                    pointSize: 16
                }
            }
            SpinBox {
                Layout.preferredWidth: unitForm.width / 3
                minimumValue: 0
                value: aaaProbability.attacker.tankCount
                onEditingFinished: aaaProbability.attacker.tankCount = value
            }
            SpinBox {
                Layout.preferredWidth: unitForm.width / 3
                minimumValue: 0
                value: aaaProbability.defender.tankCount
                onEditingFinished: aaaProbability.defender.tankCount = value
            }

            Label {
                text: "Fighter"
                font {
                    pointSize: 16
                }
            }
            SpinBox {
                Layout.preferredWidth: unitForm.width / 3
                minimumValue: 0
                value: aaaProbability.attacker.fighterCount
                onEditingFinished: aaaProbability.attacker.fighterCount = value
            }
            SpinBox {
                Layout.preferredWidth: unitForm.width / 3
                minimumValue: 0
                value: aaaProbability.defender.fighterCount
                onEditingFinished: aaaProbability.defender.fighterCount = value
            }

            Label {
                text: "Bomber"
                font {
                    pointSize: 16
                }
            }
            SpinBox {
                Layout.preferredWidth: unitForm.width / 3
                minimumValue: 0
                value: aaaProbability.attacker.bomberCount
                onEditingFinished: aaaProbability.attacker.bomberCount = value
            }
            SpinBox {
                Layout.preferredWidth: unitForm.width / 3
                minimumValue: 0
                value: aaaProbability.defender.bomberCount
                onEditingFinished: aaaProbability.defender.bomberCount = value
            }

            Button {
                Layout.columnSpan: 3
                Layout.alignment: Qt.AlignHCenter
                text: "Calculate"
                onClicked: aaaProbability.calculateLand()
            }
        }
    }
}

