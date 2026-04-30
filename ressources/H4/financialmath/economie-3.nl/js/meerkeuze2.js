!set n=$counter
!set timeout=$var7
!set max=!itemcnt $var8

<script  type="text/javascript" src="$jsdir/../lang/remarks.$taal.js"></script>
<script type="text/javascript"  src="$jsdir/precheck.js"></script>
<script  type="text/javascript">
    
    function dontknow(){
	t=confirm(r0+"\n$dontknow ?");
	if(t==true){
	    URL = '$wims_ref_name?session=$session&+module=$module&+cmd=reply&+reply$n=%3F' ; 
	    document.location.href = URL;
	} 
    }
    
    function sendanswer(){
	var reply = new Array();
	for(var p=0; p<$max;p++){
	    if(document.getElementById('my_input'+p).checked){
		reply[p] = 1;
	    }
	    else
	    {
		reply[p] = 0;
	    }
	}
	alert(reply);
	reply=encodeURIComponent( reply );
	var URL = '$wims_ref_name?session=$session&+module=$module&+cmd=reply&+reply$n='+reply ; 
	document.location.href = URL;
    } 
</script>
<div id="time_exercise" align="center">
    <table summary="a few questions">
    !for p=1 to $max
	!set v=!item $p of $var8
	<tr>
	    <td id="my_th$[$p-1]" style="display:block;"> 
		<input id="my_input$[$p-1]" name="myinput$[$p+1]" type="checkbox" name="" value="1" />$v<br/>
	    </td>
	</tr>
    !next p
	<tr>
	<td>
	    
	    <table summary="">
		<tr>
		<th>
		    <input type="button" id="schaersvoorde_ok_button" onclick="javascript:sendanswer();"  value="$send"/>
		</th>
		<th>
		    <input type="button" id="schaersvoorde_ok_button" onclick="javascript:dontknow();"  value="$dontknow"/>
		</th>
		</tr>
	    </table>
	    
	</td>
    </table>
</div>
