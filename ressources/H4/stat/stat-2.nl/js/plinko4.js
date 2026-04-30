!set rem1=!record 130 of lang/remarks.$taal
!set rem3=!record 131 of lang/remarks.$taal
!set rem4=!record 132 of lang/remarks.$taal
!set rem2=!record 133 of lang/remarks.$taal
<script type="text/javascript">
    var done=0;
    var data;
    function sendanswer(){
	if(done != 1 ){setAlarm("$rem3");return}
        // test for confirmbox...wims list -> js-array
        !set array=!replace internal , by "," in $var2
        !set array=["$array"]
        var list=$array;
	var reply=new Array();
	var reply_descr=new Array();
	var showanswer="";var rep1;var rep2;var inp;
	var p = 0;
	while(document.getElementById('myinput'+p)){
	    inp=document.getElementById('myinput'+p);
	    rep1=inp.value;
	    try{// not sure if there are selectboxes present...try/catch
		rep2=inp.options[rep1].text;
	    }catch(e){
		if( rep1.length == 0 ){setAlarm(r1+" "+p+" ["+list[p]+"]" );return}
		if( rep1.indexOf(',') != -1){setAlarm(r4);return;}
		rep1=rep1.toLowerCase();
		rep1=science(rep1);if(rep1=="error"){return;}
		if(check_o(rep1)!=1){setAlarm(r5);return;}
		rep1=rep1.replace(/:/g,'/')
		rep2 = rep1;
	    }
	    reply[p]=rep1;
	    reply_descr[p]=rep2;
	    showanswer=showanswer+" "+list[p]+"  :  "+rep2+"<br />";
	    p++;
	}
	myConfirm(showanswer, reply+","+reply_descr+","+data,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }

    function showme(t){
	if(done == 0){
	    var time="$(rem1[1])";var freq="$(rem1[2])";
    	    data = document.getElementById("Ballenbak").ReadApplet();
    	    if(data.indexOf('error')!= -1){setAlarm("Hmmmm...?\n"+"\""+data+"\"");return;}
	    var e=data.split(',');var newdiv;var t1;var t2;var p;var check=0;
	    var mydiv = document.getElementById('mydiv');
	    mydiv.setAttribute("class","embedded_central");
	    var tablebody="<td>$(rem1[5])</td>";
	    var tablehead="<td>$(rem1[4])</td>";
	    var totballs=0;

	    for(p=0;p<e.length;p++){
		t1=p+1;t2=e[p];
		totballs=1*totballs+1*(e[p]);
		tablehead=tablehead+"<td>"+t1+"</td>";
		tablebody=tablebody+"<td>"+t2+"</td>";
		if(t2==0){check++;}
	    }
	    if(totballs < $min_balls){setAlarm("$rem2");return;}
	    if(check == e.length){setAlarm("$rem3");return;}
	    mydiv.innerHTML = "<table class=\"grid_table\"><tr>"+tablehead+"</tr><tr>"+tablebody+"</tr></table>";
	    var app=document.getElementById("Ballenbak");
	    app.setAttribute("height","0",0);
	    app.setAttribute("width","0",0);
	    done=1;
	    document.getElementById("Ballenbak").stop();
	    document.getElementById("Ballenbak").destroy();
	}else{setAlarm("$rem4");return;}
    }	
</script>

<object classid="java:Plinko.class" type="application/x-java-applet;jpi-version=1.4" id="Ballenbak" width="220" height="100" ><param name="java_code" value="Plinko.class" /><param name="java_codebase" value="$appletdir" /><param name="java_archive" value="Plinko.jar" /><param name="wims_exercise" value="1" /><param name="xsize" value="500" /><param name="ysize" value="500" /><param name="fontsize" value="12" /><param name="bins" value="$bins" /><param name="chance" value="$chance" /><param name="speed" value="$speed" /><param name="title" value="WIMS Galton Applet"/><param name="language" value="$taal" /><param name="balls" value="$balls" />$nojava</object>

<div id="mydiv"></div> 

<div class="embedded_central">
<input type="button" id="schaersvoorde_extra_button" onclick="showme();"  value="$(rem1[3])" />
<input type="button" id="schaersvoorde_ok_button" onclick="sendanswer();" value="$send" />
<input type="button" id="schaersvoorde_nok_button" onclick="dontknow();"  value="$dontknow" />
</div>