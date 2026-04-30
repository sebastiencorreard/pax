<script  type="text/javascript" src="$jsdir/precheck.js"></script>
<script  type="text/javascript"  src="$jsdir/../lang/remarks.$taal.js"></script>
<script type="text/javascript">
!set n = $counter
    function dontknow(){
	var test=confirm(r0+"\n$dontknow");
	if(test==true){var URL = '$wims_ref_name?session=$session&+module=$module&+cmd=reply&+reply$n=%3F' ;document.location.href = URL;}
    }
    
    function sendanswer(){
	var rep1=document.getElementById("thisinput").value;
	rep1=rep1.toLowerCase();
	rep1=rep1.replace(/[a-z\~\!\@\#\$\&\_\=\:\ \;]/g,'');
	if(rep1.length == 0){setAlarm(r1+" $counter");return;}
	if(rep1.indexOf(",") != -1){setAlarm(r4);return;}
	var rep2=document.getElementById("thisselectbox").value;
	var txt=document.getElementById("thisselectbox").options[rep2].text;
	var reply = new Array();
	reply[0] = rep1;
	reply[1] = rep2;
	var test=confirm(r0+"\n$inputtext1 = "+rep1+"\n"+txt);
	if(test==true){
	    reply = encodeURIComponent(reply);
	    URL='$wims_ref_name?session=$session&module=$module&cmd=reply&+reply$n='+reply;
	    document.location.href = URL;
	}
    }
</script>
!if $wims_user=supervisor
    !set rep=!item 1 of $(answer$n)
    $inputtext1 &nbsp;=&nbsp;<input id="thisinput" value="$rep" size="$cols" style="background-color:lightgreen;font-size:18px"/>&nbsp;
!else
    $inputtext1 &nbsp;=&nbsp;<input id="thisinput" value="" size="$cols" style="background-color:lightgreen;font-size:18px"/>&nbsp;
!endif
