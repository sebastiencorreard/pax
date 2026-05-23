!! antwoordformaat: 3 regels met elk 3 woorden gescheiden door ":"
!!naam1:waarde1:waarde1^2 , naam2:waarde2:waarde2^2 ,naam3:waarde3:waarde3^2
<script type="text/javascript">
//<![CDATA[
<!-- no validator  -->
    function sendanswer(){
	var reply=new Array();
	var vraagnummer=1;
	var step=1;var subanswer="";var show="";var cnt=0;
	var p = 0;
	while(document.getElementById("myinput"+p)){
	    rep = document.getElementById("myinput"+p).value;
	    if( rep.length == 0 ){setAlarm(r1+" "+vraagnummer);return}
	    if( rep.indexOf(',') != -1){setAlarm(r25 +" "+ vraagnummer+"\n" +r4);return}
	    if(step == 1 ){ // this answer should be TEXT
		if(is_text(rep) == 0){
		    return;
		}
	    }
	    else // this answer should be a number
	    {
		if( is_number(rep) == 0 ){ 
		    return;
		}
	    }
	    rep=science(rep);if(rep=="error"){return;}
	    if(check_o(rep)!=1){setAlarm(r25 +" "+ vraagnummer+"\n" + r5);return;}
	    if(rep.indexOf("^")!=-1){setAlarm(r26+"  :  "+rep);return;}
	    if(step == 3){
		step = 0;
		reply[cnt]=subanswer+rep;
		show=show+"<br>"+subanswer+rep;
		cnt++;
		subanswer="";
	    }
	    else
	    {
		subanswer=subanswer+rep+":";
	    }
	    p++;
	    vraagnummer++;
	    step++;
	}
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
//]]>
</script>

