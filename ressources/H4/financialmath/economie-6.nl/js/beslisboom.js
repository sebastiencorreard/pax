!! nu DOM compatibel, en zonder innerHTML !!
<script language="JavaScript" type="text/javascript">
//<![CDATA[
<!-- no validator  -->
    !set n=$counter
    function sendanswer(){
	var reply=new Array();
	var show="";
	var tmp = document.getElementById('FlyApplet').ReadText();
	tmp = tmp.split(',');
	for(var p = 0 ; p < tmp.length - 1 ;p = p + 2){
	    x=tmp[p]+"";
	    y=tmp[p+1]+"";
	    show=show+"<br />("+x+":"+y+")";
	    if(is_number(x) != 1){return;}
	    if(is_number(y) != 1){return;}
	    reply[p] = x +","+y;
	}
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
//]]>
</script>

$var8
