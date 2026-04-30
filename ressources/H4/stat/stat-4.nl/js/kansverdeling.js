!set tekst=!record 1 of lang/remarks.$taal
!!@AANTAL,KANS,invulveld,Binomiaal,niet-binomiaal,Deze verdeling is :,Alle invulvelden zijn al weg...
!set rem1=!item 1 of $tekst
!set rem2=!item 2 of $tekst
!set rem3=!item 3 of $tekst
!set rem4=!item 4 of $tekst
!set rem5=!item 5 of $tekst
!set rem6=!item 6 of $tekst
!set rem7=!item 7 of $tekst

<script language="JavaScript" type="text/javascript">
    !set n=$counter
    !if $wims_user=supervisor
	!set m=!itemcnt $(answer$n)
	!! answer$n is oneven: laatste item is type (binomiaal/niet-binomiaal)
	var ans = new Array($m);
	!for t=1 to $[$m-1]
	    !set a=!item $t of $(answer$n)
	    ans[$[$t-1]] =  $a;
	!next p
    !endif
    var imagesize=60;
    var cnt=0;
    var incr=10;
    var color=['lightgreen','lightblue'];

    function setStyle( object, styleText ) {
	// needed to setAttribute on IE...all other browers work fine with Input.setAttribute('style','text-align:center;font-size:24px;background-color:'+color[i]+';border:4px solid #ffffff');
	if( object.style.setAttribute ){ 
	    object.style.setAttribute("cssText", styleText ); 
	}
	else
	{ 
	    object.setAttribute("style", styleText ); 
	} 
    }
    
    function ShowTable(){
	if(document.getElementById('myselect0').value == -1){dontknow();return;}
    	document.getElementById('exercise_table').style.display = "block";
    	document.getElementById('return_buttons').style.display = "block";
    }
    
    function IncreaseInputs(div,change){
	if(change == 1){
	    for(var i = 0 ;i<2 ; i++){
		var MyDiv = document.getElementById(div+i);
		var Input=document.createElement('INPUT','myinput'+cnt);
	        Input.setAttribute('id','myinput'+cnt);
		Input.setAttribute('size','$cols');
		!if $wims_user=supervisor
		    Input.setAttribute('value',ans[cnt]);
		!endif
		setStyle(Input,'text-align:center;font-size:16px;background-color:'+color[i]+';border:2px solid #ffffff');
	        !! Input.setAttribute('style','text-align:center;font-size:16px;background-color:'+color[i]+';border:4px solid #ffffff');
    		try {
		    MyDiv.appendChild(Input);
		    cnt++;
		} catch(e){setAlarm(e);}
	    }
	}
	    else
	{
	    if(cnt>0){
		for(var i = 1 ;i>-1 ; i--){
		    cnt--;
		    var MyDiv = document.getElementById(div+i);
		    var Input=document.getElementById('myinput'+cnt);
    		    try {
			MyDiv.removeChild(Input);
		    } catch(e){setAlarm(e);}
		}
	    }
	    else
	    {
		setAlarm("$rem7");
	    }
	}
	if(cnt > $[2*$num+6]){setAlarm(r43);}
    }

    function sendanswer(){    
	var reply=new Array();var show0="$rem1 ";var show1="$rem2 ";var show2="";num=0;
	if(cnt == 0){setAlarm(r1+" $counter");return;}
	if(cnt>0){
	    for(var p = 0 ; p <cnt ; p = p + 2){
		reply[p] = document.getElementById('myinput'+p).value;
		if(reply[p].length == 0){setAlarm(r44);return;}
		if(is_number(reply[p]) != 1){return;}
		num = 1;
		show0=show0+" "+reply[p];
	    }
	    for(var p = 1 ; p <cnt ; p = p + 2){
		reply[p] = document.getElementById('myinput'+p).value;
		if(reply[p].length == 0){setAlarm(r44);return;}
		if(is_number(reply[p]) != 1){return;}
		show1=show1+" "+reply[p];
		num = 1;
	    }
	}
	if(num == 0){setAlarm(r1+" $counter");return;}
	if( document.getElementById('myselect0') ){
	    reply[cnt] = document.getElementById('myselect0').value;
	    if(reply[cnt] == -1){show2 = "\n$rem6 $dontknow";}
	    if(reply[cnt] == 1 ){show2 = "\n$rem6 $rem4";}
	    if(reply[cnt] == 2 ){show2 = "\n$rem6 $rem5";}
	}
	if(cnt < $num){setAlarm(r33);}
	myConfirm(show0+"<br />"+show1 + show2,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>

$rem6 <select size="1" id="myselect0" name="myselect0" onchange="javascript:ShowTable();" style="text-align:center;font-size:18px;border:0px;background-color:lightblue"><option value="-1">&nbsp;</option><option value="-1">$dontknow</option><option value="1">$rem4</option><option value="2">$rem5</option></select>
<br><br>
<table  summary="" id="exercise_table" style="display:none">
    <tr>
	<th>
	    <table summary="">
		<tr>    
		    <th nowrap>
			$rem1
		    </th>
		</tr>
		<tr>
		    <th>
			<br>
		    </th>
		</tr>
		<tr>
		    <th nowrap>
			$rem2
		    </th>
		</tr>
	    </table>
	</th>
	<th>
	    <div id="mydiv0"></div>
	    <br>
	    <div id="mydiv1"></div>
	</th>
    </tr>
    <tr>
	<td>
	    <table summary="">
		<tr>    
		    <th nowrap>
			 <input style="font-size:16px;background-color:lightgreen" type="button" value="$rem3 + 1" onclick="javascript:IncreaseInputs('mydiv','1');">
		    </th>
		</tr>
		<tr>
		    <th nowrap>
			<input style="font-size:16px;background-color:orange" type="button" value="$rem3 &minus; 1" onclick="javascript:IncreaseInputs('mydiv','0');">
		    </th>
		</tr>
	    </table>
	</td>
    </tr>
</table>
<div id="return_buttons" class="embedded_central" style="display:none">
    <input type="button" id="schaersvoorde_ok_button" onclick="javascript:sendanswer();" value="$send" />
    <input type="button" id="schaersvoorde_nok_button" onclick="javascript:dontknow();"  value="$dontknow" />
</di>
 
