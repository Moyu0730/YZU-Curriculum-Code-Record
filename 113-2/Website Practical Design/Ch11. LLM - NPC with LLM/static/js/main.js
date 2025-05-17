let mapArray, ctx, currentImgMain;
const gridLength = 100;
var sources = {
    Mountain: 'static/images/material.png',
    Enemy: 'static/images/Enemy.png',
    Tomato: 'static/images/material.png'
};

var images = {};

function loadImages(sources, callback) {
    var loadedImages = 0;
    var numImages = 0;
    
    // get num of sources
    for(var src in sources) numImages++;
    for(var src in sources) {
        images[src] = new Image();
        images[src].onload = function() {
            if(++loadedImages >= numImages) {
                callback(images);
            }
        };
        images[src].src = sources[src];
    }
}

//initial
$(function(){
    // 0 : available, 1 : Mountain, 2 : Final Stop, 3 : Enemy, 4 : Tomato
    mapArray = [
        [0, 0, 1, 0, 0, 0, 1, 4],
        [1, 0, 0, 0, 1, 0, 0, 0],
        [1, 1, 0, 1, 1, 1, 0, 1],
        [1, 0, 0, 1, 1, 1, 0, 1],
        [1, 0, 1, 1, 1, 1, 0, 1],
        [3, 0, 1, 1, 1, 1, 0, 2],
    ];
    ctx = $("#myCanvas")[0].getContext("2d");

    imgMain = new Image();
    imgMain.src = "static/images/spriteSheet.png";
    currentImgMain = {
        x:0,
        y:0
    };

    imgMain.onload = function(){
        ctx.drawImage(imgMain, 0, 0, 80, 130, currentImgMain.x, currentImgMain.y, gridLength, gridLength);
    };

    for(let x in mapArray){
        for(let y in mapArray[x]){
            if(mapArray[x][y] == 1){
                loadImages(sources, function(images) {
                    ctx.drawImage(images.Mountain, 32, 65, 32, 32, y * gridLength, x * gridLength, gridLength, gridLength);
                });
            }else if(mapArray[x][y] == 3){
                loadImages(sources, function(images) {
                    ctx.drawImage(images.Enemy, 7, 40, 104, 135, y * gridLength, x * gridLength, gridLength, gridLength);
                });
            }else if( mapArray[x][y] == 4){
                loadImages(sources, function(images) {
                    ctx.drawImage(images.Tomato, 64, 65, 32, 32, y * gridLength, x * gridLength, gridLength, gridLength);
                });
            }
        }
    }
});

//Click Event
$(document).on("keydown", function(event){
    console.log(event.code);
    let targetImg, targetBlock, cutImagePositionX;
    targetImg = {
        x:-1,
        y:-1
    };
    targetBlock = {
        x:-1,
        y:-1
    };
    event.preventDefault();
    switch(event.code){
        case "ArrowLeft":
            targetImg.x = currentImgMain.x - gridLength;
            targetImg.y = currentImgMain.y;
            cutImagePositionX = 175;
            break;
        case "ArrowUp":
            targetImg.x = currentImgMain.x;
            targetImg.y = currentImgMain.y - gridLength;
            cutImagePositionX = 355;
            break;
        case "ArrowRight":
            targetImg.x = currentImgMain.x + gridLength;
            targetImg.y = currentImgMain.y;
            cutImagePositionX = 540;
            break;
        case "ArrowDown":
            targetImg.x = currentImgMain.x;
            targetImg.y = currentImgMain.y + gridLength;
            cutImagePositionX = 0;
            break;
        default:
            return;
    }

    if(targetImg.x <= 800 && targetImg.x >=0 && targetImg.y <= 600 && targetImg.y >=0){
        targetBlock.x = targetImg.y / gridLength;
        targetBlock.y = targetImg.x / gridLength;
    }else{
        targetBlock.x = -1;
        targetBlock.y = -1;
    }

    ctx.clearRect(currentImgMain.x, currentImgMain.y, gridLength, gridLength);

    if(targetBlock.x != -1 && targetBlock.y != -1){
        switch(mapArray[targetBlock.x][targetBlock.y]){
            case 0:
                $("#talkBox").text("");
                currentImgMain.x = targetImg.x;
                currentImgMain.y = targetImg.y;
                break;
            case 1:
                $("#talkBox").text("Mountain");
                break;
            case 2: // Final Stop
                ctx.clearRect(targetImg.x, targetImg.y, gridLength, gridLength);
                currentImgMain.x = targetImg.x;
                currentImgMain.y = targetImg.y;
                $("#talkBox").text("Destination is Thinking");
                $.post('/destArrived')
                    .done(function(data) {
                        $("#talkBox").text(data);
                    })
                    .fail(function(error) {
                        $("#talkBox").text("Error : ", error);
                    });
                break;
                break;
            case 3: //Enemy
                $("#talkBox").text("Enemy is Thinking");
                $.post('/call_llm')
                    .done(function(data) {
                        $("#talkBox").text(data);
                    })
                    .fail(function() {
                        $("#talkBox").text("Error");
                    });
                break;
            case 4: // Tomato
                $("#talkBox").text("Tomato");
                ctx.clearRect(targetImg.x, targetImg.y, gridLength, gridLength);
                currentImgMain.x = targetImg.x;
                currentImgMain.y = targetImg.y;
                break;
        }
    }else{
        $("#talkBox").text("Boundary");
    }

    ctx.drawImage(imgMain, cutImagePositionX, 0, 80, 130, currentImgMain.x, currentImgMain.y, gridLength, gridLength);

});