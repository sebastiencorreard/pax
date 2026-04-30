target=deducencad1
%%
%% L'objet de l'exercice est d'obtenir une inégalité concernant f(x)
%% a partir d'une inégalité sur x
%%
\language{fr}
\computeanswer{yes}
\precision{1000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}
#include "css.inc"
\text{tailleetiq = 40x40}
%% la liste des objets que l'on peut cliquer pour résoudre l'exercice %%
\text{sgt=>}
\text{sge=\(\ge )}
\text{slt=<}
\text{sle=\(\le )}

\text{symboles=\slt,\sle}
\text{swapsymb=2,1}

%% inégalité sur x %%
%%
\integer{a3=randint(1..10)*randint(-1,1)}
\integer{a4=randint(1..10)*randint(-1,1)}
\integer{a4=\a3=\a4?\a4+10:\a4}
\integer{a1=\a3>\a4?\a4:\a3}
\integer{a2=\a3>\a4?\a3:\a4}
\integer{symbx1=randint(1..2)}
\integer{symbx2=randint(1..2)}
\text{eqx=\a1 \symboles[\symbx1] \(x) \symboles[\symbx2] \a2}

%% choix de la fonction f %%
%%
\integer{k=random(1,2)}
  k=1 fonction carrée, 2= fonction inverse

\integer{c=randint(1..10)*randint(-1,1)}
\integer{b=randint(1..10)*randint(-1,1)}
\integer{d=randint(1..5)}
\integer{a12=\a1-\d}
\text{eqfx=\k=1?texmath(maxima((\b)*(x -(\a1))^2 +(\c);)):texmath(maxima((\b)/(x -(\a12));) +(\c))}

%% calcul de la réponse %%
%%préparation des étapes intermédiaires pour la solution
\if{\k=1}
  {
  \integer{a22=\a2 -(\a1)}
  \text{eq1= 0 \symboles[\symbx1] texmath(x-(\a1)) \symboles[\symbx2] \a22}
  \integer{a23=(\a22)^2}
  \text{eq2 = 0 \symboles[\symbx1] \(texmath(maxima((x-(\a1))^2;))) \symboles[\symbx2] \a23}
  \integer{a24=\b*(\a23)}
  \text{eq3 =\b>0?0 \symboles[\symbx1] \(texmath(maxima(\b*(x-(\a1))^2;))) \symboles[\symbx2] \a24:\a24 \symboles[\symbx2] \(texmath(maxima(\b*(x-(\a1))^2;))) \symboles[\symbx1] 0}
  \integer{a25=\a24+(\c)}
  \text{eq4 =\b>0?\c \symboles[\symbx1] \(texmath(maxima(\b*(x-(\a1))^2;)+(\c))) \symboles[\symbx2] \a25:\a25 \symboles[\symbx2] \(texmath(maxima(\b*(x-(\a1))^2;)+(\c))) \symboles[\symbx1] \c}
  \integer{rep1=\b>0?\c:\a25}
  \text{rep2=\b>0?\symboles[\symbx1]:\symboles[\symbx2]}
  \text{rep3=\b>0?\symboles[\symbx2]:\symboles[\symbx1]}
  \integer{rep4=\b>0?\a25:\c}
  \text{expliqk=les nombres positifs sont rangés dans le même ordre que leurs carrés }
 }
 {
  \integer{a22=\a2-(\a12)}
  \text{eq1= \d \symboles[\symbx1] texmath(x-(\a12)) \symboles[\symbx2] \a22}
  \rational{a23=1/(\d)}
  \rational{a13=1/(\a22)}
  \text{eq2 = \a13 \symboles[\symbx2] \(texmath(maxima(1/(x-(\a12));))) \symboles[\symbx1] \a23}
  \rational{a24=\b*(\a23)}
  \rational{a14=\b*(\a13)}
  \text{eq3 =\b>0?\a14 \symboles[\symbx2] \(texmath(maxima(\b/(x-(\a12));))) \symboles[\symbx1] \a24:\a24 \symboles[\symbx1] \(texmath(maxima(\b/(x-(\a12));))) \symboles[\symbx2] \a14}
  \rational{a25=\a24+(\c)}
  \rational{a15=\a14+(\c)}
  \text{eq4 =\b>0?\a15 \symboles[\symbx2] \(texmath(maxima(\b/(x-(\a12));)+(\c))) \symboles[\symbx1] \a25:\a25 \symboles[\symbx1] \(texmath(maxima(\b/(x-(\a12));)+(\c))) \symboles[\symbx2] \a15}
  \rational{rep1=\b>0?\a15:\a25}
  \text{rep2=\b>0?\symboles[\symbx2]:\symboles[\symbx1]}
  \text{rep3=\b>0?\symboles[\symbx1]:\symboles[\symbx2]}
  \rational{rep4=\b>0?\a25:\a15}
  \text{expliqk=les nombres positifs sont rangés dans <span style="color:red">l'ordre inverse</span> de leurs inverses}
  }
\text{clicList=
\slt,\sle
}
\text{brep=\symboles[\symbfx]}
\text{expliqb1=\b>0?\name_expliqb1[1]:\name_expliqb1[2]}
\text{expliqb2=\b>0?\name_expliqb2[1]:\name_expliqb2[2]}
\text{size=\confparm1=1 ? :x-large}
%% Maintenant, rédigeons l'énoncé %%
\statement{
<div class="rm spacer">
  \name_question[1] \eqx, \name_question[2] \(\eqfx\) ?
  <p>\name_answer:</p>
  <div class="wimscenter">
      \embed{reply1,5} \embed{reply2,\tailleetiq} \(\eqfx) \embed{reply3,\tailleetiq} \embed{reply4,5}
  </div>
 </div>
}

%% Récupération des réponses %%
\answer{}{\rep1}{type=numeric}
\answer{}{\rep2;\clicList}{type=clickfill}
\answer{}{\rep3;\clicList}{type=clickfill}
\answer{}{\rep4}{type=numeric}
%% une indication sous forme de rappel des théoremes %%
\hint{
<div class="hint">
  Servez-vous de théorèmes sur les inégalités
<ul>
<li> On peut ajouter un même nombre aux deux membres d'une inégalité:<br>
 a < b \(\Leftrightarrow) a+c < b+c pour tout réel c
</li><li> On peut multiplier par un même réel strictement positif les deux membres d'une inégalité:<br>
 a < b \(\Leftrightarrow) a \(\times) c < b \(\times) c pour tout c > 0
</li><li> On peut multiplier par un même réel strictement négatif les deux membres
 d'une inégalité <span style="color:red"> en changeant le symbole de l'inégalité:</span><br>
 a < b \(\Leftrightarrow) a \(\times) c > b \(\times) c pour tout c < 0
</li><li> les nombres positifs sont rangés dans le même ordre que leurs carrés:<br>
 0 < a < b \(\Leftrightarrow) \(a^2) < \(b^2)
</li><li> les nombres positifs sont rangés dans <span style="color:red">l'ordre inverse</span> de leurs inverses: <br>
 0 < a < b \(\Leftrightarrow) \(\frac{1}{a}) > \(\frac{1}{b})
</li></ul>
</div>
}
%% une solution rédigée au cas où %%
\solution{
  <div class="rm solution">
  Voici un <span style="color:darkcyan">exemple de rédaction</span>
  de la solution:
<table><tr><td>
  \eqx </td>
<td>\(\Leftrightarrow ) \eq1 </td><td> On peut ajouter un même nombre aux trois membres d'un encadrement</td></tr>
<tr><td>&nbsp;</td><td> \(\Leftrightarrow) \eq2 </td><td>\expliqk </td></tr>
<tr><td>&nbsp;</td><td> \(\Leftrightarrow) \eq3 </td><td> \expliqb1 </td></tr>
<tr><td>&nbsp;</td><td> &nbsp; </td><td> \expliqb2 </td></tr>
<tr><td>&nbsp;</td><td> \(\Leftrightarrow) \eq4 </td><td> On peut ajouter un même nombre aux trois membres d'un encadrement</td></tr>
</table>
</div>
}
