<script  type="text/javascript" src="$jsdir/precheck.js"></script>
<script  type="text/javascript"  src="$jsdir/../lang/remarks.$taal.js"></script>
<script type="text/javascript">
!set n = $counter
    function dontknow(){
	var test=confirm(r0+"\n$dontknow");
	if(test==true){var URL = '$wims_ref_name?session=$session&+module=$module&+cmd=reply&+reply$n=%3F' ;document.location.href = URL;}
    }
    
    !set array=!replace internal , by "," in $var2
    !set array=["$array"]
    var list=$array;
    !if $wims_user = supervisor
    function showAnswer(){
	var inputs=document.myform1.elements.length;
	!set answerarray=!replace internal , by "," in $(answer$n)
	!set answerarray=["$answerarray"]
	!set change=!replace internal , by "," in $var1
	!set change=["$change"];
	var change = $change;
	var answerarray=$answerarray;
	for(var p = 0; p<inputs;p++){
	    for(var i=0; i<change.length;i++){
		if(p == eval(change[i] - 1)){
		    document.getElementById('myinput'+p).setAttribute("style","background-color:lightgreen;font-size:18px");
		}
	    }
	    document.getElementById('myinput'+p).value = answerarray[p];
	}
    }
    !endif
    function sendanswer(){
	var inputs=document.myform1.elements.length;var tot=new Array();
	var showanswer="\n";var rep;var rep1;
	for(var p=0 ; p<inputs ; p++){
	    rep=document.getElementById('myinput'+p).value;
	    if( rep.length == 0 ){setAlarm("je hebt \""+list[p]+ "\" vergeten in te vullen" );return}
	    if( rep.indexOf(',') != -1){setAlarm("je hebt bij onderdeeltje \""+list[p]+ "\" een komma gebruikt...<br />Gebruik een decimale punt !!");return;}
	    rep=rep.toLowerCase();
	    rep=science(rep);if(rep=="error"){return;}
	    !! checks if an letter o was used instead of 0
	    if(check_o(rep)!=1){setAlarm("Je gebruikt bij \""+list[p]+ "\"  een <b>o</b> in plaats van een <b>nul</b>...");return;}
	    rep=rep.replace(/:/g,'/');rep1=rep.replace(/[a-z\~\`\""\''\@\#\%\_\=\;\$$\&\!]/g,'');
	    if( rep1.length == 0 ){setAlarm("je antwoord \""+rep+"\" bij  onderdeel \""+list[p]+"\" is onzinnig en ga ik zeker niet opsturen naar WIMS ");return;}
	    if( rep1 != rep){setAlarm("ik gebruik van je antwoord bij "+list[p]+" alleen "+rep1);}
	    tot[p]=rep1;
	    showanswer=showanswer+" "+list[p]+"  :  "+rep1+"\n";
	}
	test=confirm(r0+showanswer);
	if(test==true){tot=encodeURIComponent( tot );URL='$wims_ref_name?session=$session&module=$module&cmd=reply&+reply$n='+tot;document.location.href = URL;}
    }
</script>

    <input type="button" id="schaersvoorde_ok_button" onclick="javascript:dontknow();"  value="$dontknow"/>
 
