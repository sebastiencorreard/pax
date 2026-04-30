<script type="text/javascript" src="$jsdir/wz_dragdrop.js"></script>
!set DHTML=$empty
!set n=$counter
!if $dragcolors=$empty
    !set unused_color=#ff0000
    !set pick_color=#639bff
    !set drop_color=#00fc96
    !set blue_layer=#82bbff
!else
    !set unused_color=!item 1 of $dragcolors
    !set pick_color=!item 2 of $dragcolors
    !set drop_color=!item 3 of $dragcolors
    !set blue_layer=!item 4 of $dragcolors
!endif
!set max_width=0
!for p in $var1
    !set w=!charcnt $p
    !set w=$[12*$w]
    !if $w>$max_width
	!set max_width=$w
    !endif
!next p
!for p in $var3
    !set w=!charcnt $p
    !set w=$[12*$w]
    !if $w>$max_width
	!set max_width=$w
    !endif
!next p
!set max_width=!nospace $max_width px
!set ysize=!nospace $[$ysize+2] px
!!!set max_items=12
!set items=!itemcnt $var3

<table>
    <tr>
    <th>
	<table class="zebra_table_h2">
	    <caption>sleep spul</caption>
	!set c=0
	!set d=0
	!for p in $var1
	    !set getal=!item $[$c+1] of $var3
	    <tr>
	    <td>
		<div id="div$c" style="display:inline;position:relative;width:$max_width;height:$ysize">
		    $p
		!if $getal=?
		    &euro; <input id="myinput$d" size="10"/> 
		    !increase d
		!else
		    <b>&nbsp; $getal &nbsp;</b>
		!endif
		</div>
	    </td>
	    </tr>
	    !set DHTML=!append item "div$c" to $DHTML
	!increase c
	!next p
	</table>
    </th>
    <th>
	<table class="balans_1">
	    <caption>balans</caption>
	    <tr><th>Activa</th><th>Passiva</th></tr>
	!for i=0 to $[2*$var4-1] step 2
	    <tr>
	    <td>
		<div id="A$i" style="text-align:center;position:relative;width:$max_width;height:$ysize"></div>
	    </td>
	    <td>
		<div id="A$[$i+1]" style="text-align:center;position:relative;width:$max_width;height:$ysize"></div>
	    </td>
	    </tr>
	    !set DHTML=!append item NO_DRAG + "A$i","A$[$i+1]" to $DHTML
	!next i
	    <tr>
	    <td>
		Totaal : &euro; <input size="20" id="myinput$d" type="text" value="" />
		!increase d
	    </td>
	    <td>
		Totaal : &euro; <input size="20" id="myinput$d" type="text" value=""/>
	    </td>
	    </tr>
	</table>
    </th>
    </tr>
</table>
<div class="embedded_central">
!if $wims_user = supervisor
    <input type="button" id="schaersvoorde_extra_button" value="antwoorden : $wims_firstname $wims_lastname" onclick="javascript:showAnswer()"/>
!endif
    <input type="button" id="schaersvoorde_ok_button" onclick="javascript:sendanswer();" value="$send"/>
    <input type="button" id="schaersvoorde_nok_button" onclick="javascript:dontknow();"  value="$dontknow"/>
</div>	

<script type="text/javascript">
//<![CDATA[
<!-- no validator  -->
    SET_DHTML( CURSOR_MOVE , $DHTML);	
    var pick_id;
    var reply = new Array();
    var org_x = new Array();
    var org_y = new Array();
    var orgx,orgy;
    for(var p = 0 ; p < $[2*$var4] ; p++){
	reply[p] = -1;
    }
    for(var p = 0 ; p < $items ; p++){
	org_x[p] = dd.elements["div"+p].x;
	org_y[p] = dd.elements["div"+p].y;
    }
    
    function my_PickFunc(){
	orgx = dd.obj.x;
	orgy = dd.obj.y;
	pick_id=dd.obj.id;
    }
    !! i is volgorde in balans
    !! id is volgorde in sleep elementen lijst
    !! identificeren : reply[i] = id
    
    
    function my_DropFunc(){
	var marge=25;
	var x=dd.obj.x;
        var y=dd.obj.y;
	var found=0;
	if( dd.obj.id == pick_id ){
	    var id = pick_id.replace("div","");
	    for(var i=0 ; i < $[2*$var4] ;i++){
		if(reply[i] == id){reply[i] = -1;}// we hebben dit plaatje al in de array
		if(found == 0){
		    if( y > dd.elements["A"+i].y - marge && y < dd.elements["A"+i].y + marge && x > dd.elements["A"+i].x - 4*marge && x < dd.elements["A"+i].x + 4*marge){
			found=1;
			dd.obj.moveTo(dd.elements["A"+i].x,dd.elements["A"+i].y);
			if( reply[i] != -1){ // op deze plek staat al wat
			    dd.elements["div"+reply[i]].moveTo(org_x[ reply[i] ],org_y[ reply[i] ]);
			}
			reply[i] = id;
		    }
		}
	    }
	}
	if(found == 0){dd.obj.moveTo(orgx,orgy);}
	dd.obj='null';
	return;
    }
    !if $wims_user = supervisor
	function showAnswer(){
	!set left=!line 1 of $(answer$n)
	!set right=!line 2 of $(answer$n)
	!set inputs=!line 3 of $(answer$n)
	!set c=0
	!for p in $left
	    reply[$c] = "$p";
	    var x = dd.elements["A$c"].x;
	    var y = dd.elements["A$c"].y;
	    !set c=$[$c+2]
	    dd.elements["div$p"].moveTo(x,y);
	!next p
	
	!set c=1
	!for p in $right
	    reply[$c] = "$p";
	    var x = dd.elements["A$c"].x;
	    var y = dd.elements["A$c"].y;
	    !set c=$[$c+2]
	    dd.elements["div$p"].moveTo(x,y);
	!next p
	!set c=0
	!for p in $inputs
	    document.getElementById("myinput$c").value = "$p";
	    !increase c 
	!next p
	}
    !endif
    
    function sendanswer(){
	var found=0
	var left = new Array();
	var right = new Array();
	var inputs = new Array();
	var idx1 = 0;
	var idx2 = 0;
	var p;
	for( p = 0; p<$[2*$var4] ; p++){
	    if(p%2 == 0){left[idx1] = reply[p];idx1++;} else {right[idx2] = reply[p];idx2++;}
	    if( reply[p] != -1 ){found++;}
	}
	if(found < $items){
	    var diff=$items - found;
	    setAlarm("Je antwoord is nog niet volledig ingevuld...<br />Alle versleepbare div&rsquo;s moeten in de balans worden verwerkt<br />D&rsquo;r zijn nog "+diff+" sleep div&rsquo;s over...");
	    return;
	}
	
	var tmp;
	p = 0;
	while ( document.getElementById('myinput'+p)){
	    tmp = document.getElementById("myinput"+p).value;
	    if( is_number(tmp) == 1){ inputs[p] = tmp;}else{return;}
	    p++;
	} 
	var rep = left+"\n"+right + "\n" + inputs;
	myConfirm(inputs,rep,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
//]]>
</script>
