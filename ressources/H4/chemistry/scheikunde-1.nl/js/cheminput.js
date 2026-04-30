!set n=$counter
<script type="text/javascript">
//<![CDATA[
<!-- no validator  -->

!if $wims_user=supervisor and $var6>0
    !set ans=!lines2items $(answer$n)
    var answers = make_description("$ans",null);
    var p = 0;
    while(document.getElementById('myinput'+p)){
	document.getElementById('myinput'+p).value = answers[$p];
	p++;
    }
!endif
    function sendanswer(){
	!set rem1=!record 30 of lang/remarks.$taal
	!!@Je bent de chemische formule(s) vergeten\nin de applet in te vullen...
	var rem1="$rem1";
	var reply=new Array();
	var show="";var rep;var p=0
	!if $var6 != 0
	while(document.getElementById('myinput'+p)){
	    rep = document.getElementById('myinput'+p).value;
	    if(rep.length == 0){setAlarm(r1+" "+q);return;}
	    if(rep.indexOf(',') != -1){setAlarm(r25+" "+q+"\n"+r4);return;}
	    rep=science(rep);
	    reply[p] = rep;
	    show = show+rep+"<br />";
	    p++
	}
	!endif
	var A = document.getElementById('ChemInput').ReadAnswer();
	var H = document.getElementById('ChemInput').ReadHtml();
	//var L = document.getElementById('ChemInput').ReadLatex();
	if(A.length == 0){setAlarm(rem1);return;}
	reply[p]=A;
	reply[p+1]=H;
	//reply[p+1]=L;
	show=show+"<hr />"+H;
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
//]]>
</script>
<div class="emvedded_central">
!if $var6 >0
<table class="zebra_table_h2">
    !for p=1 to $var6
    <tr>
    <td>
	$(description[$p])
    </td>
    <td>
	:
    </td>
    <td>
	<input type="text" size="$cols" id="myinput$[$p-1]" class="schaersvoorde_input" value="" />
    </tr>
    </tr>
    !next p
</table>
!endif

<object id="ChemInput" classid="java:MiniInputApplet.class" type="application/x-java-applet;jpi-version=1.4" width="640" height="100">
<param name="java_code" value="MiniInputApplet.class" />
<param name="java_codebase" value="$appletdir" />
<param name="java_archive" value="ChemInput.jar" />
<param name="applettext" value="$applettext" /><-- latex wims question  ; default empty -->
<param name="lang" value="$taal" /><!-- default en ; options nl,fr -->
<param name="fontsize" value="$largefont" /><!-- default 18 -->
<param name="frame_width" value="$xsize" /><!-- initial width of popup window ; is user resizable -->
<param name="frame_height" value="$ysize" /><!-- initial height of popup window ; is user resizable  -->
<param name="pencolor" value="0,0,255,0.8" /><!-- default black  ; R,G,B,alpha -->
<param name="pencolor" value="0,0,255,1" /><!-- default black  ; R,G,B,alpha -->
<param name="#fffff0" value="250,240,240,1.0" /><!-- canvas bgcolor;default white ; R,G,B,alpha -->
<param name="#fffff0" value="10,255,10,0.5" /><!-- active typing bar; default green ;R,G,B,alpha -->
<param name="#a0f0g0" value="250,240,225,0.2" /><!-- menubbar color; default white ;R,G,B,alpha -->		
<param name="chembuttons" value="1" /><!-- Default 1/yes ; options 0/no ; shows a few arrows-->
<param name="navbuttons"  value="1" /><!-- Default 1/yes ; options 0/no ; shows a few navigation buttons -->
$nojava
</object>
</div>
