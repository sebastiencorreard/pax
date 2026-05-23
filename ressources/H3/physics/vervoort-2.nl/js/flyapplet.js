!set rem1=Je moet een tweetal lijnstukken tekenen in de grafiek...
!set rem2=Je hoeft maar twee lijnstukken in de grafiek te tekenen<br />Met de rechter muisknop kun je punten weer verwijderen...
<script type="text/javascript">
//<![CDATA[
<!-- no validator -->

    !set n=$counter
    function sendanswer(){
	var reply ="";
	var show="";
	var appletreply = document.getElementById('FlyApplet').ReadDrawing();
	var test = appletreply.split(",");
	!! 2 lijnen == 4 punten == 8 x,y waarden
	if(test.length < 8 ){setAlarm("$rem1");return;}
	if(test.length > 8 ){setAlarm("$rem2");return;}
	!! invoervelden
	if(document.getElementById('myinput0')){
	    for(var p = 0 ; p < $var9 ; p++){
		var tmp = document.getElementById('myinput'+p).value;
	        if(tmp.length == 0){setAlarm(r1 + ":"+(p+1));return;}
	        if(is_number(tmp) == 0){return;}
		if(p == 0){ reply = tmp; } else {reply = reply + "\n" + tmp;}
		show=show+tmp+"<br />";
	    }
	    reply = reply + "\n";
	}
	reply = reply + appletreply;
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');

    }
//]]>
</script>

$(object$n)
<table class="zebra_table_h2">
    !for p=1 to $var9
	<tr>
	<td>
	    $(description[$p])
	</td>
	<td>
	    =
	</td>
	<td>
    	    <input type="text" id="myinput$[$p-1]" class="schaersvoorde_input"size="$cols" />
	</td>
	<td>
	    $(ex$p)
	</td>
	</tr>
    !next p
</table>
!exit