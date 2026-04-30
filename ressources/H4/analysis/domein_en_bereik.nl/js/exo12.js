!!! special file exclusive for this exercise
!!! avoids the well known "WIMS unmatching parenthesis user-error"
!!! allowing <-5 : 6 ] U [7 : +inf> as an answer...

<script type="text/javascript">
var taal="$taal";

function sendanswer(){
    !set rem1=!record 69 of lang/remarks.$taal
    !set rem2=!record 66 of lang/remarks.$taal
    !set rem3=!record 67 of lang/remarks.$taal
    !set rem4=!record 68 of lang/remarks.$taal
    !set rem5=!record 65 of lang/remarks.$taal
    !set rem6=!record 71 of lang/remarks.$taal
    !set rem7=!record 72 of lang/remarks.$taal
    !set rem8=!record 73 of lang/remarks.$taal
    !set rem9=!record 74 of lang/remarks.$taal
    !set rem10=!record 75 of lang/remarks.$taal
    !set rem11=!record 76 of lang/remarks.$taal
    var rem1="$rem1";var rem2="$rem2";var rem3="$rem3";var rem4="$rem4";var rem5="$rem5";var rem6="$rem6";var rem7="$rem7";var rem8="$rem8";var rem9="$rem9";var rem10="$rem10";var rem11="$rem11";
    var tot='';
    var input=document.getElementById('myinput0').value;
    var l=input.length;
    if(l==0){setAlarm(rem2);return;}
    var test=input.indexOf(',');
    if(test !=-1){setAlarm(rem5);return;}
    test=input.replace(/\ /g,'');
    !! eerst testen op R\{a} --> omzetten naar intern formaat
    !! daarna op alleen R --> omzetten naar <-inf:inf>
    !! daarna antwoord in interval notatie [0:8>
    var test1=test.indexOf('R\\{');var test2=test.indexOf('R');var test3=test.indexOf('R/');var test4=test.indexOf('R\\');
    if(test2 !=-1 && test1 == -1){if(test3 != -1 || test4 != -1 ){setAlarm(rem8);return;}}
    if(test1 != -1){test=test.toLowerCase();test=test.replace(/[a-z\~\`\""\''\{\}\@\#\%\_\=\$$\&\!\\]/g,'');tot="langle,mininfty,s,"+test+",rangle,U,langle,"+test+",s,plusinfty,rangle";}
    else{if (test2 != -1){tot="langle,mininfty,s,plusinfty,rangle"}
    else{tot=input.toLowerCase();
	!! enkele syntaxtesten...
	test1=tot.indexOf(':');test2=tot.indexOf(';');if(test1+test2 <0){setAlarm(rem9);return;}
	test=tot.indexOf('x');if(test != -1){setAlarm(rem6);return;}
	test=tot.indexOf('y');if(test != -1){setAlarm(rem7);return;}
	test=tot.indexOf('r');if(test != -1){setAlarm(rem11);return;}
	tot=tot.replace(/\ /g,'');
	test3=tot.indexOf('<');test4=tot.indexOf('[');if(test3+test4<-1){setAlarm(rem10);return;}
	test3=tot.indexOf('>');test4=tot.indexOf(']');if(test3+test4<-1){setAlarm(rem10);return;}
	test3=tot.length;if(test3<5){setAlarm(rem10);return;}
	tot=tot.replace(/\-inf/g,',MININFTY,');tot=tot.replace(/\-on/g,',MININFTY,');tot=tot.replace(/\+inf/g,',PLUSINFTY,');
	tot=tot.replace(/\+on/g,',PLUSINFTY,');tot=tot.replace(/inf/g,',PLUSINFTY,');tot=tot.replace(/:/g,',S,');tot=tot.replace(/;/g,',S,');
	!!!! FIXME this should better be in the remarks.lang files !!!!
	tot=tot.replace(/of/g,',U,');tot=tot.replace(/en/g,',U,');
	tot=tot.replace(/or/g,',U,');tot=tot.replace(/and/g,',U,');
	tot=tot.replace(/ou/g,',U,');tot=tot.replace(/et/g,',U,');
	!!!! FIXME this should better be in the remarks.lang files !!!!
	tot=tot.replace(/u/g,',U,');tot=tot.replace(/v/g,',U,');tot=tot.replace(/\&&/g,',U,');tot=tot.replace(/\&/g,',U,');tot=tot.replace(/\]\+\[/g,']U[');tot=tot.replace(/\>\+\[/g,'>U[');tot=tot.replace(/\]\+\</g,']U<');tot=tot.replace(/\>\+\</g,'>U<');
        tot=tot.replace(/\</g,',LANGLE,');tot=tot.replace(/\>/g,',RANGLE,');tot=tot.replace(/\[/g,',LBRACKET,');tot=tot.replace(/\]/g,',RBRACKET,');tot=tot.replace(/,,/g,',');tot=tot.replace(/[a-z\~\`\""\''\@\#\%\_\=\$$\&\!]/g,'');
        l=tot.length;test=tot.substring(0,1);if(test==','){tot=tot.substring(1,l);l=tot.length;}
	test=tot.substring(l-1,l);if(test==','){tot=tot.substring(0,l-1);}tot=tot.toLowerCase();
	}
    }
    myConfirm(rem1+'<br />'+input,tot,'$wims_ref_name','$session','$module','$counter','$ok_send_color');
}
</script>

