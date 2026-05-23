<script language="JavaScript" type="text/javascript">
    var min = $[2*$options];
    !set n=$counter
    !set rem1=je moet natuurlijk wel iets tekenen in de applet...;
    !set rem2=Je moet hier $options punt(en) te tekenen...
    !set rem3=Je moet hier slechts $options punten te tekenen...<br />Een rechter_muis_knop_klik verwijdert punten...
    function sendanswer(){
	var appletreply = document.getElementById('FlyApplet').ReadDrawing();
	if( (appletreply.indexOf('error')) != -1){setAlarm("$rem1");return;}
	var reply = new Array();
	reply = appletreply.split(',');
	if(reply.length < min ){setAlarm("$rem2");return;}
	if(reply.length > min ){setAlarm("$rem3");return;}
	var show = "";
	var p = 0;var f;var y_tmp;
	for( p = 0; p < min ; p = p+2){
	    y_tmp = reply[p+1];
	    f = Math.pow(10,(Math.floor(y_tmp - 1)));                                                                        
	    reply[p+1] = f*(Math.round((Math.pow(10,y_tmp))/f)); 
	    show = show+"("+reply[p]+":"+reply[p+1]+")<br />";
	}
	if( document.getElementById('myinput0')){
	    var s = 0;var rep;
	    while( document.getElementById('myinput'+s) ){
		rep = document.getElementById('myinput'+s).value;
		if(is_real_number(rep) == 0){return;}
		reply[p+s]= rep;
		show=show+"<br />"+rep;
		s++;
	    }
	}
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>

$flyapplet

