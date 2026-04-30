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

var answer = "$wims_ref_name?session=$session&cmd=getfile&special_parm=$var1";
var ketcher_popup = null;
var isopen = false;

function open_ketcher_popup(){
 isopen = true;
 ketcher_popup = window.open('$module_dir/ketcher/ketcher.popup.html','ketcher_popup','width=$width,height=$height,left=0px,top=0px,id=ketcher_wims_window');
};

var molfile,your_svg,my_svg;
var answer = "$wims_ref_name?session=$session&cmd=getfile&special_parm=$var1";

function sendme(){
  ketcher_popup.loadFromURL(answer);
  your_svg="?";
  molfile="?";
  setTimeout(' ketcher_popup.close();sendanswer()',1000);

}
function noidea(){
 document.getElementById('schaersvoorde_exercise').setAttribute('style','background-color:$nok_send_color');
 if( !isopen ){
  ketcher_popup = window.open('$module_dir/ketcher/ketcher.popup.html','','toolbar=no,status=no,menubar=no,scrollbars=no,resizable=no,left=100000, top=100000, width=10, height=10, visible=none');
  isopen = true;
 }
  setTimeout('sendme()',1000);
 
};
function my_Confirm(){
 if( isopen ){
 your_svg = ketcher_popup.getSVG($scale_svg);
 document.getElementById('alarmtext').style.display = 'block';
 document.getElementById('alarmtext').innerHTML=r0+"<hr />"+your_svg+"<hr />"+ 
 "<input type=\"button\" id=\"schaersvoorde_confirm_ok_button\" value=\""+r45+"\" onclick=\"javascript:do_it(1);\" />"+ 
 "&nbsp;&nbsp;" + "<input type=\"button\" id=\"schaersvoorde_confirm_nok_button\" value=\""+r46+"\" onclick=\"javascript:do_it(0);\" \>";
 }
 else
 {
  setAlarm(r33);return;  
 }
};

function do_it(t){
 if( t == 1 ){
  molfile = ketcher_popup.getMolfile();
  your_svg = ketcher_popup.getSVG($scale_svg);
  ketcher_popup.loadFromURL(answer);
  ketcher_popup.close();
  document.getElementById('schaersvoorde_exercise').setAttribute('style','background-color:$ok_send_color');
  setTimeout('sendanswer()',1000);
 }
 else
 {
  document.getElementById('schaersvoorde_exercise').setAttribute('style','background-color:$nok_send_color');
  resetAlarm();
 };
};

function sendanswer(){
  my_svg = ketcher_popup.getSVG($scale_svg);
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

 <input type="button" id="schaersvoorde_extra_button" value="open Chemical Editor" onclick="javascript:open_ketcher_popup();" />
 <input type="button" id="schaersvoorde_ok_button" value="$send" onclick="javascript:my_Confirm();" />
 <input type="button" id="schaersvoorde_nok_button"  value="$dontknow" onclick="javascript:noidea();" />
