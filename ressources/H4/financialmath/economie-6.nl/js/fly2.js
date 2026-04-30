<script type="text/javascript">
//<![CDATA[
<!-- no validator  -->
!set n = $counter
    
    function sendanswer(){
	!!alleen +/- symbolen pos of neg
	var tmp;
	var reply = new Array();
	var txt = document.getElementById('FlyApplet').ReadText()+"";
	txt=txt.toLowerCase();
	txt=txt.replace(/pos/g,'+');
	txt=txt.replace('1','+');
	txt=txt.replace(/neg/g,'-');
	txt=txt.replace('0','-');
	txt=txt.replace(/[0-9]/g,'');
	txt=txt.replace(/[a-z\~\`\""\''\@\#\%\_\=\;\$$\&\!\?]/g,'');
	txt=txt.split(',');
	for(var p=0;p<txt.length;p++){
	    tmp=txt[p];
	    if(tmp.length == 0 ){setAlarm("Ik verwacht alleen een + of - teken...");return;}
	    reply[p] = tmp;
	}
	myConfirm(reply,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
//]]>
</script>

$applet

