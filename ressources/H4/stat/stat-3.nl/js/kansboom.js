!set n=$counter
<script type="text/javascript"  src="$jsdir/../lang/remarks.$taal.js"></script> 
<script type="text/javascript"  src="$jsdir/precheck.js"></script>
<script type="text/javascript">
    var URL;var done=0;
    function dontknow(){
	var t=confirm(r0+"\n$dontknow ?");
	if(t==true){
	    URL = '$wims_ref_name?session=$session&+module=$module&+cmd=reply&+reply$n=%3F' ;
	    document.location.href = URL;if(document.getElementById("KansBoom")){document.getElementById("KansBoom").destroy();}
	}
    }
    function sendanswer(){
	!! read the inputfields
	var len=document.myform.elements.length;var p;var rep;var extra_answer="";
	for(p=0;p<len;p++){
	    rep=document.myform[p].value;
	    !! or rep=document.getElementById('myinput'+p).value;
	    if(rep.length==0){setAlarm(r1+" "+(p+1));return;} 
	    rep=rep.toLowerCase();                                                                                                             
            rep=rep.replace(/[a-z\!~@#$:;=+_]/g,"");
	    if(rep.length==0){setAlarm(r2);return;}
	    extra_answer=extra_answer+"  "+rep;
	}

	var applet_data=document.getElementById("KansBoom").ReadApplet(1);
	applet_data=applet_data.split("@");
	var line_analysis=applet_data[1];
	var reply=applet_data[0];


	!!    <!--- ReadApplet(0) : gives textdata for probability tree -->
	!!    <!-- ReadApplet(whatever) gives all objects and coordinates -->
	!!    <!-- catch some errors before sending the data to wims -->
	!!    <!-- error_1 = unused_line_error -->
	!!    <!-- error_2 = too_few_items_per_line -->
	!!    <!-- error_3 = too_many_items_per_line -->
	!!    <!-- error_4 = inbalance_too_few_lines -->
	!!    <!-- error_5 = inbalance_too_many_lines -->
	!!    <!-- error_6 = text_missing -->
	!!    <!-- error_7 = lines_missing -->
	
	comments=new Array();
	!set comment_array=!record 146 of lang/remarks.$taal
	!set rem0=!record 169 of lang/remarks.$taal
	var rem0="$rem0";
	comments=[$comment_array];
	!! comments=["I have some comments on Your drawing:\n","Your answer (drawing) is empty ???",
	!! "there are lines with no labels or numbers in your probability tree...",
	!! "there are lines with not enough labels or numbers in your sketch...",
	!! "there are lines with more than the nessecary labels and/or numbers in your drawing...",
	!! "there are not enough lines to match the amount of labels/numbers in your answer... ",
	!! "there are too many lines  to match the amount of labels/numbers in your answer... ",
	!! "You have forgotten to write the numbers and names in the tree...",
	!! "You have forgotten to draw lines in the probability tree..."];
	    
	if(reply.length==0){setAlarm(comments[1]);return;}
	var remark="";
	for(p=2;p<comments.length;p++){
	    if(line_analysis.indexOf("error_"+p) != -1){remark="--> "+comments[p];p=100;}
	}
	    
	if(remark.length!=0){setAlarm(rem0+comments[0]+"\n"+remark);return;}
	var t=confirm(r0+"\n"+rep+"\n-----------------\n"+reply);
	if(t==true){
	    !!! reply format with 3 inpitfields: textanswer  textanswer textanswer"," applet_reply_array
	    reply=encodeURIComponent(extra_answer+","+reply);
	    URL = '$wims_ref_name?session=$session&+module=$module&+cmd=reply&+reply$n='+reply ;
	    document.location.href = URL;if(document.getElementById("KansBoom")){document.getElementById("KansBoom").destroy();}
	}
    }
</script>

<table summary="applet">
    <tr>
    <th style="border:1px solid #ff0000">
	<object id="KansBoom" code="KansBoom.class" archive="KansBoom.jar"  codebase="$appletdir" width="$var1" height="$var2" MAYSCRIPT>
	    <param name="xsize" value="$var3"/>
	    <param name="ysize" value="$var4"/>
	    <param name="bgcolor" value="$var5"/>
	    <param name="textcolor" value="$var6"/>
	    <param name="drawcolor" value="$var7"/>
	    <param name="penthickness" value="5"/>
	    <param name="penfontsize" value="22"/>
    	    <param name="penfontstyle" value="BOLD"/>                                                                                         
	    <param name="penfontfamily" value="Courier"/>
	    <param name="language" value="$taal"/>
    	    <param name="textlines" value="$var8"/> <!-- number of lines in the applet: strings are bound to these lines -->                        
    	    <param name="textalign" value="$var9"/> <!-- probability tree orientation -->
	</object>
    </th>
    </tr><tr>
    <th align="center">
	<table summary="reply buttons">
	    <tr>
	    <th align="center">
		<input id="sendbutton" type="button" id="schaersvoorde_ok_button" onclick="javascript:sendanswer();" value="$send" style=""/>
	    <th>
	    <th>
		<input type="button" id="schaersvoorde_ok_button" onclick="javascript:dontknow();"  value="$dontknow"/>
	    </th>
	    </tr>
	</table>
    </th>
    </tr>
</table>
