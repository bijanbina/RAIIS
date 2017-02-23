import QtQuick 2.0


Item
{
    property alias color1 : picker1.color
    property alias color2 : picker2.color
    property alias color3 : picker3.color
    property alias color4 : picker4.color
    property alias color5 : picker5.color
    property int cell_size: 29 * page.scale_x
    property int checkedNum: 0
    signal cell_clicked( var cell )
    signal cell_disable()
    Rectangle
    {
        id: picker1
        width: cell_size
        height: cell_size
        x: 0
        y: 0
        radius: cell_size/2
        Image
        {
            source: "qrc:/Resources/Button/check_mark.png"
            anchors.centerIn: parent
            width: cell_size/3
            height: cell_size/3
            visible: checkedNum==1
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                if (checkedNum==1)
                {
                    checkedNum=0;
                    cell_disable();
                }
                else
                {
                    cell_clicked(picker1)
                    checkedNum=1;
                }
            }
        }
    }
    Rectangle
    {
        id: picker2
        width: cell_size
        height: cell_size
        x: cell_size/3 + cell_size
        y: 0
        radius: width/2
        Image
        {
            source: "qrc:/Resources/Button/check_mark.png"
            anchors.centerIn: parent
            width: cell_size/3
            height: cell_size/3
            visible: checkedNum==2
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                if (checkedNum==2)
                {
                    checkedNum=0;
                    cell_disable();
                }
                else
                {
                    checkedNum=2;
                    cell_clicked(picker2)
                }
            }
        }
    }
    Rectangle
    {
        id: picker3
        width: cell_size
        height: cell_size
        x: 2 * (cell_size/3 + cell_size)
        y: 0
        radius: width/2
        Image
        {
            source: "qrc:/Resources/Button/check_mark.png"
            anchors.centerIn: parent
            width: cell_size/3
            height: cell_size/3
            visible: checkedNum==3
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                if (checkedNum==3)
                {
                    checkedNum=0;
                    cell_disable();
                }
                else
                {
                    checkedNum=3;
                    cell_clicked(picker3)
                }
            }
        }
    }
    Rectangle
    {
        id: picker4
        width: cell_size
        height: cell_size
        x: 3 * (cell_size/3 + cell_size)
        y: 0
        radius: width/2
        Image
        {
            source: "qrc:/Resources/Button/check_mark.png"
            anchors.centerIn: parent
            width: cell_size/3
            height: cell_size/3
            visible: checkedNum==4
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                if (checkedNum==4)
                {
                    checkedNum=0;
                    cell_disable();
                }
                else
                {
                    checkedNum=4;
                    cell_clicked(picker4)
                }
            }
        }
    }
    Rectangle
    {
        id: picker5
        width: cell_size
        height: cell_size
        x: 4 * (cell_size/3 + cell_size)
        y: 0
        radius: width/2
        Image
        {
            source: "qrc:/Resources/Button/check_mark.png"
            anchors.centerIn: parent
            width: cell_size/3
            height: cell_size/3
            visible: checkedNum==5
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                if (checkedNum==5)
                {
                    checkedNum=0;
                    cell_disable();
                }
                else
                {
                    checkedNum=5;
                    cell_clicked(picker5)
                }
            }
        }
    }
}
