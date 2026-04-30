<script type="text/javascript">
!set n = $counter
    function sendanswer(){
	var tot=new Array();
	var rep=document.getElementById('myinput0').value;
	if( rep.length == 0 ){setAlarm("je bent het antwoord vergeten in te vullen..." );return;}
	rep=rep.replace(/\ en\ /g,' ');
	rep=rep.replace(/\,/g,' ');
	rep=rep.replace(/[0-9\~\`\""\''\@\#\%\_\=\;\$$\&\!]/g,'');
	if( rep.length == 0 ){setAlarm("Ik verwacht hier een antwoord als<br />A , B  en C");return;}
	var l;var L;var i=0;
	var controle=$var9;
	var found;var hmm="";
	for(var s = 0 ; s < rep.length ; s++){
	    l = rep.charAt(s);
	    if(l != " "){
		L = l.toUpperCase();
		found = false;
		for(var p = 0 ; p < controle.length ; p++){
		    if(controle[p] == l || controle[p] == L){
			tot[i] = L;
			i++;
			found = true;
		    }
		}
		if(!found){hmm = hmm+"..."+l;}
	    }
	}
	if( hmm != "" ){setAlarm("Ik verwacht hier een antwoord als<br />A , B  en C<br />"+hmm+" kan ik niet vinden in het plaatje, jij wel ?");return;}
	if( i == 0 ){setAlarm("Ik verwacht hier een antwoord als<br />A , B  en C<br />en geen "+rep);return;}
	!if $teaching=1
	    if( tot.length == controle.length ){ hmm = "Denk je werkelijk dat het goede antwoord alle gebieden in de grafiek is...<br />";}
	!endif
	myConfirm(hmm+rep,tot,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
	
    }
</script>
