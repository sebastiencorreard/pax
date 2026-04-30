!! special file exclusive for this DHTML exercise
!! div0 is ontvangende div
!! div1= input1
!! div2= input2
!! div3= input3
!! div4= input4
!! image names: [ 'plusinfty' , 'mininfty' , 'langle' , 'rangle' , 'lbracket' , 'rbracket' , 'S' , 'U' ,'D' ] 
<script type="text/javascript">
!! synchroniseer my_DropFunc en sendanswer
var names=new Array('plusinfty' , 'mininfty' , 'langle' , 'rangle' , 'lbracket' , 'rbracket' , 'S' , 'U' , 'div1' , 'div2' , 'div3' , 'div4' );
var n=names.length;
function my_DropFunc()
{
    var Xmin=dd.elements['div0'].x
    var w=dd.elements['div0'].w
    var Xmax=Xmin+w;
    var wobj=dd.elements['langle'].w
    var Y0=dd.elements['div0'].y;
    var h=dd.elements['div0'].h;
    var Yc=Y0
    var delta=30;var test;var testx;var testy;var z;
    var Y01=Y0-delta
    var Y02=Y0+delta
    var y=dd.obj.y;
    var x=dd.obj.x;
    var xm1=0;var xm2=0; 
    var d=35;
    var done=0;
    if(y<Y02 && y>Y01 && x>Xmin && x<Xmax){
    !! zoek een plaatje dat te dicht bij staat dus binnen x-w ... x+w
	for(var t = 0;t < n; t++){
	    obj = names[t];
	    test = obj.substring(0,3)
	    if(test == 'div' && done == 0){
		!! divs don not have copies
		testy = dd.elements[obj].y;
		if(testy == Yc && done == 0){
		    !! dus dit object staat als ingevuld
		    testx = dd.elements[obj].x;
		    if(testx > x-d && testx < x+d){
		    !! er ligt dus een ander plaatje in de buurt
			xm1=testx + wobj + 1;
			if(xm1 > xm2){xm2 = xm1;}
		    }
		}
	    }
	    else
	    {
		if(done == 0){
		    z = dd.elements[obj].copies.length;
		    for(var f = 0; f < z; f++){
			if(done == 0){
			    testy = dd.elements[obj].copies[f].y;
			    if(testy == Yc){
				testx = dd.elements[obj].copies[f].x;
				if(testx > x-d && testx < x+d){
				    xm1 = testx + wobj +1;
				    if(xm1>xm2){xm2 = xm1;}
				}
			    }
			}
		    }
		}
	    }
	}
	if(xm2==0){dd.obj.moveTo(x,Yc);}else{dd.obj.moveTo(xm2,Yc)};
    }
    else
    {
	dd.obj.moveTo(dd.obj.defx,dd.obj.defy);
    }
}

function sendanswer(){
    !set rem1=!record 62 of lang/remarks.$taal
    !set rem2=!record 63 of lang/remarks.$taal
    !set rem3=!record 64 of lang/remarks.$taal
    !set rem4=!record 65 of lang/remarks.$taal
    !set rem5=!record 66 of lang/remarks.$taal
    !set rem6=!record 67 of lang/remarks.$taal
    !set rem7=!record 68 of lang/remarks.$taal
    var rem1="$rem1";var rem2="$rem2";var rem3="$rem3";var rem4="$rem4";var rem5="$rem5";var rem6="$rem6";var rem7="$rem7";
    var Xmin=dd.elements['div0'].x;
    var w=dd.elements['div0'].w;
    var Xmax=(Xmin+w);
    var Y=dd.elements['div0'].y;
    var count=0;var ready;
    var tot=new Array();
    var showanswer1="unicode:\t";var showanswer2="ascii:\t";
    var obj;var test;var val;var ls;;
    var Y0=dd.elements['div0'].y;
    var h=dd.elements['div0'].h;
    var Yc=Y0
    var m1;var m2;var s;var z;var ding1;var ding2;var sepcnt=0;var bndcnt=0;
    !! scannen van links naar rechts
    for(width = Xmin; width < Xmax;width=width+4){
    !! 68 loops...
	m1=width-2;
	m2=width+2;
	ready=0;
	for(s = 0;s < n ; s++){
	    if(ready == 0){
		obj = names[s];
		test = obj.substring(0,3)
		if(test=='div'){
		    !! divs do not have copies
		    y=dd.elements[obj].y;
		    if(y == Yc){
			x = dd.elements[obj].x;
			if(x>m1&&x<m2){
			    num=obj.substring(3,4);
			    num=num-1;
			    val=document.getElementById('myinput'+num).value;
			    if(val.length == 0){setAlarm(rem2);return;}
			    if(val.indexOf(',') !=-1){setAlarm(rem4);return;}
			    val=val.replace(/[a-z\~\@\#\$\%\\&\_\=\:\,\;\(\)]/g,'');
			    if(val.length == 0){setAlarm(rem3);return;}
			    tot[count]=val;
			    count++;
			    ready=1;
			    showanswer1=showanswer1+val;
			    showanswer2=showanswer2+val;
			}
		    }
		}
		else
		{
		    z = dd.elements[obj].copies.length;
		    for(var t = 0; t < z; t++){
			y = dd.elements[obj].copies[t].y;
			if(y == Yc){
			    x=dd.elements[obj].copies[t].x;
			    if(x>m1 && x<m2){ 
				tot[count]=obj;
				count=count+1;
				ready=1;
				switch(obj){
				    case 'langle':ding1=' \u2991 ';ding2=' < ';bndcnt++;break;
				    case 'rangle':ding1=' \u2992 ';ding2=' >';bndcnt++;break;
				    case 'lbracket':ding1=' [ ';ding2='[ ';bndcnt++;break;
				    case 'rbracket':ding1=' ] ';ding2=' ]';bndcnt++;break;
				    case 'mininfty':ding1=' -\u221E ';ding2=' -inf ';break;
				    case 'plusinfty':ding1=' +\u221E ';ding2=' +inf ';break;
				    case 'S':ding1=' : ';ding2=' : ';sepcnt++;break;
				    case 'U':ding1=' U ';ding2=' U ';break;
				} 
				showanswer1=showanswer1+ding1;showanswer2=showanswer2+ding2;
			    }
			}
		    }
		}
	    }
	}
    }
    if(tot.length == 0){setAlarm(rem5);return;}
    if(sepcnt == 0){setAlarm(rem6);return;}
    if(bndcnt < 2){setAlarm(rem7);return;}
    myConfirm(rem1+"<br />"+showanswer1+"<br />"+showanswer2,tot,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
}
</script>
