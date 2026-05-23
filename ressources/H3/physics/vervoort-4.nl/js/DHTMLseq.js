!! var1 is table row with static images <td>...</td><td>...</td> 
!! var2 is the alt_text == value 
!! var3  is dhtml of table from var1

!set DHTML=$empty
!set n=$counter
!if $var1 != $empty
    !set max=$[2*$options-1]
!else
    !set max=$options
!endif
!set k1=lightgreen
!set k2=lightblue
!set k3=orange

<table class="grid_table" >
    <tr>
!for p=1 to $max
    <th>
	<div id="target$[$p-1]"  style="vertical-align:middle;background-color:$k2;position:relative;width:$[$width+5]px;height:$[$height+10]px"></div>
    </th>
    !set DHTML=!append item "target$[$p-1]"+NO_DRAG to $DHTML
!next p
    </tr>
    <tr>
!for p=1 to $max
 !if $p <= $options
    !set ans=!item $p of $var2
    <th>
	<div id="image$[$p-1]" title="$ans" style="vertical-align:middle;background-color:$k1;position:relative;height:$[$height+10]px;width:$[$width+5]px">
	    !set ins_attr= title="$ans"
	    !insmath $(ex$p)
	</div>
    </th>
 !else
    !if $var1=1
	<th>
	    <div id="image$[$p-1]" title=">" style="vertical-align:middle;background-color:$k1;position:relative;height:$[$height+10]px;width:$[$width+5]px">
		<br /><span style="font-size:130%">&gt;</span>
	    </div>
	</th>
    !else
	<th>
	    <div id="image$[$p-1]" title="<" style="vertical-align:middle;background-color:$k1;position:relative;height:$[$height+10]px;width:$[$width+5]px">
		<br /><span style="font-size:130%">&lt;</span>
	    </div>
	</td>
    !endif
 !endif
 !set DHTML=!append item "image$[$p-1]" to $DHTML
!next p
    </tr>
    <tr>
!for i=1 to $max
    !increase p
    !if $i<= $options
	!if $var1=2
	    <th>
		<div id="image$[$p-1]" title=">" style="vertical-align:middle;background-color:$k1;position:relative;height:$[$height+10]px;width:$[$width+5]px">
		    <br /><span style="font-size:130%">&gt;</span>
		</div>
	    </td>
	!else
	    <th>
		<div id="image$[$p-1]" title="<" style="vertical-align:middle;background-color:$k1;position:relative;height:$[$height+10]px;width:$[$width+5]px">
		    <br /><span style="font-size:130%">&lt;</span>
		</div>
	    </th>
	!endif
    !else
	<th>
	    <div id="image$[$p-1]" title="=" style="vertical-align:middle;background-color:$k1;position:relative;height:$[$height+10]px;width:$[$width+5]px">
		<br /><span style="font-size:130%">=</span>
	    </div>
	</th>
    !endif
    !set DHTML=!append item "image$[$p-1]" to $DHTML
!next i
    </tr>
</table>

!set dhtml=<script type="text/javascript">SET_DHTML( CURSOR_MOVE , $DHTML);</script>

!! dhtml is onderdeel van myjavascript.phtml...
!set rem1=Je antwoord moet natuurlijk iets zijn als:\n 1/2 > 1/4 \n of iets als \n 1/4 < 1/2 < 3/4 < 1
<script type="text/javascript">
//<![CDATA[
    var occupied = new Array();
    var delta=$[0.5*$width];

    for(var p=0;p<$max;p++){
	occupied[p] = null;
    }

    function sendanswer(){
	var show=" ";var X,Y,found;
	var reply = new Array();var cnt = 0;
	for(var p = 0;p < $max ;p++){
	    X=dd.elements['target'+p].x;
	    Y=dd.elements['target'+p].y;
	    found = 0;
	    for(var i = 0 ; i < dd.elements.length ; i++){
		if( found == 0 && dd.elements['image'+i] ){
		    if( dd.elements['image'+i].x == X && dd.elements['image'+i].y == Y ){
			reply[p] = document.getElementById('image'+i).getAttribute('title');
			if(p%2 == 0){
			    if( reply[p].indexOf('>') == 0 || reply[p].indexOf('<') == 0 || reply[p].indexOf('=') == 0){
				setAlarm("$rem1");return;
			    }
			}
		        found = 1;
		        cnt++;
			show=show+"&nbsp;"+reply[p];
		    } 
		}
	    }
	}
	if(cnt != $max ){setAlarm(r19);return;}
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }

    function my_PickFunc(){
    	document.getElementById(dd.obj.id).style.backgroundColor = '$k3'; 
    }
    
    function my_DropFunc(){
	var x=dd.obj.x;var y=dd.obj.y;
	var X,Y,found=0;
	for(var p = 0;p < $max ;p++){
	    if(found ==0 ){
		X=dd.elements['target'+p].x
	        Y=dd.elements['target'+p].y
		if(x > X-delta && x < X+delta && y > Y-delta && y < Y+delta){ 
		    if(occupied[p] != null){ 
			if(dd.elements[occupied[p]].x == X &&  dd.elements[occupied[p]].y == Y){
		    	    dd.elements[occupied[p]].moveTo(dd.obj.defx,dd.obj.defy); 
			    document.getElementById(occupied[p]).style.backgroundColor = '$k1';
			}
		    }
		    occupied[p] = dd.obj.id; 
		    dd.obj.moveTo(X,Y);
		    found=1;
		    document.getElementById(dd.obj.id).style.backgroundColor = '$k2'; 
		}
	    }
	}
	if(found == 0 ){ 
	    dd.obj.moveTo(dd.obj.defx,dd.obj.defy); 
	    document.getElementById(dd.obj.id).style.backgroundColor = '$k1';
	}
	dd.obj='null';
   }
//<![CDATA[
</script>



