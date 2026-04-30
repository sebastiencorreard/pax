<script type="text/javascript">
    var done=0;
    !set rem2=!record 43 of lang/remarks.$taal
    !set rem1=!record 44 of lang/remarks.$taal
    !set rem6=!record 45 of lang/remarks.$taal
    !set rem9=!record 53 of lang/remarks.$taal
    !set rem3=!item 1 of $rem2
    !set rem4=!item 2 of $rem2
    !set rem5=!item 3 of $rem2
    !set rem7=!item 4 of $rem2
    !set rem8=!item 5 of $rem2
    !set rem10=!item 6 of $rem2
    var rem1="$rem1";var rem2="$rem2";var rem3="$rem3";var rem4="$rem4";var rem5="$rem5";var rem6="$rem6";var rem7="$rem7";var rem8="$rem8";var rem9="$rem9";var rem10="$rem10"
    var read_once=0;var data;
    function sendanswer(){
	if(done == 1){
	    if(read_once == 0 ){
		data=document.getElementById("Ballenbak-II").ReadApplet();
		if(data.indexOf('error')!= -1){setAlarm(rem1+"\n"+"\""+data+"\"");return;}
		var e=data.split(',');var t1;var t2;var p;var check=0;
		for( p= 0;p<e.length;p++){
		    t2=e[p];if(t2==0){check++;}
		}
		if(check == e.length){setAlarm(rem6);return;}
		read_once = 1;	
	    }
	    var reply=new Array();var show="<ul>";var rep;var vraagnummer=1;
	    p = 0;
	    while( document.getElementById("myinput"+p) ){
		rep = document.getElementById("myinput"+p).value;
		if(rep.length == 0){setAlarm(r1+"&nbsp;"+vraagnummer);return 0;}
		if(rep.indexOf(',') != -1){setAlarm(r25+" "+vraagnummer+"<br />"+r4);return} 
		rep = rep.toLowerCase();if(check_o(rep)!=1){setAlarm(r25 + " " + vraagnummer +"\n"+ r5);return;} 
		rep = prefix(rep);rep = science(rep);rep = rep.replace(/[a-z\~\`\""\''\@\#\%\_\=\:\;\$$\&\!]/g,'');
		if(rep.length == 0){setAlarm(r2);return;}
	        show=show+"<li>"+description[p]+"&nbsp;=&nbsp;"+rep+"</li>";reply[p] = rep;
		p++;
		vraagnummer++;
	    }
	    show=show+"</ul>";
	    myConfirm(show,reply+","+data,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
	}
	else
	{
	    setAlarm(rem9);return;
	}
    }


    function showme(t){
	if(done == 0){
	    var time=rem3;var freq=rem4;
    	    var d=document.getElementById("Ballenbak-II").ReadApplet();if(d.indexOf('error')!= -1){setAlarm(rem1+"\n"+"\""+d+"\"");return;}
	    var e=d.split(',');var newdiv;var t1;var t2;var p;var check=0;
	    var old = document.getElementById('mydiv');
	    newdiv = document.createElement('div');newdiv.setAttribute("id","mydiv1");newdiv.setAttribute("name","mydiv");
	    var tablebody="<td><b>"+rem8+"</b></td>";
	    var tablehead="<td><b>"+rem7+"</b></td>";

	    for(p=0;p<e.length;p++){
		t1=p+1;t2=e[p];
		tablehead=tablehead+"<td><b>"+t1+"</b></td>";
		tablebody=tablebody+"<td><b>"+t2+"</b></td>";
		if(t2==0){check++;}
	    }
	    if(check == e.length){setAlarm(rem6);return;}
	    newdiv.innerHTML = "<table class=\'grid_table\'><tr>"+tablehead+"</tr><tr>"+tablebody+"</tr></table>";
	    old.appendChild(newdiv);
	    !! now we make applet "invisible": 
	    
	    var app=document.getElementById("Ballenbak-II");
	    !! app.setAttribute((document.all ? "style","visibility" : "hidden"), "hide");
	    !! app.setAttribute((document.all ? "Width" : "0"), "0");
	    app.setAttribute("height","0",0);
	    app.setAttribute("width","0",0);
	    done=1;
	    document.getElementById("Ballenbak-II").stop();
	    document.getElementById("Ballenbak-II").destroy();
	}else{setAlarm(rem9);return;}
    }	
</script>

<object id="Ballenbak-II" width="220" height="100"  classid="java:PlinkoNegativeBinomial.class" type="application/x-java-applet;jpi-version=1.4" ><param name="java_code" value="PlinkoNegativeBinomial.class" /><param name="java_codebase" value="$appletdir" /><param name="java_archive" value="Plinko-II.jar" /><param name="wims_exercise" value="1" /> <param name="xsize" value="$xsize" /><param name="ysize" value="$ysize" /><param name="fontsize" value="12" /><param name="R" value="$var5" /><param name="bins" value="$var1" /><param name="chance" value="$var4" /><param name="speed" value="$var3" /><param name="title" value="Applet created by Dr. D.P. Little" /><param name="language" value="$taal" /><param name="balls" value="$var2" />$nojava</object>
<div id="mydiv" name="mydiv"></div> 
<div id="send_buttond" class="embedded_central">
    <input type="button" id="schaersvoorde_extra_button" onclick="showme();" value="$rem5" />
    <input type="button" id="schaersvoorde_ok_button" onclick="javascript:sendanswer();" value="$send" />
    <input type="button" id="schaersvoorde_nok_button" onclick="javascript:dontknow();"  value="$dontknow" />
</div>




