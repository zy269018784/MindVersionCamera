import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts
import QtQuick.Controls


Rectangle
{
	id: rect
	property string str1: qsTr("默认标题")
	property string str2: qsTr("默认标题")
	property string str3: qsTr("默认标题")
	property int    spacing: 10
	RowLayout 
	{
		spacing: rect.spacing
		anchors.fill: parent 
		Label {
			text: rect.str1
			height: parent.height		
		}

		TextField {
			Layout.fillWidth: true  
			height: parent.height
			placeholderText: rect.str3
		}

		Label {
			text: rect.str3
			height: parent.height
		}	
	}	
}