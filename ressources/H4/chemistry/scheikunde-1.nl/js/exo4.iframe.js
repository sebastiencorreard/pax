!set n=$counter
!set width=500
!set height=400
!set scale_svg=0.5
!if $template_index_url=$empty
 !set template_index_url=null
!endif
!if wims_atoms=$empty
 !set wims_atoms=['C','H','N','O','S','P','Br','Cl','F']
!endif

<iframe id="ketcher_iframe" src="$module_dir/ketcher/ketcher.iframe.html" width="$width" height="$height" >NO IFRAMES ? </iframe>
<script type="text/javascript">
 var wims_config = {
 new:'no',
 open:'yes',
 save:'yes',
 undo:'yes',
 redo:'yes',
 cut:'yes',
 copy:'yes',
 paste:'yes',
 zoom_in:'yes',
 zoom_out:'yes',
 lasso:'yes',
 clear:'yes',
 wims_template:'yes',
 wims_bonds:'yes',
 wims_chain:'yes',
 wims_charge_plus:'no',
 wims_charge_min:'no',
 wims_sgroup:'no',
 wims_rgroup:'no',
 atom_table:'no',
 zoom_list_cell:'no',
 reaction_menu:'no',
 main_toolbar:'yes',
 toolText:'yes',
 rotate_tool:'no',
 wims_no_warning:true,
 wims_atom_button_fontsize:'24',
 wims_atoms:$wims_atoms,
 ketcher_div:{'width':'$width','height':'$height'},
 template_index_url:'$template_index_url',
 load_from_url:null
};

var wims_opts = {
showSelectionRegions:false,
showAtomIds:false,
showBondIds:false,
showHalfBondIds:false,
showLoopIds:false,
showValenceWarnings:false,
autoScale:false,
autoScaleMargin:0,
atomColoring:1,
hideImplicitHydrogen:false, /* false=shows ending CH3 , true=shows ending C */
hideTerminalLabels:false, /* true : will show never carbon */
ignoreMouseEvents:false, /* viewer mode */
selectionDistanceCoefficient:0.4
};
var molfile,your_svg,my_svg;
var answer = "$wims_ref_name?session=$session&cmd=getfile&special_parm=$var1";
var iframe = document.getElementById('ketcher_iframe');

function my_Confirm(){
 your_svg = iframe.contentWindow.getSVG($scale_svg);
 document.getElementById('alarmtext').style.display = 'block';
 document.getElementById('alarmtext').innerHTML=r0+"<hr />"+your_svg+"<hr />"+ 
 "<input type=\"button\" id=\"schaersvoorde_confirm_ok_button\" value=\""+r45+"\" onclick=\"javascript:do_it(1);\" />"+ 
 "&nbsp;&nbsp;" + "<input type=\"button\" id=\"schaersvoorde_confirm_nok_button\" value=\""+r46+"\" onclick=\"javascript:do_it(0);\" \>";
};

function do_it(t){
 if( t == 1 ){
  molfile = iframe.contentWindow.getMolfile();
  your_svg = iframe.contentWindow.getSVG($scale_svg);
  iframe.contentWindow.loadFromURL(answer);
  iframe.setAttribute('width','0px');
  iframe.setAttribute('height','0px');
  document.getElementById('schaersvoorde_exercise').setAttribute('style','background-color:$ok_send_color');
  setTimeout('sendanswer()',1000);
 }
 else
 {
  document.getElementById('schaersvoorde_exercise').setAttribute('style','background-color:$nok_send_color');
  resetAlarm();
 };
};

function No_idea(){
 document.getElementById('schaersvoorde_exercise').setAttribute('style','background-color:$nok_send_color');
 iframe.contentWindow.loadFromURL(answer);
 molfile='?';
 your_svg='?';
 iframe.setAttribute('width','0px');
 iframe.setAttribute('height','0px');
 setTimeout('sendanswer()',1000);
};
 
function sendanswer(){
 my_svg = iframe.contentWindow.getSVG($scale_svg);
 var chemdata = document.getElementById('chem_data');
 chemdata.value = my_svg + '\n' + your_svg+'\n'+ molfile;
 document.getElementById("chem_form").submit();
};
</script>

<form id="chem_form" action="$wims_ref_name?form-data$session" method="post" enctype="multipart/form-data" >
 <input type="hidden" name="session" value="$session" />
 <input type="hidden" name="lang" value="nl" />
 <input type="hidden" name="cmd" value="reply" />
 <input type="hidden" name="module" value="$module" />
 <input type="hidden" id="chem_data"  name="reply$n" value="" />
</form>

 <input type="button" id="schaersvoorde_ok_button" value="$send" onclick="javascript:my_Confirm();" />
 <input type="button" id="schaersvoorde_nok_button"  value="$dontknow" onclick="javascript:No_idea();" />
