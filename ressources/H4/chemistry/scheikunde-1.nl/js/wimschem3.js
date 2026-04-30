<!-- MDLmol formaat -->
!set n=$counter

<form id="chem_form" action="$wims_ref_name?form-data$session" method="post" enctype="multipart/form-data" >
 <input type="hidden" name="session" value="$session" />
 <input type="hidden" name="lang" value="nl" />
 <input type="hidden" name="cmd" value="reply" />
 <input type="hidden" name="module" value="$module" />
 <input type="hidden" id="chem_data"  name="reply$n" value="" />
 <script  type="text/javascript">
//<![CDATA[ 
  function my_Confirm(){
   var wimschem = document.getElementById('WIMSchem');
   var your_svg = wimschem.getSVG("1");
   var h = parseInt( (document.documentElement.clientHeight)/2);
   var w = parseInt( (document.documentElement.clientWidth)/2 - 200);
   document.getElementById('alarmtext').style.top = h+'px';
   document.getElementById('alarmtext').style.left = w+'px';
   document.getElementById('alarmtext').style.display = 'block';
   window.scrollTo(w,h-120);
   document.getElementById('alarmtext').innerHTML=r0+"<hr />"+your_svg+"<hr />"+
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
    var my_svg = wimschem.getSVG("2");
    var chem_data = document.getElementById("chem_data");
    if( t == 0 ){ // dontknow
     chem_data.value = my_svg+"\n?"+"\n?";
    }
    else
    {
     var your_svg = wimschem.getSVG("1");
     var mdmol = wimschem.GetMoleculeMDLMol();    
     if( document.getElementById('myinput0') ){
      var p = 0;var reply = new Array();
       while( document.getElementById('myinput'+p) ){
        reply[p] = document.getElementById('myinput'+p).value;
        p++;
       }
       chem_data.value = my_svg+"\n"+your_svg+"\n"+reply+"\n"+mdmol;
     }
     else
     {
       chem_data.value = my_svg+"\n"+your_svg+"\n"+mdmol;
     }
    }
    wimschem.stop();
    wimschem.destroy();
    document.getElementById("chem_form").submit();
    return;
  }
//]]> 
 </script>
 <div class="embedded_central">
  <object id="WIMSchem"  width="640" height="400" classid="java:WIMSchem.MainApplet.class" type="application/x-java-applet;jpi-version=1.4" >
    <param name="java_code" value="WIMSchem.MainApplet" />
    <param name="java_codebase" value="$module_dir/docs" /><!-- use new svg applet -->
    <param name="java_archive" value="WIMSchem.jar" />
    <param name="language" value="$taal" />
    <param name="use_zoom" value="0" />
    <param name="wims_ref_name" value="$wims_ref_name" />
    <param name="session" value="$session" />
    <param name="module" value="$module" />
    <param name="atom_button_row" value="1" />
    <param name="replyarguments" value="reply$counter" />
    <param name="file2" value="$wims_ref_name?session=$session&cmd=getfile&special_parm=$var1" />
    <param name="show_hydrogen" value="1" />
    <param name="show_carbon" value="1" /> 
    <param name="TOOL_TEMPLATE" value="yes" />
    $var2
!if $wims_user=supervisor
    <param name="file" value="$wims_ref_name?session=$session&cmd=getfile&special_parm=$var1" />
    <param name="showfile" value="yes" />
!endif
    $nojava
  </object>
 !if $inputs>0
  <table class="zebra_table_h2" >
  !for p=1 to $inputs
   <tr>
    <td> <kbd>$(description[$p])</kbd></td>
    <td> <input type="text" id="myinput$[$p-1]" class="schaersvoorde_input" size="$cols" value="" /></td>
   </tr>
  !next p
  </table>
 !endif
  <br />
  <input type="button" id="schaersvoorde_ok_button" value="$send" onclick="javascript:my_Confirm();" />
  <input type="button" id="schaersvoorde_nok_button"  value="$dontknow" onclick="javascript:sendanswer(0);" />
 </div>
</form>

!exit

