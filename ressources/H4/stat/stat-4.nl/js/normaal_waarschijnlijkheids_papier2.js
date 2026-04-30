!! aantal invulvelden
!set nm=2
!set rem2=!record 59 of lang/remarks.$taal
!!#@De standaardafwijking $m_sigma,Het gemiddelde
!set rem1=!record 55 of lang/remarks.$taal
<script language="JavaScript" type="text/javascript">
    !set n=$counter
    function sendanswer(){
	var reply;var show="";var tmp;
	for(var p = 0 ; p < $nm ; p++){
	    var tmp = document.getElementById('myinput'+p).value;
	    if(tmp.length == 0){setAlarm(r1);return;}
	    if(is_number(tmp) == 0){return;}
	    if(p == 0){ reply = tmp; } else {reply = reply + "\n" + tmp;}
	    show=show+tmp+"<br />";
	}
	reply = reply + "\n";
	// at last read the graphdata
	var itemcnt;
	!if $var8=0
	    tmp = document.getElementById('FlyApplet').ReadDrawing();
	!else
	    tmp = (read_canvas()).toString();
	    tmp = tmp.replace(/\:/g,',');
	!endif
	itemcnt=tmp.split(',');
	!! 4 lijnen == 8 punten == 16 x,y waarden
	if(itemcnt.length < 16 ){setAlarm("$rem1");return;}
	reply = reply + tmp;
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>

<table id="exercise" class="exercise" >
    <tr>
    <th style="text-align:center;vertical-align:top">
	$prob_paper
    </th>
    </tr>
    <tr>
    <th>
	<table>
		<tr>
	    !for p=1 to $nm
		<td>
		    !item $p of $rem2
		</td>
		<td>
    		    <input name="myinput$[$p-1]" id="myinput$[$p-1]" style="text-align:center;font-size:16px;background-color:lightblue;" size="6">
		</td>
	    !next p
		</tr>
	</table>
    </th>
    </tr>
</table>
