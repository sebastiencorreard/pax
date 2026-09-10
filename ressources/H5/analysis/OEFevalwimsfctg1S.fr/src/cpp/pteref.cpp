target=pteref1 pteref2 pteref3 pteref4 pteref5
#include "author.inc"
#include "vartab.inc"
#include "lang_titles.inc"
\precision{1000}
#if defined TARGET_pteref1
\rational{a=randitem(-1,-2,-1/2,1,2,1/2)}
\integer{b=randint(-4..4)}
\text{f=texmath(pari(\a*x+\b))}
\text{lstf=\f,x^2,\frac{1}{x},\sqrt{x}}
\text{ind=shuffle(4)}
\text{rept=\a>0?\(T_2),\(T_4),\(T_5),\(T_3):\(T_1),\(T_4),\(T_5),\(T_3)}
\text{repc=\(C_4),\(C_3),\(C_1),\(C_2)}
\integer{i1=position(1,\ind)}
\text{t1=\rept[\ind[1]]}
\text{c1=\repc[\ind[1]]}
\integer{i2=position(2,\ind)}
\text{t2=\rept[\ind[2]]}
\text{c2=\repc[\ind[2]]}
\integer{i3=position(3,\ind)}
\text{t3=\rept[\ind[3]]}
\text{c3=\repc[\ind[3]]}
\integer{i4=position(4,\ind)}
\text{t4=\rept[\ind[4]]}
\text{c4=\repc[\ind[4]]}
\text{dessin=
 xrange -8,8
 yrange= -6,11
 segment 0,-6,0,11,black
 segment -8,0,8,0,black
 plot red,\a*x+\b
 plot blue,x^2
 plot green, sqrt(x)
 plot orange, 1/x
 text red,-1,\b,medium,C4
 text blue,-2,5,medium,C3
 text green,4,3,medium,C2
 text orange,-5,0,medium,C1
}
\text{lsttab=\(T_1),\(T_2),\(T_3),\(T_4),\(T_5)}
\text{lstcourbe=\(C_1),\(C_2),\(C_3),\(C_4)}
\text{t5=\a>0?\(T_1):\(T_2)}
#include "ptereftab.inc"
\statement{
  On considère les quatre fonctions \(f_1), \(f_2), \(f_3) et \(f_4) définies par
<div class="wimscenter">\(f_1(x)=\lstf[\ind[1]]);
\(f_2(x)=\lstf[\ind[2]]); \(f_3(x)=\lstf[\ind[3]]) et \(f_4(x)=\lstf[\ind[4]]).</div>
<div class="center">\lsttabs</div>
<div class="wims_columns">
 <div class="medium_size img_col">\draw{300,300}{\dessin}</div>
<div class="medium_size text_col">Associer chaque fonction à son tableau de variation et à sa courbe.
<table class="wimscenter wimsborder">
<tr><th>Fonction</th><th>Tableau des variations</th><th>Courbe</th></tr>
<tr><td>\(f_1) </td><td>\embed{reply1,150x30}</td><td>\embed{reply2}</td></tr>
<tr><td>\(f_2) </td><td>\embed{reply3}</td><td>\embed{reply4}</td></tr>
<tr><td>\(f_3) </td><td>\embed{reply5}</td><td>\embed{reply6}</td></tr>
<tr><td>\(f_4) </td><td>\embed{reply7}</td><td>\embed{reply8}</td></tr>
</table>
</div>
</div>
}
\answer{tableau de \(f_1)}{\t1;\t5}{type=dragfill}
\answer{courbe de \(f_1)}{\c1}{type=dragfill}
\answer{tableau de \(f_2)}{\t2}{type=dragfill}
\answer{courbe de \(f_2)}{\c2}{type=dragfill}
\answer{tableau de \(f_3)}{\t3}{type=dragfill}
\answer{courbe de \(f_3)}{\c3}{type=dragfill}
\answer{tableau de \(f_4)}{\t4}{type=dragfill}
\answer{courbe de \(f_4)}{\c4}{type=dragfill}
#endif
#if defined TARGET_pteref2
\integer{n=randint(3..10)}
\rational{invn=1/\n}
\rational{minvn=-\invn}
\integer{mn=-\n}
\real{decn=0.\n}
\integer{nc=\n^2}
\integer{mnc=-\nc}
\integer{mn2=-2*\n}
\integer{n2=2*\n}
\text{varx=random(x,y,z,t,u)}
\text{data=-1 a pour inverse,-1,1,0.1
  0.1 a pour inverse,10,1,0.9
\n a pour opposé,\mn,\invn,\decn
\(\frac{1}{\n}) a pour inverse,\n,\minvn,\decn
\(-\n^2) est égal à,-\nc,\nc,\mn2
\((\n\varx)^2) est égal à,\(\nc \varx^2),2\n\varx,\(\n \varx^2)
\((-\varx)^2+\varx^2) est égal à, \(2\varx^2),0,\((2\varx)^2)
}
\text{ind=shuffle(7)}
\text{cedata=row(\ind[1],\data)}
\text{quest1=\cedata[1]}
\text{lstrep1=item(2..4,\cedata)}
\text{cedata=row(\ind[2],\data)}
\text{quest2=\cedata[1]}
\text{lstrep2=item(2..4,\cedata)}
\text{cedata=row(\ind[3],\data)}
\text{quest3=\cedata[1]}
\text{lstrep3=item(2..4,\cedata)}
\text{cedata=row(\ind[4],\data)}
\text{quest4=\cedata[1]}
\text{lstrep4=item(2..4,\cedata)}
\statement{
  Choisir la bonne réponse:
<ol>
<li>\quest1: \embed{reply1}</li>
<li>\quest2: \embed{reply2}</li>
<li>\quest3: \embed{reply3}</li>
<li>\quest4: \embed{reply4}</li>
</ol>
}
\answer{\quest1}{1;\lstrep1}{type=radio}{option=shuffle}
\answer{\quest2}{1;\lstrep2}{type=radio}{option=shuffle}
\answer{\quest3}{1;\lstrep3}{type=radio}{option=shuffle}
\answer{\quest4}{1;\lstrep4}{type=radio}{option=shuffle}
#endif
#if defined TARGET_pteref3
\integer{a=randint(1..10)}
\integer{b=\a+randint(1..10)}
\integer{ac=\a^2}
\integer{bc=\b^2}
\text{varx=random(x,y,z,t,u)}
\text{data=Si \(\a \leq \varx \leq \b) alors \(\ac \leq \varx^2 \leq \bc),1
  Si \(\ac \leq \varx^2 \leq \bc) alors \(\a \leq \varx \leq \b),2
  Si \(-\a \leq \varx \leq \b) alors \(\ac \leq \varx^2 \leq \bc),2,contre-exemple \(0 \in [-\a;\b]) et \(0 \not \in [\ac;\bc])
  Si \(\varx<-\a) alors \(\varx^2 < \ac),2,La fonction carré est décroissante sur &#93;\(-\infty) &#59; 0 &#91;
}
\text{ind=shuffle(4)}
\text{cedata=row(\ind[1],\data)}
\text{quest1=\cedata[1]}
\integer{rep1=\cedata[2]}
\text{tfeed=\cedata[3]}
\text{cedata=row(\ind[2],\data)}
\text{quest2=\cedata[1]}
\integer{rep2=\cedata[2]}
\text{tfeed=\tfeed<br>\cedata[3]}
\integer{k=randint(1,2)}
\if{\k=1}
 {
\text{quest3=Si \(\varx^2 > \ac) alors \(\varx > \a) ou \(\varx < -\a)}
\integer{rep3=1}
\text{quest4=Si \(\varx^2 > \ac) alors \(\varx > \a) et \(\varx < -\a)}
\integer{rep4=2}
 }
 {
\text{quest3=Pour tout \(\varx > 1) alors \(\varx^2 > \varx)}
\integer{rep3=1}
\text{quest4=Il existe \(\varx > 0) tel que \(\varx^2 < \varx)}
\integer{rep4=1}
\text{tfeed=\tfeed<br> 0.5 > 0 et 0.25 < 0.5}
 }
\text{lstq=\quest1,\quest2,\quest3,\quest4}
\text{lstr=\rep1,\rep2,\rep3,\rep4}
\text{ind=shuffle(4)}
\statement{
  Dire si les propositons suivantes sont vraies ou fausses:
<ol>
<li>\lstq[\ind[1]]: \embed{reply1}</li>
<li>\lstq[\ind[2]]: \embed{reply2}</li>
<li>\lstq[\ind[3]]: \embed{reply3}</li>
<li>\lstq[\ind[4]]: \embed{reply4}</li>
</ol>
}
\answer{\lstq[\ind[1]]}{\lstr[\ind[1]];Vrai, Faux}{type=radio}
\answer{\lstq[\ind[2]]}{\lstr[\ind[2]];Vrai, Faux}{type=radio}
\answer{\lstq[\ind[3]]}{\lstr[\ind[3]];Vrai, Faux}{type=radio}
\answer{\lstq[\ind[4]]}{\lstr[\ind[4]];Vrai, Faux}{type=radio}
\feedback{1=1}{\tfeed}
#endif
#if defined TARGET_pteref4
\integer{a=randint(1..10)}
\integer{b=\a+randint(1..10)}
\integer{ac=\a^2}
\integer{bc=\b^2}
\integer{n=randint(2..10)}
\text{varx=random(x,y,z,t,u)}
\text{data=Si \(\a \leq \varx \leq \b) alors \(\frac{1}{\a} \geq \frac{1}{\varx} \geq \frac{1}{\b}),1
  Si \(-\b \leq \varx \leq -\a) alors \(-\frac{1}{\b} \leq \frac{1}{\varx} \leq -\frac{1}{\a}),2
  Si \(\frac{1}{\varx} > \frac{1}{\n}) alors \(\varx < \n),1
  Si \(\varx<\n) alors \(\frac{1}{\varx} > \frac{1}{\n}),2,contre-exemple \(-\n < \n) et \(-\frac{1}{\n} < \frac{1}{\n})
  Si \(\varx > \n) alors \(\frac{1}{\varx} < \frac{1}{\n}),1
  Si \(\frac{1}{\varx} < \frac{1}{\n}) alors \(\varx > \n),2,contre-exemple \(-\frac{1}{\n} < \frac{1}{\n}) et \(-\n < \n)
}
\text{ind=shuffle(3)}
\text{cedata=row(2*\ind[1]-1,\data)}
\text{quest1=\cedata[1]}
\integer{rep1=\cedata[2]}
\text{tfeed=\cedata[3]}
\text{cedata=row(2*\ind[1],\data)}
\text{quest2=\cedata[1]}
\integer{rep2=\cedata[2]}
\text{tfeed=\tfeed<br>\cedata[3]}
\text{cedata=row(2*\ind[2]-1,\data)}
\text{quest3=\cedata[1]}
\integer{rep3=\cedata[2]}
\text{tfeed=\tfeed<br>\cedata[3]}
\text{cedata=row(2*\ind[2],\data)}
\text{quest4=\cedata[1]}
\integer{rep4=\cedata[2]}
\text{tfeed=\tfeed<br>\cedata[3]}
\text{lstq=\quest1,\quest2,\quest3,\quest4}
\text{lstr=\rep1,\rep2,\rep3,\rep4}
\text{ind=shuffle(4)}
\integer{c=randint(2..10)}
\text{quest5=Si \(a \in \RR^*\) et \(b=\c a), choisir les bonnes réponses&nbsp;}
\text{lstrep=\(\frac{1}{b}=\c\frac{1}{a}),\(\frac{1}{b}=\frac{1}{\c}\times\frac{1}{a}),\(\frac{1}{b}=\frac{1}{\c a}),\(\frac{1}{a}=\frac{b}{\c}),\(\frac{1}{a}=\frac{\c}{b}),\(\frac{1}{a}=\c\times\frac{1}{b})}

\text{rep5=2,3,5,6}
\text{quest6=Donner un réel \(x) strictement positif tel que \(\frac{1}{x}>x)}

\statement{
  Dire si les propositions suivantes sont vraies ou fausses:
<ol>
<li>\lstq[\ind[1]]: \embed{reply1}</li>
<li>\lstq[\ind[2]]: \embed{reply2}</li>
<li>\lstq[\ind[3]]: \embed{reply3}</li>
<li>\lstq[\ind[4]]: \embed{reply4}</li>
</ol>
\quest5
<ul>
  <li>\embed{reply5,1}</li>
  <li>\embed{reply5,2}</li>
  <li>\embed{reply5,3}</li>
  <li>\embed{reply5,4}</li>
  <li>\embed{reply5,5}</li>
  <li>\embed{reply5,6}</li>
</ul>
\quest6:\embed{reply6}
}
\answer{\lstq[\ind[1]]}{\lstr[\ind[1]];Vrai, Faux}{type=radio}
\answer{\lstq[\ind[2]]}{\lstr[\ind[2]];Vrai, Faux}{type=radio}
\answer{\lstq[\ind[3]]}{\lstr[\ind[3]];Vrai, Faux}{type=radio}
\answer{\lstq[\ind[4]]}{\lstr[\ind[4]];Vrai, Faux}{type=radio}
\answer{}{\rep5;\lstrep}{type=checkbox}{option=shuffle}
\answer{}{\rep6}{type=numeric}
\feedback{1=1}{\tfeed}
\condition{x}{\reply6<1 and \reply6>0}
\feedback{\reply6>=1 or \reply6<=0}{Pour avoir \(\frac{1}{x} > x), il faut choisir \(x \in )&#93;0;1&#91;}
#endif
#if defined TARGET_pteref5
\text{dessina=
 xrange -pi,pi
 yrange -1.3,1.3
 segment -pi,0,pi,0,black
 segment 0,-1.3,0,1.3,black
 parallel -0.1,-1,0.1,-1,0,1,3,black
 parallel -3,-0.05,-3,0.05,1,0,7,black
 plot red,sin(x)
 text black,-0.2,1,medium,1
 text black,0.8,-0.1,medium,1
}
\text{dessinc=
 xrange -pi,pi
 yrange -2.6,2.6
 segment -pi,0,pi,0,black
 segment 0,-2.6,0,2.6,black
 parallel -0.1,-2,0.1,-2,0,1,5,black
 parallel -3,-0.1,-3,0.1,1,0,7,black
 plot red,2*sin(x)
 text black,-0.2,1,medium,1
 text black,0.8,-0.1,medium,1
}
\text{dessinb=
 xrange -pi,pi
 yrange -1.3,1.3
 segment -pi,0,pi,0,black
 segment 0,-1.3,0,1.3,black
 parallel -0.1,-1,0.1,-1,0,1,3,black
 parallel -3,-0.05,-3,0.05,1,0,7,black
 plot red,cos(x)
 text black,-0.2,1,medium,1
 text black,0.8,-0.1,medium,1
}
\text{dessind=
 xrange -pi,pi
 yrange -2.6,2.6
 segment -pi,0,pi,0,black
 segment 0,-2.6,0,2.6,black
 parallel -0.1,-2,0.1,-2,0,1,5,black
 parallel -3,-0.1,-3,0.1,1,0,7,black
 plot red,2*cos(x)
 text black,-0.2,1,medium,1
 text black,0.8,-0.1,medium,1
}
\text{ind=shuffle(4)}
\if{\ind[1]=1}{\text{dessin1=\dessina} \integer{gc1=1}}
\if{\ind[1]=2}{\text{dessin1=\dessinb} \integer{gc2=1}}
\if{\ind[1]=3}{\text{dessin1=\dessinc}}
\if{\ind[1]=4}{\text{dessin1=\dessind}}
\if{\ind[2]=1}{\text{dessin2=\dessina} \integer{gc1=2}}
\if{\ind[2]=2}{\text{dessin2=\dessinb} \integer{gc2=2}}
\if{\ind[2]=3}{\text{dessin2=\dessinc}}
\if{\ind[2]=4}{\text{dessin2=\dessind}}
\if{\ind[3]=1}{\text{dessin3=\dessina} \integer{gc1=3}}
\if{\ind[3]=2}{\text{dessin3=\dessinb} \integer{gc2=3}}
\if{\ind[3]=3}{\text{dessin3=\dessinc}}
\if{\ind[3]=4}{\text{dessin3=\dessind}}
\if{\ind[4]=1}{\text{dessin4=\dessina} \integer{gc1=4}}
\if{\ind[4]=2}{\text{dessin4=\dessinb} \integer{gc2=4}}
\if{\ind[4]=3}{\text{dessin4=\dessinc}}
\if{\ind[4]=4}{\text{dessin4=\dessind}}
\text{lstfnc=sinus,cosinus}
\text{lstgcb=C\gc1,C\gc2}
\text{lstcb=C1,C2,C3,C4}
\text{lstbadc=wims(listcomplement \lstgcb in \lstcb)}
\integer{gf1=1}
\integer{gf2=2}
\text{size=50x20x1}
\integer{k=randint(1,2)}
\text{labela=\k=1?\(T_1\):\(T_2\)}
\text{labelb=\k=1?\(T_2\):\(T_1\)}
\text{taba=<table class="tab_var">
<caption>\labela</caption>
<tr>
  <th>\(x)</th>
  <td style="text-align:left">\(0)</td>
  <td></td>
  <td>\(\frac{\pi}{2})</td>
  <td></td>
  <td>\(\frac{3\pi}{2})</td>
  <td></td>
  <td style="text-align:right">\(2\pi)</td>
</tr><tr>
  <th valign="middle">var</th>
  <td style="text-align:left" valign="bottom">\(0) </td>
  <td>\(\nearrow) </td>
  <td valign="top">1 </td>
  <td>\(\searrow)  </td>
  <td valign="bottom">-1 </td>
  <td>\(\nearrow)  </td>
  <td valign="top">\(0) </td>
  </tr>
</table>
}
\text{tabb=<table class="tab_var">
 <caption>\labelb</caption>
<tr>
  <th>\(x)</th>
  <td style="text-align:left">\(0)</td>
  <td></td>
  <td>\(\pi)</td>
  <td></td>
  <td style="text-align:right">\(2\pi)</td>
</tr><tr>
  <th valign="middle">var</th>
  <td style="text-align:left" valign="top">\(1) </td>
  <td>\(\searrow) </td>
  <td valign="bottom">-1 </td>
  <td>\(\nearrow)  </td>
  <td valign="top">\(1) </td>
  </tr>
</table>
}

\text{tab1=\k=1?\taba:\tabb}
\text{tab2=\k=1?\tabb:\taba}
\integer{rep1=\k}
\integer{rep2=3-\k}
\statement{
  Voici deux tableaux des variations et quatre courbes sinusoïdales:
<div class="float_right">
\tab1

\tab2
</div>
<table class="wimscenter wimsborder">
<tr><td>\(C_1)</td><td>\(C_2)</td></tr>
<tr><td>\draw{200,200}{\dessin1}</td><td>\draw{200,200}{\dessin2}</td></tr>
<tr><td>\(C_3)</td><td>\(C_4)</td></tr>
<tr><td>\draw{200,200}{\dessin3}</td><td>\draw{200,200}{\dessin4}</td></tr>
</table>
<br class="clearall">
  Compléter les phrases suivantes&nbsp;:
<ul><li>
  Le tableau de variations \(T_1) est celui de la fonction \embed{reply1} sur &#91; 0; \(2\pi) &#93;.
</li><li>
  Le tableau de variations \(T_2) est celui de la fonction \embed{reply2} sur &#91; 0; \(2\pi) &#93;.
</li><li>
  La courbe \embed{reply3,\size} est une restriction de celle de la fonction \embed{reply4}.
</li><li>
  La courbe \embed{reply5,\size} est une restriction de celle de la fonction \embed{reply6}.
</li></ul>

}
\answer{T1}{\rep1;\lstfnc}{type=menu}
\answer{T2}{\rep2;\lstfnc}{type=menu}
\answer{}{\rep3;\lstbadc}{type=dragfill}
\answer{}{\rep4;\lstfnc}{type=menu}
\answer{}{\rep5;\lstgcb}{type=dragfill}
\answer{}{\rep6;\lstfnc}{type=menu}
\condition{(\reply3 issametext C\gc1 and \reply4 issametext \lstfnc[\gf1]) or (\reply3 issametext C\gc2 and \reply4 issametext \lstfnc[\gf2])}
\condition{(\reply5 issametext C\gc1 and \reply6 issametext \lstfnc[\gf1]) or (\reply5 issametext C\gc2 and \reply6 issametext \lstfnc[\gf2])}
#endif
