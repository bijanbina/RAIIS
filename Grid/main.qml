import QtQuick 2.1
import QtQuick.Window 2.0

Window {
    id:page
    visible: true
    property alias miheight:page.width
    color:"#171717"
    minimumHeight: 405
    minimumWidth: 720
    //Properties
    property string ipAddress: "192.168.1.101"

    //Signals:
    signal mousePressed(real x, real y)
    signal mouseReleased(real x, real y)

    MouseArea{
        id: screen_area
        anchors.fill: parent
        z: 1
        onPressed: mousePressed(mouseX/page.width,mouseY/page.height)
        onReleased: mouseReleased(mouseX/page.width,mouseY/page.height)
    }

    Canvas
    {
        id: gridCanvas
        anchors.fill: parent
        z: 3
        onPaint: {
            var ctx = gridCanvas.getContext('2d')
            ctx.beginPath();
            ctx.lineWidth = 1;
            //ctx.strokeStyle = '#ff0000';
            ctx.globalAlpha = 0.5;/* Grid
            ///////////////Center///////////////
            ctx.moveTo(page.minimumWidth/2,0);
            ctx.lineTo(page.minimumWidth/2,page.minimumHeight);
            ctx.moveTo(0,page.minimumHeight/2);
            ctx.lineTo(page.minimumWidth,page.minimumHeight/2);

            ///////////////Horizontal///////////////
            ctx.moveTo(page.minimumWidth/4,0);
            ctx.lineTo(page.minimumWidth/4,page.minimumHeight);
            ctx.moveTo(0,page.minimumHeight/4);
            ctx.lineTo(page.minimumWidth,page.minimumHeight/4);

            ///////////////Vertical///////////////

            ctx.moveTo(3 * page.minimumWidth/4,0);
            ctx.lineTo(3 * page.minimumWidth/4,page.minimumHeight);
            ctx.moveTo(0,3 * page.minimumHeight/4);
            ctx.lineTo(page.minimumWidth,3 * page.minimumHeight/4);*/

            ctx.moveTo(page.minimumWidth/2,page.minimumHeight/2 - page.minimumHeight/8);
            ctx.lineTo(page.minimumWidth/2,page.minimumHeight/2 + page.minimumHeight/8);
            ctx.moveTo(page.minimumWidth/2 - page.minimumHeight/8,page.minimumHeight/2);
            ctx.lineTo(page.minimumWidth/2 + page.minimumHeight/8,page.minimumHeight/2);

            var t1t_x = page.minimumWidth/2 - page.minimumWidth/6;
            var t1t_y = page.minimumHeight/2 - page.minimumHeight/4;
            var t1t_len = page.minimumHeight/16;
            ctx.moveTo(t1t_x,t1t_y);
            ctx.lineTo(t1t_x + t1t_len,t1t_y);
            ctx.moveTo(t1t_x,t1t_y);
            ctx.lineTo(t1t_x,t1t_y + t1t_len);

            t1t_x = page.minimumWidth/2 + page.minimumWidth/6;
            t1t_y = page.minimumHeight/2 - page.minimumHeight/4;
            ctx.moveTo(t1t_x,t1t_y);
            ctx.lineTo(t1t_x - t1t_len,t1t_y);
            ctx.moveTo(t1t_x,t1t_y);
            ctx.lineTo(t1t_x,t1t_y + t1t_len);

            t1t_x = page.minimumWidth/2 - page.minimumWidth/6;
            t1t_y = page.minimumHeight/2 + page.minimumHeight/4;
            ctx.moveTo(t1t_x,t1t_y);
            ctx.lineTo(t1t_x + t1t_len,t1t_y);
            ctx.moveTo(t1t_x,t1t_y);
            ctx.lineTo(t1t_x,t1t_y - t1t_len);

            t1t_x = page.minimumWidth/2 + page.minimumWidth/6;
            t1t_y = page.minimumHeight/2 + page.minimumHeight/4;
            ctx.moveTo(t1t_x,t1t_y);
            ctx.lineTo(t1t_x - t1t_len,t1t_y);
            ctx.moveTo(t1t_x,t1t_y);
            ctx.lineTo(t1t_x,t1t_y - t1t_len);



            ctx.stroke();
        }
    }


    Rectangle{
        id: pageOverlay
        anchors.fill: parent

        CamLCD{}
    }
}
