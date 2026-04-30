<script type="text/javascript">
!set n = $counter
    function sendanswer(){
	var showanswer="";
	var reply=new Array();
	if(document.getElementById('MiniInputApplet')){
	    var A = document.getElementById('MiniInputApplet').ReadAnswer()+"";
	    var H = document.getElementById('MiniInputApplet').ReadHtml()+"";
	    var L = document.getElementById('MiniInputApplet').ReadLatex();
	    if(A.length == 0){setAlarm(r1+"$counter");return;}
	    reply[0]=A;
	    reply[1]=H;
	    reply[2]=L;
	    showanswer=showanswer+A;
	}
	else
	{
	    var p = 0;var rep;
	    while(document.getElementById('myinput'+p) ){
		rep=document.getElementById('myinput'+p).value;
		if( rep.length == 0 ){setAlarm(r44+":"+description[p] );return}
		if( rep.indexOf(',') != -1){setAlarm(r4+":"+ description[p]);return;}
		rep = rep.toLowerCase();
		rep = science(rep);if(rep=="error"){return;}
		reply[p]=rep;
		showanswer=showanswer+description[p]+"  :  "+rep+"<br />";
		p++;
	    }
	}
	myConfirm(showanswer,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>
