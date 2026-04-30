target=transfineg1
\text{expliq1=\b>0?positif:négatif}
\text{expliq2=\b>0?on conserve le sens de l'inégalité: on inverse le sens de l'inégalité}

%%
\observation{L'objet de l'exercice est d'obtenir une inégalité concernant f(x) à partir d'une inégalité sur x}
%%
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\computeanswer{yes}
\precision{1000}
\format{html}
#include "css.inc"
\text{tailleetiq=40x40}
%% la liste des objets que l'on peut cliquer pour résoudre l'exercice %%
\text{sgt=>}
\text{sge=\(\ge )}
\text{slt=<}
\text{sle=\(\le )}

\text{symboles=\sgt,\slt,\sge,\sle}
\text{symboles2=>,<,\ge,\le}
\text{swapsymb=2,1,4,3}
%% inégalité sur x %%
%%
\integer{a=randint(1..10)*randint(-1,1)}
\integer{symbx=randint(1..4)}
\text{eqx= \(x) \symboles[\symbx] \a}
\text{eqx__= x \symboles2[\symbx] \a}

%% choix de la fonction f %%
%%
\integer{c=randint(1..10)*randint(-1,1)}
\integer{b=randint(1..10)*randint(-1,1)}
\text{eqfx=texmath((\b)*x +(\c))}

%% calcul de la réponse %%
\integer{symbfx=\b>0?\symbx:\swapsymb[\symbx]}
\integer{d=(\b)*(\a)+(\c)}
%% preparation de la solution rédigée
\integer{e=(\b)*(\a)}
\text{eq1= \b \(\times) \(x) \symboles[\symbfx] \b \(\times) (\a)}
\text{eq1= \b \times x \symboles2[\symbfx] \b \times \a}
\text{eq2= \b \(\times) \(x) \symboles[\symbfx] \e}
\text{eq2= \b \times x \symboles2[\symbfx] \e}
\text{expliq1=\b>0?\name_expliq1[1]:\name_expliq1[2]}
\text{expliq2=\b>0?\name_expliq2[1]:\name_expliq2[2]}

\text{clicList=
\sgt,\sge,\slt,\sle
}
\text{brep=\symboles[\symbfx]}

text{size=\confparm1=1 ? :x-large}
%% Maintenant, rédigeons l'énoncé %%
\statement{
<div class="rm">
  \name_question[1] \eqx,
  \name_question[2] \(\eqfx\) ?
  <p>\name_answer:</p>
  <div class="wimscenter">
      \(\eqfx) \embed{reply1,\tailleetiq} \embed{reply2,5}

  </div>
</div>
}

%% Récupération des réponses %%
\answer{}{\brep;\clicList}{type=clickfill}
\answer{}{\d}{type=numeric}
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
</li><li> les nombres positifs sont rangés dans le même ordre que leurs carrés: <br>
 0 < a < b \(\Leftrightarrow) \(a^2) < \(b^2)
</li><li> les nombres positifs sont rangés dans <span style="color:red">l'ordre inverse</span> de leurs inverses: <br>
 0 < a < b \(\Leftrightarrow) \(\frac{1}{a}) > \(\frac{1}{b})
</li></ul>
</div>
}

%% une solution rédigée au cas où %%
\solution{<div class="rm solution">
  Voici un <b>exemple de rédaction</b> de la solution:
  <br>
en multipliant les 2 termes de l'inégalité par \b \expliq1, \expliq2 :
<br>

 \(\begin{split}
 \eqx__ &\Leftrightarrow \eq1 \\
  &\Leftrightarrow \eq2 \\
 & \Leftrightarrow \eqfx \symboles2[\symbfx] \d
\end{split}\)
</div>}
