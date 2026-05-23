!set n=$counter
!set inputs=yes
<script   type="text/javascript">
//<![CDATA[
<!-- no validator  -->
    function sendanswer(){
	var p = 0;
	var reply = new Array();
	var tmp;
	var show="";
	var vraagnummer="1";
	while( document.getElementById('myinput'+p) ){
	    tmp = document.getElementById('myinput'+p).value;
	    if( tmp.indexOf(',') != -1 ){ setAlarm(r4); return; }
	    if( tmp.length == 0 ){ setAlarm(r1 +" "+vraagnummer); return; }
	    tmp = science(tmp);if( tmp == "error" ){ return; }
	    if( check_x(tmp) == 0){ return; }
	    tmp = nthroot(tmp);if(tmp == "error"){ return; }
	    if( check_f(tmp) == 0){return;}if(check_o(tmp) == 0 ){ return; }
	    if( check_log_NaN(tmp) == 0 ){ return; }if(check_sqrt_NaN(tmp) == 0 ){ return; }
	    !!! check on arrows and variable x ... var2=minimum number of arrows/steps
	    tmp = arrows(tmp,"4","x","$var2");if( tmp == "error" ){ return; }
	    tmp = tmp.replace(/x/g,'X');tmp=upper_f(tmp);
	    !!! all siginifcant things are now uppercase,rest may be deleted.
	    tmp = tmp.replace(/[a-z\~\`\""\''\@\#\%\_\:\;\$$\&\!]/g,'');
	    tmp = tmp.toLowerCase();
	    reply[p] = tmp;
	    show = show + tmp.replace(/-\>/g,'  \u2192\n') + "<br />";
	    p++;
	    vraagnummer++;
	}
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
//]]>
</script>
