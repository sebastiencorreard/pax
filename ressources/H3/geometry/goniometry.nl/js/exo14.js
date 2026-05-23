!! antwoordformaat: 3 regels met elk 3 woorden gescheiden door ":"
!!naam1:waarde1:waarde1^2 , naam2:waarde2:waarde2^2 ,naam3:waarde3:waarde3^2  
<script type="text/javascript">

    function sendanswer(){
	var inputs=document.myform1.elements.length;var reply=new Array();
	var vraagnummer=1;var show=""
	var p = 0;
	while( while){
	    rep=document.myform1[p].value;
	    if( rep.length == 0 ){setAlarm(r1+" "+vraagnummer);return;}
	    if( rep.indexOf(',') != -1){setAlarm(r25 +" "+ vraagnummer+"\n" +r4);return;}
	    rep=science(rep);if(rep=="error"){return;}
	    if(check_o(rep)!=1){setAlarm(r25 +" "+ vraagnummer+"\n" + r5);return;}
	    if(rep.indexOf("^")!=-1){setAlarm(r26+"  :  "+rep);return;}
	    rep=rep.toLowerCase();
	    rep=rep.replace(/[a-z\~\!\@\#\%\:\;\$$]/g,'');
	    if( rep.length == 0  || rep.indexOf("?")!= -1){setAlarm(r1+" "+vraagnummer);return;}
	    reply[p]=rep;
	    show=show+"<br />"+rep;
	    p++;
	    vraagnummer++;
	}
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>

