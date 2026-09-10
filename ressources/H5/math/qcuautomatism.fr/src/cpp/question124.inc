\title{Question 124 NS Calcul avec des rationnels }
\keywords{quizz,skill_calculate}
\observation{Question du sujet zéro sujet-specifique-2_0.pdf publié sur EDUSCOL en juin 2025 }

\matrix{donnees=1/2,1/3,4/3,5/3,8/3,1/6,5/6,2/7,4/7,1/4,2,3,3,3,3,6,6,7,7,4
1/3,1/2,3/2,5/2,7/2,6/5,9/5,6/7,9/7,3/7,3,2,2,2,2,5,5,7,7,7
2/3,1/2,5/2,7/2,9/2,6/5,9/5,6/7,3/7,1/4,3,2,2,2,2,5,5,7,7
5/3,1/2,5/2,7/2,3/4,1/4,6/7,9/7,6/11,9/11,3,2,2,2,4,4,7,7,11,11
8/3,1/2,3/2,5/2,1/4,3/4,3/5,6/5,3/7,6/7,3,2,2,2,4,4,5,5,7,7
1/6,1/2,3/2,5/2,7/2,1/4,3/5,6/5,12/5,6/7,6,2,2,2,2,4,5,5,5,7
5/6,1/2,3/2,5/2,7/2,1/4,3/4,6/5,6/7,6/11,6,2,2,2,2,4,4,5,7,11
2/7,1/2,7/2,1/3,7/3,14/3,1/4,3/4,7/5,7/6,7,2,2,3,3,3,4,4,5,6
4/7,1/2,7/2,1/3,7/3,14/3,1/4,3/4,7/5,7/6,1/2,7,2,2,3,3,3,4,4,5,7}

\text{l=randomrow(\donnees)}
\integer{pos=randint(2..10)}
\rational{a=\l[1]}
\rational{b=\l[\pos]}
\text{atex=texmath(\a)}
\text{btex=texmath(\b)}
\text{enonce=On considère \(A=\atex-\atex \times \btex\).}

\integer{aden=\l[11]}
\integer{anum=\a*\aden}
\integer{bden=\l[9+\pos]}
\integer{bnum=\b*\bden}

\rational{g=\a-\a*\b}
\rational{b1=(\anum-\anum*\bnum==0)? 1:(\anum-\anum*\bnum)/(\aden-\aden*\bden)}   
\rational{b2=(\anum-\anum*\bden==0 or \aden-\aden*\bnum==0)? randitem(-1,2):(\anum-\anum*\bden)/(\aden-\aden*\bnum)}
\rational{b3=0}

\text{good=\(A=texmath(\g)\)}
%%%%%%%%%% 
\text{bad1=\(A=texmath(\b1)\)}
\text{bad2=\(A=\b2\)}
\text{bad3=\(A=\b3\)}
\text{bads=\bad1,\bad2,\bad3}

%%%%%%%%%%
\rational{c=\a*\b}
\text{ctex=texmath(\c)}

\text{feedback=La bonne réponse est \good. <br>On commence par calculer \(\atex \times \btex=\ctex\) puis \(A=\atex-\ctex=texmath(\g)\). }
