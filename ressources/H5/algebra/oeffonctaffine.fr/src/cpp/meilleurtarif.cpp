target=meilleurtarif
\title{Le meilleur tarif}
\language{fr}
\author{Rémi, Belloeil}
\email{remi.belloeil@orange.fr}
\format{html}

#define TYPE 1
\text{list=1,5,6,8,7}
\text{list2=1,5,6,8,7}
\text{repchoix=f,a,b,c,d,e}
#include "method.inc"

%% Choix de la solution
\integer{k=randint(2,4,5)}
\integer{x=\k*randint(5..9)}

\real{aa=4/\k}
\integer{s=random(-1,1)}
\real{a=\aa*\s}
\real{ag=4+0.5*randint(0..14)}
\real{af=\ag+\a}

\integer{b=-\a*\x}
\real{b0= abs(\b)}
\real{bf=randint(5..20)}
\real{bg=\bf-\b}
\if{\bg<0}{
  \real{bf=\bf-\bg+10}
  \real{bg=\bf-\b}
              }

\function{\f=\af*x+\bf}
\function{\g=\ag*x+\bg}

%% Calcul des extrema
\integer{x1=10*ceil(min(2*\x,50)*0.1)}
\integer{x2=\x1+3}
\real{yf=\af*\x1+\bf}
\real{yg=\ag*\x1+\bg}
\integer{y1=50*ceil(max(\yf,\yg)/50)}
\if{\bf<\bg}{
  \integer{y2=20}
  \integer{y3=20*ceil(\y1/100)}
}{
  \integer{y2=20*ceil(\y1/100)}
  \integer{y3=20}
}
%% Graphique %%
\text{graph = xrange -5,\x2
yrange -20,\y1
linewidth 1
parallel 5,0,5,\y1,5,0,22,black
parallel 0,50,\x1,50,0,50,20,black
linewidth 2
arrow -5,0,\x1,0,10,black
arrow 0,-20,0,\y1,10,black
text black, -2,-2,large,"0"
text black, 9,-2,large,"10"
text black, 19,-2,large,"20"
text black, 29,-2,large,"30"
text black, 39,-2,large,"40"
text black, 49,-2,large,"50"
text black, 59,-2,large,"60"
text black, -4,3,large,"0"
text black, -4,53,large,"50"
text black, -4,103,large,"100"
text black, -4,153,large,"150"
text black, -4,203,large,"200"
text black, -4,253,large,"250"
text black, -4,303,large,"300"
text black, -4,353,large,"350"
text black, -4,403,large,"400"
text black, -4,453,large,"450"
text black, -4,503,large,"500"
text black, -4,553,large,"550"
text black, -4,599,large,"600"
}
\text{url = draw(405,420
\graph)}
\text{graphS = \graph
text red, 2,\y2,giant,PA
text blue, 2,\y3,giant,GT
segment 0,\bf,\x1,\yf, red
segment 0,\bg,\x1,\yg, blue
}
\text{urlS = draw(405,420
\graphS)}

%% Textes pour le sens des inéquations
\text{slt=<}
\text{sgt=>}

\text{ListCo=\slt,\sgt}
\text{TCo= \a>0 ? \slt : \sgt }
\text{STCo= \a>0 ? moins : plus }
\integer{co= \a>0 ? 1 : 2 }
\text{ListTCo=inférieur,supérieur}

%% taille des symboles et des champs à remplir par clic LxHxnb %%
\text{size=70x25x1}

\text{W=}
\text{ETAPE = r1}
\text{COND = 1}
\nextstep{ \ETAPE}
\conditions{ \COND}

%%%%% énoncé de l'exo %%%%%
\statement{
<div class="wims_question">
Deux entreprises : "Petit Avion" (PA) et "Grand Train" (GT) proposent leurs tarifs pour fournir des tee-shirts à une association.<br>
PA fournit les tee-shirts à \af &euro; pièce et facture \bf &euro; les frais de transport de l'ensemble des tee-shirts.<br>
GT fournit les tee-shirts à \ag &euro; pièce et facture \bg &euro; les frais de transport.<br>
Le but de l'exercice est de savoir pour combien de tee-shirts l'entreprise PA coûte moins cher que GT pour l'association.</div>


\if{\step=1}{
#include "listmethodb.inc"
}
\if{\step>1}{
  \if{\W = a}{
  <p>Il s'agit de réaliser le graphique sur une feuille.</p>
  <p>L'association achètera au maximum \x1 tee-shirts et le coût sera certainement inférieur à \y1 €.</p>
  \if{\step=2}{
    <p><label for="reply7">Le prix pour \x1 tee-shirts avec PA est :</label> \embed{reply7,\size} &euro;</p>
  }
  \if{\step=3}{
    <ul>
     <li>Le prix pour \x1 tee-shirts avec PA est : \yf &euro;</li>
     <li><label for="reply8">Le prix pour \x1 tee-shirts avec GT est :</label> \embed{reply8,\size} &euro;</li>
    </ul>
  <p>Ces informations permettent de réaliser le graphique.</p>
  }
  \if{\step=4}{
    Le graphique doit se présenter comme ceci :<br>
    <img src="\url" alt="quadrillage avec une graduation horizontale de 0 à \x1 et verticale de 0 à \y1">
    <p>Il reste à tracer les droites qui représentent les coûts de PA et GT en fonction du nombre de tee-shirts,<br>
en joignant les points de coordonnées (0;\bf) à (\x1;\yf) et de (0;\bg) à (\x1;\yg).</p>
  }
}{
  <p>On note \(f(x)) et \(g(x)) le coût de \(x) tee-shirts, transport compris, respectivement pour PA et GT.</p>
      \if{\step=2 and \W!=f}
      {<ul class="wims_nopuce">
      <li>Le prix total pour \(x) tee-shirts avec PA est <label for="reply2">\(f(x)=)</label> \embed{reply2,\size} &euro;</li>
      <li>Le prix total pour \(x) tee-shirts avec GT est <label for="reply3">\(g(x)=)</label> \embed{reply3,\size} &euro;</li>
      </ul>
}
}

\if{\W = b}{
  \if{\step=3}{
  L'équation \(\f = \g) équivaut à :
  <ul class="wims_nopuce">
  <li><label for="reply4">\a \(x) =</label> \embed{reply4,\size}</li>
  <li><label for="reply5">\(x) =</label> \embed{reply5,\size}</li>
  </ul>
  }
  \if{\step=4}{
  <p>L'équation \(\f = \g\) équivaut à \(x\) = \x</p>
  }}
  \if{\W = c}{
      \if{\step=3}{
     <p>\(f(x)=\) \f et \(g(x)=\) \g</p>
     <p>L'association achètera au maximum \x1 tee-shirts et le coût sera certainement inférieur à \y1 &euro;.</p>
     <ul class="wims_nopuce">
     <li><label for="reply7">Le prix pour \x1 tee-shirts avec PA est</label> : \embed{reply7,\size} &euro;</li>
     <li><label for="reply8">Le prix pour \x1 tee-shirts avec GT est</label> : \embed{reply8,\size} &euro;</li>
     </ul>
     <p>Il est pratique d'utiliser le tableau de valeurs de la calculatrice pour déterminer les valeurs ci-dessus.</p>
     }
     \if{\step=4}{
     <p>Entrer dans la calculatrice les fonctions :<br>
     \(f(x)=\) \f et \(g(x)=\) \g</p>
     Définir la fenêtre :
     <ul>
     <li>Xmin=0</li>
     <li>Xmax=\x1</li>
     <li>Ymin=0</li>
     <li>Ymax=\y1</li>
     </ul>
     <p>Afficher le graphique pour comparer les tarifs.
     On peut utiliser le tableau de valeurs de la calculatrice pour comparer les tarifs
     de façon précise.</p>
     }
  }
  \if{\W = d}{
     \if{\step=3}{
     L'inéquation \(\f < \g\) équivaut à :
     <ul class="wims_nopuce">
      <li><label for="reply4">\a \(x\) < </label>\embed{reply4,\size}</li>
      <li><label for="reply6">\(x\)</label> \embed{reply6} &nbsp \embed{reply5,\size}</li>
     </ul>
     }
     \if{\step=4}{
     <p>L'inéquation \(\f < \g\) équivaut à \(x\) \TCo \x</p>
     }
  }

\if{\step=4 or \W = f}{
<div><label for="reply9">Le prix proposé par PA est inférieur à celui proposé par GT
lorsque le nombre de tee-shirts est</label> \embed{reply9}<label for="reply10"> à </label>\embed{reply10}.</div>
}
}
}

%%% soumission de réponse %%%

\answer{Méthode}{\var1;\repchoix}{type=radio}{option=nonstop}
\answer{\(f(x)=\)}{\f}{type=algexp}
\answer{\(g(x)=\)}{\g}{type=algexp}
\answer{2ème membre}{-\b}{type=numeric}
\answer{\(x\)}{\x}{type=numeric}
\answer{Sens de l'inéquation}{\co;\ListCo}{type=menu}
\answer{Prix max avec PA}{\yf}{type=numeric}
\answer{Prix max avec GT}{\yg}{type=numeric}
\answer{Connecteur}{\co;\ListTCo}{type=menu}
\answer{}{\x}{type=numeric}
\condition{Choix de la méthode}{1=1}

#include "method_step.inc"
\text{W=\var1}
\solution{
<p>Le graphique est assez facile à faire si on connaît les valeurs maximales.</p>
<img src="\urlS" alt="graphique avec deux segments qui représentent les deux tarifs et qui se croisent">
<p>Mais les coordonnées précises du point d'intersection sont souvent difficiles à lire.</p>
<p>L'utilisation de la calculatrice permet de préciser pour combien de tee-shirts les prix sont égaux.</p>
<p>Résoudre l'équation \(\f = \g\) est très rapide
mais il faut réfléchir pour savoir si le tarif de PA est plus avantageux avant ou après la solution.</p>
<p>La méthode la plus rapide consiste à résoudre l'inéquation \(\f < \g\).</p>
<p>L'inéquation \(\f < \g\) équivaut à \(x\) \TCo \x.</p>
<p>La commande est plus avantageux chez PA lorsque l'association achète \STCo de \x tee-shirts.</p>}
