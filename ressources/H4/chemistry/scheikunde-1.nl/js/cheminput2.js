!set n=$counter
<script type="text/javascript">
    function sendanswer(){
	!set rem1=!record 30 of lang/remarks.$taal
	!!@Je bent de chemische formule(s) vergeten\nin de applet in te vullen...
	!set rem2=!record 73 of lang/remarks.$taal
	var reply=new Array();
	var tmp=new Array();
	var show="";var rep;var p = 0;
	while( document.getElementById('myinput'+p) ){
	    rep = document.getElementById('myinput'+p).value;
	    if(rep.length == 0){setAlarm(r1+" "+parseInt(p+1));return;}
	    if(rep.indexOf(',') != -1){setAlarm(r25+" "+parseInt(p+1)+"<br />"+r4);return;}
	    if(rep.indexOf(':') == -1 ){setAlarm("$rem2");return;}
	    tmp[p] = rep;
	    p++;
	}
	p = 0;var A;var q = 1;var tot = 0;var c = 0;
	while( document.getElementById('MiniInputApplet'+p) ){
	    A=document.getElementById('MiniInputApplet'+p).ReadAnswer();
	    if(A.length == 0){setAlarm("$rem1");return;}
	    reply[p]=A;
	    show=show+A+"&nbsp;&nbsp;&nbsp;&nbsp;";
	    tot++;q++;
	    if(q == 4){// 4 sub_vraagjes per vraag : 3 applets + 1 invulveld
		reply[tot]=tmp[c];
		show=show+"&nbsp;&nbsp;&nbsp;&nbsp;"+tmp[c]+"<br />";
		tot++;q=1;c++;
	    }
	    p++;
	}
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }

</script>
<div class="embedded_central">
    $var9
    <br />
    <input type="button" id="schaersvoorde_ok_button" onclick="javascript:sendanswer();" value="$send"/>
    <input type="button" id="schaersvoorde_nok_button" onclick="javascript:dontknow();"  value="$dontknow"/>
</div>
