
<script language="JavaScript" type="text/javascript">
 "use strict";
 var student_boxplot=new Array(5);
 var show="";var shown=false;
 function showboxplot(){
  var tmp;
  for(var p=0;p<5;p++){
   tmp = document.getElementById('myinput'+p).value;
   if(is_real_number(tmp) == 0){return;}
   student_boxplot[p] = tmp;
   show=show+"<br/>"+description[p]+" = "+tmp;
  };
   document.getElementById('boxplot').style.display = "block";
   draw_boxplot(195,1,5.00,5.00,[0,0,0,0,0],2,"0,0,255",0.78,"255,165,0",0.30,1,0,4,4);
   shown=true;
  };
  function sendanswer(){
   var timeout=10;
   if(!shown){showboxplot();timeout=1000;};
   setTimeout("myConfirm(show,student_boxplot,'$wims_ref_name','$session','$module','$counter','$ok_send_color')",timeout);
  }
</script>
<div id="return_buttons" class="embedded_central">
    <input type="button" id="schaersvoorde_extra_button" onclick="javascript:showboxplot();" value="showboxplot" />
    <input type="button" id="schaersvoorde_ok_button" onclick="javascript:sendanswer();" value="$send" />
    <input type="button" id="schaersvoorde_nok_button" onclick="javascript:dontknow();"  value="$dontknow" />
</div>
 
