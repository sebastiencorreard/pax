!! gelijk aan plinko2.js ; maar nu met negative binomial 

<script type="text/javascript">
    var done=0;
    !set rem1=!record 161 of lang/remarks.$taal
    !set rem2=!record 160 of lang/remarks.$taal
    !set rem3=!record 163 of lang/remarks.$taal
    !set rem4=!record 164 of lang/remarks.$taal
    !set rem5=!record 165 of lang/remarks.$taal
    !set rem6=!record 162 of lang/remarks.$taal

    function sendanswer(){
	if(done != 1){setAlarm("$rem2");return;}
	var reply=new Array();var v;
	var show="";body1="";body2="";body3="";body4="";head="";
	var tmp=new Array();
	!! pre-checking the values:
	var p = 0;
	while( document.getElementById('myinput'+p) ){
	    v=document.getElementById('myinput'+p).value;
	    if(v.length == 0){setAlarm("$rem1"); return;}
	    v=v.toLowerCase();
	    v=v.replace(/[a-z\!~@#$:;=+_]/g,"");
	    if(v.length == 0){setAlarm("$rem3"); return;}
	    tmp[p]=v;
	    p++;
	}
	if(tmp.length != p){setAlarm("ERROR IN PROGRAM");return;}
	var len=parseInt($var1+1); // rest bakje erbij !
	var rows=parseInt(tmp.length / len);
	var delta;var theoretisch;
	for(p = 0;p < len;p++){
	    bakje=parseInt(p+1);
	    ballen=tmp[p];
	    kans=tmp[p+len];
	    if(rows == 2){
		head=head+"<td>"+bakje+"</td>";
		body1=body1+"<td>"+ballen+"</td>";
		body2=body2+"<td>"+kans+"</td>";
		reply[p]=ballen+"@"+kans;
	    }
	    else
	    {
		if(rows == 3){
		    theoretisch=tmp[p+2*len];
		    reply[p]=ballen+"@"+kans+"@"+theoretisch;
		    head=head+"<td>"+bakje+"</td>";
		    body1=body1+"<td>"+ballen+"</td>";
		    body2=body2+"<td>"+kans+"</td>";
		    body3=body3+"<td>"+theoretisch+"</td>";
		}
		else
		{
		    if(rows == 4){
			theoretisch=tmp[p+2*len];
			delta=tmp[p+3*len];
			reply[p]=ballen+"@"+kans+"@"+theoretisch+"@"+delta;
			head=head+"<td>"+bakje+"</td>";
			body1=body1+"<td>"+ballen+"</td>";
			body2=body2+"<td>"+kans+"</td>";
			body3=body3+"<td>"+theoretisch+"</td>";
			body4=body4+"<td>"+delta+"</td>";
		    }
		}
	    }	
	}
	if(rows == 2){
	    show = "<table class=\'grid_table\'><tr>"+head+"</tr><tr>"+body1+"</tr><tr>"+body2+"</tr></table>"; 
	}
	else
	{
	    if(rows == 3){
		show = "<table class=\'grid_table\'><tr>"+head+"</tr><tr>"+body1+"</tr><tr>"+body2+"</tr><tr>"+body3+"</tr></table>"; 
	    }
	    else
	    {
		show = "<table class=\'grid_table\'><tr>"+head+"</tr><tr>"+body1+"</tr><tr>"+body2+"</tr><tr>"+body3+"</tr><tr>"+body4+"</tr></table>";
	    }
	}
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }

    function showme(t){if(done == 0){var time="$rem3";var freq="$rem4";var d=document.getElementById("Ballenbak-II").ReadApplet();if(d.indexOf('error')!= -1){setAlarm("$rem1"+"<br />"+"\""+d+"\"");return;}var e=d.split(',');var t;var p;sum=3;var min=$var2;for(p=0;p<e.length;p++){t=e[p];sum=1*sum+1*t;}if(sum < min){setAlarm("$rem2");done = 0 ;return;}for(p=0;p<e.length;p++){t=e[p];document.getElementById('myinput'+p).value=t;document.getElementById('myinput'+p).setAttribute("readonly","readonly");} document.getElementById("schaersvoorde_extra_button").setAttribute("value","$rem6");document.getElementById("schaersvoorde_extra_button").setAttribute("style","background-color:orange");document.getElementById("schaersvoorde_ok_button").setAttribute("style","background-color:lightgreen");}else{setAlarm("$rem4");return;}}	
</script>

<object id="Ballenbak-II"  width="220" height="100" classid="java:PlinkoNegativeBinomial.class" type="application/x-java-applet;jpi-version=1.4">
<param name="java_code" value="PlinkoNegativeBinomial.class" /> 
<param name="java_codebase" value="$appletdir" />
<param name="java_archive" value="Plinko-II.jar" />
<param name="wims_exercise" value="1"/>
<param name="xsize" value="$xsize"/>
<param name="ysize" value="$ysize"/>
<param name="fontsize" value="12"/>
<param name="R" value="$var6"/>
<param name="bins" value="$var1"/>
<param name="chance" value="$var4"/>
<param name="speed" value="$var3"/>
<param name="title" value="Applet created by Dr. D.P. Little"/>  
<param name="language" value="$taal"/>
<param name="balls" value="$var2"/>
</object> 

<div class="embedded_central">
    <input type="button" id="schaersvoorde_extra_button"  onclick="showme();" value="$rem5" />
    <input type="button" id="schaersvoorde_ok_button" onclick="javascript:sendanswer();" value="$send" style="" />
    <input type="button" id="schaersvoorde_nok_button" onclick="javascript:dontknow();"  value="$dontknow" />
</div>
