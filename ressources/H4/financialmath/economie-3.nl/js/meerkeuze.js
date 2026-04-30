!set n=$counter
!set max=!itemcnt $vragen
<script  type="text/javascript">
//<![CDATA[
<!-- no validator  -->
	var max=$max;var reply = new Array();var i = 0;var stop_counting = 0;
	
	function count_down(cnt){
	    if( stop_counting == 0){
		if(cnt == 0 ){cnt = 10;}
		window.setTimeout("tik("+cnt+")", $[($timeout/10)]);
	    }
	    else
	    {
	    	document.getElementById('countdown').value = 'klaar';
	    }
	}
	
	function tik(cnt){
	    cnt = cnt - 1;
	    document.getElementById('countdown').value = cnt;
	    count_down(cnt);
	}
	
	function LoadExercise(){
	    count_down("10");
	    document.getElementById('start_button').style.display = "none"
	    document.getElementById('quit_button').style.display = "block"
	    if(i < max){
		window.setTimeout("LoadExercise()",$timeout);
		document.getElementById('my_th'+i).style.display = "block"
		document.getElementById('my_input'+i).focus();
		if(i>0){
		    document.getElementById('my_input'+(i-1)).disabled = "true";
		    document.getElementById('my_input'+(i-1)).setAttribute("style","background-color:orange");
		}
		i++;
	    }
	    else
	    {
		stop_counting = 1;
		document.getElementById('my_input'+(i-1)).disabled = "true";
		document.getElementById('my_input'+(i-1)).setAttribute("style","background-color:orange");
		sendanswer();
	    }
	}
    
    function sendanswer(){
	var show="<ol>";
	for(var p=0; p<max;p++){
	    document.getElementById('my_input'+p).readOnly = "true"
	    reply[p] = document.getElementById('my_input'+p).value;
	    if(reply[p].length == 0){
		reply[p]="?"
		show = show +"<li>?</li>";
	    }
	    else
	    {
		if(is_real_number(reply[p]) == 0){
		    reply[p]="?";
		    show = show +"<li>?</li>";
		}
		else
		{
		    if(reply[p] == 1){
			show = show + "<li>waar</li>";
		    }
		    else
		    {
			if(reply[p] == 0){
			    show = show + "<li>onwaar</li>";
			}
			else
			{
			    show = show +"<li>$dontknow</li>";
			}
		    }
		}
	    }
	}
	show = show +"</ol>";
	myConfirm(show,reply,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
    
    
//]]>
</script>
<table class="zebra_table_h2">
    <tr>
    <th>
	<input type="text" id="countdown" value="10" size="3" style="text-align:center;font-size:2.0em" />
    </th>
    </tr>
!for p=1 to $max
    <tr>
!set v=!item $p of $vragen
    <td id="my_th$[$p-1]" style="display:none;" nowrap="nowrap" > 
	$p) $v : <select size="1" id="my_input$[$p-1]" class="schaersvoorde_input"><option value="-1">geen idee</option><option value="0">onwaar</option><option value="1">waar</option></select>
    </td>
    </tr>
!next p
    <tr>
    <td id="start_button">
	<a onmouseover="return escape('$helptext')">Druk op </a><input type="button" id="schaersvoorde_extra_button" onclick="LoadExercise();" value="START" />
    </td>
    <td id="quit_button" style="text-align:center;display:none">
	<input type="button" id="schaersvoorde_nok_button" onclick="javascript:dontknow();"  value="$dontknow" />
    </td>
    </tr>
</table>
