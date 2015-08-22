import QtQuick 2.5
import QtQuick.Window 2.2
import AAAProbability 1.0

Item {
    anchors.fill: parent
    visible: true

    Loader {
        id: panelLoader
        anchors {
            fill: parent
            margins: 5
        }

        sourceComponent: unitFormComponent

        states: [
            State {
                when: aaaProbability.panelState === PanelState.UnitForm
                PropertyChanges { target: panelLoader; sourceComponent: unitFormComponent }
            },
            State {
                when: aaaProbability.panelState === PanelState.Results
                PropertyChanges { target: panelLoader; sourceComponent: resultComponent }
            }
        ]
    }

    Component {
        id: unitFormComponent

        UnitForm {
            anchors.fill: parent

        }
    }

    Component {
        id: resultComponent

        Results {
            anchors.fill: parent

        }
    }
}
