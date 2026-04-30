target=sensvar1 sensvar2 sensvar3 sensvar4 sensvar5
\author{Régine, Mangeard}

#define TITRE Sens de variation
#if defined TARGET_sensvar1
# define NUM 1
#endif
#if defined TARGET_sensvar3
# define NUM 3
#endif
#if defined TARGET_sensvar4
# define NUM 4
#endif
#if defined TARGET_sensvar2
# define NUM 2
# endif
#if defined TARGET_sensvar5
# define NUM 5
#endif
\title{TITRE NUM}
\css{<style>
table.tab_var {margin-left:auto;margin-right:auto;
   border:solid 1px black;}
table.tab_var tr, table.tab_var td, table.tab_var th {
   padding:7pt;margin-top:10px; margin-bottom:10px;
   text-align:center; border-collapse:collapse; min-width:10pt;
   }
table.tab_var th { border:solid 1px black}
table.tab_var tr { border:solid 1px black}
</style>}
#if (defined TARGET_sensvar1 || defined TARGET_sensvar2 || defined TARGET_sensvar3 )
\integer{xmin=random(-10..-5)}
\integer{xmax=random(5..10)}
\text{xlist=wims(makelist x for x=\xmin to \xmax)}
\text{monotone=strictement croissante, strictement décroissante}
\text{ind=shuffle(\xmax-\xmin+1)}
\integer{xm=randint(\xmin+3..\xmax-3)}
\integer{ym=\xm+randint(1..4)*randint(1,-1)}

#if defined TARGET_sensvar1
\integer{sens=randint(1,2)}
\text{lstrep=\(f(\xlist[\ind[1]]) < f(\xlist[\ind[2]])), \(f(\xlist[\ind[1]]) > f(\xlist[\ind[2]])), \(f(\xlist[\ind[3]]) < f(\xlist[\ind[4]])), \(f(\xlist[\ind[3]]) > f(\xlist[\ind[4]])), \(f(\xlist[\ind[5]]) < f(\xlist[\ind[6]])), \(f(\xlist[\ind[5]]) > f(\xlist[\ind[6]]))}
\text{indrep=}
\if{\sens=1}{
   \integer{rep1=\xlist[\ind[1]]<\xlist[\ind[2]]?1:2}
   \integer{rep2=\xlist[\ind[3]]<\xlist[\ind[4]]?3:4}
   \integer{rep3=\xlist[\ind[5]]<\xlist[\ind[6]]?5:6}
 }{
   \integer{rep1=\xlist[\ind[1]]<\xlist[\ind[2]]?2:1}
   \integer{rep2=\xlist[\ind[3]]<\xlist[\ind[4]]?4:3}
   \integer{rep3=\xlist[\ind[5]]<\xlist[\ind[6]]?6:5}
 }
\text{indrep=\rep1,\rep2,\rep3}
\statement{
  Soit une fonction \(f) définie sur l'intervalle \(&#91; \xmin ; \xmax &#93;)
  et <span class="wims_emph">\monotone[\sens] </span>.
  Cocher la (ou les) proposition(s) vérifiée(s):
<ul><li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
<li>\embed{reply1,5}</li>
<li>\embed{reply1,6}</li>
</ul>
}
\answer{\(f) \monotone[\sens]}{\indrep;\lstrep}{type=checkbox}
#endif
#if defined TARGET_sensvar2
\text{monotone=strictement croissante, strictement décroissante, non monotone}
\integer{xm=randint(\xmin+3..\xmax-3)}
\integer{k=randint(1,2)}
\text{sens=\k=1?1,2:2,1}
\text{symb=<,>}
\integer{rep1=3}
\integer{rep2=\sens[1]}
\integer{rep3=\sens[2]}

\statement{
  Soit une fonction \(h) définie sur l'intervalle \(&#91; \xmin ; \xmax &#93;) , telle que
<ol>
<li>pour tous réels \(x_1) et \(x_2) de \(&#91; \xmin ; \xm &#93;), tels que \(x_1 < x_2), on a \(h(x_1) \symb[\sens[1]] h(x_2))</li>
<li>pour tous réels \(x_1) et \(x_2) de \(&#91; \xm ; \xmax &#93;), tels que \(x_1 < x_2), on a \(h(x_1) \symb[\sens[2]] h(x_2))</li>
</ol>
  Alors, on peut en déduire que :
<ul>
<li>\(h) est \embed{reply1} sur \(&#91; \xmin ; \xmax &#93;)</li>
<li>\(h) est \embed{reply2} sur \(&#91; \xmin ; \xm &#93;)</li>
<li>\(h) est \embed{reply3} sur \(&#91; \xm ; \xmax &#93;)</li>
</ul>
}
\answer{sur \(&#91; \xmin ; \xmax &#93;)}{\rep1;\monotone}{type=menu}
\answer{sur \(&#91; \xmin ; \xm &#93;)}{\rep2;\monotone}{type=menu}
\answer{sur \(&#91; \xm ; \xmax &#93;)}{\rep3;\monotone}{type=menu}
#endif
#if defined TARGET_sensvar3
\text{extrem=maximum,minimum}
\integer{k=randint(1,2)}
\text{lstrep=\(f(x) \le \xm), \(f(x) \ge \xm), \(f(x) \le \ym), \(f(x) \ge \ym), \(f(x) \le f(\ym)), \(f(x) \ge f(\ym))}
\integer{indrep=\k=1?3:4}
\if{\k=1}{
  \integer{rep2=1}
  \integer{rep3=2}
 }{
  \integer{rep2=2}
  \integer{rep3=1}
 }
\statement{
  Soit une fonction \(f) définie sur l'intervalle \(&#91; \xmin ; \xmax &#93;) ,
  dont <span class="wims_emph">le \extrem[\k] </span> \ym est atteint en \xm.
<p>
  Alors, on peut en déduire que, pour tout \(x \in )&#91; \xmin ; \xmax &#93;:
</p>
<ul><li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
<li>\embed{reply1,5}</li>
<li>\embed{reply1,6}</li>
</ul>
  Sachant que \(f) ne change qu'une seule fois de sens de variation,
  on peut aussi en déduire que:
<div class="wimscenter">
\(f) est \embed{reply2} sur \(&#91; \xmin ; \xm &#93;) et \embed{reply3} sur \(&#91; \xm ; \xmax &#93;)
</div>}
\answer{Déduction1}{\indrep;\lstrep}{type=radio}
\answer{Déduction2}{\rep2;strictement croissante, strictement décroissante}{type=menu}
\answer{Déduction3}{\rep3;strictement croissante, strictement décroissante}{type=menu}
#endif
#endif
#if defined TARGET_sensvar4
%%%% Choix de 4 points dans le cadre
\integer{x0=random(-4..-2)}
\integer{x1=\x0+random(1..3)}
\integer{x2=\x1+random(1..3)}
\integer{x3=\x2+1}
\integer{c=random(1..3)*random(1,-1)}
\integer{d=random(-2..2)}

\matrix{symb = \(\searrow),\(\nearrow),\(\searrow)
\(\nearrow),\(\searrow),\(\nearrow)}
\text{variations = \(\nearrow),\(\searrow)}
\text{monotone = \(\nearrow),\(\searrow)}

%%%% choix du sens de variation
\integer{cas=random(1,2)}
\integer{i1=\cas=1?1:2}
\integer{i2=\cas=1?2:1}
\text{c_f=\cas=1?1,2,1:2,1,2}
\text{monotone=\symb[\cas;]}

%%%% choix des valeurs de x
\integer{x1=random(-10..10)}
\integer{x2=\x1+random(1..10)}
\integer{x3=\x2+random(1..10)}
\integer{x4=\x3+random(1..10)}
\text{xl=\x1,\x2,\x3,\x4}


%%%% choix des valeurs de f(x)
\integer{y1=random(-10..10)}
\if{\cas=1}
 {
 \integer{y2=\y1-random(1..10)}
 \integer{y3=\y2+random(1..10)}
 \integer{y4=\y3-random(1..10)}
 }
 {
 \integer{y2=\y1+random(1..10)}
 \integer{y3=\y2-random(1..10)}
 \integer{y4=\y3+random(1..10)}
 }
\text{yl=\y1,\y2,\y3,\y4}
\text{indl=shuffle(4)}
%%%% on choisit la question image de \xl[\indl[1]]
%%%% et on veut tester la compréhension
%%%% on veut \yl[indl[2]]=\xl[\indl[1]]
\integer{rep1=\yl[\indl[1]]}
\integer{offset=\xl[\indl[1]]-\yl[\indl[2]]}
\integer{y1=\y1+\offset}
\integer{y2=\y2+\offset}
\integer{y3=\y3+\offset}
\integer{y4=\y4+\offset}
\integer{rep1=\rep1+\offset}

\if{\cas=1}{
  \text{pos=top,bottom,top,bottom}
 }{
   \text{pos=bottom,top,bottom,top}
 }

 \text{d1=\y1}
 \text{d2=\y2}
 \text{d3=\y3}
 \text{d4=\y4}
%%%% Choix des intervalles
\matrix{interval=\x1,\x2
\x2,\x3
\x3,\x4
\x1,\x3
\x2,\x4}

%%%% Préparation des réponses
\text{replist=non monotone, croissante, décroissante}
\if{\cas=1}
 { \text{goodrep=3,2,3,1,1}}
 { \text{goodrep=2,3,2,1,1}}

%%%% Préparation des questions
\text{indl=shuffle(5)}
\text{q1=\interval[\indl[1];]}
\text{q2=\interval[\indl[2];]}
\text{q3=\interval[\indl[3];]}
\text{q4=\interval[\indl[4];]}
\text{q5=\interval[\indl[5];]}

%%%%%%%%%%%% enoncé de l'exo %%%%%%%%%%%%#


\statement{
  Soit \(f) une fonction définie sur &#91; \x1;\x4 &#93; dont le
  tableau des variations est donné ci-dessous
<table class="tab_var">
<caption>Tableau de variations</caption>
<tr>
  <th style="width:15%">\(x)</th>
      <td style="width:15%;text-align:left">\x1</td>
      <td style="width:8%"></td>
      <td style="width:15%">\x2</td>
      <td style="width:8%"></td>
      <td style="width:15%">\x3</td>
      <td style="width:8%"></td>
      <td style="width:15%;text-align:right">\x4</td>
</tr><tr>
  <th style="width:15%;vertical-align:middle">\(f(x))</th>
     <td style="width:15%;text-align:left;vertical-align:\pos[1]">\d1 </td>
     <td style="width:8%">\monotone[1] </td>
     <td style="width:15%;vertical-align:\pos[2]">\d2 </td>
     <td style="width:8%">\monotone[2]  </td>
     <td style="width:15%;vertical-align:\pos[3]">\d3 </td>
     <td style="width:8%">\monotone[3] </td>
     <td style="width:15%;text-align:right;vertical-align:\pos[4]">\d4 </td>
      </tr>
</table>
  Votre réponse :
<ul>
<li>sur &#91;\q1[1];\q1[2]&#93;, \(f) est :  \embed{reply1}</li>
<li>sur &#91;\q2[1];\q2[2]&#93;, \(f) est :  \embed{reply2}</li>
<li>sur &#91;\q3[1];\q3[2]&#93;, \(f) est :  \embed{reply3}</li>
<li>sur &#91;\q4[1];\q4[2]&#93;, \(f) est :  \embed{reply4}</li>
<li>sur &#91;\q5[1];\q5[2]&#93;, \(f) est :  \embed{reply5}</li>
</ul>
}
%%%%%%%% soumission de réponse %%%%%%%%
\answer{ \(f) est:}{\goodrep[\indl[1]];\replist}{type=menu}
\answer{ \(f) est:}{\goodrep[\indl[2]];\replist}{type=menu}
\answer{ \(f) est:}{\goodrep[\indl[3]];\replist}{type=menu}
\answer{ \(f) est:}{\goodrep[\indl[4]];\replist}{type=menu}
\answer{ \(f) est:}{\goodrep[\indl[5]];\replist}{type=menu}
#endif
#if defined TARGET_sensvar5
\integer{xmin=-10}
\integer{xmax=10}
\integer{ymin=-10}
\integer{ymax=10}

%%%%# la liste des objets que l'on peut cliquer pour résoudre l'exercice %%%%#
\text{vse=\(\searrow)}
\text{vne=\(\nearrow)}
\matrix{symb = \vse,\vne,\vse
\vne,\vse,\vne}
\text{variations = \(\nearrow),\(\searrow)}
\text{monotone = \(\nearrow),\(\searrow)}

%%%% choix du sens de variation
\integer{cas=random(1,2)}
\integer{cas2=random(1..4)}

%%%% cas pour déterminer sens de variation
\integer{i1=\cas=1?1:2}
\integer{i2=\cas=1?2:1}
\text{c_f=\cas=1?1,2,1:2,1,2}
\text{monotone=\symb[\cas;]}

%%%% choix des valeurs de x
\integer{x1=random(-10..-5)}
\integer{x2=\x1+random(3..5)}
\integer{x3=\x2+random(3..5)}
\integer{x4=\x3+random(3..5)}
\text{xl=\x1,\x2,\x3,\x4}

%%%% choix des valeurs de f(x)
\integer{y1=random(-3..3)}
\if{\cas=1}{
 \integer{y2=\y1-random(2..6)}
 \integer{y3=\y2+random(2..7)}
 \integer{y3=\y3=\y1?\y3+1}
 \integer{y4=\y3-random(2..5)}
 \integer{y4=\y4=\y1?\y4-1}
 \integer{y4=\y4=\y2?\y4-1}
 \integer{y4=\y4<\ymin?\ymin}
 }{
 \integer{y2=\y1+random(2..6)}
 \integer{y3=\y2-random(2..7)}
 \integer{y3=\y3=\y1?\y3-1}
 \integer{y4=\y3+random(2..5)}
 \integer{y4=\y4=\y1?\y4+1}
 \integer{y4=\y4=\y2?\y4+1}
 \integer{y4=\y4>\ymax?\ymax}
 }
\text{yl=\y1,\y2,\y3,\y4}
\text{indl=shuffle(4)}
\if{\cas=1}{
 \text{pos=top,bottom,top,bottom}
 \text{d1=\y1}
 \text{d2=\y2}
 \text{d3=\y3}
 \text{d4=\y4}
 }{
 \text{pos=bottom,top,bottom,top}
 \text{d1=\y1}
 \text{d3=\y3}
 \text{d2=\y2}
 \text{d4=\y4}
 }
%%%% Choix des intervalles
\matrix{interval=\x1,\x2
\x2,\x3
\x3,\x4
\x1,\x3
\x2,\x4}

%%%%# la liste des objets que l'on peut cliquer pour résoudre l'exercice %%%%#
\text{vx1=\(\x1)}
\text{vx2=\(\x2)}
\text{vx3=\(\x3)}
\text{vx4=\(\x4)}
\text{vy1=\(\y1)}
\text{vy2=\(\y2)}
\text{vy3=\(\y3)}
\text{vy4=\(\y4)}
\text{vesp=&#32;}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{empt=\(\emptyset)}
\text{ptvirg=&#59;}

\text{permut=shuffle(\vx1,\vx2,\vx3,\vx4,\vy1,\vy2,\vy3,\vy4)}
\text{permut= wims(listuniq \permut)}

\text{clicList=
\vse,\vne,\ptvirg,\vesp,\infg,\infd,\empt,\permut
}
%%%% taille des symboles et des champs à remplir par clic LxHxnb %%%%
\text{size=60x40x7}
\integer{ind1=wims( positionof item \vx1 in \permut)}
\integer{ind2=wims( positionof item \vx2 in \permut)}
\integer{ind3=wims( positionof item \vx3 in \permut)}
\integer{ind4=wims( positionof item \vx4 in \permut)}
\integer{jnd1=wims( positionof item \vy1 in \permut)}
\integer{jnd2=wims( positionof item \vy2 in \permut)}
\integer{jnd3=wims( positionof item \vy3 in \permut)}
\integer{jnd4=wims( positionof item \vy4 in \permut)}

\text{grepx=\permut[\ind1],\vesp,\permut[\ind2],\vesp,\permut[\ind3],\vesp,\permut[\ind4]}
\text{crog=&#91;}
\text{crod=&#93;}
\if{\cas=1}{
 \text{grepfx=\permut[\jnd1]}
 \text{grepfx=\grepfx,\monotone[1],\permut[\jnd2],\monotone[2],\permut[\jnd3],\monotone[3]}
 \text{grepfx=\grepfx,\permut[\jnd4]}
 }{
 \text{grepfx=\permut[\jnd1]}
 \text{grepfx=\grepfx,\monotone[1],\permut[\jnd2],\monotone[2],\permut[\jnd3],\monotone[3]}
 \text{grepfx=\grepfx,\permut[\jnd4]}
 }


%%%% Préparation des questions
\text{indl=shuffle(5)}
\text{q1=\interval[\indl[1];]}
\text{q2=\interval[\indl[2];]}
\text{q3=\interval[\indl[3];]}
\text{q4=\interval[\indl[4];]}
\text{q5=\interval[\indl[5];]}

%%%% Choix du graphique: 1=droites 2=paraboles
\integer{typegr=random(1,2)}
\integer{typegr=2}
\if{\typegr=2}{
 \rational{t3=((\x2)+(\x3))/2}
 \rational{yt3=((\y2)+(\y3))/2}
%%%% première parabole
%%%% passe par x1,y1 et x2,y2 et dérivée s'annule en x2
\rational{a1=((\y1)-(\y2))/((\x1)-(\x2))^2}
\rational{b1=-2*\a1*\x2}
\rational{c1=( (\y2)*( (\x1)^2-2*(\x1)*(\x2) )+(\y1)*(\x2)^2 )/((\x1)-(\x2))^2}
\text{f= \a1*t^2+(\b1)*t+(\c1)}

%%%% deuxième parabole
%%%% passe par t3,yt3 et x2,y2 et dérivée s'annule en x2
\rational{a2=((\yt3)-(\y2))/((\t3)-(\x2))^2}
\rational{b2=-2*\a2*\x2}
\rational{c2=( (\y2)*( (\t3)^2-2*(\t3)*(\x2) )+(\yt3)*(\x2)^2 )/((\t3)-(\x2))^2}
\text{g= \a2*t^2+(\b2)*t+(\c2)}

%%%% troisième parabole
%%%% passe par t3,yt3 et x3,y3 et dérivée s'annule en x3
\rational{a3=((\yt3)-(\y3))/((\t3)-(\x3))^2}
\rational{b3=-2*\a3*\x3}
\rational{c3=( (\y3)*( (\t3)^2-2*(\t3)*(\x3) )+(\yt3)*(\x3)^2 )/((\t3)-(\x3))^2}
\text{h= \a3*t^2+(\b3)*t+(\c3)}

%%%% quatrième parabole
%%%% passe par x3,y3 et x4,y4 et dérivée s'annule en x3
\rational{a4=((\y4)-(\y3))/((\x4)-(\x3))^2}
\rational{b4=-2*\a4*\x3}
\rational{c4=( (\y3)*( (\x4)^2-2*(\x4)*(\x3) )+(\y4)*(\x3)^2 )/((\x4)-(\x3))^2}
\text{l= \a4*t^2+(\b4)*t+(\c4)}

\text{cadrefct=
trange \x1,\x2
 plot red,t,\f
trange \x2,\t3
 plot red,t,\g
trange \t3,\x3
 plot red,t,\h
trange \x3,\x4
 plot red,t,\l
}
}{
\text{cadrefct=
polyline red,\x1,\y1,\x2,\y2,\x3,\y3,\x4,\y4
}
}
%%%%# cadre générique %%%%#
\text{cadre=
xrange \xmin,\xmax
yrange \ymin,\ymax
linewidth 1
parallel \xmin,\ymin,\xmin,\ymax,0.2,0,100,\gridcolor
parallel \xmin,\ymin,\xmax,\ymin,0,0.2,100,\gridcolor
linewidth 2
parallel \xmin,\ymin,\xmin,\ymax,1,0,21,blue
parallel \xmin,\ymin,\xmax,\ymin,0,1,21,blue
linewidth 2
vline 0,0,black
hline 0,0,black
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
linewidth 2
\cadrefct
}
%%%% fin du cadre générique %%%%

%%%%%%%%%%%%# enoncé de l'exo %%%%%%%%%%%%#

\statement{
<div class="wims_columns">
<div class="medium_size">\draw{400,400}{\cadre}</div>
<div class="medium_size">
  Dans le plan muni d'un repère orthogonal \((O,i,j)\),
  on a tracé la courbe représentative d'une fonction \(f) définie sur l'intervalle
\crog \x1;\x4 \crod.
<p>
  Construire le tableau des variations de \(f) en draguant les éléments
  nécessaires dans la ligne \(x) et dans la ligne \(f(x)) du tableau
  ci-dessous.
</p>
  </div>
  </div>
 <table class="tab_var">
  <tr><th>\(x)</th><td>\embed{reply1,\size}</td></tr><tr>
  <th>\(f(x))</th><td>\embed{reply2,\size}</td></tr>
</table>
}

\answer{}{\grepx;\clicList}{type=clickfill}
\answer{}{\grepfx;\clicList}{type=clickfill}
#endif
