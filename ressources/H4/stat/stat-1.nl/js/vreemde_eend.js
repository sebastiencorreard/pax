<script type="text/javascript">
    var done=0;
    !set rem2=!record 43 of lang/remarks.$taal
    !set rem1=!record 44 of lang/remarks.$taal
    !set rem6=!record 45 of lang/remarks.$taal
    !set rem3=!item 1 of $rem2
    !set rem4=!item 2 of $rem2
    !set rem5=!item 3 of $rem2
    var rem1="$rem1";var rem2="$rem2";var rem3="$rem3";var rem4="$rem4";var rem5="$rem5";var rem6="$rem6";
    var var5="$var5";
    var applet_data="";
    function sendanswer(){
	if( applet_data.length <10 || applet_data.indexOf('error')!= -1){setAlarm(rem1);return;}
	var reply=new Array();var show="<ul>";var rep;var vraagnummer = 1;
	var p = 0;
	while( document.getElementById("myinput"+p)){
	    rep = document.getElementById("myinput"+p).value;
	    if(rep.length == 0){ setAlarm(r1+"&nbsp;"+vraagnummer);return 0;}
	    if(rep.indexOf(',') != -1){setAlarm(r25+"&nbsp;"+vraagnummer+"<br />"+r4);return} 
	    rep=rep.toLowerCase();if(check_o(rep)!=1){setAlarm(r25 + "&nbsp;" + vraagnummer +"<br />"+ r5);return;} 
	    rep=prefix(rep);rep=science(rep);rep=rep.replace(/[a-z\~\`\""\''\@\#\%\_\=\:\;\$$\&\!]/g,'');
	    if(rep.length==0){setAlarm(r2);return;}
	    show=show+"<li>"+description[p]+" "+rep+"</li>";
	    reply[p]=rep;
	    p++;
	}
	show = show + "</ul>";
	myConfirm(show,reply+","+applet_data,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
	document.getElementById("VreemdeEend").destroy();
    }

    function showme(t){
	!! data= totaltime [seconds] , max \n 
	!! time_1 : frequency_1 \n
	!! time_2 : frequency_2 \n
	!! ...
	!! time_n : frequency_n
	if(done==0){
	    var time=rem3;var freq=rem4;
    	    applet_data=document.getElementById("VreemdeEend").ReadApplet();
    	    if(applet_data.indexOf('error')!= -1){setAlarm(rem1);return;}
	    var e=applet_data.split('\n');var l=e.length;var newdiv;var line;var f;var n;var r;
	    var old = document.getElementById('mydiv');;
	    newdiv = document.createElement('div');newdiv.setAttribute("id","mydiv1");newdiv.setAttribute("name","mydiv");
	    var tablehead="";var tablebody="";var c=0;var t;
	    var rows=Math.ceil(l/5);
	    if(var5 == 1){
		tablehead="<tr>";
		for(n=0;n<rows+1;n++){
		    tablehead=tablehead+"<th>"+time+"</th><th>"+freq+"</th>";
		}
		tablehead=tablehead+"</tr>";
		tablebody="<tr>";
		for(n=1;n<l;n++){
	    	line=e[n];f=line.split(':');t=f.length;
		    if(t>1){
			if(c == rows){
			    c=0;tablebody = tablebody+"<td>"+f[0]+"</td><td>"+f[1]+"</td></tr>";
			    if(n != l-1){
				tablebody=tablebody+"<tr>";
			    }
			}
			else
			{
			    c++;
			    tablebody=tablebody+"<td>"+f[0]+"</td><td>"+f[1]+"</td>";
			}
		    }
		}
		newdiv.innerHTML = "<table class=\'zebra_table_v3\'>"+tablehead+tablebody+"</table>";
	    }
	    else
	    {
		tablehead="<tr>";
		for(n=0;n<rows+1;n++){
		    tablehead=tablehead+"<th>"+time+"</th>";
		}
		tablehead=tablehead+"</tr>";
		tablebody="<tr>";
		for(n=1;n<l;n++){
	    	line=e[n];f=line.split(':');t=f.length;
		    if(t>1){
			if(c==rows){
			    c=0;
			    tablebody=tablebody+"<td>"+f[0]+"</td>";
			    if(n != l-1){
				tablebody=tablebody+"<tr>";
			    }
			}
			else
			{
			    c++;
			    tablebody=tablebody+"<td>"+f[0]+"</td>";
			}
		    }
		}
		newdiv.innerHTML = "<table class=\'grid_table\'>"+tablehead+tablebody+"</table>";
	    }
	    old.appendChild(newdiv);
	    !! now we make applet "invisible": 
	    var app=document.getElementById("VreemdeEend");
	    app.setAttribute("height","0");
	    app.setAttribute("width","0");
	    done=1;
	}
    }	
</script>

!if $subject isin 10,11
    <object id="VreemdeEend"  width="660" height="210" classid="java:VreemdeEend1.class" type="application/x-java-applet;jpi-version=1.4">>
	<param name="java_code" value="VreemdeEend1.class" />
	<param name="java_codebase" value="$module_dir/applets" />
	<param name="java_archive" value="VreemdeEend.jar" />
	<param name="max" value="$var4"/>
	<param name="renew" value="$var3"/>
	<param name="language" value="$taal"/>
	<param name="show_result" value="yes"/>
    </object>
!else
    <object id="VreemdeEend"  width="800" height="210" classid="java:VreemdeEend2.class" type="application/x-java-applet;jpi-version=1.4">>
	<param name="java_code" value="VreemdeEend2.class" />
	<param name="java_codebase" value="$module_dir/applets" />
	<param name="java_archive" value="VreemdeEend.jar" />
	<param name="max" value="$var4"/>
	<param name="renew" value="$var3"/>
	<param name="language" value="$taal"/>
	<param name="show_result" value="yes"/>
	<param name="questions" value="$var6"/>
    </object>
!endif
<div id="mydiv" name="mydiv"></div> 
<div id="send_buttons" class="embedded_central">
    <input type="button" id="schaersvoorde_extra_button" onclick="showme();" value="$rem5"/>
    <input type="button" id="schaersvoorde_ok_button" onclick="javascript:sendanswer();" value="$send"/>
    <input type="button" id="schaersvoorde_nok_button" onclick="javascript:dontknow();"  value="$dontknow"/>
</div>