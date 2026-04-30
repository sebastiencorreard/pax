!set nm=2
!set rem1=!record 55 of lang/remarks.$taal
!set rem2=!record 59 of lang/remarks.$taal
<script language="JavaScript" type="text/javascript">
    !set n=$counter
    
    function sendanswer(){
	var reply ="";
	var show="\n";
	var itemcnt;
	!if $var8=0
	 var appletreply = document.getElementById('FlyApplet').ReadDrawing();
	!else
	 var appletreply = (read_canvas()).toString();
	 appletreply = appletreply.replace(/\:/g,',');
	!endif
	itemcnt = appletreply.split(',');
	if(document.getElementById('myinput1')){
	    !! 4 lijnen == 8 punten == 16 x,y waarden
	    if(itemcnt.length < 16 && $counter == 2 ){setAlarm("$rem1");return;}
	    for(var p = 0 ; p < $nm ; p++){
		var tmp = document.getElementById('myinput'+p).value;
	        if(tmp.length == 0){setAlarm(r1);return;}
	        if(is_number(tmp) == 0){return;}
		if(p == 0){ reply = tmp; } else {reply = reply + "\n" + tmp;}
		show=show+tmp+"<br />";
	    }
	    reply = reply + "\n";
	}
	reply = reply + appletreply;
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>
<table id="exercise" class="exercise" >
    <tr>
    <th style="text-align:center;vertical-align:top">
	$prob_paper
    </th>
    !if $counter=2
    </tr>
    <tr>
	<th style="text-align:center;vertical-align:top">
	    <table summary="input fields">
		<tr>
		!for p=1 to $nm
		    <td>
			!item $p of $rem2
		    </td>
		    <td>
			=
		    </td>
		    <td>
    			<input name="myinput$[$p-1]" id="myinput$[$p-1]" style="text-align:center;font-size:16px;background-color:lightblue;" size="6">
		    </td>
		!next p
		</tr>
	    </table>
	</th>
    !endif
    </tr>
</table>
