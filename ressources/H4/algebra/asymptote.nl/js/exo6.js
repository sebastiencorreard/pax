!! plus-sign : img1
!! minus-sign: img2
!! div1 : f(x) receiving field
!! div0 : x-values receiving field
!! div2.....div999 : the inputfield/asymptote-symbols  <input size=5 name=reply$n value=$(reply$n)/> with value: reply1
!! wimsvariabele options= number of div elements in DHTML 
!! answer scheme: x_1,x_2,...x_n,+,x,-,x,+
!! multiple + and - will be  stripped:  + + + + x - - - -  => +x- 
!set rem1=!record 37 of lang/remarks.$taal
!set rem2=!record 38 of lang/remarks.$taal
!set rem3=!record 39 of lang/remarks.$taal
!set rem4=!record 40 of lang/remarks.$taal

<script type="text/javascript">
/* "use strict"; */
function my_DropFunc(){
 var maxplus = dd.elements.img1.copies.length;var maxmin = dd.elements.img2.copies.length; var divnum = $options;var delta = parseInt(0.2*(dd.elements['div0'].w));var Y0 = dd.elements['div0'].y; var Y1 = dd.elements['div1'].y; var Y11 = Y1-delta;var Y12 = Y1+delta;var y = dd.obj.y;var x = dd.obj.x; var moved = 0;var naam = dd.obj.name;naam = naam.substring(0,3);if(naam == "img"){ for( var s = 1 ; s<maxplus+1 ; s++){if( moved == 0 ){if( y<Y12 && y>Y11 ){dd.obj.moveTo(x,Y0);moved = 1;}else{ dd.obj.moveTo(dd.obj.defx,dd.obj.defy);};};};}else{ for( var s = 2 ; s<divnum+1 ; s++){if( moved == 0){if( y<Y12 && y>Y11 ){dd.obj.moveTo(x,Y1);moved = 1;}else{ dd.obj.moveTo(dd.obj.defx,dd.obj.defy);};};};};
};

function mysort(a, b){ return (a-b); }
function sendanswer(){
 var rem1="$rem1";var rem2="$rem2";var rem3="$rem3";var rem4="$rem4";var Xmin = dd.elements['div0'].x;var w = dd.elements['div0'].w;var Xmax = (Xmin + w);var maxplus = dd.elements.img1.copies.length;var maxmin = dd.elements.img2.copies.length;var divnum = $options;var taal = "$taal";var count = 0;var Ydiv;var Yimg;var Y0 = dd.elements['div1'].y;var Y1 = dd.elements['div0'].y;var tot = new Array();var mintekens = new Array();var plustekens = new Array(); var roots = new Array();var total=new Array(); var things = new Array('sin','cos','tan','sqrt','log','abs');var numthings = things.length;if( Y0 > Y1 ){ Ydiv = Y1;Yimg = Y0}else{ Ydiv = Y0;Yimg = Y1;}; var inp_id = 0;var img_id = 0;while( document.getElementById("myinput"+inp_id) ){var rep = document.getElementById("myinput"+inp_id).value;img_id = inp_id + 2;var x = dd.elements['div'+img_id].x;var y = dd.elements['div'+img_id].y;if( y == Ydiv ){var c = rep.indexOf(',');if( c != -1 ){ setAlarm(rem1); return ;}; rep = rep.toLowerCase();for(var t = 0;t < numthings;t++){var w = things[t];var W = w.toUpperCase(); rep = rep.replace(w,W);};rep = rep.replace(/[a-z\,\=\@\:\;\#\~\!\ ]/g,''); rep = rep.toLowerCase();if( rep.length == 0){ setAlarm(rem2);return; }else{tot[count] = rep;roots[count] = x;total[count] = x;count++;}; }; inp_id++;}; if( count == 0 ){ setAlarm(rem3); };var tots = new Array();var totals = new Array();roots.sort(function(a, b){return a-b});for(var p = 0 ; p < count ; p++){ for(var q = 0 ; q < count ; q++){if( roots[p] == total[q] && total[q] != null){totals[p] = total[q];tots[p] = tot[q];total[q] = null;tot[q] = null;};};};tot = tots;total = totals;img_id = 0;for(var p = 0;p < maxplus;p++){var y = dd.elements['img1'].copies[p].y;if( y == Yimg){var x = dd.elements['img1'].copies[p].x; plustekens[img_id] = x;total[count+img_id] = x;img_id++;};};var tekens = 0;for(p = 0; p < maxplus;p++){ var y = dd.elements['img2'].copies[p].y; if( y == Yimg){var x = dd.elements['img2'].copies[p].x;mintekens[tekens] = x; total[count+img_id+tekens] = x;tekens++; };};if( img_id + tekens == 0 ){ setAlarm(rem4);return; };total = total.sort(mysort);var y = total.length;for(var s = 0 ; s < count ;s++){var x = roots[s]; for ( var i = 0; i < y ;i++){var c = total[i];if ( c == x ){total[i]='x';};};};for( var s = 0 ; s < img_id ;s++){ var x = plustekens[s]; for( var i = 0; i < y ;i++){var c = total[i];if ( c == x ){total[i]='+';};};};for(var s = 0 ; s < tekens ;s++){ var x = mintekens[s]; for(var i = 0; i < y ;i++){var c = total[i];if ( c == x ){total[i]='-';};};}; myConfirm("$send ?",tot+","+total,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
};
</script>
