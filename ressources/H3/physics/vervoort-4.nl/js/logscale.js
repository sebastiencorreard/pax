!! hotspot questions  var3 = xmin,xmax,ymin,ymax in coordinatesystem of the graph.
!! without ISMAP
!set n=$counter
!for p=0 to $[$options-1]
    <div id="dot_ie$p" style="position:absolute;z-index:100;display:none;background-color:red;top:0px;left:0px;width:4px;min-height:4px;max-height:4px;height:auto!important;height:4px;"><table summary="" bgcolor="red" width="4" height="4"><tr><th></th></tr></table></div>
    <div id="dot_w3c$p" style="position:absolute;z-index:100;display:none;background-color:red;top:0px;left:0px;width:4px;height:4px;"></div>
!next p
!set xmin=!item 1 of $var3
!set xmax=!item 2 of $var3
!set ymin=!item 3 of $var3
!set ymax=!item 4 of $var3
!set n=$counter
!set ins_attr= id="myimage"
!set insplot_set=$var5
<table>
<tr>
<td>
    !insplot $var4
</td>
<td>
<ul>
!if $wims_user=supervisor
!set c=1
!for p=1 to $options
    !set x=!item $c of $(answer$n)
    !increase c
    !set y=!item $c of $(answer$n)
    !increase c
    <li>Co&ouml;rdinaten punt $p) = <input type="text" value="($x:$y)" id="myinput$[$p-1]" size="6" class="schaersvoorde_input" /></li>    
!next p
!else
!for p=1 to $options
    <li>Co&ouml;rdinaten punt $p) : <input type="text" value="" id="myinput$[$p-1]" size="6" class="schaersvoorde_input" /></li>    
!next p
!endif
</ul>

</td>
</table>
<script type="text/javascript">
//<![CDATA[
<!-- no validator -->
    document.getElementById("wait_gif").style.display = "inline";
    function dontknow(){
	myConfirm('$dontknow','?','$wims_ref_name','$session','$module','$counter','$nok_send_color');
    }

    function sendanswer(){
	var p=0;var rep;
	var reply = new Array();
	while(document.getElementById('myinput'+p)){
	    rep=document.getElementById('myinput'+p).value;
	    if(is_number(rep) != "error"){
		reply[p] = rep;
	    }
	    p++;
	}
	myConfirm(reply,reply,'$wims_ref_name','$session','$module','$counter','$nok_send_color');

    }
    
    !! wims variables
    var xpoints=$var7;
    var ypoints=$var8;
    var xsize=$xsize;
    var ysize=$ysize;
    var xmin=$xmin,xmax=$xmax,ymin=$ymin,ymax=$ymax;
    var IE;
    if (!document.all){
	IE=false
    }
    else
    { 
	IE=true;
    }

    function findPosX(i){
	var obj = document.getElementById(i);
	var curleft = 0;
	if(obj.offsetParent){
    	    while(1){
        	curleft += obj.offsetLeft;
        	if(!obj.offsetParent){break;}
		obj = obj.offsetParent;
    	    }
	}
	else
	{
	    if(obj.x){
    		curleft += obj.x;
	    }
	}
	return curleft;
    }

    function findPosY(i){
	var obj = document.getElementById(i);
	var curtop = 0;
	if(obj.offsetParent){
    	    while(1){
        	curtop += obj.offsetTop;
        	if(!obj.offsetParent){break;}
		obj = obj.offsetParent;
    	    }
	}
	else
	{
	    if(obj.y){
    		curtop += obj.y;
	    }
	}
	return curtop;
    }
    
    function y2px(y){ // y-coords to pixel
	Y =  ymax*ysize/(ymax-ymin) - y*ysize/(ymax - ymin);
        return Y;
    }
    function x2px(x){ // x-coords to pixel
	var X = x*xsize/(xmax - xmin) -  xsize*xmin/(xmax - xmin);
        return X;
    }
    // wachten tot alarmdiv weg is ... 
    setTimeout('draw()',4000);
    
    function draw(){
        var dx = findPosX('myimage') - 4;
	var dy = findPosY('myimage') - 4;
        for(var p = 0 ; p < $options; p++){
	    var x0 = parseInt( x2px(xpoints[p]) + dx );
	    var y0 = parseInt( y2px(ypoints[p]) + dy );
	    if(IE){
		document.getElementById('dot_ie'+p).style.top = y0 + document.body.scrollTop+'px';
	        document.getElementById('dot_ie'+p).style.left = x0 + document.body.scrollLeft+'px';
	        document.getElementById('dot_ie'+p).style.display = "inline";
	    }else{
		document.getElementById('dot_w3c'+p).style.top = y0 + 'px';
	        document.getElementById('dot_w3c'+p).style.left = x0 + 'px';
		document.getElementById('dot_w3c'+p).style.display = "inline";
    	    }
	}
    	document.getElementById("wait_gif").style.display = "none";
    }

//]]>
</script>
!exit
