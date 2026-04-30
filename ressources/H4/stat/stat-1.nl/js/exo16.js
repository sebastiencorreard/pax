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
	var reply=geogebra2wims(list_of_things);
	var test=reply.split(",");var found_nothing=0;
	for(var p=0;p<test.length;p++){
	    if(test[p] == 0){found_nothing++;}
	}
	if(found_nothing == test.length){setAlarm(r1+" $counter");return;}
	myConfirm("$send",reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>

<object classid="java:geogebra.GeoGebraApplet.class" type="application/x-java-applet;jpi-version=1.4" id="ggbApplet" name="ggbApplet" width="164" height="48" ><param name="java_code" value="geogebra.GeoGebraApplet" /><param name="java_codebase" value="java/geogebra" /><param name="java_archive" value="geogebra.jar" /><param name="language" value="$taal" /><param name="type" value="button" /><param name="language" value="$taal"/><param name="filename" value="../../$module_dir/$ggb"/><param name="showToolBar"  value="$showToolBar"/><param name="showMenuBar"  value="$showMenuBar"/><param name="framePossible" value="$framePossible"/><param name="customToolBar" value="$customToolBar"/><param name="showAlgebraInput" value="$showAlgebraInput"/>$nojava</object>
<script type="text/javascript">
    $appletcommand
</script>
