<script  type="text/javascript"  src="$jsdir/../lang/remarks.$taal.js"></script>
<script type="text/javascript"  src="$jsdir/precheck.js"></script>
<script  type="text/javascript"  src="$jsdir/zirkel2wims.js"></script> 
!set n=$counter

<script  type="text/javascript">
    var URL;

    function dontknow(){
	t=confirm(r0+"\n$dontknow ?");
	if(t==true){
	    URL = '$wims_ref_name?session=$session&+module=$module&+cmd=reply&+reply$n=%3F' ;
	    document.location.href = URL;if(document.getElementById("zirkel")){document.getElementById("zirkel").destroy();}
	}
    }

    function sendanswer(){
	if(document.getElementById("zirkel")){var appletid=document.getElementById("zirkel").id;if(appletid=="CaR"){applet=1;}}
	if(applet==1){
	    var total=new Array;
	    var data=new Array;
	    !set s=!linecnt $var1
	    !for p=0 to $[$s-1]
		!set L=!line $[$p+1] of $var1
		data[$p]=document.getElementById("zirkel").getDrawing( $L );    
	    !next p
	    !!data =document.getElementById("zirkel").getDrawing("line","line1,line2,line3");
	    !! applet: polygon=x=1:y=2:x=3:y=6...
	    setAlarm(data);
	    var v=data.length;
	    if(v==0){setAlarm(r1);return;}
	    var sum="";
	    for (p=0;p<v;p++){
		t=data[p];
		if(p!=0){sum=t+":"+sum}else{sum=t;}
	    }
	    total[0]=sum;
	}

	if(document.mydefaultform){
	    var ml=document.mydefaultform.elements.length;
	    var total=new Array;
	    var input;var v;var z;
	    var inputfieldnumber=0;
	    for(z=0;z<ml;z++){
		if(document.mydefaultform[z].id=="myinput"){
		    input=document.mydefaultform[z].value;
		    v=input.length;if (v==0){var qu=z+1; setAlarm(r1+"\ "+qu);return;}
		    input=nthroot(input);if(input=="error"){return;}
		    if(input.indexOf(',')!=-1){setAlarm(r4);return;}
		    if(check_f(input)==0){return;}if(check_o(input)==0){return;}
		    if(check_log_NaN(input)==0){return;}if(check_sqrt_NaN(input)==0){return;}
		    input=science(input);if(check_x(input)==0){return;}
		    t1=input.indexOf("[");
		    if(t1 !=- 1){
			if(input.indexOf("sqrt[")!=-1){input=specialroot(input);if(input=="error"){return;}}
			if(input.indexOf("log[")!=-1){input=speciallog(input);if(input=="error"){return;}}
			t1=input.indexOf("[");if(t1!=-1){setAlarm(r13);return;}
		    }
		    input=input.replace(/#/g,' ');
		    total[inputfieldnumber]=input;
		    inputfieldnumber=inputfieldnumber+1;
		}
	    }
	    v=total.length;if(v==0){setAlarm(r1);return;}
	}
	var t=confirm(r0+"\n"+total);
	if(t==true){total=encodeURIComponent(total);URL = '$wims_ref_name?session=$session&+module=$module&+cmd=reply&+reply$n='+total ;document.location.href = URL;if(applet==1){document.getElementById("zirkel").destroy();}}
    }
</script>
$(object$n)
<table summary="buttons">
    <tr>
    <th>
        <input type="button" id="schaersvoorde_ok_button" onclick="javascript:sendanswer();" value="$send" />
    </th>
    <th>
	<input type="button" id="schaersvoorde_ok_button" onclick="javascript:dontknow();"  value="$dontknow" />
    </th>
    </tr>
</table>
