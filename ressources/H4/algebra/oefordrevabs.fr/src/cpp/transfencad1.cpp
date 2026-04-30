target=transfencad1
%%
\observation{L'objet de l'exercice est d'obtenir une inégalité concernant f(x) à partir d'une inégalité sur x}
%%
\language{fr}
\computeanswer{yes}
\precision{1000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}
#include "css.inc"
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
\integer{a4=\a3=\a4?\a4+1}
\integer{a1=\a3<\a4?\a3:\a4}
\integer{a2=\a3<\a4?\a4:\a3}
\integer{symbx1=randint(1..2)}
\integer{symbx2=randint(1..2)}
\text{eqx=\a1 \symboles[\symbx1] \(x) \symboles[\symbx2] \a2}

%% choix de la fonction f %%
%%
\integer{c=randint(1..10)*randint(-1,1)}
\integer{b=randint(1..10)*randint(-1,1)}
\text{eqfx=texmath((\b)*x +(\c))}

%% calcul de la réponse %%
\integer{symbfx1=\b>0?\symbx1:\symbx2}
\integer{symbfx2=\b>0?\symbx2:\symbx1}
\integer{d3=(\b)*(\a1)+(\c)}
\integer{d4=(\b)*(\a2)+(\c)}
\integer{d1=\d3<\d4?\d3:\d4}
\integer{d2=\d3<\d4?\d4:\d3}
%% preparation de la solution rédigée
\integer{a3=\b>0?\a1:\a2}
\integer{a4=\b>0?\a2:\a1}
\integer{e3=(\b)*(\a3)}
\integer{e4=(\b)*(\a4)}
\text{eq1=\b \(\times) (\a3) \symboles[\symbfx1] \b \(\times) \(x) \symboles[\symbfx2] \b \(\times) \a4}
\text{eq2=\e3 \symboles[\symbfx1] \b \(\times) \(x) \symboles[\symbfx2] \e4}
\text{expliq1=\b>0?\name_expliq1[1]:\name_expliq1[2]}
\text{expliq2=\b>0?\name_expliq2[1]:\name_expliq2[2]}

\text{clicList=
\slt,\sle
}
\text{brep1=\symboles[\symbfx1]}
\text{brep2=\symboles[\symbfx2]}
\text{size=50x40}

\text{size1=\confparm1=1 ? :x-large}
%% Maintenant, rédigeons l'énoncé %%
\statement{
<div class="rm">
  \name_question[1] \eqx,
  \name_question[2] \(\eqfx\) ?
  <p>\name_answer:</p>
  <div class="wimscenter">
    \embed{reply1,5} \embed{reply2,\size} \(\eqfx) \embed{reply3,\size} \embed{reply4,5}
  </div>
</div>
}

%% Récupération des réponses %%
\answer{}{\d1}{type=numeric}
\answer{}{\brep1;\clicList}{type=clickfill}
\answer{}{\brep2;\clicList}{type=clickfill}
\answer{}{\d2}{type=numeric}
%% une indication sous forme de rappel des théoremes %%
\hint{
<div class="rm hint">
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
</li><li> les nombres positifs sont rangés dans <span style="color:red">
l'ordre inverse</span> de leurs inverses: <br>
 0 < a < b \(\Leftrightarrow) \(\frac{1}{a}) > \(\frac{1}{b})
</li></ul>
</div>
}

%% une solution rédigée au cas où %%
\solution{
  <div class="rm solution">
  Voici un <b><span style="color:darkcyan">exemple de rédaction</span></b>
  de la solution:
  <br>
<table><tr><td>
  \eqx \(\Leftrightarrow ) \eq1 </td><td> En multipliant les 3 termes de l'encadrement par \b \expliq1,
</td></tr>
<tr><td>
  \(\Leftrightarrow) \eq2 </td><td> \expliq2 </td></tr>
<tr><td>
  \(\Leftrightarrow) \d1 \symboles[\symbfx1] \(\eqfx) \symboles[\symbfx2] \d2
  </td></tr></table>
</div>
}
