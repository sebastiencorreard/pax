!set n=$counter
!set jsremarks=!record 5 of lang/remarks.$taal
!set rem1=!record 6 of lang/remarks.$taal
!set rem5=!record 7 of lang/remarks.$taal
!set x=!item 1 of $jsremarks
!set f=!item 2 of $jsremarks
!set g=!item 3 of $jsremarks
!set add_row=!item 4 of $jsremarks
!set del_row=!item 5 of $jsremarks
!set rem2=!item 6 of $jsremarks
!set rem3=!item 7 of $jsremarks

<script  type="text/javascript">
    var rem1="$rem1";
    var rem2="$rem2";
    var rem3="$rem3";
    var rem4="$rem4";
    var rem5="$rem5";
    var URL;
    var numrows=0;
    var saved=new Array();

    function sendanswer(){
	if(numrows < 3){setAlarm(rem1);return;}
	var reply=new Array();
	var s=0;var show="<table><tr>";
	var p = 0;
	while( document.getElementById("myinput"+p) ){
	    rep=document.getElementById("myinput"+p).value;
	    if(rep.length==0){setAlarm(rem2+" "+parseInt(p+1)+" "+rem3);return;}
	    check_o(rep);rep=science(rep);if(rep == "error"){return;}
	    if(is_number(rep) == 0){return;}
	    reply[p] = rep;
	    if(s == 3){show=show+"</tr><tr>";s=0;}
	    show=show+"<td>"+rep+"</td>";
	    s++;
	    p++;
	    if(p > 100){dontknow();return;}
	}
	show=show+"</tr></table>"
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    } 

    function save_data(){
	var p = 0;
	while( document.getElementById("myinput"+p) ){
	    saved[p] = document.getElementById("myinput"+p).value;
	    p++
	    if(p > 100){dontknow();return;}
	}
    }

    function restore_data(){
	var p = 0;
	while( document.getElementById("myinput"+p) ){
	    if( saved[p] ){
		document.getElementById("myinput"+p).value = saved[p];
	    }
	    p++
	}
    }

    function make_table(t){
	save_data();
	numrows=numrows+t;
	if(numrows<1){setAlarm(rem1);return;}
	if(numrows>10){setAlarm(rem5);return;}
	var old = document.getElementById('mydiv');
	try{
	    var last = document.getElementById('mydiv0');
            old.removeChild(last);
	}catch(e){}
	var divIdName = "mydiv0";
	var newdiv = document.createElement('div');
	newdiv.setAttribute("id",divIdName);
	var rijen="";
	var i  = 0;var id1;var id2;var id3;
	for(var p=0;p<numrows;p++){
	    id1="myinput"+i;
	    i++;
	    id2="myinput"+i;
	    i++;
	    id3="myinput"+i;
	    i++;
	    rijen=rijen+"<tr><td><input id=\""+id1+"\"style=\"text-align:center;font-size:18px;background-color:lightgreen;border:1px solid #ff0000\" size=\"$cols\" type=\"text\" value=\"\" /></td><td><input id=\""+id2+"\" style=\"text-align:center;font-size:18px;background-color:#7fbbff;border:1px solid #ff0000\"  size=\"$[2*$cols]\" type=\"text\" value=\"\"/></td><td><input id=\""+id3+"\" style=\"text-align:center;font-size:18px;background-color:#7f96b5;border:1px solid #ff0000\"  size=\"$[2*$cols]\" type=\"text\" value=\"\"/></td></tr>" ;
	}
	newdiv.innerHTML="<table><tr><td style=\"background-color:lightgreen;text-align:center;font-size:18px;\">$x</td><td style=\"background-color:#7fbbff;text-align:center;font-size:18px;\">$f</td><td style=\"background-color:#7f96b5;text-align:center;font-size:18px;\">$g</td></tr>"+rijen+"</table>";
	old.appendChild(newdiv);
	restore_data();
    }

</script>

<div class="embedded_central">
    <table>
	<tr>
	    <td>
		<div id="mydiv"></div>
	    </td>
	    <td>
		<table>
		    <tr><td><input type="button" style="background-color:lightgreen;font-weight:normal;font-size:16px;text-align:center;" onclick="javascript:make_table(1)" value="$add_row" /></th></tr>
		    <tr><td><input type="button" style="background-color:orange;font-weight:normal;font-size:16px;text-align:center;" onclick="javascript:make_table(-1)" value="$del_row" /></th></tr>
		</table>
	    </td>
	</tr>
    </table>
 
</div>

!!!!! door inputs=yes handelt $phtmldir/myjavascript de knoppen [OK en versturen] en [geen idee] mooi gecentreerd af...
 
