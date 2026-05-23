target= slin slinguide
#if defined TARGET_slin
 \title{Suites linéaires}
#endif
#if defined TARGET_slinguide
 \title{Suites linéaires (guidé)}
#endif
\language{fr}
\author{David, Doyen}
\email{david.doyen@u-pem.fr}

% Données pour l'affichage des figures

\css{<style>
table{margin: 0 auto;}
td{padding: 5px 15px;}
</style>}
\text{col=lightgrey,dimgrey}
\text{ncol=2}
\text{npc=20} % taille des cases des figures

% Tirage aléatoire des suites de figures. Pour chaque suite, les cinq premières figures sont stockées.
% Chaque figure est stockée dans une matrice. Les valeurs positives indiquent les cases de la figure.
% Les différentes valeurs indiquent les décompositions des figures pour l'indication.

\text{c1=randint(1..10)}

\if{\c1==1}{
\text{fn=2*n+2}
\matrix{A0=1,2
}
\matrix{A1=1,2,2
1,0,0
}
\matrix{A2=1,2,2,2
1,0,0,0
1,0,0,0}
\matrix{A3=1,2,2,2,2
1,0,0,0,0
1,0,0,0,0
1,0,0,0,0}
\matrix{A4=1,2,2,2,2,2
1,0,0,0,0,0
1,0,0,0,0,0
1,0,0,0,0,0
1,0,0,0,0,0}
}

\if{\c1==2}{
\text{fn=2*n+1}
\matrix{A0=1
}
\matrix{A1=1,2
2,0
}
\matrix{A2=1,2,2
2,0,0
2,0,0}
\matrix{A3=1,2,2,2
2,0,0,0
2,0,0,0
2,0,0,0}
\matrix{A4=1,2,2,2,2
2,0,0,0,0
2,0,0,0,0
2,0,0,0,0
2,0,0,0,0}
}

\if{\c1==3}{
\text{fn=2*n+2}
\matrix{A0=1,1
}
\matrix{A1=1,1,1
2,0,0
}
\matrix{A2=1,1,1,1
2,2,0,0
}
\matrix{A3=1,1,1,1,1
2,2,2,0,0
}
\matrix{A4=1,1,1,1,1,1
2,2,2,2,0,0
}
}

\if{\c1==4}{
\text{fn=2*n+1}
\matrix{A0=1
}
\matrix{A1=1,1
2,0
}
\matrix{A2=1,1,1
2,2,0
}
\matrix{A3=1,1,1,1
2,2,2,0
}
\matrix{A4=1,1,1,1,1
2,2,2,2,0
}
}

\if{\c1==5}{
\text{fn=3*n+1}
\matrix{A0=1
}
\matrix{A1=1,2
1,2
}
\matrix{A2=1,2,2
1,0,0
1,2,2}
\matrix{A3=1,2,2,2
1,0,0,0
1,0,0,0
1,2,2,2}
\matrix{A4=1,2,2,2,2
1,0,0,0,0
1,0,0,0,0
1,0,0,0,0
1,2,2,2,2}
}

\if{\c1==6}{
\text{fn=3*n+2}
\matrix{A0=1
1
}
\matrix{A1=1,1
2,0
1,1}
\matrix{A2=1,1,1
2,0,0
2,0,0
1,1,1}
\matrix{A3=1,1,1,1
2,0,0,0
2,0,0,0
2,0,0,0
1,1,1,1}
\matrix{A4=1,1,1,1,1
2,0,0,0,0
2,0,0,0,0
2,0,0,0,0
2,0,0,0,0
1,1,1,1,1}
}

\if{\c1==7}{
\text{fn=3*n+1}
\matrix{A0=1
}
\matrix{A1=1,2,1
0,1,0
}
\matrix{A2=1,1,2,1,1
0,0,1,0,0
0,0,1,0,0}
\matrix{A3=1,1,1,2,1,1,1
0,0,0,1,0,0,0
0,0,0,1,0,0,0
0,0,0,1,0,0,0}
\matrix{A4=1,1,1,1,2,1,1,1,1
0,0,0,0,1,0,0,0,0
0,0,0,0,1,0,0,0,0
0,0,0,0,1,0,0,0,0
0,0,0,0,1,0,0,0,0}
}


\if{\c1==8}{
\text{fn=3*n+2}
\matrix{A0=1
1
}
\matrix{A1=0,2,0
1,2,1
0,1,0
}
\matrix{A2=0,0,2,0,0
1,1,2,1,1
0,0,1,0,0
0,0,1,0,0}
\matrix{A3=0,0,0,2,0,0,0
1,1,1,2,1,1,1
0,0,0,1,0,0,0
0,0,0,1,0,0,0
0,0,0,1,0,0,0}
\matrix{A4=0,0,0,0,2,0,0,0,0
1,1,1,1,2,1,1,1,1
0,0,0,0,1,0,0,0,0
0,0,0,0,1,0,0,0,0
0,0,0,0,1,0,0,0,0
0,0,0,0,1,0,0,0,0}
}

\if{\c1==9}{
\text{fn=3*n+3}
\matrix{A0=1,2
0,1
}
\matrix{A1=1,1,2,2
0,0,1,1
}
\matrix{A2=1,1,1,2,2,2
0,0,0,1,1,1
}
\matrix{A3=1,1,1,1,2,2,2,2
0,0,0,0,1,1,1,1
}
\matrix{A4=1,1,1,1,1,2,2,2,2,2
0,0,0,0,0,1,1,1,1,1
}
}

\if{\c1==10}{
\text{fn=4*n+1}
\matrix{A0=1
}
\matrix{A1=
0,1,0
1,2,1
0,1,0
}
\matrix{A2=
0,0,1,0,0
0,0,1,0,0
1,1,2,1,1
0,0,1,0,0
0,0,1,0,0}
\matrix{A3=
0,0,0,1,0,0,0
0,0,0,1,0,0,0
0,0,0,1,0,0,0
1,1,1,2,1,1,1
0,0,0,1,0,0,0
0,0,0,1,0,0,0
0,0,0,1,0,0,0}
\matrix{A4=
0,0,0,0,1,0,0,0,0
0,0,0,0,1,0,0,0,0
0,0,0,0,1,0,0,0,0
0,0,0,0,1,0,0,0,0
1,1,1,1,2,1,1,1,1
0,0,0,0,1,0,0,0,0
0,0,0,0,1,0,0,0,0
0,0,0,0,1,0,0,0,0
0,0,0,0,1,0,0,0,0}
}

% Pour augmenter la variété des suites, un décalage est appliqué aléatoirement.

\text{c2=randitem(0,1)}

\if{\c2==0}{
\text{fn=wims(mathsubst n=(n-1) in \fn)}
\text{A4=\A3}
\text{A3=\A2}
\text{A2=\A1}
\text{A1=\A0}
}
\text{fn=simplify(\fn)}

% Pour augmenter la variété des suites, différentes symétries sont appliquées aléatoirement.

\text{t1=randitem(0,1)}
\text{t2=randitem(0,1)}
\text{t3=randitem(0,1)}

\if{\t1==1}{
\text{A1=pari(mattranspose(Mat([\A1])))}
\text{A2=pari(mattranspose([\A2]))}
\text{A3=pari(mattranspose([\A3]))}
\text{A4=pari(mattranspose([\A4]))}
}


\text{s=pari(matsize(Mat([\A1])))}
\text{n1=\s[1]}
\text{m1=\s[2]}
\text{s=pari(matsize([\A2]))}
\text{n2=\s[1]}
\text{m2=\s[2]}
\text{s=pari(matsize([\A3]))}
\text{n3=\s[1]}
\text{m3=\s[2]}
\text{s=pari(matsize([\A4]))}
\text{n4=\s[1]}
\text{m4=\s[2]}

\if{\t2==1}{
\text{A1=pari(vecextract(Mat([\A1]),"-1..-\n1" , "1..\m1"))}
\text{A2=pari(vecextract([\A2],"-1..-\n2" , "1..\m2"))}
\text{A3=pari(vecextract([\A3],"-1..-\n3" , "1..\m3"))}
\text{A4=pari(vecextract([\A4],"-1..-\n4" , "1..\m4"))}
}

\if{\t3==1}{
\text{A1=pari(vecextract(Mat([\A1]),"1..\n1" , "-1..-\m1"))}
\text{A2=pari(vecextract([\A2],"1..\n2" , "-1..-\m2"))}
\text{A3=pari(vecextract([\A3],"1..\n3" , "-1..-\m3"))}
\text{A4=pari(vecextract([\A4],"1..\n4" , "-1..-\m4"))}
}

% Création des figures avec flydraw.

\text{fig1=}
\text{cfig1=}
\for{i=1 to \n1}{
\for{j=1 to \m1}{
\if{\A1[\i;\j]>0}{
\text{fig1= \fig1
rect \i-1,\j,\i,\j-1,black
}}
\for{k=1 to \ncol}{
\if{\A1[\i;\j]=\k}{
\text{\cfig1= \cfig1
fillrect \i-1,\j,\i,\j-1,\col[\k]
}}}
}}

\text{fig2=}
\text{cfig2=}
\for{i=1 to \n2}{
\for{j=1 to \m2}{
\if{\A2[\i;\j]>0}{
\text{fig2= \fig2
rect \i-1,\j,\i,\j-1,black
}}
\for{k=1 to \ncol}{
\if{\A2[\i;\j]=\k}{
\text{\cfig2= \cfig2
fillrect \i-1,\j,\i,\j-1,\col[\k]
}}}
}}

\text{fig3=}
\text{cfig3=}
\for{i=1 to \n3}{
\for{j=1 to \m3}{
\if{\A3[\i;\j]>0}{
\text{fig3= \fig3
rect \i-1,\j,\i,\j-1,black
}}
\for{k=1 to \ncol}{
\if{\A3[\i;\j]=\k}{
\text{\cfig3= \cfig3
fillrect \i-1,\j,\i,\j-1,\col[\k]
}}}
}}

\text{fig4=}
\text{cfig4=}
\for{i=1 to \n4}{
\for{j=1 to \m4}{
\if{\A4[\i;\j]>0}{
\text{fig4= \fig4
rect \i-1,\j,\i,\j-1,black
}}
\for{k=1 to \ncol}{
\if{\A4[\i;\j]=\k}{
\text{\cfig4= \cfig4
fillrect \i-1,\j,\i,\j-1,\col[\k]
}}}
}}

% Enoncé de l'exercice


#if defined TARGET_slinguide
\text{q1=5}
\text{fn1=evalue(\fn,n=\q1)}
\text{q2=randint(10..20)}
\text{fn2=evalue(\fn,n=\q2)}
#endif

\statement{On considère une suite de figures géométriques constituées de cases. Voici les premières figures de cette suite :
<div class="wimscenter">
<table><tr><td>
\draw{\n1*\npc,\m1*\npc}{
xrange -0.1,\n1+0.1
yrange -0.1,\m1+0.1
\fig1}
</td><td>
\draw{\n2*\npc,\m2*\npc}{
xrange -0.1,\n2+0.1
yrange -0.1,\m2+0.1
\fig2}
</td><td>
\draw{\n3*\npc,\m3*\npc}{
xrange -0.1,\n3+0.1
yrange -0.1,\m3+0.1
\fig3}
</td><td>
\draw{\n4*\npc,\m4*\npc}{
xrange -0.1,\n4+0.1
yrange -0.1,\m4+0.1
\fig4}
</td></tr><tr><td>
Figure 1
</td><td>
Figure 2
</td><td>
Figure 3
</td><td>
Figure 4
</td></tr></table>
</div>
<br class="spacer">
#if defined TARGET_slin
Quel est le nombre de cases de la figure \(n\) ? &nbsp;\embed{reply1,10}
#endif
#if defined TARGET_slinguide
<ol class="spacer">
  <li>Quel est le nombre de cases de la figure \(\q1\) ? &nbsp;\embed{reply1,2}</li>
  <li>Quel est le nombre de cases de la figure \(\q2\) ? &nbsp;\embed{reply2,2}</li>
  <li>Quel est le nombre de cases de la figure \(n\) ? &nbsp;\embed{reply3,10}</li>
</ol>
#endif
}

% Indication
\hint{
#if defined TARGET_slinguide
Pour déterminer le nombre de cases de la figure \(n\), décomposer les figures en des structures plus simples. Voilà un exemple de décomposition (d'autres sont possibles).
#endif
#if defined TARGET_slin
<ol class="spacer">
  <li>Calculer le nombre de cases pour les premières figures de la suite.</li>
  <li>Décomposer les figures en des structures plus simples. Voilà un exemple de décomposition (d'autres sont possibles).</li>
</ol>
#endif
<div class="wimscenter">
<table><tr><td>
\draw{\n1*\npc,\m1*\npc}{
xrange -0.1,\n1+0.1
yrange -0.1,\m1+0.1
\cfig1
\fig1}
</td><td>
\draw{\n2*\npc,\m2*\npc}{
xrange -0.1,\n2+0.1
yrange -0.1,\m2+0.1
\cfig2
\fig2}
</td><td>
\draw{\n3*\npc,\m3*\npc}{
xrange -0.1,\n3+0.1
yrange -0.1,\m3+0.1
\cfig3
\fig3}
</td><td>
\draw{\n4*\npc,\m4*\npc}{
xrange -0.1,\n4+0.1
yrange -0.1,\m4+0.1
\cfig4
\fig4}
</td></tr><tr><td>
Figure 1
</td><td>
Figure 2
</td><td>
Figure 3
</td><td>
Figure 4
</td></tr></table>
</div>
}

% Analyse de la réponse

#if defined TARGET_slin
\answer{}{\fn}{type=function}
#endif
#if defined TARGET_slinguide
\answer{}{\fn1}{type=numeric}
\answer{}{\fn2}{type=numeric}
\answer{}{\fn}{type=function}
#endif
