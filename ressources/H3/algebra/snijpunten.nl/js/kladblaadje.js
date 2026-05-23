!set n=$counter
!! wims 
!set jsremarks=!record 5 of lang/remarks.$taal
!set kladblaadje=!record 8 of lang/remarks.$taal
!set x=!item 1 of $jsremarks
!set f=!item 2 of $jsremarks
!set g=!item 3 of $jsremarks
!set add_row=!item 4 of $jsremarks
!set del_row=!item 5 of $jsremarks

<script  type="text/javascript">
    function sendanswer(){
	var v;var input;var show="" ;var reply=new Array();
	var ml;var t1;var t2;
	var p = 0 ;
	while( document.getElementById("myinput"+p)){
	    input=document.getElementById("myinput"+p).value;
	    if(input.length == 0){var qu=z+1; setAlarm(r1+"\ "+qu);return;}
	    input=nthroot(input);if(input=="error"){return;}
	    if(input.indexOf(',')!=-1){setAlarm(r4);return;}
	    input=arrows(input,2,"","");if(input=="error"){return;}
	    if(check_f(input)==0){return;}if(check_o(input)==0){return;}
	    if(check_log_NaN(input)==0){return;}if(check_sqrt_NaN(input)==0){return;}
	    input=science(input);if(input=="error"){return;}
	    if(check_x(input)==0){return;}
	    show=show+input+"\n";
	    t1=input.indexOf("[");
	    if(t1 !=- 1){
		if(input.indexOf("sqrt[")!=-1){input=specialroot(input);if(input=="error"){return;}}
		if(input.indexOf("log[")!=-1){input=speciallog(input);if(input=="error"){return;}}
		t1=input.indexOf("[");if(t1!=-1){setAlarm(r13);return;}
	    }
	    input=input.replace(/#/g,' ');
	    reply[p]=input;
	    p++;
	}
	if(reply.length == 0){setAlarm(r1);return;}
	
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }

    var saved=new Array();
    function save_data(){
	var p = 0
	while( document.getElementById('dummy'+p) ){
	    saved[p] = document.getElementById('dummy'+p).value;
	    p++;
	}
    }
    
    function restore_data(){
	var p = 0
	while( document.getElementById('dummy'+p) ){
	    if(saved[p]){
		document.getElementById('dummy'+p).value = saved[p];
	    }
	    p++;
	}
    }

    var numrows=0;

    function make_table(t){
	save_data();
	numrows=numrows+t;
	var old = document.getElementById('mydiv');
	try{
	    var last = document.getElementById('mydiv0');
            old.removeChild(last);
	}catch(e){}
	var divIdName = "mydiv0";
	var newdiv = document.createElement('div');
	newdiv.setAttribute("id",divIdName);
	var rijen="";
	var i=0;var id1;var id2;var id3;
	for(var p=0;p<numrows;p++){
	    id1="dummy"+i;
	    i++;
	    id2="dummy"+i;
	    i++;
	    id3="dummy"+i;
	    i++;
	    rijen=rijen+"<tr><td><input id=\""+id1+"\" style=\"text-align:center;font-size:18px;background-color:lightgreen;border:1px solid #ff0000\" size=\"4\" type=\"text\" value=\"\" /></td><td><input id=\""+id2+"\" style=\"text-align:center;font-size:18px;background-color:lightblue;border:1px solid #ff0000\"  size=\"4\" type=\"text\" value=\"\" /></td><td><input id=\""+id3+"\" style=\"text-align:center;font-size:18px;background-color:lightblue;border:1px solid #ff0000\"  size=\"4\" type=\"text\" value=\"\"/></td></tr>";
	}
	if(numrows>0){
	    newdiv.innerHTML="<table><tr><td><table summary=\"0\" border=\"1\"><tr><td style=\"background-color:lightgreen;text-align:center;font-size:18px;\">$x</td><td style=\"background-color:lightblue;text-align:center;font-size:18px;\">$f</td><td style=\"background-color:lightblue;text-align:center;font-size:18px;\">$g</td></tr>"+rijen+"</table></td></tr><tr><td><font size=\"-2\"><b><em>$kladblaadje</em></b></td></tr></table>";	
	    old.appendChild(newdiv);
	    restore_data();
	}
    }

</script>

<div class="embededd_central">
    <table>
	<tr>
	    <td>
		<div id="mydiv"></div>
	    </td>
	    <td>
		<table summary="">
		    <tr><td><input type="button" style="background-color:lightgreen;font-weight:normal;font-size:16px;text-align:center;" onclick="javascript:make_table(1)" value="$add_row"/></th></tr>
		    <tr><td><input type="button" style="background-color:orange;font-weight:normal;font-size:16px;text-align:center;" onclick="javascript:make_table(-1)" value="$del_row"/></th></tr>
		</table>
	    </td>
	</tr>
    </table>
 
</div>

!!!!! door inputs=yes handelt $phtmldir/myjavascript de knoppen [OK en versturen] en [geen idee] mooi gecentreerd af...
 
