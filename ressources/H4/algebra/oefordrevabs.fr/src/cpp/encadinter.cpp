target=encadinter
%%
\observation{ L'objet de l'exercice est de traduire un encadrement de x par l'appartenance à un intervalle}
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
%% borne pour la valeur absolue d'une des racines %%
\integer{singmax=20}

%% écart maximale entre les racines %%
\integer{singdif=30}

%% Choix des bornes %%
\integer{sing1=random(-\singmax..\singmax)}
\integer{sing2=random(1..\singdif)+\sing1}

%% la liste des objets que l'on peut cliquer pour résoudre l'exercice %%
\text{x1=\(\sing1)}
\text{x2=\(\sing2)}
\integer{x3=\sing1-random(1,5)}
\integer{x4=\sing2+random(1,5)}
\text{x3=\(\x3)}
\text{x4=\(\x4)}
\text{crocg=&#91;}
\text{crocd=&#93;}
\text{union=\(\cup)}
\text{inter=\(\cap)}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{ptvirg=&#59;}

\text{permut=shuffle(\x1,\x2,\x3,\x4)}

\text{clicList=
\crocg,\ptvirg,\crocd,\union,\inter,\infg,\infd,\permut[1],\permut[2],\permut[3],\permut[4]
}
%% taille des symboles et des champs à remplir par clic LxHxnb %%
\text{size=60x40x12}

%% Choix du type d'encadrement
\integer{k=randint(1..3)}
%% k= 1 encadrement, k= 2 x symb val , k=3 val symb x
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
\if{\k=1}{
  \text{eqx=\sing1 \symboles[\symbx1] \(x) \symboles[\symbx2] \sing2 }
}{
  \text{eqx=\k=2? \(x) \symboles[\symbx] \sing2: \sing1 \symboles[\symbx] \(x) }
}

%% calcul de la bonne réponse %%
\if{\k=1}{
  \text{croc1=\symbx1=1?\crocd:\crocg}
  \text{croc2=\symbx2=1?\crocg:\crocd}
  \text{brep=\croc1,\x1,\ptvirg,\x2,\croc2}
  \text{brepf=\croc1\x1\ptvirg\x2\croc1}
  \text{typeeq=\name_typeeq}
}{
  \text{typeeq=l'inégalité}
  \if{\k=2 and \symbx2=1}{
%% x < ou <= sing2
    \text{croc2=\symbx1=1?\crocg:\crocd}
    \text{brep=\crocd,\infg,\ptvirg,\x2,\croc2}
    \text{brepf=\crocd\infg\ptvirg\x2\croc2}
  }
  \if{\k=2 and \symbx2=2}{
%% x > ou >= sing2
    \text{croc1=\symbx1=1?\crocd:\crocg}
    \text{brep=\croc1,\x2,\ptvirg,\infd,\crocg}
    \text{brepf=\croc1\x2\ptvirg\infg\crocg}
  }
  \if{\k=3 and \symbx2=1}{
%% sing1 < ou <= x
    \text{croc1=\symbx1=1?\crocd:\crocg}
    \text{brep=\croc1,\x1,\ptvirg,\infd,\crocg}
    \text{brepf=\croc1\x1\ptvirg\infg\crocg}
  }
  \if{\k=3 and \symbx2=2}{
%% sing1 > ou >= x
    \text{croc2=\symbx1=1?\crocg:\crocd}
    \text{brep=\crocd,\infg,\ptvirg,\x1,\croc2}
    \text{brepf=\crocd\infg\ptvirg\x1\croc2}
  }
}
\text{size1=\confparm1=1 ? :x-large}
%% Maintenant, rédigeons l'énoncé %%
\statement{
<div class="rm">
      \name_question[1] \typeeq
      <div class="wimscenter">
        \eqx,
      </div>
      \name_question[2]?
  <p>\name_answer:</p>
  <div>
     \(x) \(\in\) \embed{reply1,\size}.
  </div>
</div>
}
%% Récupération des réponses %%
\answer{}{\brep;\clicList}{type=clickfill}
