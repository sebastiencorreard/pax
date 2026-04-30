<script type="text/javascript">
  function sendanswer(){
   var reply = [];var rep;
   var idx = 0; var show = "{";
   while( document.getElementById("mathml"+idx) ){
    rep = document.getElementById("mathml"+idx).value;
    if(rep.length == 0 ){ rep = "leeg";};
    if( rep.indexOf('?') != -1 ){rep = "?";};
    if( rep.indexOf(',') < 1 ){ rep = words2items(rep); };
    show = show.concat(rep);
    reply[idx] = rep.replace(/\,/g,'\n');
    idx++;
   };
   show = show.concat('}');
   myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
  };
</script>

