<div id="coords_display" style="opacity:0.6;filter:alpha(opacity=60);position:absolute;z-index:100;display:block;background-color:lightgreen;top:0px;left:0px;font-size:24pt;color:red;"></div>

<script type="text/javascript">
    var sizex=$xsize,sizey=$ysize,xmin=$(var9[1]),xmax=$(var9[2]),ymin=$(var9[3]),ymax=$(var9[4]),rounding=10,relx=0,rely=0,IE=false;
    var image = document.getElementById('myimage');
    if( !image.addEventListener ){
	image.attachEvent("onmousemove", test);
    }
    else
    {
	image.addEventListener("mousemove", test, false);
    }
    document.getElementById("coords_display").style.top = findPosY()+"px";
    document.getElementById("coords_display").style.left = findPosX()+"px";
    
    function test(e){
	if (!document.all){ // mozillla
	    recalculate(e.pageX,e.pageY);
	    e.stopPropagation();
	}
	else
	{
	    IE=true;
	    recalculate(event.x,event.y);
	}
    }
    
    function recalculate(x,y){
	var xi = findPosX();
	var yi = findPosY();
	if(IE){xi=xi-document.body.scrollLeft ;yi=yi-document.body.scrollTop ;}
	if(x > xi && x < xi+sizex && y > yi && y < yi+sizey){
	    xi=x - xi;yi=y - yi;
	    relx=px2x(xi);rely=px2y(yi);
	    relx=(Math.round(rounding*relx))/rounding;
	    rely=(Math.round(rounding*rely))/rounding;
	    document.getElementById('coords_display').innerHTML='('+relx+':'+rely+')';
	}
    }
    
    function findPosX(){
	obj = document.getElementById('myimage');
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

    function findPosY(){
	obj = document.getElementById('myimage');
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
    		curleft += obj.y;
	    }
	}
	return curtop;
    }
    function px2x(px){ //pixel to x-coords
        var X = eval(px*(xmax - xmin)/sizex + xmin);
        return X;
    }
    function px2y(py){ // pixel to y-coords
        Y = eval(ymax -  py*(ymax - ymin)/sizey);
        return Y;
    }
    
    function sendanswer(){
	//expecting a formula
	var reply;
	var tmp = document.getElementById('myinput0').value;
	if( tmp.length == 0 ){setAlarm(r0+" 1");return;}
	if( tmp.indexOf(',') != -1 ){setAlarm(r4);return;}
	if(check_o(tmp) == 0 ){return;}
	if(check_x(tmp) == 0 ){return;}
	if(check_f(tmp) == 0 ){return;}
	if( tmp.indexOf('=') != -1 ){
	    tmp = tmp.split('=');
	    reply = tmp[tmp.length - 1];
	}
	else
	{
	    reply = tmp
	}
	reply = "g(x)="+reply;
	myConfirm(reply,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>
