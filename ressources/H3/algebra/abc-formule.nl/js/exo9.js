!! plus teken: img1
!! min teken: img2
!! div1 : f(x) waarden invulsleepveld
!! div0 : x waarden invulsleepveld
!! div2.....div999 : de invulvelden
!! wimsvariabele options= aantal div elementen in DHTML 
!! antwoord: x_1,x_2,...x_n,+,x,-,x,+
!! multiple + en - worden gestript (++++x----  => +x- )

<script  type="text/javascript">
    !set re0=!record 35 of lang/remarks.$taal
    !set re1=!record 36 of lang/remarks.$taal
    !set re2=!record 37 of lang/remarks.$taal
    !set re3=!record 38 of lang/remarks.$taal
    var re0="$re0";var re1="$re1";var re2="$re2";var re3="$re3";

    function my_DropFunc(){
	!! de plus en min plaatjes (img1 en img2) willen we op Y-waarde div0 element hebben
	!! de invulelementen (div2... div_options) willen we op Y-waarde div1 element hebben
	var maxplus=dd.elements.img1.copies.length;var maxmin=dd.elements.img2.copies.length;var divnum=$options;
	if ( maxplus != maxmin){setAlarm("there is an inbalance in the amount of\n possible copies of the plus.gif and min.gif");return;}
	var delta=dd.elements['div0'].w;
	var corr=0.5*delta;delta=0.2*delta;
	var Y0=dd.elements['div0'].y;
	var Y1=dd.elements['div1'].y;
	var Y11=Y1-delta;var Y12=Y1+delta;var s;var y=dd.obj.y;var x=dd.obj.x;var moved=0;
	!! we zoeken naar de naam... eerste 3 letters ---> "img" of "div"
	var naam=dd.obj.name;naam=naam.substring(0,3);
	if (naam == "img"){
	    moved=0;
	    for ( s=1 ; s<maxplus+1 ; s++){
		if(y<Y12 && y>Y11){
		    dd.obj.moveTo(x,Y0);
		    moved=1;
		}
	    }
	    if(moved == 0 ){dd.obj.moveTo(dd.obj.defx,dd.obj.defy);}
	}
	else
	{	
	    moved=0;
	    for ( s=2 ; s<divnum+1 ; s++){
		if(moved==0){
		    if(y<Y12 && y>Y11){
			dd.obj.moveTo(x,Y1);
			moved=1;
		    }
		    else
		    {
			dd.obj.moveTo(dd.obj.defx,dd.obj.defy);
		    }
		}
	    }
	}
    }
    
    function sendanswer(){
	!! we scannen de twee sleepinvul_div_elementen af: div0 en div1
	!! door de my_DropFunc() zijn de plaatjes en invulvelden goed geplaatst
	!! we hoeven die de zaak alleen op x-waarde af te tasten
	reply=new Array();
	var Xmin=dd.elements['div0'].x;
	var w=dd.elements['div0'].w;
	var Xmax=(Xmin+w);
	var maxplus=dd.elements.img1.copies.length;
	var maxmin=dd.elements.img2.copies.length;
	var divnum=$options;
	var count=0;var x;var s;var r;var t;var c;var y;var Ydiv;var Yimg;var w;var W;
	var Y0=dd.elements['div1'].y;var Y1=dd.elements['div0'].y;var mintekens=new Array();var plustekens=new Array();
	var roots=new Array();var things=new Array('sin','cos','tan','sqrt','log','abs');var numthings=things.length;
	!! het onderste sleepveld (dus de hoogste Ypix-waarde) is bedoeld voor het inslepen van div-elementen (input)
	!! het bovenste sleepveld (dus de kleinste Ypix-waarde) is bedoeld voor het inslepen van img-elementen (plus en min tekens)
	if(Y0>Y1){Ydiv=Y1;Yimg=Y0}else{Ydiv=Y0;Yimg=Y1}
	function mysort(a, b){ return (a-b); }
	var total=new Array();
	s=0
	while(document.getElementById("myinput"+s)){
	    rep=document.getElementById("myinput"+s).value;
	    !! div0 en div1 zijn insleepvelden
	    !! div2....div9 zijn input sleep_divs
	    r=s+2;x=dd.elements['div'+r].x;y=dd.elements['div'+r].y;
	    !! is het invulveld in de goede positie ?
	    if(y == Ydiv){
		!! filteren van antwoord...alvast
		c=rep.indexOf(',');if ( c != -1){setAlarm(re0);return;}
		rep=rep.toLowerCase();
		for (t=0;t<numthings;t++){
		    w=things[t];
		    W=w.toUpperCase();
		    while(rep.indexOf(w)!=-1){
			rep=rep.replace(w,W);
		    }
		}
		rep=rep.replace(/[a-z\,\=\@\:\;\#\~\!\ ]/g,'');rep=rep.toLowerCase();
		if(rep.length==0){
		    setAlarm(re1);return;
		}
		else
		{
		    reply[count]=rep;
		    roots[count]=x;
		    total[count]=x;
		    count++;
		}
	    }
	    else
	    {
		if(s==0){setAlarm(re2);}
	    }
	    s++;
	}
	!! de plustekens
	r=0;
	for (p=0;p<maxplus;p++){
	    y=dd.elements['img1'].copies[p].y;
	    if ( y == Yimg){
		x=dd.elements['img1'].copies[p].x;
		plustekens[r]=x;
		total[count+r]=x;
		r++;
	    }
	}
	!! de mintekens
	t=0;
	for (p=0;p<maxplus;p++){
	    y=dd.elements['img2'].copies[p].y;
	    if ( y == Yimg){
		x=dd.elements['img2'].copies[p].x;
		mintekens[t]=x;
		total[count+r+t]=x;
		t++;
	    }
	}
	if( r+t==0){setAlarm(re3);return;}
	!! sort numerical
	!!plustekens=plustekens.sort( mysort );
	!!mintekens=mintekens.sort( mysort );
	total=total.sort(mysort);
	y=total.length;
	for ( s=0 ; s<count ;s++){
	    x=roots[s];
	    for ( i=0; i<y ;i++){
		c=total[i];
		if ( c == x ){
		    total[i]='x';
		}
	    }
	}
	for ( s=0 ; s<r ;s++){
	    x=plustekens[s];
	    for ( i=0; i<y ;i++){
		c=total[i];
		if ( c == x ){
		    total[i]='+';
		}
	    }
	}
	for ( s=0 ; s<t ;s++){
	    x=mintekens[s];
	    for ( i=0; i<y ;i++){
		c=total[i];
		if ( c == x){
		    total[i]='-';
		}
	    }
	}
	var list = total[0];
	for(p=1 ; p<total.length;p++){
	    list = list +","+total[p]
	}
	while( list.indexOf('-,-') != -1 ){
	    list = list.replace('-,-','-');
	}
	while( list.indexOf('+,+') != -1 ){
	    list = list.replace('+,+','+');
	}
	myConfirm("$send ?",reply+","+list,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
    }
</script>
