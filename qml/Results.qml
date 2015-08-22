import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import AAAProbability 1.0

Item {
    id: resultsRoot

    BusyIndicator {
        id: busy
        anchors.centerIn: parent
        visible: false

        running: aaaProbability.processing
    }

    Label {
        id: procLabel
        anchors {
            top: busy.bottom
            horizontalCenter: parent.horizontalCenter
        }
        visible: false

        text: "Processing"
    }

    ColumnLayout {
        id: column
        visible: true
        anchors.fill: parent

        spacing: 10

        Label {
            Layout.alignment: Qt.AlignHCenter

            text: (aaaProbability.probability * 100).toFixed(3) + "%"
            font {
                pointSize: 24
            }

            color: aaaProbability.probability > 0.5 ? "green" : "red"
        }

        GridLayout {
            Layout.alignment: Qt.AlignHCenter
            columns: 3
            columnSpacing: 30

            Label {
                text: "Attacker"
                font {
                    pointSize: 16
                }
            }
            Label {
                text: "Defender"
                font {
                    pointSize: 16
                }
            }
            Label {
                Layout.rowSpan: 2
                text: "Avg IPC Lost"
                font {
                    pointSize: 12
                }
            }
            Label {
                text: aaaProbability.attackerAverageLostIPC.toFixed(3)
                font {
                    pointSize: 16
                }
            }
            Label {
                text: aaaProbability.defenderAverageLostIPC.toFixed(3)
                font {
                    pointSize: 16
                }
            }
        }

        Rectangle {
            Layout.preferredWidth: parent.width
            height: 3

            color: "#aaa"
        }

        ScrollView {
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
            Layout.minimumHeight: 100

            ListView {
                id: list
                width: parent.width

                model: !aaaProbability.processing ? aaaProbability.sortedResults : undefined
                delegate: Item {
                    width: parent.width
                    height: childrenRect.height

                    Column {
                        width: parent.width

                        Rectangle {
                            width: parent.width
                            height: 1

                            color: "#aaa"

                            visible: index > 0
                        }

                        Label {
                            id: probText

                            text: (item.probability * 100).toFixed(3) + "%"
                            font {
                                pointSize: 20
                            }
                        }

                        Item { width:1; height: 10 }

                        Label {
                            text: "Attacker"
                            font {
                                pointSize: 16
                            }
                        }

                        Grid {
                            columns: 2
                            flow: Grid.TopToBottom
                            spacing: 10

                            Label {
                                text: "Infantry"
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: item.attacker.infantryCount
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: "Tank"
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: item.attacker.tankCount
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: "Fighter"
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: item.attacker.fighterCount
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: "Bomber"
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: item.attacker.bomberCount
                                font {
                                    pointSize: 16
                                }
                            }
                        }

                        Item { width:1; height: 10 }

                        Label {
                            text: "Defender"
                            font {
                                pointSize: 16
                            }
                        }

                        Grid {
                            columns: 2
                            flow: Grid.TopToBottom
                            spacing: 10

                            Label {
                                text: "Infantry"
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: item.defender.infantryCount
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: "Tank"
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: item.defender.tankCount
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: "Fighter"
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: item.defender.fighterCount
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: "Bomber"
                                font {
                                    pointSize: 16
                                }
                            }
                            Label {
                                text: item.defender.bomberCount
                                font {
                                    pointSize: 16
                                }
                            }
                        }

                        Item { width:1; height: 10 }

                    }
                    states: [
                        State {
                            when: item.resultType === Result.Attacker
                            PropertyChanges { target: probText; color: "green"; }
                        },
                        State {
                            when: item.resultType === Result.Defender
                            PropertyChanges { target: probText; color: "red"; }
                        },
                        State {
                            when: item.resultType === Result.Tie
                            PropertyChanges { target: probText; color: "blue"; }
                        }

                    ]
                }
            }

        }

        Rectangle {
            Layout.preferredWidth: parent.width
            height: 3

            color: "#aaa"
        }

        Button {
            Layout.alignment: Qt.AlignHCenter

            text: "Back"
            onClicked: aaaProbability.navigateToForm();
        }
    }

    states: [
        State {
            when: aaaProbability.processing
            PropertyChanges { target: busy; visible: true; }
            PropertyChanges { target: procLabel; visible: true; }
            PropertyChanges { target: column; visible: false; }
        }
    ]
}

