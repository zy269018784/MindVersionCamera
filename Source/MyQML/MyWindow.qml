import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts
import QtQuick.Controls

Window {
	id: window
    width: 400
    height: 300
    visible: true
    title: qsTr("Hello QML")
    
	
	Image {
		width: parent.width
		height: parent.height - 30
		source: "image://live/camera1"  
		cache: false
		fillMode: Image.PreserveAspectFit
	}
}