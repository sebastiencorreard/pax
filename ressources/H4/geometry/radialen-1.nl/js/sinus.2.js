
<!-- begin generated javascript include for canvasdraw -->
"use strict";
<!-- these variables and functions must be global -->
var read_dragdrop0;var read_canvas;var set_clock;var clear_draw_area;
var wims_canvas_function = function(){
 <!-- common used stuff -->
 var userdraw_x = [];var userdraw_y = [];var userdraw_radius = [];
 var xsize = 200;var ysize = 200;var precision = 100;
 var canvas_div = document.getElementById("canvas_div0");
 var create_canvas = function(canvas_type,size_x,size_y){var cnv;if(document.getElementById("wims_canvas"+canvas_type)){ cnv = document.getElementById("wims_canvas"+canvas_type);}else{try{ cnv = document.createElement("canvas"); }catch(e){alert("Your browser does not support HTML5 CANVAS:GET FIREFOX !");return;};
 canvas_div.appendChild(cnv);};cnv.width = size_x;cnv.height = size_y;cnv.style.top = 0;cnv.style.left = 0;
 cnv.style.position = "absolute";cnv.id = "wims_canvas"+canvas_type;return cnv;};
 function findPosX(i){ var obj = i;var curleft = 0;if(obj.offsetParent){while(1){curleft += obj.offsetLeft;if(!obj.offsetParent){break;};obj = obj.offsetParent;};}else{if(obj.x){curleft += obj.x;};};return curleft;};
 function findPosY(i){var obj = i;var curtop = 0;if(obj.offsetParent){while(1){curtop += obj.offsetTop;if(!obj.offsetParent){break;};obj = obj.offsetParent;};}else{if(obj.y){curtop += obj.y;};};return curtop;};
 function x2px(x){if(use_xlogscale == 0 ){return parseFloat(x*xsize/(xmax - xmin) - xsize*xmin/(xmax - xmin));}else{var x_max = Math.log(xmax)/Math.log(xlogbase);var x_min = Math.log(xmin)/Math.log(xlogbase);var x_in = Math.log(x)/Math.log(xlogbase);return x_in*xsize/(x_max - x_min) - xsize*x_min/(x_max - x_min);};};
 function px2x(px){if(use_xlogscale == 0 ){return parseFloat(px*(xmax - xmin)/xsize + xmin);}else{var x_max = Math.log(xmax)/Math.log(xlogbase);var x_min = Math.log(xmin)/Math.log(xlogbase);var x_out = x_min +px*(x_max - x_min)/(xsize);return Math.pow(xlogbase,x_out);};};
 function px2y(py){if(use_ylogscale == 0 ){return parseFloat(ymax - py*(ymax - ymin)/ysize);}else{var y_max = Math.log(ymax)/Math.log(ylogbase);var y_min = Math.log(ymin)/Math.log(ylogbase);var y_out = y_max +py*(y_min - y_max)/(ysize);return Math.pow(ylogbase,y_out);};};
 function y2px(y){if(use_ylogscale == 0){return parseFloat(-1*y*ysize/(ymax - ymin) + ymax*ysize/(ymax - ymin));}else{var y_max = Math.log(ymax)/Math.log(ylogbase);var y_min = Math.log(ymin)/Math.log(ylogbase);var y_in = Math.log(y)/Math.log(ylogbase);return (y_max - y_in)*ysize/(y_max - y_min);};};
 function scale_x_radius(rx){return rx*xsize/(xmax - xmin);};
 function scale_y_radius(ry){return ry*ysize/(ymax - ymin);};
 function distance(x1,y1,x2,y2){return parseInt(Math.sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ));};
 function distance_to_line (r,q,x,y){var c = (y) - (-1/r)*(x);var xs = r*(c - q)/(r*r+1);var ys = (r)*(xs)+(q);return parseInt(Math.sqrt( (xs-x)*(xs-x) + (ys-y)*(ys-y) ));};
 function move(obj,dx,dy){for(var p = 0 ; p < obj.x.length; p++){obj.x[p] = obj.x[p] + dx;obj.y[p] = obj.y[p] + dy;};return obj;};
 function slide(obj,dx,dy){for(var p = 0 ; p < obj.x.length; p++){obj.x[p] = x2px(obj.xorg[p] + dx);obj.y[p] = y2px(obj.yorg[p] + dy);};return obj;};var x_use_snap_to_grid = 0;var y_use_snap_to_grid = 0;var snap_x = 1;var snap_y = 1;
 function snap_to_x(x){return x2px(snap_x*(Math.round((px2x(x))/snap_x)));};
 function snap_to_y(y){return y2px(snap_y*(Math.round((px2y(y))/snap_y)));};var xlogbase = 10;var ylogbase = 10;var use_xlogscale = 0;var use_ylogscale = 0;var x_strings = null;
 var y_strings = null;var use_pan_and_zoom = 0;var use_jsmath = 0;var xstart = 0;var ystart = 0;var unit_x=" ";var unit_y=" ";
 <!-- begin drag_drop_onclick shape library -->
 if( typeof dragdrop_precision == 'undefined' ){var dragdrop_precision = 100;};
 function Shape(click_cnt,onclick,direction,type,x,y,w,h,line_width,stroke_color,stroke_opacity,fill_color,fill_opacity,use_filled,use_dashed,dashtype0,dashtype1,use_rotate,angle,text,font_size,font_family,use_affine,affine_matrix,slider,slider_cnt){ this.slider = slider || 0; this.slider_cnt = slider_cnt || 0; this.text = text || 0; this.font_size = font_size || 12; if( font_family.indexOf('px') > 0 ){this.font_family = font_family;}else{this.font_family = this.font_size+'px Ariel';}; this.use_rotate = use_rotate || 0; this.angle = angle*(Math.PI/180) || 0; this.use_affine = use_affine || 0; this.affine_matrix = affine_matrix || [1,0,0,1,0,0]; this.click_cnt = click_cnt || 1; this.onclick = onclick || 0; this.direction = direction || 0; this.type = type || 1; this.xorg = x; this.yorg = y; this.x = [x.length]; this.y = [x.length]; this.w = [x.length]; this.h = [x.length]; for(var p=0;p<x.length;p++){  this.x[p] = x2px(x[p]-xstart);  this.y[p] = y2px(y[p]-ystart);  if( p > w.length){    this.w[p] = w[0];    this.h[p] = h[0];  }  else  {    this.w[p] = w[p];    this.h[p] = h[p];  } }; this.line_width = line_width || 30; this.stroke_opacity = stroke_opacity || 1.0; this.stroke_color = "rgba("+stroke_color+","+stroke_opacity+")" || '#FF0000'; this.fill_opacity = fill_opacity || 1.0; this.fill_color = "rgba("+fill_color+","+fill_opacity+")" || '#FF0000'; this.use_filled = use_filled || 0; this.use_dashed = use_dashed || 0; this.dashtype0 = dashtype0 || 4; this.dashtype1 = dashtype1 || 4;};Shape.prototype.draw = function(ctx){ ctx.lineWidth = this.line_width; ctx.strokeStyle = this.stroke_color; ctx.fillStyle = this.fill_color; ctx.lineJoin = "round"; ctx.save(); if(this.use_rotate == 1){  var x_c = x2px(0);  var y_c = y2px(0);  ctx.translate(x_c,y_c);  ctx.rotate(this.angle);ctx.translate(-x_c,-y_c); }; if( this.use_affine == 1 ){  ctx.setTransform(this.affine_matrix[0],this.affine_matrix[1],this.affine_matrix[2],this.affine_matrix[3],this.affine_matrix[4],this.affine_matrix[5]); }; ctx.beginPath(); switch(this.type){  case 1: ctx.rect(this.x[0], this.y[0], this.x[1]-this.x[0], this.y[2] - this.y[0]);break;  case 2: ctx.arc(this.x[0],this.y[0],this.w[0],0,2*Math.PI,false);break;  case 3: ctx.save();var w = 0.5*(scale_x_radius(this.w[0]));var h = 0.5*(scale_y_radius(this.h[0]));ctx.scale(1,h/w);ctx.beginPath();ctx.arc(this.x[0], w/h*this.y[0], w, 0, 2 * Math.PI);if(this.use_filled == 1){ ctx.fillStyle = this.fill_color; ctx.fill(); };ctx.closePath();ctx.stroke();ctx.restore();break;  case 4: for(var p = 0; p < this.x.length - 1;p++){ctx.moveTo(this.x[p], this.y[p]);ctx.lineTo(this.x[p+1],this.y[p+1]);};break;  case 5: ctx.moveTo(this.x[0], this.y[0]);for(var p = 1; p < this.x.length;p++){ctx.lineTo(this.x[p],this.y[p]);};ctx.lineTo(this.x[0],this.y[0]);break;  case 6: var w = this.x[1] - this.x[0];var h = this.y[1] - this.y[0];var r = this.w[0];ctx.beginPath();ctx.moveTo(this.x[0] + r, this.y[0]);ctx.lineTo(this.x[0] + w - r, this.y[0]);ctx.quadraticCurveTo(this.x[0] + w, this.y[0], this.x[0] + w, this.y[0] + r);ctx.lineTo(this.x[0] + w, this.y[0] + h - r);ctx.quadraticCurveTo(this.x[0] + w, this.y[0] + h, this.x[0] + w - r, this.y[0] + h);ctx.lineTo(this.x[0] + r, this.y[0] + h);ctx.quadraticCurveTo(this.x[0], this.y[0] + h, this.x[0], this.y[0] + h - r);ctx.lineTo(this.x[0], this.y[0] + r);ctx.quadraticCurveTo(this.x[0], this.y[0], this.x[0] + r, this.y[0]);ctx.closePath();break;  case 7: ctx.moveTo(this.x[0]-this.w[0],this.y[0]-this.h[0]);ctx.lineTo(this.x[0]+this.w[0],this.y[0]+this.h[0]);ctx.moveTo(this.x[0]-this.w[0],this.y[0]+this.h[0]);ctx.lineTo(this.x[0]+this.w[0],this.y[0]-this.h[0]);break;  case 8: var dx;var dy;var len;var arrow_head = this.w[0];for(var p = 0; p < this.x.length - 1;p++){ctx.save();if(this.use_dashed == 1 ){if( ctx.setLineDash ){ ctx.setLineDash([this.dashtype0,this.dashtype1]);}else{ ctx.mozDash = [this.dashtype0,this.dashtype1];};};dx = this.x[p+1] - this.x[p];dy = this.y[p+1] - this.y[p];len = Math.sqrt(dx*dx+dy*dy);ctx.translate(this.x[p+1],this.y[p+1]);ctx.rotate(Math.atan2(dy,dx));ctx.lineCap = "round";ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(-len,0);ctx.closePath();ctx.stroke();ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(-1*arrow_head,-0.5*arrow_head);ctx.lineTo(-1*arrow_head, 0.5*arrow_head);ctx.closePath();ctx.fill();};break;  case 9: ctx.moveTo(this.x[0], this.y[0]);for(var p = 1; p < this.x.length - 1;p++){if( Math.abs(this.y[p] - this.y[p-1]) < ysize && Math.abs(this.y[p+1] - this.y[p]) < ysize ){ctx.lineTo(this.x[p],this.y[p]);}else{ctx.moveTo(this.x[p],this.y[p]);};};break;  case 10: var dx;var dy;var len;ctx.save();if(this.use_dashed == 1 ){if( ctx.setLineDash ){ ctx.setLineDash([this.dashtype0,this.dashtype1]);}else{ ctx.mozDash = [this.dashtype0,this.dashtype1];};};dx = this.x[1] - this.x[0];dy = this.y[1] - this.y[0];len = Math.sqrt(dx*dx+dy*dy);ctx.translate(this.x[1],this.y[1]);ctx.rotate(Math.atan2(dy,dx));ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(-len,0);ctx.closePath();ctx.stroke();ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(-1*this.w[0],0.5*this.w[0]);ctx.lineTo(-1*this.w[0],-0.5*this.w[0]);ctx.closePath();ctx.lineCap = "round";ctx.fill();ctx.restore();ctx.save();ctx.translate(this.x[0],this.y[0]);ctx.rotate(Math.atan2(dy,dx));ctx.beginPath();ctx.moveTo(0,0);ctx.lineTo(this.w[0],0.4*this.w[0]);ctx.lineTo(this.w[0],-0.4*this.w[0]);ctx.closePath();ctx.lineCap = "round";ctx.fill(); break;  case 11: var x1 = this.x[0];var y1 = this.y[0];var x2 = this.x[1];var y2 = this.y[1];var dx = this.x[2];var dy = this.y[2];var n  = this.w[0];for(var p = 0 ; p < n ; p++ ){ctx.beginPath();ctx.moveTo(x1,y1);ctx.lineTo(x2,y2);ctx.stroke();x1 = x1 + dx;y1 = y1 + dy;x2 = x2 + dx;y2 = y2 + dy;ctx.closePath();};break;  case 12: ctx.save();var start;var end;if(this.h[0] < this.h[1]){start = this.h[0];end = this.h[1]}else{start = this.h[1];end = this.h[0];};start=360-start;end=360-end;var r = this.w[0];ctx.arc(this.x[0], this.y[0], r, start*(Math.PI / 180), end*(Math.PI / 180),true);if(this.use_filled){ctx.lineTo(this.x[0],this.y[0]);ctx.fill();};ctx.restore();break;  case 13: for(var p = 0; p < this.x.length; p++){ ctx.arc(this.x[p],this.y[p],scale_x_radius(this.w[p]),0,2*Math.PI,false);};break;  case 14: ctx.font = this.font_family ;ctx.fillText(this.text,this.x[0],this.y[0]);break;  case 15: break;  case 16: for(var p = 0; p < this.x.length;p++){ctx.fillRect( this.x[p], this.y[p],this.line_width,this.line_width );};break;  case 17: ctx.save();var start;var end;if(this.h[0] < this.h[1]){start = this.h[0];end = this.h[1]}else{start = this.h[1];end = this.h[0];};start=360-start;end=360-end;var r = scale_x_radius(this.w[0]);ctx.arc(this.x[0], this.y[0], r, start*(Math.PI / 180), end*(Math.PI / 180),true);if(this.use_filled){ctx.lineTo(this.x[0],this.y[0]);ctx.fill();};ctx.restore();break;  case 18: ctx.moveTo(this.x[0], this.y[0]);ctx.lineTo(this.x[1],this.y[1]);break;  default: alert("draw primitive unknown");break; }; if(this.use_filled == 1){ ctx.fill();} if(this.use_dashed == 1 ){if( ctx.setLineDash ){ ctx.setLineDash([this.dashtype0,this.dashtype1]);}else{ ctx.mozDash = [this.dashtype0,this.dashtype1];};}; ctx.stroke(); ctx.restore();};Shape.prototype.contains = function(mx, my){ var marge = 2*this.line_width; switch(this.type){  case 1: for(var p = 0 ; p < this.x.length; p++ ){if( mx < this.x[p] + marge &&  mx > this.x[p] - marge ){if( my < this.y[p]+marge && my > this.y[p] - marge ){return p;};};};break;  case 2: for(var p = 0 ; p < this.x.length; p++ ){if( Math.abs(distance(this.x[p],this.y[p],mx,my) ) < this.w[p] + marge ){return p;break;};};break;  case 3: for(var p = 0 ; p < this.x.length; p++ ){if( Math.abs(distance(this.x[p],this.y[p],mx,my) ) < scale_x_radius(this.w[p]) + marge ){return p;break;};};break;  case 4: var diff;var q;var r;for(var p = 0 ; p < this.x.length-1; p = p+2  ){if( ((this.x[p+1] - this.x[p]) != 0)  && ((this.y[p+1]-this.y[p]) != 0) ){r = (this.y[p+1]-this.y[p])/(this.x[p+1]-this.x[p]);q = this.y[p] - (r)*(this.x[p]);diff = distance_to_line(r,q,mx,my);}else{if( (this.y[p+1]-this.y[p]) != 0 ){diff = Math.abs(this.x[p] - mx);}else{diff = Math.abs(this.y[p] - my);};};if( diff  < marge ){ return p;};}; break;  case 5: break;  case 6: for(var p = 0 ; p < this.x.length; p++ ){if( mx < this.x[p] + marge &&  mx > this.x[p] - marge ){if( my < this.y[p]+marge && my > this.y[p] - marge ){return p;};};};break;  case 7: for(var p = 0 ; p < this.x.length; p++ ){if( (this.x[p] - this.w[p] <= mx) && (this.x[p] + this.w[p] >= mx) &&  (this.y[p] - this.h[p] <= my) && (this.y[p] + this.h[p] >= my) ){return p;};};break;  case 8: var diff;var q;var r;for(var p = 0 ; p < this.x.length-1; p = p+2  ){if( ((this.x[p+1] - this.x[p]) != 0)  && ((this.y[p+1]-this.y[p]) != 0) ){r = (this.y[p+1]-this.y[p])/(this.x[p+1]-this.x[p]);q = this.y[p] - (r)*(this.x[p]);diff = distance_to_line(r,q,mx,my);}else{if( (this.y[p+1]-this.y[p]) != 0 ){diff = Math.abs(this.x[p] - mx);}else{diff = Math.abs(this.y[p] - my);};};if( diff  < marge ){ return p;};}; break;  case 9: for(var p = 0 ; p < this.x.length; p++ ){if( (this.x[p] - this.line_width <= mx) && (this.x[p] + this.w[p] + this.line_width >= mx) &&  (this.y[p] - this.line_width <= my) && (this.y[p] + this.h[p] +this.line_width  >= my) ){return p;};};break;  case 10: var diff;var q;var r;for(var p = 0 ; p < this.x.length-1; p = p+2  ){if( ((this.x[p+1] - this.x[p]) != 0)  && ((this.y[p+1]-this.y[p]) != 0) ){r = (this.y[p+1]-this.y[p])/(this.x[p+1]-this.x[p]);q = this.y[p] - (r)*(this.x[p]);diff = distance_to_line(r,q,mx,my);}else{if( (this.y[p+1]-this.y[p]) != 0 ){diff = Math.abs(this.x[p] - mx);}else{diff = Math.abs(this.y[p] - my);};};if( diff  < marge ){ return p;};}; break;  case 11: break;  case 12: break;  case 13: for(var p = 0 ; p < this.x.length; p++ ){if( Math.abs(distance(this.x[p],this.y[p],mx,my) ) < scale_x_radius(this.w[p]) + marge ){return p;break;};};break;  case 14: for(var p = 0 ; p < this.x.length; p++ ){if(this.y[p] < my + 0.5*(this.font_size) && this.y[p] > my - 0.5*(this.font_size)){var w = parseInt(0.8*(this.font_size)*((this.text).length));if(this.x[p] < mx + w && this.x[p] > mx - w ){ return p;break;};};};break;  case 15: break;  case 16: break;  case 17: break;  case 18: var diff;var q;var r;if(((this.x[1] - this.x[0]) != 0) && ((this.y[1]-this.y[0]) != 0)){r = (this.y[1]-this.y[0])/(this.x[1]-this.x[0]);q = this.y[0] - (r)*(this.x[0]);diff = distance_to_line(r,q,mx,my);}else{if((this.y[1]-this.y[0])!= 0){diff = Math.abs(this.x[0] - mx);}else{diff = Math.abs(this.y[0] - my);};};if( diff  < marge ){ return 0;};break;  default: for(var p = 0 ; p < this.x.length; p++ ){if( (this.x[p] - this.line_width <= mx) && (this.x[p] + this.w[p] + this.line_width >= mx) &&  (this.y[p] - this.line_width <= my) && (this.y[p] + this.h[p] +this.line_width  >= my) ){return p;};};break; }; return -1;};var reply = [];function CanvasState(canvas,container_div){ this.canvas = canvas; this.width = canvas.width; this.height = canvas.height; var ctx = canvas.getContext("2d"); this.ctx = ctx; this.valid = false; this.shapes = []; this.moved = []; this.dragging = false; this.selection = null; var myState = this; container_div.addEventListener( 'mouseup'    , mouseup,false); container_div.addEventListener( 'mousemove'  , mousemove,false); container_div.addEventListener( 'mousedown'  , mousedown,false); container_div.addEventListener( 'touchend'   , mouseup,false); container_div.addEventListener( 'selectstart', function(e) { e.preventDefault(); return false; }, false); container_div.addEventListener( 'touchstart' , mousedown,false); container_div.addEventListener( 'touchmove'  , mousemove,false); function mousedown(e){  var mouse = myState.getMouse(e);  var mx = mouse.x;  var my = mouse.y;  if( use_pan_and_zoom == 1 && my > ysize - 15){   check_zoom_or_pan(mx);  }  else  {   var shapes = myState.shapes;   var l = shapes.length;   var chk = -1;   for(var i=0;i<l;i++){    chk = shapes[i].contains(mx, my);    if ( chk != -1 ){     if( myState.moved[shapes[i].click_cnt] != 1){      myState.moved[shapes[i].click_cnt] = 1;      myState.x_start = shapes[i].x[chk];      myState.y_start = shapes[i].y[chk];     };     var org_line_width = shapes[i].line_width;     var org_font_family = shapes[i].font_family;     var org_stroke_opacity = shapes[i].stroke_opacity;     myState.chk = chk;     myState.selection = shapes[i];     myState.valid = false;     switch(shapes[i].onclick){      case 0: myState.dragging = false;break;      case 1: myState.selection.line_width = 3*org_line_width;myState.selection.font_family = "bold italic "+myState.selection.font_size+"px Courier";myState.dragging = false;myState.draw();reply[0] = myState.selection.click_cnt;myState.selection.line_width = org_line_width;myState.selection.font_family = org_font_family;break;      case 2: myState.dragging = true;break;      default:break;     };     return;    };   };  };  myState.selection = null;  myState.valid = true;  return; }; function mouseup(e){;  if(myState.selection != null ){   if(myState.selection.onclick == 2 ){    if( x_use_snap_to_grid == 1 || y_use_snap_to_grid == 1){     var mouse = myState.getMouse(e);     var dx=mouse.x;     var dy=mouse.y;     if( x_use_snap_to_grid == 1 && y_use_snap_to_grid == 1 ){       dx = snap_to_x(dx) - myState.selection.x[myState.chk];      dy = snap_to_y(dy) - myState.selection.y[myState.chk];     }else{      if( x_use_snap_to_grid == 1 ){        dx = snap_to_x(dx) - myState.selection.x[myState.chk];       dy = 0;      }else{       dx = 0;       dy = snap_to_y(dy) - myState.selection.y[myState.chk];      };     };     switch(myState.selection.direction){      case 0: myState.selection = move(myState.selection,dx,dy);break;      case 1: myState.selection = move(myState.selection,dx,0);break;      case 2: myState.selection = move(myState.selection,0,dy); break;     };    };    reply[myState.selection.click_cnt] = myState.selection.click_cnt+":"+px2x(myState.x_start)+":"+px2y(myState.y_start)+":"+(Math.round(dragdrop_precision*(px2x(myState.selection.x[myState.chk]))))/dragdrop_precision+":"+(Math.round(dragdrop_precision*(px2y(myState.selection.y[myState.chk]))))/dragdrop_precision;   };   myState.valid = false;   myState.draw();   myState.valid = true;  };  myState.dragging = false; }; function mousemove(e){  if(myState.dragging){   var mouse = myState.getMouse(e);   var dx=mouse.x - myState.selection.x[myState.chk];   var dy=mouse.y - myState.selection.y[myState.chk];   switch(myState.selection.direction){    case 0: myState.selection = move(myState.selection,dx,dy);break;    case 1: myState.selection = move(myState.selection,dx,0);break;    case 2: myState.selection = move(myState.selection,0,dy); break;    default:break;   };   myState.valid = false;  }; }; function check_zoom_or_pan(x){  var key = -1;  for(var p = 15 ; p < 106 ; p = p+15){    key++;    if(x > xsize - p){start_canvas(key);return;}  }  return; }; this.interval = 30; setInterval(function() { myState.draw(); }, myState.interval);};CanvasState.prototype.addShape = function(shape){ this.shapes.push(shape); this.valid = false;};CanvasState.prototype.clear = function(){ this.ctx.clearRect(0, 0, this.width, this.height);};CanvasState.prototype.draw = function(){ if(this.valid == false ){  var shapes = this.shapes;  this.clear();  var l = shapes.length;var shape;  for(var i = 0; i < l; i++){   shape = shapes[i];   shape.draw(this.ctx);  };  this.valid = true; }};
 CanvasState.prototype.Slide = function(slider_value,slider_count){ 
  this.ctx.clearRect(0,0,xsize,ysize); var what;var len = this.shapes.length;var shape;var lu; 
  for(var i = 0; i < len ; i++){  
   if( this.shapes[i] ){
    shape = this.shapes[i];   
    if( shape.slider != 0 ){
     if(shape.slider_cnt == slider_count ){     
      what = shape.slider;     
      lu = shape.x.length;
      reply[0]=slider_value[0];
      switch(what){      
       case 1: slide(shape,Math.cos(slider_value[0]),0);break;      
       case 2: slide(shape,0,Math.sin(slider_value[0]));break;      
       case 3: if(shape.type == 12 || shape.type == 17){shape.h[1] = 180*slider_value[0]/Math.PI;if(shape.h[1] > 360){shape.h[1] = shape.h[1] - 360;};}else{shape.use_rotate = 1;shape.angle = -1*slider_value[0];};break;      
       case 4: slide(shape,slider_value[0],slider_value[1]);break;      default:break;     
      };    
     };   
    };   
    this.valid = false;   
    shape.draw(this.ctx);  
   }; 
  };
 };
 CanvasState.prototype.Zoom = function(xmin,xmax,ymin,ymax){ (this.ctx).clearRect(0,0,this.width,this.height); var len = this.shapes.length;var shape; for(var i = 0; i < len ; i++){  shape = this.shapes[i];  for(var p = 0 ; p < shape.x.length;p++){   shape.x[p] = x2px(shape.xorg[p]);   shape.y[p] = y2px(shape.yorg[p]);  }  this.valid = false;  shape.draw(this.ctx); }; reply = new Array();};CanvasState.prototype.getMouse = function(e){var element = this.canvas, offsetX = 0,offsetY = 0;while( ( element = element.offsetParent) ){offsetX += element.offsetLeft;offsetY += element.offsetTop;}var mx = e.clientX - offsetX + (document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft);var my = e.clientY - offsetY + (document.documentElement.scrollTop ? document.documentElement.scrollTop :document.body.scrollTop); return {x: mx, y: my};};
 CanvasState.prototype.read_dragdrop = function(){ 
  if( wims_status == "done"){return null;};
  if(reply[0] == 'undefined' ){alert("hmmm?");return null;}
  return reply;
 };
 var obj = create_canvas(4,xsize,ysize);var container_div = document.getElementById("canvas_div0");var dragstuff = new CanvasState(obj,container_div);read_dragdrop0 = dragstuff.read_dragdrop;
 var xmin = -1.1;var xmax = 1.1;
 var ymin = -1.1;var ymax = 1.1;
 snap_x = 0.250000;snap_y = 0.250000;
 /* circle */
 dragstuff.addShape(new Shape(1,0,-1,13,[0.000],[0.000],[1.000],[1.000],1,"0,0,255",0.80,"0,0,255",0.80,0,0,4,4,0,0.0,"",12,"bold 14px Ariel ",0,[1,0,0,1,0,0],0,0));
 function show_slider_value(value,use_slider_display){ 
  var current_canvas = create_canvas(2,xsize,ysize); 
  var current_context = current_canvas.getContext("2d"); 
  current_context.clearRect(0,0,xsize,ysize); 
  current_context.font = "24px Ariel"; 
  var prec = Math.log(100)/(Math.log(10)); 
  var string; 
  if(value.length == 2){  string = " "+value[0].toFixed(prec)+" "+unit_x+":"+value[1].toFixed(prec)+" "+unit_y; }else{ if(use_slider_display == 2){   value[0] = value[0]*180/Math.PI;   string = " "+value[0].toFixed(prec)+"\u00B0";  }else{if(use_slider_display == 3){    string = " "+value[0].toFixed(prec)+" rad";   };  }; }; 
  var s = parseInt(1.2*24*(string).length); 
  current_context.strokeStyle = "rgba(#00000,0.80)"; 
  current_context.clearRect(0,0,s,1.2*24); 
  current_context.fillText(string,0,24);
 };
 <!-- begin add_slider no. 1 --> 
 function add_slider_1(){ if( wims_status == "done" ){return;}; 
  var tooltip_div = document.getElementById("tooltip_placeholder_div"); 
  var slider_type = 3; 
  var span = document.createElement("span"); span.setAttribute('style','font:bold 14px Ariel ;color:#00000'); 
  var title = document.createTextNode(slider_text); 
  var br = document.createElement("br"); span.appendChild(title); 
  span.appendChild(br); tooltip_div.appendChild(span); 
  var slider_fillcolor = "255,255,255"; 
  var slider_strokecolor = "0,0,255"; 
  var slider_linewidth = "1"; 
  var slider_canvas = document.createElement("canvas");
  slider_canvas.id = "slider_canvas1"; 
  tooltip_div.appendChild(slider_canvas); br = document.createElement("br"); 
  tooltip_div.appendChild(br);
  var slider_center = 0.5*slider_height; var slider_radius = 4*slider_linewidth; 
  var slider_opacity = 0.800000; slider_canvas.width = slider_width; 
  slider_canvas.height = slider_height; 
  var canvas_rect = (slider_canvas).getBoundingClientRect(); 
  var slider_ctx = slider_canvas.getContext("2d"); 
  slider_ctx.font = "bold 14px Ariel "; 
  slider_ctx.strokeStyle = "rgba("+slider_strokecolor+","+slider_opacity+")"; 
  slider_ctx.fillStyle = "rgba("+slider_fillcolor+","+slider_opacity+")"; 
  slider_ctx.lineWidth = slider_linewidth; slider_ctx.beginPath(); 
  slider_ctx.arc(10,slider_center,slider_radius,0,2*Math.PI,false); 
  slider_ctx.moveTo(10,slider_center); slider_ctx.lineTo(slider_width-10,slider_center); 
  slider_ctx.rect(0,0,slider_width,slider_height); slider_ctx.closePath(); slider_ctx.fill(); 
  slider_ctx.stroke(); 
  slider_canvas.addEventListener("click",slider_start,false);
  var flipflop=0;
  function slider_start(evt){
   if(flipflop == 0 ){
    flipflop=1;
    slider_canvas.addEventListener("mousemove",slider_1,false);
   }
   else
   {
    slider_canvas.removeEventListener("mousemove",slider_1,false);
    flipflop = 0;
   }
  }
  function slider_1(evt){
   slider_ctx.clearRect(0,0,slider_width,slider_height); 
   var x = evt.clientX - canvas_rect.left; 
   var value = x*(slider_max - slider_min)/slider_width + slider_min; 
   slider_ctx.beginPath(); slider_ctx.arc(x,slider_center,slider_radius,0,2*Math.PI,false);
   slider_ctx.moveTo(10,slider_center); slider_ctx.lineTo(slider_width-10,slider_center); 
   slider_ctx.rect(0,0,slider_width,slider_height); slider_ctx.closePath(); slider_ctx.fill(); 
   slider_ctx.stroke(); dragstuff.Slide( [value] , 1 );
   show_slider_value([value],slider_value_type);
   return; 
  };
 };
 add_slider_1(); 
 dragstuff.addShape(new Shape(2,0,-1,4,[0.000,1.000],[0.000,0.000],[30,30],[30,30],2,"255,165,0",0.80,"255,165,0",0.80,0,0,4,4,0,0.0,"",24,"bold 14px Ariel ",0,[1,0,0,1,0,0],3,1));
 dragstuff.addShape(new Shape(3,0,-1,17,[0.000,0.000],[0.000,0.000],[0.300,0.300],[0.000,0.000],2,"0,128,0",0.80,"0,255,0",0.30,1,0,4,4,0,0.0,"",24,"bold 14px Ariel ",0,[1,0,0,1,0,0],3,1));
 dragstuff.addShape(new Shape(3,0,-1,2,[1.000],[0.000],[3],[3],3,"255,165,0",0.80,"255,165,0",0.80,1,0,0,0,0,0.0,"",24,"bold 14px Ariel ",0,[1,0,0,1,0,0],3,1));
 dragstuff.addShape(new Shape(4,0,-1,14,[0.900],[0.100],[30],[30],3,"0,0,0",0.80,"0,0,0",0.80,0,0,0,0,0,0.000000,"P",24,"italic 24px Courier",0,[1,0,0,1,0,0],3,1));
 dragstuff.addShape(new Shape(4,0,-1,14,[-0.2],[-0.2],[30],[30],3,"0,0,0",0.80,"0,0,0",0.80,0,0,0,0,0,0.000000,"O",24,"italic 24px Courier",0,[1,0,0,1,0,0],3,0));
 dragstuff.addShape(new Shape(0,0,-1,4,[-1.000,1.000],[0.000,0.000],[30,30],[30,30],1,"255,0,0",0.80,"255,0,0",0.80,0,0,4,4,0,0.0,"",12,"12px Ariel",0,[1,0,0,1,0,0],0,0));                                   
 dragstuff.addShape(new Shape(0,0,-1,4,[0.000,0.000],[-1.000,1.000],[30,30],[30,30],1,"255,0,0",0.80,"255,0,0",0.80,0,0,4,4,0,0.0,"",12,"12px Ariel",0,[1,0,0,1,0,0],0,0));
 dragstuff.addShape(new Shape(0,0,-1,14,[1.000],[0.000],[30],[30],1,"0,0,0",0.80,"0,0,0",0.80,0,0,0,0,0,0.000000,"1",12,"italic 12px Ariel",0,[1,0,0,1,0,0],0,0));
 dragstuff.addShape(new Shape(0,0,-1,14,[-1.000],[0.000],[30],[30],1,"0,0,0",0.80,"0,0,0",0.80,0,0,0,0,0,0.000000,"-1",12,"italic 12px Ariel",0,[1,0,0,1,0,0],0,0));
 dragstuff.addShape(new Shape(0,0,-1,14,[0.000],[1.000],[30],[30],1,"0,0,0",0.80,"0,0,0",0.80,0,0,0,0,0,0.000000,"1",12,"italic 12px Ariel",0,[1,0,0,1,0,0],0,0));
 dragstuff.addShape(new Shape(0,0,-1,14,[0.000],[-1.000],[30],[30],1,"0,0,0",0.80,"0,0,0",0.80,0,0,0,0,0,0.000000,"-1",12,"italic 12px Ariel",0,[1,0,0,1,0,0],0,0));                                                                      
                                                     
 dragstuff.addShape(new Shape(0,0,-1,4,[-1.000,1.000],[0.000,0.000],[30,30],[30,30],1,"0,0,255",0.80,"0,0,255",0.80,0,1,6,6,0,0.0,"",12,"12px Ariel",0,[1,0,0,1,0,0],2,1));                                                            
 dragstuff.addShape(new Shape(0,0,-1,4,[0.000,0.000],[-1.000,1.000],[30],[30],1,"0,0,255",0.80,"0,255,0",0.80,0,1,6,6,0,0.0,"",12,"12px Ariel",0,[1,0,0,1,0,0],1,1));

};
<!-- end wims_canvas_function -->
wims_canvas_function();
