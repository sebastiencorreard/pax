!!! viewer
!set n=$counter
!set width=300
!set height=300
!set scale_svg=0.5

<iframe width="$width" height="$height" id="ketcher_iframe" src="$module_dir/ketcher/ketcher.iframe.viewer.html" >NO IFRAMES ? </iframe>

<script type="text/javascript">
 var iframe = document.getElementById('ketcher_iframe');
 var wims_config = {
 new:'no',
 open:'no',
 save:'no',
 undo:'no',
 redo:'no',
 cut:'no',
 copy:'no',
 paste:'no',
 zoom_in:'yes',
 zoom_out:'yes',
 lasso:'no',
 clear:'no',
 wims_template:'no',
 wims_bonds:'no',
 wims_chain:'no',
 wims_charge_plus:'no',
 wims_charge_min:'no',
 wims_sgroup:'no',
 wims_rgroup:'no',
 atom_table:'no',
 zoom_list_cell:'no',
 reaction_menu:'no',
 main_toolbar:'no',
 toolText:'no',
 rotate_tool:'no',
 wims_no_warning:true,
 wims_atom_button_fontsize:'24',
 wims_atoms:null,
 ketcher_div:{'width':'$width','height':'$height'},
 template_index_url:null,
 load_from_url:"$wims_ref_name?session=$session&cmd=getfile&special_parm=file$counter.mol"
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
ignoreMouseEvents:true, /* viewer mode */
selectionDistanceCoefficient:0.4
};

function sendanswer(t){
 var p=0;var tmp;var reply=[];var my_svg;
 if(t != 0 ){
 while(document.getElementById('myinput'+p)){
   tmp = document.getElementById('myinput'+p).value;
   if( tmp.length < 1 ){setAlarm(r1);return;}
    reply[p] = tmp;
    p++;
  };
 }
 else
 {
  reply[0]='?';  reply[1]='?';  reply[2]='?';
 }
 my_svg = iframe.contentWindow.getSVG($scale_svg);
 var chemdata = document.getElementById('chem_data');
 /* return mass+"\n"+brutto+"\n"+brutto_html; */
 var brutto_mass = iframe.contentWindow.getBrutto();
 chemdata.value = reply + '\n' + brutto_mass + '\n' + my_svg;
 document.getElementById("chem_form").submit();
};

</script>
<form id="chem_form" action="$wims_ref_name?form-data$session" method="post" enctype="multipart/form-data" >
 <input type="hidden" name="session" value="$session" />
 <input type="hidden" name="lang" value="nl" />
 <input type="hidden" name="cmd" value="reply" />
 <input type="hidden" name="module" value="$module" />
 <input type="hidden" id="chem_data"  name="reply$n" value="" />

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
 <input type="button" id="schaersvoorde_ok_button"  value="$send" onclick="javascript:sendanswer(1);" />
 <input type="button" id="schaersvoorde_nok_button" value="$dontknow" onclick="javascript:sendanswer(0);" />
                                                                                                                  
</form>   
 
</script>

