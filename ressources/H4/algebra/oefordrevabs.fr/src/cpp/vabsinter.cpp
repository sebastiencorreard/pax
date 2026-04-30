target=vabsinter
%%
\observation{L'objet de l'exercice est de traduire un abs(x-a) < b par l'appartenance à un intervalle}
%%
\language{fr}
\computeanswer{yes}
\precision{1000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}
#include "css.inc"

%% les deux racines de f1 et f2 %%
%% borne pour le rayon %%
\integer{rayonmax=20}

%% borne pour le centre %%
\integer{centremax=10}

%% Choix des bornes %%
\integer{sing1=random(1..\centremax)*randint(1,-1)}
\integer{sing2=random(1..\rayonmax)}

%% la liste des objets que l'on peut cliquer pour résoudre l'exercice %%
\text{x1=\(\sing1)}
\text{x2=\(\sing2)}
\integer{x3=\sing1-(\sing2)}
\integer{x4=\sing1+(\sing2)}
\integer{x5=\sing2-(\sing1)}
\integer{x6=-(\sing2)-(\sing1)}
\text{x3=\(\x3)}
\text{x4=\(\x4)}
\text{x5=\(\x5)}
\text{x6=\(\x6)}
\text{crocg=&#91;}
\text{crocd=&#93;}
\text{union=\(\cup)}
\text{inter=\(\cap)}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{ptvirg=&#59;}

\text{permut=shuffle(\x1,\x2,\x3,\x4,\x5,\x6)}

\text{clicList=
\crocg,\ptvirg,\crocd,\union,\inter,\infg,\infd,\permut[1],\permut[2],\permut[3],\permut[4],\permut[5],\permut[6]
}
%% taille des symboles et des champs à remplir par clic LxHxnb %%
\text{size=50x40x12}

%% Choix du type d'encadrement
%% la liste des symboles d'inégalité %%
\text{sgt=>}
\text{sge=\(\ge )}
\text{slt=<}
\text{sle=\(\le )}

\text{symboles=\slt,\sle,\sgt,\sge}
\text{swapsymb=3,4,1,2}
\integer{symbx1=randint(1..2)}
\integer{symbx2=randint(1..2)}
\integer{symbx=\symbx1+2*(\symbx2-1)}
%% Choix de l'hypothèse
    \text{eqx=\(abs(texmath(x-(\sing1)))) \symboles[\symbx] \sing2 }

%% calcul de la bonne réponse %%

\if{\symbx2=1}{
  \text{croc1=\symbx1=1?\crocd:\crocg}
  \text{croc2=\symbx1=1?\crocg:\crocd}
  \text{brep=\croc1,\x3,\ptvirg,\x4,\croc2}
  \text{brepf=\croc1\x3\ptvirg\x4\croc1}
  \text{typeeq=l'encadrement}
  }{
  \text{croc1=\symbx1=1?\crocg:\crocd}
  \text{croc2=\symbx1=1?\crocd:\crocg}
  \text{brep=\crocd,\infg,\ptvirg,\x3,\croc1,\union,\croc2,\x4,\ptvirg,\infd,\crocg}
  \text{brepf=\crocd\infg\ptvirg\x3\croc1\union\croc2\x4\ptvirg\infd\crocg}
}
\text{size1=\confparm1=1 ? :x-large}
%% Maintenant, rédigeons l'énoncé %%
\statement{
<div class="rm">
 \name_question[1]
  <div class="wimscenter">\eqx</div>
   \name_question[2]
  <div class="wims_instruction">\name_instruction</div>
<p>\name_answer:</p>
 <div>\(x \in\) \embed{reply1,\size}</div>
</div>
}

%% Récupération des réponses %%
\answer{}{\brep;\clicList}{type=clickfill}
