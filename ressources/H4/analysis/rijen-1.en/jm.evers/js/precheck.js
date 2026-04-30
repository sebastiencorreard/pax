
function check_s(t){
    t=t.replace(/\*\*/g,'^');
    t=t.replace(/x10/g,'*10')
    e=t.indexOf('e');
    cc=['0','1','2','3','4','5','6','7','8','9'];
    var c0;var c1;var t0;var t1;var c;var a;
    while(e!=-1){
	t0=t.charAt(e-1);
	t1=t.charAt(e+1);
	t2=t.charAt(e+2);
	c0=0;c1=0;
	for(p=0;p<10;p++){a=cc[p];if(t0==a){c0=1;}}
	for(p=0;p<10;p++){a=cc[p];if(t1==a){c1=1;}}
	if(c0==0 && c1==1){t=t.replace('e','10^');}
	if(c0==0 && c1==0 && t1=="+"){t=t.replace('e+','10^');}
	if(c0==0 && c1==0 && t1=="-"){t=t.replace('e-','10^-');}
	if(c0==0 && c1==0 && t1==""){t=t.replace('e','E');}
	if(c0==1 && c1==1){t=t.replace('e','*10^');}
	if(c0==1 && c1==0 && t1=="+"){t=t.replace('e+','*10^');}
	if(c0==1 && c1==0 && t1=="-"){t=t.replace('e-','*10^-');}
	if(c0==1 && c1==0 && t1==""){t=t.replace('e','E');}
	t=t.replace('e','E');
	e=t.indexOf('e');
    }
    t=t.replace(/E/g,"e");
    t=t.replace(/10\^0/g,"10^");
    return t;
}

function check_o(t){
    var dingen=['1','2','3','4','5','6','7','8','9','0','.','+','-','*','/','^','=',' '];
    var ld=dingen.length;var t2;var d;
    var os=['o','O'];var o;
    for(s=0;s<2;s++){
	o=os[s];t1=t.indexOf(o)
	while(t1!=-1){
	    if(t1<1){t2='a';}else{t2=t.charAt(t1-1);}
	    t3=t.charAt(t1+1);if(t3!=" " && t2!=" "){for(p=0;p<ld;p++){d=dingen[p];if(t3==d || t2==d){alert(r5);return 0;}}}
	    t=t.replace(o,'0');t1=t.indexOf(o);
	}
    }
    return 1;
}

function check_f(t){
    t=t.replace(/log\[/g,'#');
    t=t.replace(/sqrt\[/g,'#');
    var ft;var ismatch;var fun;var F;var t2;var c0;var functies=['log','ln','abs','sqrt','sin','cos','tan','atan','acos','sinh','cosh','tanh'];
    ft=functies.length;
    for(s=0;s<ft;s++){
	fun=functies[s];ismatch=t.indexOf(fun);F=fun.toUpperCase();c0=fun.length;
	while(ismatch != -1 ){
	    c=c0+ismatch;t2=t.substring(c,c+1);
	    if(t2=='('){t=t.replace(fun,F);ismatch=t.indexOf(fun);}else{alert(r9);return 0;}
	}
    }
    return 1;
}

function check_x(t){
    var dingen=['1','2','3','4','5','6','7','8','9','0'];
    var t2;var t3;var d;var chk;
    t1=t.indexOf('x');
    while(t1>0){
	chk=0;
	t2=t.charAt(t1-1);
	t3=t.charAt(t1+1);
	for(s=0;s<10;s++){
	    d=dingen[s];
	    if(t2==d){chk=chk+1;}if(t3==d){chk=chk+1;}
	}
	if(chk==2){alert(r7);return 0;}
	t=t.replace('x','*');t1=t.indexOf('x');
    }
    return 1;
}

function specialroot(t){
    var power;var sqrt;var begin;var end;var mod;var tot;var wait;var got;var chr;var t1;var t2;var t3;var t4;var test;var org;
    t2=t.indexOf("](");if(t2==-1){alert(r11);t="error";return t;}
    org=t;t=t.replace(/sqrt\(/g,"SQRT(");
    t=t.replace(/log\[/g,"LOG~");t=t.replace(/sqrt\[/g,"@[");test=t.replace(/[a-z]\[/g,"#");
    if(test.indexOf("#")!=-1){alert(r11);t="error"; return t;}
    t2=t.indexOf("[");var trouble=0;
    while(t2 != -1){
	begin=t.indexOf("@");t2=t.indexOf("[");t3=t.indexOf("]");
	if(t2==begin+1 && t3>t2){
	    power=t.substring(t2+1,t3);
	    if(power.length==0){alert(r16);t="error";return t;}
	    if(power<2){alert(r16);t="error";return t;}
	    t4="["+power+"]";t=t.replace(t4,'');
	    tot=t.length;wait=0;got=0;end=0;
	    for(s=begin;s<tot;s++){
		if(end==0){
		    chr=t.charAt(s);
		    if(chr=="("){wait=wait+1;}
		    if(chr==")"){got=got+1;}
		    if(got!=0){if(wait==got){end=s;}}
		}
	    }
	    begin=begin+2;
	    sqrt=t.substring(begin,end);
	    mod=(power % 2);
	    if(sqrt<0 && mod!=1){alert(r16);t="error";return t;}
	    t=t.replace("@("+sqrt+")","("+sqrt+")^(1/"+power+")");
	}
	else{t=t.replace("]","?");}
	trouble++;
	if(trouble>100){alert(r20);t=error;return t;}
    }
    t=t.replace(/SQRT\(/g,"sqrt(");t=t.replace(/LOG~/g,"log[");t=t.replace(/~/g,"[");t=t.replace(/\?/g,"]");t=t.replace(/@/g,"sqrt");
    return t;
}
    
function speciallog(t){
    var noemer;var teller;var begin;var end;var tot;var wait;var got;var chr;var t1;var t2;var t3;var t4;
    t2=t.indexOf("](");if(t2==-1){alert(r11);t="error";return t;}
    t=t.replace(/log\(/g,'LOG(');
    t=t.replace(/log/g,"@");
    t2=t.indexOf("[");
    while(t2 != -1){
    begin=t.indexOf("@");t3=t.indexOf("]");
    if(t2==begin+1 && t3>t2){
	grondtal=t.substring(t2+1,t3);
	if(grondtal=="10"){alert(r14);t="error";return t;}
	if(grondtal=="e" || grondtal=='E'){alert(r15);t="error";return t;}
	t4="["+grondtal+"]";t=t.replace(t4,'');
	tot=t.length;wait=0;got=0;end=0;
	for(s=begin;s<tot;s++){
	    if(end==0){
		chr=t.charAt(s);
		if(chr=="("){wait=wait+1;}
		if(chr==")"){got=got+1;}
		if(got!=0){if(wait==got){end=s;}}
	    }
	}
	begin=begin+2;teller=t.substring(begin,end);
	if(grondtal==teller){alert(r17);}
	t=t.replace("@("+teller+")","(~("+teller+")/~("+grondtal+"))");
	}else{t=t.replace("[","%");}
	t2=t.indexOf("[");
    }
    t=t.replace(/\%/g,"[");t=t.replace(/~/g,"log");t=t.replace(/LOG\(/g,"log(");t=t.replace(/@/g,"log");
    return t;
}

function check_log_NaN(t){
    t=t.replace(/log\(/g,'@(');if(t.indexOf('@')==-1){return 1;}
    if(t.indexOf('--')!=-1 || t.indexOf('++')!=-1 ){alert(r18);return 0;}
    dingen=['@','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'];
    begin=t.indexOf('@');var exp;var variable;var trouble=0;
    while(begin != -1){
	t1=t.indexOf('(');
	t2=t.indexOf(')');
	if(t1=begin+1 && t2>t1){
	    tot=t.length;wait=0;got=0;end=0;
	    for(s=begin;s<tot;s++){
		if(end==0){
		    chr=t.charAt(s);
		    if(chr=="("){wait=wait+1;}
		    if(chr==")"){got=got+1;}
		    if(got!=0){if(wait==got){end=s;}}
		}
	    }
	    begin=begin+2;exp=t.substring(begin,end);p=0;variable=0;
	    while(p<27){v=dingen[p];w=exp.indexOf(v);if(w!=-1){p=27;variable=1;}p++;}
	    if(variable==0){test=eval(exp);if(test<=0){alert(r16);return 0;}}
	    t=t.replace('@(','log(');begin=t.indexOf('@');
	}else{return 1;}
	trouble++;
	if(trouble>100){alert(r20);t=error;return t;}
    }
    return 1;
}

function check_sqrt_NaN(t){
    t=t.replace(/sqrt\(/g,'@(');if(t.indexOf('@')==-1){return 1;}
    if(t.indexOf('--')!=-1 || t.indexOf('++')!=-1 ){alert(r18);return 0;}
    dingen=['@','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'];
    begin=t.indexOf('@');var exp;var variable;var trouble=0;
    while(begin != -1){
	t1=t.indexOf('(');
	t2=t.indexOf(')');
	if(t1=begin+1 && t2>t1){
	    tot=t.length;wait=0;got=0;end=0;
	    for(s=begin;s<tot;s++){
		if(end==0){
		    chr=t.charAt(s);
		    if(chr=="("){wait=wait+1;}
		    if(chr==")"){got=got+1;}
		    if(got!=0){if(wait==got){end=s;}}
		}
	    }
	    begin=begin+2;exp=t.substring(begin,end);p=0;variable=0;
	    while(p<27){v=dingen[p];w=exp.indexOf(v);if(w!=-1){p=27;variable=1;}p++;}
	    if(variable==0){test=eval(exp);if(test<0){alert(r16);return 0;}}
	    t=t.replace('@(','sqrt(');begin=t.indexOf('@');
	}else{return 1;}
	trouble++;
	if(trouble>100){alert(r20);t=error;return t;}
    }
    return 1;
}

