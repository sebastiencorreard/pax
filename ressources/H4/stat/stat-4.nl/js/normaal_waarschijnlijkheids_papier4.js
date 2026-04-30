!set rem1=!record 56 of lang/remarks.$taal
!set rem2=!record 57 of lang/remarks.$taal
!set rem3=!record 58 of lang/remarks.$taal
<script language="JavaScript" type="text/javascript">
    !set n=$counter
    function sendanswer(){
	var reply;var tmp;
	// first we read the selectbox
	if(document.getElementById('myselect0').value == -1){dontknow();return;}
	reply = document.getElementById('myselect0').value+ "\n";
	// at last read the graphdata
	!if $var8=0
	tmp = document.getElementById('FlyApplet').ReadDrawing();
	!else
	tmp = (read_canvas()).toString();
	tmp = tmp.replace(/\:/g,',');
	!endif
	var test = tmp.split(",");
	if(test.length < 10 ){setAlarm("$rem1");return;}
	if(test.length > 26 ){setAlarm("$rem2");return;}
	reply = reply + tmp;
	myConfirm("$send ?",reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>
<table id="exercise" class="exercise">
    <tr>
    <th style="text-align:center;vertical-align:top">
	$prob_paper
    </th>
    </tr>
    <tr>
    <th>
	$(rem3[1]) <select size="1" id="myselect0" name="myselect0" style="text-align:center;font-size:16px;border:0px;background-color:lightblue"><option value="-1">$dontknow</option><option value="1">$(rem3[2])</option><option value="2">$(rem3[3])</option></select>
    </th>
    </tr>
</table>
