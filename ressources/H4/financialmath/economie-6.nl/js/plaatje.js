!! nu DOM compatibel, en zonder innerHTML !!
<script language="JavaScript" type="text/javascript">
//<![CDATA[
<!-- no validator  -->
    !set n=$counter
    
    function sendanswer(){
	var reply="";
	var show="";
	var p=0;var tmp="";
	// als er invulvelden zijn; lees ze uit...
	while(document.getElementById('myinput'+p)){
	    tmp = document.getElementById('myinput'+p).value;
	    if(tmp.length == 0){setAlarm(r1+" "+eval(p+1)+" ...");return;}
	    if(is_number(tmp) == 0){return;}
	    if(p == 0){ reply = tmp; } else {reply = reply + "\n" + tmp;}
	    show=show+tmp+"<br />";
	    p++;
	}
	reply = reply + "\n";
	// lees de applet
	tmp = document.getElementById('FlyApplet').ReadDrawing();
	var test = (tmp.split(',')).length;
	if($n == 1 ){tmp="";}//geen tekening if(tmp.equals("error")){tmp="";}!	
	if( ($n == 2 || $n == 3 || $n == 5) && test != 2){//een enkel punt wordt verwacht
	    if(test<2){
		setAlarm("Je moet hier gewoon een punt aanklikken met je muis...<br />is goed te doen, normaal gesproken...");
	    }
	    else
	    {
		setAlarm("Je hoeft hier slechts 1 punt aan te klikken !! en geen "+ Math.round(test/2) +" punten<br />Met je rechter muisknop kun je de punten weer verwijderen");
	    }
	    return;
	}
	if( $n == 6 ){//een enkel punt wordt verwacht
	    if(test<2){
		setAlarm("Je moet hier gewoon punten aanklikken met je muis...<br />is goed te doen, normaal gesproken...");
		return;
	    }
	    else
	    {
		if(test>10){
		    setAlarm("Je klikt nu wel erg veel punten aan<br />kan niet goed zijn...<br />Met je rechter muisknop kun je de punten weer verwijderen");
		    return;
		}
	    }
	}
	if($n == 4 && test != 4){
	    if(test<4){
		setAlarm("je moet met je muis een rechthoek tekenen<br />Gewoon klikken en slepen...");
	    }
	    else
	    {
		setAlarm("Je hoeft hier slechts 1 rechthoek aan te klikken !! en geen "+ Math.round(test/4) +" rechthoeken<br />Met je rechter muisknop kun je de rechthoeken weer verwijderen");  
	    }
	    return;
	}
	reply = reply + tmp;
	myConfirm(show+"<br />"+tmp,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
//]]>
</script>

$applet
