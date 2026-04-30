!set n=$counter
<!-- old style : uses applet to check and grade (eg no use of "mathmol") -->
<script  type="text/javascript">
    function show(){
	document.WIMSchem.SetMoleculeNative($var1);
    }
    var sp;
    function readapplet(){
	!! first load the correct answer molecule in the applet
	document.getElementById('WIMSchem').GetQuestion($var1);
	!! then call the compare routines
	var reply=document.getElementById('WIMSchem').CompareNative();
	if(reply.indexOf("error")!= -1){setAlarm(reply);return;}
	sp=reply.split("@");
	var t=confirm("$send");
	if(t==true){
	    if(document.getElementById){
		document.getElementById('wait').style.visibility = 'visible';
	    }
	    else
	    {
		if (document.layers) {
		    document.wait.visibility = 'hidden';
		}
		else
		{
		    document.all.wait.style.visibility = 'hidden';
		}
	    }
	    document.getElementById('WIMSchem').AppendMoleculeNative(sp[2]);
	    !set sometext=!record 68 of lang/remarks.$taal
	    setAlarm("$sometext");
	    setTimeout("sendanswer()", 5000);
	}
    }

    function sendanswer(){
	myConfirm("$send",sp[0],'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>
<div class="embedded_central" >
    <object id="WIMSchem"  width="640" height="400" classid="java:WIMSchem.MainApplet.class" type="application/x-java-applet;jpi-version=1.4">
	<param name="java_code" value="WIMSchem.MainApplet" />
        <param name="java_codebase" value="java/WIMSchem" />
	<param name="java_archive" value="WIMSchem.jar" />
	<param name="language" value="$taal" />
        $var2
	$nojava
    </object>
!if $inputs>0
    <table class="zebra_table_h2">
    !for p=1 to $inputs
	<tr>
	<td>
	    <kbd>$(description[$p])</kbd>
	</td>
	<td>:</td>
	<td>
	    <input type="text" id="myinput$[$p-1]" class="schaersvoorde_input" size="$cols" value="" />
	</td>
	</tr>
    !next p
    </table>
!endif
!if $wims_user=supervisor
    !set correctanswer=!record 69 of lang/remarks.$taal
    <input type="button" style="background-color:orange;font-weight:normal;text-align:center;" value="$correctanswer" onclick="javascript:show();" />
!endif
    <input type="button" id="schaersvoorde_ok_button" value="$send" onclick="javascript:readapplet();" />
    <input type="button" id="schaersvoorde_nok_button"  value="$dontknow" onclick="javascript:dontknow();" />
</div>
