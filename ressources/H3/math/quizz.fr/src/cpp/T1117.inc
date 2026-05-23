\title{Question T1117 Résolution graphique d'inéquation}
\keywords{mental_calculation,functions,inequalities}

#include "T11courbe01.inc"

\text{fig17=<img src="\courbe01" alt="">}
\integer{choix=randint(2..(rows(\valeurs)-1))}
\integer{k=\valeurs[\choix;1]}
\real{sol1=\valeurs[\choix;2]}
\real{sol2=\valeurs[\choix;3]}
\real{sol3=\valeurs[\choix;4]}
\text{ante17=\sol1,\sol2,\sol3}
\real{img17=round(10*evalue(\f01,x=\k))/10}

\text{listerep=&#93;,&#91;,-&infin;,+&infin;,&empty;,&#59;,\ante17,&cap;,&cup;,\img17 }
\integer{typineg=randint(1..4)}
\text{ineg=<,&le;,>,&ge;}
\if{\typineg==1}{\text{temp17=&#93;,\sol1,&#59;,\sol2,&#91;,&cup;,&#93;,\sol3,&#59;,+&infin;,&#91;}}
\if{\typineg==2}{\text{temp17=&#91;,\sol1,&#59;,\sol2,&#93;,&cup;,&#91;,\sol3,&#59;,+&infin;,&#91;}}
\if{\typineg==3}{\text{temp17=&#93;,-&infin;,&#59;,\sol1,&#91;,&cup;,&#93;,\sol2,&#59;,\sol3,&#91;}}
\if{\typineg==4}{\text{temp17=&#93;,-&infin;,&#59;,\sol1,&#93;,&cup;,&#91;,\sol2,&#59;,\sol3,&#93;}}
%%% feedback %%%%
\text{texttypineg=strictement au dessous,au dessous ou sur,strictement au dessus,au dessu ou sur}

\text{rep=\temp17;\listerep}
\text{size=50x35x11}
\text{enonce=On considère une fonction \(f) définie sur \(\mathbb{R}) dont la courbe est dessinée ci-dessous. <br><table><tr><td>\fig17 </td><td> L'ensemble des solutions de l'inéquation \(f(x)\ineg[\typineg] \k\) est : </td></tr></table>  }
\text{enonceb= <div class="wims_instruction">Faire glisser les vignettes bleues pour former la réponse.</div>}
\text{feedback=C'est toutes les abscisses des points de la courbe qui sont \texttypineg[\typineg] de la droite d'équation \(y=\k\).}

%%%%%% pour course anstype=mark
\text{enoncebcourse= <div class="wims_instruction">Marquer la bonne réponse en cliquant dessus.</div>}
\text{listerepcourse=&#93; \sol1  &#59;   \sol2 &#91; &cup; &#93; \sol3  &#59;  +&infin; &#91; &nbsp; &nbsp;  &nbsp; &nbsp;,  &#91;\sol1 &#59; \sol2 &#93; &cup; &#91; \sol3 &#59; +&infin; &#91;  &nbsp; &nbsp;  &nbsp; &nbsp;, &#93;-&infin; &#59; \sol1 &#91; &cup; &#93; \sol2 &#59; \sol3 &#91;  &nbsp; &nbsp; , &#93;-&infin; &#59; \sol1 &#93; &cup; &#91; \sol2 &#59; \sol3 &#93;}
\text{repcourse=\listerepcourse}
\integer{goodrepT1117=\typineg}
