<script  type="text/javascript">
//<![CDATA[ 
  function my_Confirm(){
   var tmp;var show="<ol>";
   for(var p =0; p < $inputs ; p++){
    tmp = document.getElementById('myinput'+p).value;
    if( tmp.length < 1 ){setAlarm( r1+" "+parseInt(p+1) );return;}
    show = show+"<li>"+description[p]+" = "+tmp+"</li>";
   }
   show = show + "</ol>";
   var h = parseInt( (document.documentElement.clientHeight)/2);
   var w = parseInt( (document.documentElement.clientWidth)/2 - 200);
   document.getElementById('alarmtext').style.top = h+'px';
   document.getElementById('alarmtext').style.left = w+'px';
   document.getElementById('alarmtext').style.display = 'block';
   window.scrollTo(w,h-120);
   document.getElementById('alarmtext').innerHTML=r0+show+
   "<input type=\"button\" id=\"schaersvoorde_confirm_ok_button\" value=\""+r45+"\" onclick=\"javascript:do_it(1);\" />"+
   "&nbsp;&nbsp;"+
   "<input type=\"button\" id=\"schaersvoorde_confirm_nok_button\" value=\""+r46+"\" onclick=\"javascript:do_it(0);\" \>";
  }

  function do_it(t){
    if( t == 1 ){
     document.getElementById('schaersvoorde_exercise').setAttribute('style','background-color:$ok_send_color');
     sendanswer(1);
    }
    else
    {
	document.getElementById('schaersvoorde_exercise').setAttribute('style','background-color:$nok_send_color');
	resetAlarm();
    }
  }
  
  function sendanswer(t){
    var wimschem = document.getElementById('WIMSchem');
    var my_svg = wimschem.getSVG("1");
    var chem_data = document.getElementById("chem_data");
    var appletinfo = wimschem.ReadApplet();
    if(appletinfo.indexOf("error")!= -1){setAlarm(appletinfo);return;}
    var reply = ""
    if( t == 0 ){ // dontknow
      for(var p = 0; p < $inputs ; p++){
        reply = reply + "?\n";
      }
      chem_data.value = my_svg+"\n"+reply+appletinfo;
    }
    else
    {
      var tmp= "";
      for(var p = 0; p < $inputs ; p++){
        tmp = document.getElementById('myinput'+p).value;
        if( tmp.length < 1 ){setAlarm(r1);return;}
        reply = reply +tmp+"\n";
      }
      chem_data.value = my_svg+"\n"+reply+appletinfo;
    }
    wimschem.stop();
    wimschem.destroy();
    document.getElementById("chem_form").submit();
    return;
  }
//]]> 
</script>


<form id="chem_form" action="$wims_ref_name?form-data$session" method="post" enctype="multipart/form-data" >
 <input type="hidden" name="session" value="$session" />
 <input type="hidden" name="lang" value="nl" />
 <input type="hidden" name="cmd" value="reply" />
 <input type="hidden" name="module" value="$module" />
 <input type="hidden" id="chem_data"  name="reply$n" value="" />


!set n=$counter
<div class="embedded_central">
<object id="WIMSchem"  width="380" height="240" classid="java:WIMSchem.MainApplet.class" type="application/x-java-applet;jpi-version=1.4">
    <param name="java_code" value="WIMSchem.MainApplet" />
    <param name="java_archive" value="WIMSchem.jar" />
    <param name="java_codebase" value="$module_dir/docs" /><!-- use new svg applet -->
    <param name="use_zoom" value="1" />
    <param name="language" value="$taal" />
    <param name="formattype" value="latex" />
    <param name="TOOL_CURSOR" value="no" />
    <param name="TOOL_ROTATOR" value="no" />
    <param name="TOOL_ERASOR" value="no" />
    <param name="TOOL_DIALOG" value="no" />
    <param name="TOOL_EDIT" value="no" />
    <param name="TOOL_SETATOM" value="no" />
    <param name="TOOL_SINGLE" value="no" />
    <param name="TOOL_DOUBLE" value="no" />
    <param name="TOOL_TRIPLE" value="no" />
    <param name="TOOL_ZERO" value="no" />
    <param name="TOOL_INCLINED" value="no" />
    <param name="TOOL_DECLINED" value="no" />
    <param name="TOOL_UNKNOWN" value="no" />
    <param name="TOOL_CHARGE" value="no" />
    <param name="TOOL_UNDO" value="no" />
    <param name="TOOL_REDO" value="no" />
    <param name="TOOL_TEMPLATE" value="no" />
    <param name="TOOL_CUT" value="no" />
    <param name="TOOL_COPY" value="no" />
    <param name="TOOL_PASTE" value="no" />
    <param name="MENU_BLOCK" value="no" />
    <param name="MENU_SELECT" value="no" />
    <param name="MENU_TRANSFORM" value="yes" />
    <param name="MENU_ZOOM" value="yes" />
    <param name="MENU_SHOW" value="no" />
    <param name="MENU_HYDROGEN" value="no" />
    <param name="MENU_STEREO" value="no" />
    <param name="MENU_HELP" value="no" />
    $nojava
    </object>
!if $inputs>1
<table class="zebra_table_h2">
!for p=1 to $inputs
    <tr>
    <td>
	<kbd>$(description[$p])</kbd>
    </td>
    <td>:
    </td>
    <td>
	<input type="text" id="myinput$[$p-1]" class="schaersvoorde_input" size="$cols" value="" />
    </td>
    </tr>
!next p
</table>
  <input type="button" id="schaersvoorde_ok_button" value="$send" onclick="javascript:my_Confirm();" />
  <input type="button" id="schaersvoorde_nok_button"  value="$dontknow" onclick="javascript:sendanswer(0);" />
</div>
</form>
<script type="text/javascript">
//<![CDATA[ 
    var molecule=$var1;
    document.getElementById('WIMSchem').SetMoleculeNative(molecule);
//]]> 
</script>

!exit

