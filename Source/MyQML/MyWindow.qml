import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts
import QtQuick.Controls

Window {
	id: window
    width: 400
    height: 300
    visible: true
    title: qsTr("压花机")
    
	
	Image {
		width: parent.width - 400
		height: parent.height
		source: "image://live/camera1"  
		cache: false
		fillMode: Image.PreserveAspectFit
	}
	
	Button {
		x: parent.width - 400
		y: 0
		width: 100
		height: 50
		text: qsTr("人字")
		Layout.fillWidth: true
	}
	
	Button {
		x: parent.width - 250
		y: 0
		width: 100
		height: 50
		text: qsTr("一字")
		Layout.fillWidth: true
	}
	

	LabelWithInput
	{
		spacing: 10
		x: parent.width - 400
		y: 150
		width: 400
		height: 50
		str1: qsTr("针长")
		str2: qsTr("0")
		str3: qsTr("mm")
	}
	
	LabelWithInput
	{
		spacing: 10
		x: parent.width - 400
		y: 200
		width: 400
		height: 50
		str1: qsTr("间距")
		str2: qsTr("0")
		str3: qsTr("mm")
	}
	
	LabelWithInput
	{
		spacing: 10
		x: parent.width - 400
		y: 250
		width: 400
		height: 50
		str1: qsTr("条数")
		str2: qsTr("0")
		str3: qsTr("")
	}

}