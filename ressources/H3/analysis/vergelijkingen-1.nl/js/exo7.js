!! plus teken: img1
!! min teken: img2
!! div1 : f(x) waarden invulsleepveld
!! div0 : x waarden invulsleepveld
!! div2.....div999 : de invulvelden <input size=5 name=reply$n value=$(reply$n)/> met als waarde: reply1
!! wimsvariabele options= aantal div elementen in DHTML 
!! antwoord: x_1,x_2,...x_n,+,x,-,x,+
!! multiple + en - worden gestript (++++x----  => +x- )
<script type="text/javascript">

function my_DropFunc(){
    !! de plus en min plaatjes (img1 en img2) willen we op Y-waarde div0 element hebben
    !! de invulelementen (div2... div_options) willen we op Y-waarde div1 element hebben

    var maxplus=dd.elements.img1.copies.length;
    var maxmin=dd.elements.img2.copies.length;
    var divnum=$options;
    if ( maxplus != maxmin){setAlarm("there is an inbalance in the amount of\n possible copies of the plus.gif and min.gif");return;}
    var delta=dd.elements['div0'].w;
    var corr=0.5*delta;
    delta=0.2*delta;
    var Y0=dd.elements['div0'].y;
    var Y1=dd.elements['div1'].y;
    var Y11=Y1-delta
    var Y12=Y1+delta
    var s;
    var y=dd.obj.y;
    var x=dd.obj.x;
    var moved=0;
    !! we zoeken naar de naam... eerste 3 letters ---> "img" of "div"
    var naam=dd.obj.name;
    naam=naam.substring(0,3);
    if (naam == "img"){
	for ( s=1 ; s<maxplus+1 ; s++){
	    if(y<Y12 && y>Y11){
		dd.obj.moveTo(x,Y0);
		moved=1;
	    }
	    else
	    {
		dd.obj.moveTo(dd.obj.defx,dd.obj.defy);
	    }
	}
    }
    else
    {
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
    tot=new Array();
    var Xmin=dd.elements['div0'].x;
    var w=dd.elements['div0'].w;
    var Xmax=(Xmin+w);
    var maxplus=dd.elements.img1.copies.length;
    var maxmin=dd.elements.img2.copies.length;
    var divnum=$options;
    var taal="$taal";
    var count=0;
    var x;var s;var r;var t;var c;var y;var Ydiv;var Yimg;var w;var W;
    var Y0=dd.elements['div1'].y;
    var Y1=dd.elements['div0'].y;
    var mintekens=new Array();
    var plustekens=new Array();
    var roots=new Array();
    var things=new Array('sin','cos','tan','sqrt','log','abs');
    var numthings=things.length;
    !! het onderste sleepveld (dus de hoogste Ypix-waarde) is bedoeld voor het inslepen van div-elementen (input)
    !! het bovenste sleepveld (dus de kleinste Ypix-waarde) is bedoeld voor het inslepen van img-elementen (plus en min tekens)
    if(Y0>Y1){Ydiv=Y1;Yimg=Y0}else{Ydiv=Y0;Yimg=Y1}
    function mysort(a, b){ return (a-b); }
    var total=new Array();
    s = 0;
    while (document.getElementById("myinput"+s)){
	rep=document.getElementById("myinput"+s).value;
	!! div0 en div1 zijn insleepvelden
	!! div2....div9 zijn input sleep_divs
	r=s+2;
	x=dd.elements['div'+r].x;
	y=dd.elements['div'+r].y;
	!! is het invulveld in de goede positie ?
	if(y == Ydiv){
	    !! filteren van antwoord...alvast
	    c=rep.indexOf(',');
	    if ( c != -1){
		!!!! FIXME this should be in the lang/remarks.$taal file
		if(taal=='nl'){setAlarm("Je kunt beter geen komma\'s gebruiken in je antwoord... \n");}
		if(taal=='fr'){setAlarm("Evitez d\'utiliser des virgules dans votre réponse");}
		if(taal=='en' || taal=='cn'){setAlarm("Better not to use commas in your answer...\n");}
		return ;
	    }
	    rep=rep.toLowerCase();
	    for (t=0;t<numthings;t++){
		w=things[t];
		W=w.toUpperCase();
		rep=rep.replace(w,W);
	    }
	    rep=rep.replace(/[a-z\,\=\@\:\;\#\~\!\ ]/g,'');
	    rep=rep.toLowerCase();
	    if(rep.length==0){
		!!!! FIXME this should be in the lang/remarks.$taal file
		    if(taal=='nl'){setAlarm("Je hebt een invulveld geplaatst, maar nog niet (zinvol ?) ingevuld \n Graag even het nulpunt noteren of (als je vind dat dit nulpunt niet bestaat) \n het invulveld weer terugzetten...\n ");}
		    if(taal=='fr'){"Vous avez mis une inputfield, mais pas encore remplir le vide...\nSil vous plaît remplir le correspondant de la racine ou le lieu inputfield dans sa position d\'origine.";}
		    if(taal=='en' || taal=='cn'){setAlarm("You have placed an inputfield, but not yet filled in \n Please fill in the corresponding root\n or place the inputfield in it\'s original position..\n");}
		    return;
	    }
	    else
	    {
		tot[count]=rep;
		roots[count]=x;
		total[count]=x;
		count=count+1;
	    }
	}
	else
	{
	    if(s==0){
		!!!! FIXME this should be in the lang/remarks.$taal file
		if(taal=="nl"){setAlarm("ATTENTIE \n Je hebt x1 invulveld niet geplaatst \n En niet ingevuld... \n Dit interpreteer ik als:\n \n \n Er zijn geen nulpunten.");}
		if(taal=="fr"){setAlarm("ATTENTION \n Je vais interpréter votre réponse comme:\nIl n\'ya pas de racines ");}
		if(taal=="en" || taal=="cn"){setAlarm("ATTENTION \n You did not place the inputfield(s) \n nor filled in any value for x1  \n I will interpret this as :\n \n \n There are no roots.");}
	    }
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
	    r=r+1;
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
	    t=t+1;
	}
    }
    if( r+t==0){
	!!!! FIXME this should be in the lang/remarks.$taal file
	if(taal=="nl"){setAlarm("Je hebt geen plus of mintekens geplaatst  \n Dat is wel de bedoeling van deze som \n dat je het tekenverloop van de functie beschrijft \n Als je het antwoord niet weet klik dan op \n \"Ik weet het niet\"");}
	if(taal=="fr"){setAlarm("Vous n'avez pas faites glisser les objets \"+\" ou \"-\" à leur place\nLe but de cet exercice est de déterminer la nature de la courbe\nSi vous ne connaissez pas la réponse cliquez: \" $dontknow\"");}
	if(taal=="en" || taal=="cn"){setAlarm("You did not drag the + and/or - signs  \n The intention of this exercise is the analysis of the signs of a function\n  If You don\'t know the answer , just click \n \"I don\'t know\"");}
	return;
    }
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
	    if ( c == x ){
		total[i]='-';
	    }
	}
    }

    var tt=new Array();
    c=0
    y=total.length;
    for ( i=0; i <= y ;i++){
	t=total[i];
	r=total[i+1];
	s=total[i+2];
	w=total[i+3];
	    if ( t != r){
		tt[c]=t
		c=c+1;
	    }
	    else
	    {
		if( t == s && t == w){i=i+3;}
		if( t == r && t != w){i=i+2;}
		switch(t){
		    case '+':tt[c]='+';c=c+1;break;
		    case '-':tt[c]='-';c=c+1;break;
		    case 'x':tt[c]='x';c=c+1;break;
		}
	    }
    }
    tot[count]=tt;
    myConfirm("$send ?",tot,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
}
</script>
