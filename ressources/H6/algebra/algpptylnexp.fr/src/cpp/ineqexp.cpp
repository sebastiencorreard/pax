target=ineqexp1 ineqexp2
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}
#if defined TARGET_ineqexp1
\text{lim=10}
\text{lim2=5}
\text{var=x,u,z,t}
#endif
#if defined TARGET_ineqexp2
\text{lim=50}
\text{lim2=20}
\text{var=x,y,z,t}
#endif
\integer{sa=random(1,-1)}
\integer{a0=random(1..\lim)}
\integer{a=\a0*\sa}
\integer{sb=random(1,-1)}
\integer{b0=random(1..\lim)}
\integer{b=\b0*\sb}
\integer{sc=random(1,-1)}
\integer{c=random(1..\lim2)*\sc}
\integer{d=random(-\lim..\lim)}
\text{x=randitem(\var)}
\function{u=(\b=0)?\a\x:\a\x+\b}
\text{utex=texmath(\u)}
#if defined TARGET_ineqexp1
\function{f=(\d=0)? \c*e^(\u):\c*e^(\u) - \d}
\text{symb=>}
!!! chgment sens inégalité si division par c negatif
\text{symb1=(\c>0)?\symb:<}
#endif
#if defined TARGET_ineqexp2
\text{symb=random(<,>)}
\text{pos=position(\symb,<,>)}
!!! chgment sens inégalité
\text{symb1=(\c>0)?\symb}
\text{symb1=(\c<0 && \pos=1)?item(2,<,>)}
\text{symb1=(\c<0 && \pos=2)?item(1,<,>)}
#endif
\rational{rep1=\d/\c}
\text{signe=(\rep1=0)?\name_posneg[3]}
\text{signe=(\rep1>0)?\name_posneg[1]}
\text{signe=(\rep1<0)?\name_posneg[2]}
\integer{takeln=(\signe issametext \name_posneg[1])?1:2}
\integer{chge=\a*\c}
#if defined TARGET_ineqexp1 || defined TARGET_ineqexp2
\text{symb2=(\chge>0)?\symb:<}
#endif
#if defined TARGET_ineqexp2
\text{symb2=(\chge<0 && \pos=1)?item(2,<,>)}
\text{symb2=(\chge<0 && \pos=2)?item(1,<,>)}
#endif
!!!!! 16 oct 2009 : si rep1 = 1 , simplifier ln(1) = 0
\text{lnrep1=(\rep1=1)?0:ln(\rep1)}
\function{rep2=(\a=1)?\lnrep1-\b:(\lnrep1-\b)/(\a)}
\function{rep2=(\a=-1)?\b-\lnrep1}
\function{rep2=(\rep1=1)?simplify(\rep2)}

!!! pretty printing for rep2
\text{oppb=(\b<0)?+\b0:-\b}
#if defined TARGET_ineqexp1
\text{texrep2=(\a=1)?\ln(\rep1) \oppb:\frac{\ln(\rep1) \oppb}{\a}}
#endif
#if defined TARGET_ineqexp2
\text{texrep2=\frac{\ln(\rep1) \oppb}{\a}}
\text{texrep2=(\a=1)?\ln(\rep1) \oppb}
#endif
\integer{pprint=(\a<0 || \rep1=1)?1:0}
\if{\pprint=1}{
  \rational{pprep2=(\rep1=1)?-\b/\a}
  \text{pprep2=(\rep1!=1 && \a<0)?\frac{\b - \ln(\rep1)}{\a0}}
  \text{pprep2=(\rep1!=1 && \a=-1)?\b - \ln(\rep1)}
}{ \text{pprep2=\texrep2} }
#if defined TARGET_ineqexp1
\text{ineq=f(\x) \symb 0}
\text{ineq1=\(\ineq\)}
#endif
#if defined TARGET_ineqexp2
\text{ineq=\c*e^(\u) \symb \d}
\text{ineq1=(I)}
#endif
!!! intervalle des solutions
\if{\takeln=2}{
\integer{typesol=(\symb1 issametext <)?1:2}}
\text{laregle= la règle \(e^u \symb1 v \Longleftrightarrow u \symb1 ln(v)\)}
#if defined TARGET_ineqexp1
\if{\takeln=1}{
  \text{s1=\symb2 issametext <?+:-}
  \text{s2=\symb2 issametext <?-:+}
}
\if{\takeln=2}{\text{s3=\typesol=2?+:-}}
#endif
!!!!!! QUESTIONS / ANSWERS
\if{\takeln=1}{
  \text{questionstep2=choice3,reply3}
  \text{questionstep3=choice4,choice5}
}{
  \text{questionstep2=reply4}
  \text{questionstep3=choice6}
}
#if defined TARGET_ineqexp1
\steps{choice1,reply1,reply2,choice2
\questionstep2
\questionstep3}
#endif
#if defined TARGET_ineqexp2
\steps{choice1,reply1,reply2,choice2
\questionstep2
}
#endif
!!! STATEMENT
\statement{
#if defined TARGET_ineqexp1
On veut étudier en fonction de \(\x\) le signe de :
\(f(\x) = \f\) .
Pour ce faire, on commence par résoudre l'inéquation \(\ineq\).
<p>
Résolvez l'inéquation sur papier libre
puis complétez les affirmations suivantes.
</p>
#endif
#if defined TARGET_ineqexp2
On veut résoudre dans \(\mathbb{R}\) l'inéquation (I) : \(\ineq\) .
<p>
Résolvez (I) sur papier libre,
en complétant les affirmations suivantes.
</p>
#endif
\if{\step=1}{
<ul><li>
On peut écrire l'équivalence suivante :
<div class="wimscenter">
  \ineq1 \(\Longleftrightarrow e^{\utex}\)
  \embed{choice1} \embed{reply1,5}
</div>
</li><li>
On \embed{reply2} appliquer \laregle car
le deuxième membre de l'inéquation est \embed{choice2}.
</li></ul>
}
\if{\step=2 && \takeln=1}{
<ul><li>
On peut écrire l'équivalence suivante :
<div class="wimscenter">
  \ineq1 \(\Longleftrightarrow e^{\utex} \symb1 \rep1 \)
</div>
</li>
<li>
 On peut appliquer \laregle, car
le deuxième membre de l'inéquation est <span class="bold"\signe</span>.
</li>
<li>
En appliquant cette règle, on obtient :
<div class="wimscenter">
\ineq1 \(\Longleftrightarrow \x\)\embed{choice3} \embed{reply3}.</div>
</li></ul>}

\if{\step=2 && \takeln=2}{
<ul>
<li>On peut écrire l'équivalence suivante :
<div class="wimscenter">
 \ineq1 \(\Longleftrightarrow e^(\utex) \symb1 \rep1\)
</div>
</li><li>
On <font color=blue>ne peut pas</font> appliquer \laregle , car
le deuxième membre de l'inéquation est <font color=blue>\signe</font>.
</li>
<li> Sachant que \(e^{t}>0) pour tout réel t, on conclut que
l'inéquation \ineq1 \embed{reply4}.
</li></ul>}
#if defined TARGET_ineqexp1
\if{\step=3 && \takeln=1}{
  <ul><li>
  En résolvant \(\ineq) on obtient :
  <div class="wimscenter">\(\ineq) \(\Longleftrightarrow)
  \(\x) <font color=blue> \symb2 \(\pprep2)</font>.</div>
  </li>
  <li>
  Posons \(\x _{0} = \pprep2 ). On dresse alors le tableau de signes suivant :
  <table style="width:75%" class="wimscenter wimsborder">
  <tr>
  <td style="width:5%;text-align:center">\(\x)</td>
  <td style="width:45%;text-align:left">\(-\infty)</td>
  <td style="width:5%;text-align:center">\(\x _{0})</td>
  <td style="width:45%;text-align:right"> \(+\infty)</td>
  </tr><tr>
  <td style="text-align:center">\(f(\x))</td>
  <td style="text-align:center">\embed{choice4}</td>
  <td style="text-align:center">0</td>
  <td style="text-align:center">\embed{choice5}</td>
  </tr>
  </table>
  </li></ul>
  }
  \if{\step=3 && \takeln=2}{
  <ul>
  <li>En résolvant \(\ineq\) on obtient que l'inéquation
  \if{\typesol=1}{n'a aucune solution}{admet tous les réels comme solutions}.
  </li><li>
  On dresse alors le tableau de signes suivant :
  <table style="width:60%;" class="wimscenter wimsborder">
  <tr>
  <td style="width:5%">\(\x)</td>
  <td style="width:5%">\(-\infty\)</td>
  <td style="width:85%"></td>
  <td style="width:5%"> \(+\infty\)</td>
  </tr><tr>
  <td>\(f(\x))</td>
  <td></td>
  <td>\embed{choice6}</td>
  <td></td>
  </tr>
  </table>
  </li></ul>
  }
#endif
}
\choice{Première question a.}{\symb1}{<,>}{option=nonstop}
\answer{Première question b.}{\rep1}{type=numexp}{option=nonstop}
\answer{Deuxième question a.}{\takeln;peut,ne peut pas}{type=menu}{option=nonstop}
\choice{Deuxième question b.}{\signe}{\name_posneg[2],\name_posneg[3],\name_posneg[1]}{option=nonstop}
#if defined TARGET_ineqexp1
\choice{Troisième question a.}{\symb2}{<,>}{option=nonstop}
\answer{Troisième question b.}{\rep2}{type=formal}{weight=2}{option=nonstop}
\answer{Troisième question}{\typesol;n'a aucune solution,admet tous les réels comme solutions}{type=menu}{option=nonstop}
\choice{Tableau de signes a.}{\s1}{+,-}
\choice{Tableau de signes b.}{\s2}{+,-}
\choice{Tableau de signes}{\s3}{+,-}
#endif
#if defined TARGET_ineqexp2
\choice{Troisième question a.}{\symb2}{<,>}
\answer{Troisième question b.}{\rep2}{type=formal}{weight=2}
\answer{Troisième question}{\typesol;n'a aucune solution,admet tous les réels comme solutions}{type=menu}

#endif
!!!!! RESOLUTION FEEDBACK
#if defined TARGET_ineqexp1
\feedback{0=0}{
<b>Voici une étude de signe détaillée de \(f(\x) = \f) :</b>

<p>La fonction exponentielle est définie sur \(\mathbb{R}\), donc il n'y a pas de précaution de définition à prendre.</p>
<p>On résout d'abord l'inéquation \(\ineq\) :</p>
 <div class="wimscenter">
\(\ineq\) \(\Longleftrightarrow e^{\utex} \symb1 \rep1\)
</div>
\if{\takeln=1}{
On peut appliquer \laregle, car le logarithme du second membre est défini (\rep1 > 0):
<div class="wimscenter">
\(\ineq) \(\Longleftrightarrow \utex \symb1 ln(\rep1)\)
<br>
\(\ineq) \(\Longleftrightarrow \a\x \symb1 ln(\rep1) \oppb \)
 <br>
\(\ineq) \(\Longleftrightarrow \x \symb2 \texrep2 \)
 <br>
\if{\pprint=1}{\(\ineq) \(\Longleftrightarrow \x \symb2 \pprep2\)}
</div>
On obtient le tableau de signes suivant, où \(\x _{0} = \pprep2\) :
<table style="width:75%;" class="wimscenter wimsborder"><tr>
<td style="width:5%">\(\x\)</td>
<td style="width:45%;text-align:left">\(-\infty\)</td>
<td style="width:5%">\(\x _{0}\)</td>
<td style="width:45%;text-align:right"> \(+\infty\)</td>
</tr><tr>
<td>\(f(\x)\)</td><td>\s1</td><td>0</td><td>\s2</td>
</tr></table>
}
\if{\takeln=2}{
<p>On sait que \(e^{\alpha}>0\) pour tout réel \(\alpha\).
 \if{\symb1 issametext >}{
 Donc  l'inégalité  \(e^(\u) > \rep1\)  est toujours vraie, quel que soit \(\x).}
{ Donc l'inégalité \(e^(\u) < \rep1\) est toujours fausse, quel que soit \(\x).}
On en déduit
\if{\typesol=1}{qu'il n'y a aucun réel \(\x) tel que \(\ineq).}
{que \(\ineq) pour tout réel \(\x).}</p>
<p>D'où le tableau de signes suivant :</p>
<table style="width:60%;" class="wimscenter wimsborder">
<tr>
<td style="width:5%">\(\x\)</td>
<td style="width:5%">\(-\infty\)</td>
<td style="width:85%"> </td>
<td style="width:5%">\(+\infty\)</td>
</tr><tr>
<td>\(f(\x)\)</td>
<td></td>
<td>\s3</td>
<td></td>
</tr>
</table>
}
}
#endif
#if defined TARGET_ineqexp2
\feedback{0=0}{
<b>Voici une résolution détaillée de l'inéquation (I) : \(\ineq\) :</b>

<p>La fonction exponentielle est définie sur \(\mathbb{R}\),
donc il n'y a aucune précaution de définition à prendre.</p>
<p> On commence par diviser l'inéquation par \(\c\)
\if{\c<0}{(en inversant le sens de l'inégalité car on divise par un nombre négatif)} :</p>
<div class="wimscenter">
(I) \(\Longleftrightarrow e^{\utex} \symb1 \rep1\)
</div>
\if{\takeln=1}{
On peut appliquer \laregle, car le logarithme du second membre est défini (\rep1 > 0\):
<div class="wimscenter">
(I) \(\Longleftrightarrow \utex \symb1 ln(\rep1)\)
<br>
(I) \(\Longleftrightarrow \a\x \symb1 ln(\rep1) \oppb \)
</div>
On divise par \(\a\) \if{\a<0}{(en inversant le sens de l'inégalité
  car on divise par un nombre négatif)} :
<div class="wimscenter">
(I) \(\Longleftrightarrow \x \symb2 \texrep2 \)
<br>
\if{\pprint=1}{
(I) \(\Longleftrightarrow \x \symb2 \pprep2 \)}
</div>
<p> Posons \(\x _{0} = \pprep2).
L'ensemble des solutions de (I) est l'intervalle
\if{\symb2 issametext >}{&#93; \(\x _0 \; ; \; +\infty) &#91;}{&#93; \( -\infty \; ; \; \x _0 ) &#91; .}
</p>
}
\if{\takeln=2}{
<p>On sait que \(e^{\alpha}>0) pour tout réel \(\alpha\). Donc on a \(e^(\u) >0\)
pour tout réel \(\x\).</p>
<p>Par suite, l'inégalité
\if{\symb1 issametext >}{
 \(e^(\u) > \rep1\) est toujours vraie, quel que soit \(\x\).}
{ \(e^(\u) < \rep1\) est toujours fausse, quel que soit \(\x\).}
On conclut que l'inéquation (I)
\if{\typesol=1}{n'a aucune solution.}{admet tous les réels comme solutions.}
L'ensemble des solutions de (I) est
\if{\typesol=1}{l'ensemble vide.}{\(\mathbb{R}\) entier.}
</p>
}
}
#endif
