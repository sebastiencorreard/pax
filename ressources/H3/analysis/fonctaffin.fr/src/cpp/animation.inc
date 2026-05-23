jQuery(function(){
  jQuery(".accordion").accordion({
          collapsible: true,
          active: false,
        });
      } );
      
function animateBoundingBox(board,targetBbox,duration) {
  var startBbox=board.getBoundingBox().slice(); 
  var fps=60,
      totalFrames=Math.ceil(duration*fps/1000),
      frame=0;
  function step() {
    frame++;
    var t=frame/totalFrames;
    if (t>1) t=1;
    var interpBbox=startBbox.map(function(startVal,i) {
      var endVal=targetBbox[i];
      return startVal+(endVal-startVal)*t;
    });
   board.setBoundingBox(interpBbox);
    board.update();
    if (t<1) {
      requestAnimationFrame(step);
    }
  }
  requestAnimationFrame(step);
}    


function blink(node, duration, interval) {
  var visible = false;
  var blinkId = setInterval(function() {
    if (visible === true) {
      visible = false;
    } else {
      visible = true;
    }
    node.setAttribute({ visible: visible });
    board2.update();
  }, interval);
  setTimeout(function() {
    clearInterval(blinkId);
    node.setAttribute({ visible: true });
    board2.update();
  }, duration);
}
