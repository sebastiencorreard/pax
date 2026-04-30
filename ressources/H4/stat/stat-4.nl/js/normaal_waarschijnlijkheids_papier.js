!set nm=!itemcnt $var3
!set rem1=!record 52 of lang/remarks.$taal
!!#@Je moet hier een percentage invullen...<br>0&le;percentage&le;100
!set rem2=!record 53 of lang/remarks.$taal
!!#@Ik verwacht hier $nm punten op het<br>normaal waarschijnlijkheids papiertje...
!set jtxt=!record 54 of lang/remarks.$taal
!!#@klassen,aantallen,cumulatief<br>percentage,Deze verdeling is,Niet normaal verdeeld,Normaal verdeeld
<script language="JavaScript" type="text/javascript">
    !set n=$counter
    function sendanswer(){
	var reply;
	// first we read the selectbox
	if(document.getElementById('myselect0').value == -1){dontknow();return;}
	reply = document.getElementById('myselect0').value+ "\n";
	
	// secondly we read the table: check for empty inputsfields
	var tmp;
	for(var p = 0 ; p < $nm ; p++){
	    tmp = document.getElementById('myinput'+p).value;
	    if(tmp.length == 0){setAlarm(r1);return;}
	    if(is_number(tmp) == 0){return;}
	    if(tmp>100 || tmp<0){setAlarm("$rem1");return;}
	    if(p == 0){
		reply = reply + tmp;
	    }else{reply = reply + "," + tmp;}
	}
	reply = reply + "\n";
	/* canvas or applet ? */
	!if $var8=1
	    tmp = (read_canvas()).toString();
	    tmp = tmp.replace(/\:/g,',');
	!else
	    tmp = document.getElementById('FlyApplet').ReadDrawing();
	!endif

	/* at last read the graphdata :sometimes 1 point may be outside the graph */
	var test = tmp.split(",");
	if(test.length < $[2*$nm - 2] ){setAlarm("$rem2");return;}
	if(test.length > $[2*$nm+2] ){ setAlarm("$rem2");return;}
	reply = reply + tmp;
	myConfirm("$send",reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>
<table summary="">
    <tr>
    <th style="vertical-align:top">
	<table class="zebra_table_h2">
	    <tr>
	    <th>
		$(jtxt[1])
	    </th>
	    <th>
		$(jtxt[2])
	    </th>
	    <th>
		$(jtxt[3])
	    </th>
	    </tr>
	!if $wims_user=supervisor
	!for p=1 to $nm
	    <tr>
		<th nowrap="nowrap">
		    !item $p of $var3
		</th>
		<th>
		    !item $p of $var5
		</th>
		<th>
		    !set a=!item $[$p+1] of $(answer$n)
		    <input type="text" id="myinput$[$p-1]" size="6" value="$a" class="schaersvoorde_input" />
		</th>
	    </tr>
	!next p
	
	!else
	!for p=1 to $nm
	    <tr>
		<th>
		    !item $p of $var3
		</th>
		<th>
		    !item $p of $var5
		</th>
		<th>
		    <input type="text" id="myinput$[$p-1]" size="6" value="" class="schaersvoorde_input" />
		</th>
	    </tr>
	!next p
	!endif
	</table>
	<br>	
	$(jtxt[4]) : <select size="1" id="myselect0" class="schaersvoorde_input" ><option value="-1">$dontknow</option><option value="1">$(jtxt[5])</option><option value="2">$(jtxt[6])</option></select>
    </th>
    <th style="vertical-align:top">
	$prob_paper
    </th>
    </tr>
</table>
