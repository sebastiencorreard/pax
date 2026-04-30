<script type="text/javascript">
  function sendanswer(){
	var reply = document.getElementById("sinus").ReadApplet();
	if(reply.length == 0){setAlarm("THE APPLET DID NOT RESPOND\nPLEASE LOOK AT THE JAVA CONSOLE\nTO DEBUG THIS");return;}
	var sdata = reply.split(',');
	var show = sdata[$var1];
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
  }
</script>
