import QtQuick 2.0

Rectangle{
        width: 175
        //color: "#0F343F"
        color: parent.color

        Canvas {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            width: 75
            height: 75
            onPaint: {
                var ctx = getContext("2d");
                ctx.reset();

                //ctx.fillStyle = "#0F34FF";
                //ctx.fillRect(0, 0, width, height);

                var xStart = width / 2;
                var yStart = height * 0.9;

                ctx.beginPath();
                ctx.fillStyle = "#4D515C";
                ctx.moveTo(xStart, yStart);
                ctx.arc(xStart, yStart, width/1.25, Math.PI * 5.25 / 4, Math.PI * 6.75 / 4, false);
                ctx.lineTo(xStart, yStart);
                ctx.fill();

                ctx.beginPath();
                ctx.fillStyle = "#e8e9e3";
                ctx.moveTo(xStart, yStart);
                ctx.arc(xStart, yStart, width/1.5, Math.PI * 5.25 / 4, Math.PI * 6.75 / 4, false);
                ctx.lineTo(xStart, yStart);
                ctx.fill();
            }
        }
}
