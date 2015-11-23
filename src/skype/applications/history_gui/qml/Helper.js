var component;
var obj;
function createComponentAccSettingsRect() {
    component = Qt.createComponent("AccSettingsRect.qml");
    if (component.status === Component.Ready)
        finishCreation();
    else
        component.statusChanged.connect(finishCreation);
}
function finishCreation() {
    if (component.status === Component.Ready) {
        obj = component.createObject(settings_container, {"color": "lightgreen", "width": 300, "height": 100});
        if (obj == null) {
            // Error Handling
            console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // Error Handling
        console.log("Error loading component:", component.errorString());
    }
}
