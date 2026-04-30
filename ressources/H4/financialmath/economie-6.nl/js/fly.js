<script type="text/javascript">
!set n = $counter
    function sendanswer(){
	var tmp;
	var reply = new Array();
	var txt = document.getElementById('FlyApplet').ReadText()+"";
	txt=txt.toLowerCase();
	// O-B=
	txt=txt.replace(/[a-z]*-*[a-z]/g,'');
	txt=txt.replace(/[a-z\~\`\""\''\@\#\?\%\_\=\;\$$\&\!\ \:]/g,'');
	txt=txt.split(',');
	var p = 0;
	for(p = 0;p < txt.length;p++){
	    tmp=txt[p];
	    var n = p+1;
	    if(tmp.length == 0){setAlarm("van antwoord nummer "+n+" in de applet kan ik geen soep koken..." );return;}
	    if(is_real_number(tmp) == 1 ){reply[p] = tmp;}else{return;}
	}
	if(document.getElementById("myinput0")){
	    for(var r=0 ; r<3; r++){
		tmp = document.getElementById('myinput'+r).value;
		tmp = tmp.toLowerCase();
		tmp = tmp.replace(/[a-z\~\`\""\''\@\#\?\%\_\=\;\$$\&\!\ \:]/g,'');
	        if(tmp.length == 0){setAlarm("van invulveld nummer "+r+" kan ik geen soep koken..." );return;}
		if(is_real_number(tmp) == 1 ){
		    reply[p] = tmp; p++;
		}
		else
		{
		    return;
		}
	    }
	}
	myConfirm(reply,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>

$applet
