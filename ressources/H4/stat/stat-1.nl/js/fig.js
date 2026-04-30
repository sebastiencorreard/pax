"use strict";
function x2px(x){return parseInt( x*xsize/(xmax - xmin) - xsize*xmin/(xmax - xmin) );}
function y2px(y){return parseInt( -1*y*ysize/(ymax - ymin) + ymax*ysize/(ymax - ymin) );}
function drawPoly(id,x,y,xsize,ysize,linewidth,strokecolor,fillcolor,opacity,angle){
 var canvas = document.getElementById('vreemde_eend_'+id);
 var ctx = canvas.getContext('2d');
 ctx.clearRect(0,0,xsize,ysize);
 ctx.lineWidth = linewidth
 ctx.strokeStyle = "rgba("+strokecolor+","+opacity+")";
 ctx.fillStyle = "rgba("+fillcolor+","+opacity+")";
 var len = x.length;
 var x_c = x2px(0);
 var y_c = y2px(0);
 ctx.translate(x_c,y_c);
 ctx.rotate(angle*Math.PI/180);
 ctx.translate(-x_c,-y_c);
 ctx.beginPath();
 ctx.moveTo(x2px(x[0]),y2px(y[0]));
 for(var p = 1; p < len ; p++){
    ctx.lineTo(x2px(x[p]),y2px(y[p]));
 }
 ctx.closePath();
 ctx.fill();
 ctx.stroke();
 return;
}

var linewidth=4;
var xmin =-11;
var xmax = 11;
var ymin =-11;
var ymax = 11;
var opacity = 0.8;
var xsize=160
var ysize=160

function new_vreemde_eend_start(){
 var pnts=randint(4,8);
 var colors = shuffle(["255,0,0","0,255,0","0,0,255","255,138,0","#000000","0,205,205","147,112,219","85,107,47"]);
 var X = new Array(pnts);
 var Y = new Array(pnts);
 var poly_array_x = new Array(pnts);
 var poly_array_y = new Array(pnts);
 var ans_array_x = new Array(pnts);
 var ans_array_y = new Array(pnts);

 X=shuffle([-1,2,-3,4,-5,6,-7,8,-9]);
 Y=shuffle([ 1,-2,3,-4,5,-6,7,-8,9]);
 for(var p = 0 ; p < pnts ; p++){
  poly_array_x[p] = X[p];
  poly_array_y[p] = Y[p];
  ans_array_x[p] =  X[p];
  ans_array_y[p] = -1*(Y[p]);
 };

 X=shuffle([1,-2,3,-4,5,-6,7,-8,9]);
 Y=shuffle([-1,2,-3,4,-5,6,-7,8,-9]);
 for(var p = 0 ; p < pnts ; p++){
  poly_array_x[p] = X[p];
  poly_array_y[p] = Y[p];
  ans_array_x[p] = X[p];
  ans_array_y[p] = -1*(Y[p]);
 };
 /* correct answer*/
 answer = Math.round(3*(Math.random()) );
 var angle;
 for(var p=0 ; p < pnts ;p++){
  angle = randint(30,330); 
  if( p == answer ){ 
   drawPoly(p,ans_array_x,ans_array_y,xsize,ysize,linewidth,colors[0],colors[1],opacity,angle);
  }
  else
  { 
   drawPoly(p,poly_array_x,poly_array_y,xsize,ysize,linewidth,colors[0],colors[1],opacity,angle);
  };
 };
};

