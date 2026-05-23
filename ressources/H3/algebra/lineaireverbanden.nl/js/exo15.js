<script type="text/javascript"  src="$jsdir/geogebra2wims.js"></script>
<script type="text/javascript">
    var list_of_things=new Array();
    !if $list_of_things=$empty 
	!! A list of all possible object names
	list_of_things=['text','point','line','segment','circle','function','polygon','conic','ellipse','polynomial','vector','number','angle'];
    !else
	list_of_things=$list_of_things
    !endif
    function sendanswer(){
	var table_answer=new Array();
	var show="";var ans;
	var p = 0;
	while( document.getElementById("myinput"+p)){
	    ans=document.getElementById("myinput"+p).value;
	    if(ans.indexOf(",") !=-1){setAlarm(r4);return;}
	    if(ans.length == 0){setAlarm(r1+" "+(p+1));return;}
	    ans=ans.toLowerCase();
	    ans=ans.replace(/[\~\!\@\#\:\;]/g,"");
	    if(ans.length == 0){setAlarm(thisform[p].value+" ... "+r2);return;}
	    table_answer[p]=ans;
	    show=show+"&nbsp;&nbsp;&nbsp;&nbsp;"+ans;
	    p++;
	}
	var reply=geogebra2wims(list_of_things);
	myConfirm(show,reply+','+table_answer,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }

</script>
!set n=$counter
<object classid="java:geogebra.GeoGebraApplet.class" type="application/x-java-applet;jpi-version=1.4" id="ggbApplet" name="ggbApplet" width="180" height="50" >
    <param name="java_code" value="geogebra.GeoGebraApplet" />
    <param name="java_codebase" value="java/geogebra" />
    <param name="java_archive" value="geogebra.jar" />
    <param name="type" value="button" />
    <param name="language" value="$taal"/>
    <param name="filename" value="../../$module_dir/$ggb"/>
    <param name="showToolBar"  value="$showToolBar"/>
    <param name="showMenuBar"  value="$showMenuBar"/>
    <param name="framePossible" value="$framePossible"/>
    <param name="customToolBar" value=$customToolBar/>
    <param name="showAlgebraInput" value="$showAlgebraInput"/>
    $nojava
</object>
<script type="text/javascript">
//<![CDATA[
<!-- no validator  -->
    var xml =new String(document.getElementById("ggbApplet").getXML());
    var old1=new String("<axis id=\"0\" label=\"x-axis\" unitLabel=\"\" showNumbers=\"true\"/>");
    var new1=new String("<axis id=\"0\" label=\"$var1\" unitLabel=\"\" showNumbers=\"true\"/>");
    var old2=new String("<axis id=\"1\" label=\"y-axis\" unitLabel=\"\" showNumbers=\"true\"/>");
    var new2=new String("<axis id=\"1\" label=\"$var2\" unitLabel=\"\" showNumbers=\"true\"/>");
    xml=xml.replace(old1,new1);
    xml=xml.replace(old2,new2);
    document.getElementById("ggbApplet").setXML(xml);
//]]>
</script>
