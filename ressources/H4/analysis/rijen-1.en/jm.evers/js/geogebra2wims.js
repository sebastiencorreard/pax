// the next is all very text-based and largely depending on the strings GeoGebra sends us
// so barely mathematics...and likely to change with other versions of the applet. 

function geogebra2wims(list_of_things) {
    var debug=0;var totalobject_count=0;var point_count=0;var line_count=0;var circle_count=0;var segment_count=0;var polygon_count=0;
    var function_count=0;var polynomial_count=0;var conic_count=0;var ellipse_count=0;var hyperbola_count=0;var vector_count=0;var angle_count=0;var text_count=0;
    var test;var points_of_polygon;var a,b,c,d,e,f,g,h,n,x,y,p,max,r,s,t,i,it,whatisit,broken_up_string,browser,thing,listcnt,def,name
    var reply='';var total = new Array();var data = new Array();
    if (document.applets[0].getAllObjectNames()){total=document.applets[0].getAllObjectNames();}else{total=['T1','T2','T3','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','z','y','z','\u03b1','\u03b2','\u03b3','\u03b4','\u03b5','\u03b6','\u03b7','\u03b8','\u03b9','\u03c0','\u03c1','\u03c2','\u03c3','\u03c4','\u03c5','\u03c6','\u03c7','\u03c8','\u03c9','\u03d0','\u03d1','\u03d2','\u03d3','\u03d4','\u03d5','\u03d6','a1','b1','c1','d1','a2','b2','c2','d2','a3','b3','c3','d3','a4','b4','c4','d4','a5','b5','c5','d5','A1','A2','A3','A4','B1','B2','B3','B4','P1','P2','P3','P4','R1','R2','R3','R4','S1','S2','S3','S4','X1','X2','X3','X4','Y1','Y2','Y3','Y4','a_1','b_1','c_1','d_1','e_1','f_1','g_1','h_1','g_1','h_1','l_1','k_1','A_1','A_2','A_3','A_4','B_1','B_2','B_3','B_4','P_1','P_2','P_3','P_4','R_1','R_2','R_3','R_4','S_1','S_2','S_3','S_4','X_1','X_2','X_3','X_4','Y_1','Y_2','Y_3','Y_4'];}
    max=total.length;if(debug=='1'){alert('list_of_things to check = '+list_of_things);}
    listcnt=list_of_things.length;
    for ( i=0 ; i < max ; i++){
	thing = total[i];whatisit=document.applets[0].getObjectType(thing);points_of_polygon='';def=document.applets[0].getCommandString(thing);
	test=def.match("Polygon");
	if (test !=null){def=encodeURIComponent(def);points_of_polygon=def.replace(/Polygon/g,'');points_of_polygon=points_of_polygon.replace(/\%5B/g,'');points_of_polygon=points_of_polygon.replace(/\%5D/g,'');points_of_polygon=points_of_polygon.replace(/\%2C\%20/g,'@');points_of_polygon=decodeURIComponent(points_of_polygon);}
	for ( p=0 ; p < listcnt ; p++){
	    it=list_of_things[p];
	    if (it==whatisit){
		data=document.applets[0].getValueString(thing);data=encodeURIComponent(data);
		if (it=="circle"){data=data.replace(/%C2%B2/g,'@');} else {data=data.replace(/%C2%B/g,'^');}data= decodeURIComponent(data);
		if (data.indexOf("_") != 2 ){
		    totalobject_count=totalobject_count + 1;
		    if (it=="point"){x=document.applets[0].getXcoord(thing);y=document.applets[0].getYcoord(thing);data='point@'+thing+'@'+x+'@'+y ;point_count=point_count + 1;}  
		    else if (it=="circle"){ data=data.replace(/\=/g,'');t=data.length;c=data.indexOf(':');data=data.substring(c+1,t);broken_up_string=data.replace(/[x-y]/g,'');broken_up_string = broken_up_string.split("@");x = broken_up_string[0];y = broken_up_string[1];d = broken_up_string[2];if (x==' ' || x==' + ' || x==' - '){x=0;}if (y==' ' || y==' + ' || y==' + '){y=0;}if (d==' '){d=0;}x='-1*('+x+')';y='-1*('+y+')';circle_count=circle_count+1;data='circle@'+thing+'@'+x+'@'+y+'@'+d;}
		    else if (it=="line"){t=data.length;n=data.indexOf(':');f=data.indexOf('=');d=data.indexOf('x');e=data.indexOf('y');if (d >0 && e >0){a=data.substring(n+1,d);a=a.replace(/\ /g,"");if(a=='x'){a='1';}if(a==''){a='1';}if(a=='-'){a='-1';}b=data.substring(d+1,e);b=b.replace(/\ /g,"");if(b=='+'){b='1';}if(b=='-'){b='-1';}c=data.substring(f+1,t);r='(-1*('+a+')/('+b+'))';q='('+c+')/('+b+')';}else if (d >0 ){c=data.substring(f+1,t);r='perp';q='x='+c;}else {c=data.substring(f+1,t);r='0';q=c;}data='line@'+thing+'@'+r+'@'+q;line_count=line_count + 1;}
    		    else if (it=="polygon"){polygon_count=polygon_count + 1;data=data.replace(/\=/g,'@');data='polygone@'+data+'@'+points_of_polygon;}
    		    else if (it=="segment"){segment_count=segment_count + 1;data='segment@'+data;}	
    		    else if (it=="function"){function_count=function_count + 1;data='function@'+data;}
    		    else if (it=="polynomial"){polynomial_count=polynomial_count + 1;data='polynomial@'+data;}
    		    else if (it=="conic"){conic_count=conic_count + 1;data='conic@'+data;}
    		    else if (it=="ellipse"){ellipse_count=ellipse_count + 1;data='ellipse@'+data;}
    		    else if (it=="hyperbola"){hyperbola_count=hyperbola_count + 1;data='hyperbola@'+data;}
    		    else if (it=="text"){text_count=text_count + 1;data='text@'+data;}
    		    else if (it=="angle"){data = data.split("=");name = data[0];data = data[1];angle_count=angle_count + 1;data=name+'@'+data;}
    		    else if (it=="vector"){x=document.applets[0].getXcoord(thing);y=document.applets[0].getYcoord(thing);data='vector@'+thing+'@'+x+'@'+y ;vector_count=vector_count + 1;}
		    else {alert ('object type with name: '+thing+'... is not in my list, please add: ' + it);}
		    reply=reply + data + ',' ;
		    if(debug=='1'){alert ('we add the variable data to the URL string :' +data);}
		}			
	    }
	}
    }
    // lost track about this ...
    reply=reply.replace(/undefined/g,'');
    reply=reply.replace(/%C2%B/g,'^');
    reply=reply.replace(/%CE%B/g,'angle@');
    reply=reply.replace(/\^0/g,' degree');
    reply=totalobject_count+','+point_count+','+circle_count+','+line_count+','+segment_count+','+polygon_count+','+conic_count+','+ellipse_count+','+hyperbola_count+','+angle_count+','+vector_count+','+function_count+','+polynomial_count+','+text_count+','+reply;
    // if some inputarea is present and it is inside a  <form name="sendtext"> than read this as well
    // and append it to the "geogebra string" as "text="+txt
    if(document.forms['sendtext']){var txt; var l=document.forms['sendtext'].length;for(p=0;p<l;p++){t=document.forms['sendtext'].elements[p].value;if(p==0){txt=t;}else{txt=txt+','+t;}} reply=reply+"text="+txt;}
    return reply;
}

