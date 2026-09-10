\title{Question 104 NS Résolution de problème }
\keywords{quizz,mental_calculation,pbsolving}
\observation{Question du sujet zéro sujet-specifique-3_0.pdf publié sur EDUSCOL en juin 2025 }
%%%%%%%%%Question 6 %%%%%%%%%%%%%%%%%%%%%%%
\real{a6=randint(10,10,10,6,8,9)}
\real{unite6=random(0.60,0.70,0.80,0.90)}
\integer{c6=\a6=8?2:3}
\text{c6t=slib(numeration/ecriturelettre \c6)}
\real{rep=\c6*\unite6}
\real{b6=\a6*\unite6}
\text{enonce=\(\a6\) stylos coûtent en tout \(\b6\)&euro;.<br> Le prix de \c6t stylos est égal à&nbsp;&#58;  }
\text{enonceb=&euro;}
\text{good=\rep euros}
\real{bad1=\rep+randomitem(0.3,0.25,0.20)*randomitem(-1,1)}
\real{bad2=\rep+\c6}
\real{bad3=\bad1+\c6}
\text{bads= \bad1 euros,\bad2 euros,\bad3 euros}
\text{feedback=La bonne réponse est <b>\good</b>. <br>Par une division&#44; un stylo coûte \unite6 &euro;. Il reste ensuite à effectuer <span class="nowrap">\(\c6\times \unite6=\rep\).</span>}
