target=psprojorth3, psprojorth4
#define TITRE Projection orthogonale
\author{Cyrille,Douriez}
\email{cyrille.douriez@ac-amiens.fr}
\integer{a=2*randint(4..7)}
\integer{b=\a-2*randint(1..3)}

\text{figure=canvasdraw(320,216
xrange -1,9
yrange -1,7
linewidth 2
segment 0,0,8,0,black 
segment 0,0,0,6,black 
segment 8,0,8,6,black 
segment 0,6,8,6,black 
segment 0,0,8,6,black
segment 0,6,8,0,black
segment -0.2,3,0.2,3,black
segment 7.8,3,8.2,3,black
segment 4,5.8,4,6.2,black
segment 4,-0.2,4,0.2,black
text black,-0.4,-0.4,large,D
text black,8,-0.4,large,C
text black,-0.4,6,large,A
text black,8,6,large,B
text black,3.8,-0.7,large,K
text black,-0.6,2.8,large,L
text black,4,6.3,large,I
text black,8.3,2.8,large,J
text black,3.7,3.2,large,O
)}

\text{entete=<p>\(ABCD) est un rectangle, \({I}) est le milieu de \([AB]\), \({J}\) est le milieu de \([BC]\), \(K\) est le milieu de \([CD]\), \(L\) est le milieu de \([AD]\) et \(O\) est le milieu 
de \([AC]\). </p>\figure}

#if defined TARGET_psprojorth3
\title{TITRE 3}
\matrix{q1=AB,AC,\a^2,AB
AB,AK,\a^2/2,AI
AB,AO,\a^2/2,AI
AB,DB,\a^2,AB
AB,OB,\a^2/2,IB
AI,AC,\a^2/2,AB
AI,AO,\a^2/4,AI
AI,DI,\a^2/4,AI
IB,ID,-\a^2/4,IA
IA,IC,-\a^2/4,IB }
\integer{c1=randint(1..rows(\q1))}

\matrix{q2=AD,AJ,\b^2/2,AL
AD,AO,\b^2/2,AL
AD,AK,\b^2,AD
BC,BD,\b^2,BC
BC,BL,\b^2/2,BJ
CB,BD,-\b^2,BC
AL,AC,\b^2/2,AD
AL,AO,\b^2/4,AL
LD,DB,-\b^2/2,DA
LA,LC,-\b^2/4,LD
JB,JD,-\b^2/4,JC
JC,JA,-\b^2/4,JB
LD,LI,-\b^2/4,LA
JB,JK,-\b^2/4,JC
AD,DO,-\b^2/2,DL
BC,CL,-\b^2/2,CJ }
\integer{c2=randint(1..rows(\q2))}

\matrix{q3=AB,DO,\a^2/2,AI
CD,LI,-\a^2/2,DK
AD,JK,\b^2/2,LD
BC,AO,\b^2/2,BJ
AB,DJ,\a^2,AB
AD,CI,-\b^2,DA
CD,AJ,-\a^2,DC
CB,KA,\b^2,CB
AB,KJ,\a^2/2,IB
AB,JK,-\a^2/2,BI
AD,OB,-\b^2/2,LA
AD,IJ,\b^2/2,AL
AD,OC,\b^2/2,LD
AI,KJ,\a^2/4,IB
AI,OD,-\a^2/4,IA
AI,OC,\a^2/4,IB
BJ,LK,\b^2/4,JC
AL,CO,-\b^2/4,DL
AL,BO,\b^2/4,AL}
\integer{c3=randint(1..rows(\q3))}

\real{s1=\q1[\c1;3]}
\real{s2=\q2[\c2;3]}
\real{s3=\q3[\c3;3]}

\statement{\entete. <p>On pose \(AB=\a\, cm\) et \(AD=\b\, cm\).</p>
Calculer les produits scalaires suivants :
<ul><li>\(\overrightarrow{\q1[\c1;1]}.\overrightarrow{\q1[\c1;2]}\)=\embed{r1,4}</li>
<li>\(\overrightarrow{\q2[\c2;1]}.\overrightarrow{\q2[\c2;2]}\)=\embed{r2,4}</li>
<li>\(\overrightarrow{\q3[\c3;1]}.\overrightarrow{\q3[\c3;2]}\)=\embed{r3,4}</li></ul></ul>}

\answer{}{\s1}{type=numexp}
\answer{}{\s2}{type=numexp}
\answer{}{\s3}{type=numexp}

\solution{<ul>En utilisant la projection orthogonale, <li>\(\overrightarrow{\q1[\c1;1]}.\overrightarrow{\q1[\c1;2]}=\overrightarrow{\q1[\c1;1]}.\overrightarrow{\q1[\c1;4]}={}\)
\if{\q1[\c1;3]>0}{\(\q1[\c1;1] \times \q1[\c1;4]=\s1\) \if{\q1[\c1;1] notsametext \q1[\c1;4]}{(\(\overrightarrow{\q1[\c1;1]}\) et \(\overrightarrow{\q1[\c1;4]}\) sont colinéaires de même sens)}}{\(-\q1[\c1;1] \times \q1[\c1;4]=\s1\) (\(\overrightarrow{\q1[\c1;1]}\) et \(\overrightarrow{\q1[\c1;4]}\) sont colinéaires de sens opposés)}</li>
<li>\(\overrightarrow{\q2[\c2;1]}.\overrightarrow{\q2[\c2;2]}=\overrightarrow{\q2[\c2;1]}.\overrightarrow{\q2[\c2;4]}={}\)
\if{\q2[\c2;3]>0}{\(\q2[\c2;1] \times \q2[\c2;4]=\s2\) \if{\q2[\c2;1] notsametext \q2[\c2;4]}{(\(\overrightarrow{\q2[\c2;1]}\) et \(\overrightarrow{\q2[\c2;4]}\) sont colinéaires de même sens)}}{\(-\q2[\c2;1] \times \q2[\c2;4]=\s2\) (\(\overrightarrow{\q2[\c2;1]}\) et \(\overrightarrow{\q2[\c2;4]}\) sont colinéaires de sens opposés)}</li>
<li>\(\overrightarrow{\q3[\c3;1]}.\overrightarrow{\q3[\c3;2]}=\overrightarrow{\q3[\c3;1]}.\overrightarrow{\q3[\c3;4]}={}\)
\if{\q3[\c3;3]>0}{\(\q3[\c3;1] \times \q3[\c3;4]=\s3\) \if{\q3[\c3;1] notsametext \q3[\c3;4]}{(\(\overrightarrow{\q3[\c3;1]}\) et \(\overrightarrow{\q2[\c2;4]}\) sont colinéaires de même sens)}}{\(-\q3[\c3;1] \times \q3[\c3;4]=\s3\) (\(\overrightarrow{\q3[\c3;1]}\) et \(\overrightarrow{\q3[\c3;4]}\) sont colinéaires de sens opposés)}</li>

</li></ul>}
#endif

#if defined TARGET_psprojorth4
\title{TITRE 4}
\text{donnees1=A,B,I,O,K
B,C,J,O,L
A,D,L,O,J
C,D,K,O,I
B,A,I,O,K
I,A,B,J,C
L,A,D,K,C
L,D,A,I,B
J,B,C,K,D
}

\text{q=randomrow(\donnees1)}

\statement{\entete
Compléter avec une lettre qui convient (la lettre \(\q[3]\) n'est pas acceptée) : \(\overrightarrow{\q[1]\q[2]}.\overrightarrow{\q[1]\q[3]}\)=\special{mathmlinput [\overrightarrow{\q[1]\q[2]}.\overrightarrow{{\q[1] \reply1}}],1
reply1,2
}}

\answer{}{\var}{type=case}
\condition{Lettre acceptée ?}{\var isitemof \q[4,5]}
\solution{\(\q[3]\) est le projeté orthogonal de \(\q[4]\) et \(\q[5]\) sur la droite \((\q[1]\q[2])\) donc \(\overrightarrow{\q[1]\q[2]}.\overrightarrow{\q[1]\q[3]}=\overrightarrow{\q[1]\q[2]}.\overrightarrow{\q[1]\q[4]}=\overrightarrow{\q[1]\q[2]}.\overrightarrow{\q[1]\q[5]}\).}
#endif
