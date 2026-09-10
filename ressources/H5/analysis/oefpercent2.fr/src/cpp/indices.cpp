target=compevol,comployer1
\language{fr}
\range{-5..5}
\author{Rémi,Belloeil}
\email{remi.belloeil@orange.fr}
\computeanswer{yes}
\format{html}
\precision{1000}
\css{<style>
.myred {color:red}
.myblue {color:blue}
</style>}
% nombre de valeurs 10
% Séries statistiques L et V
% Listes L1 et L2 puis indices L3 e L4 dans les tableaux.
% Valeurs initiales loyer a0 et prix b0
#if defined TARGET_compevol
\title{Comparaison d'évolutions}
\description{Choisir parmi 5 graphiques pour comparer et comment calculer.}

\integer{k=randint(12..15)}
\integer{l=10}
\text{t1=la liste 1}
\text{t2=la liste 2}
\integer{b0=randint(15..20)}
\integer{a0=\k*\b0+10+randint(1..5)}
#endif
#if defined TARGET_comployer1
% Sens s = 1 : le loyer augmente plus vite, s = -1 : le loyer augmente moins vite, s = 0 l'augmentation est la même.

\title{Comparaison loyers et prix par graphique}
\description{Choisir parmi 4 graphiques, préciser les calculs à faire, comparer.}

\integer{s=randint(-1,0,1)}
\integer{cs=1-\s*\s}
\integer{l=5}
\text{t1=le loyer}
\text{t2=l'indice des prix}

\integer{b0=100}
\integer{a0=400+10*randint(1..5)}
#endif

\real{k1=100/\a0}
\real{k2=100/\b0}

\integer{ai=\a0}
\integer{bi=\b0}

\text{L=\a0}
\text{V=\b0}
\text{L3=\t1,100}
\text{L4=\t2,100}

#if defined TARGET_comployer1
\integer{ui=100}
\integer{vi=\b0}
\integer{h=1}
#endif
\text{L0=Année 2010 +,0}
\text{P1=polyline red, 0,\a0}
\text{P2=polyline blue, 0,\b0}
\text{P3=polyline red, 0,100}
\text{P4=polyline blue, 0,100}
#if defined TARGET_compevol
\real{wi=\a0/\l}
\text{P5=polyline red, 0,\wi}
#endif
\integer{M=\a0}
\integer{n=\b0}
\for{i=1 to 9}{
#if defined TARGET_compevol
  \integer{bi=\bi+randint(-2..5)}
  \integer{ai=\k*\bi+4*randint(0..\k)}
  \real{wi=\ai/\l}
  \text{P5=\P5,\i,\wi}
#endif
#if defined TARGET_comployer1
  \integer{d=\i%2}
  \integer{d=2*\d-1}
  \real{t=1+0.01*randint(5..8)}
  \real{h=\h*\t}
  \integer{bi=\bi*\t}
  \real{r=randint(1..5)*0.01}
  \integer{ai=\cs*\a0*\h*(1+\d*\r)+(1-\cs)*\ai*(\t+\s*\r)}
#endif
  \integer{M=max(\M,\ai)}
  \integer{n=max(\n,\bi)}
  \integer{ui=\k1*\ai}
  \integer{vi=\k2*\bi}

  \text{L0=\L0,\i}
  \text{L=\L,\ai}
  \text{V=\V,\bi}
  \text{P1=\P1,\i,\ai}
  \text{P2=\P2,\i,\bi}
  \text{P3=\P3,\i,\ui}
  \text{P4=\P4,\i,\vi}
  \if{\i=1}{\text{L3=\L3,\ui}}{\text{L3=\L3, xxx}}
#if defined TARGET_compevol
  \text{L4=\L4, xxx}
#endif
#if defined TARGET_comployer1
  \text{L4=\L4,\ui}
#endif
  }
\text{L1=\t1,\L}
\text{L2=\t2,\V}
\matrix{matrice=\L0;\L1;\L2}
\text{Mat=slib(text/matrixhtml [\matrice],wimscenter wimsborder,TH=[;1] CAPTION="Tableau initial")}
\matrix{matr2=\L0;\L3;\L2}
\text{Mat2=slib(text/matrixhtml [\matr2],wimscenter wimsborder,TH=[;1] CAPTION="Tableau des indices de base 100 en 2010")}

\integer{n=1.15*\n}
\integer{M=1.1*\M}
\integer{M1=max(110*\M/\a0,\n)}
#if defined TARGET_comployer1
\matrix{matr3=\L0;\L4;\L2}
\text{Mat3=slib(text/matrixhtml [\matr3],wimscenter wimsborder,TH=[;1] CAPTION="Tableau des indices de base 100 en 2010")}
\integer{l=ceil(\M/\n)}
\integer{wi=\a0/\l}
\text{P5=polyline red, 0,\wi}
#endif

#include "graphics.inc"

#if defined TARGET_compevol
\matrix{methode=Données brutes dans un même repère.
  Pourcentage par rapport à la valeur de 2010.
  Chaque série dans un repère adapté<br />l'un en dessous de l'autre.
  Un seul graphique avec un axe pour chaque liste
  Les coordonnées des points sont les nombres <br />de chaque série correspondant à la même année}
\text{t3=Voici deux séries statistiques&nbsp;:}
\steps{reply1
reply2,reply3}
#endif
#if defined TARGET_comployer1
\matrix{methode=Données brutes dans un même repère.
  Indices de base 100 en 2010.
  Chaque série dans un repère adapté l'un en dessous de l'autre.
  Un seul graphique avec un axe pour chaque liste.}
\text{t3=Jean compare l'évolution de son loyer depuis 2010 avec l'indice des prix.}

\steps{reply1
reply2
reply3}
#endif

\statement{\t3
\Mat

\if{\step=1}{
  <p>Déterminer parmi les graphiques ci-dessous celui qui permet le mieux de comparer
  les évolutions des deux séries statistiques à partir de 2010.
  </p>
  Dans les graphiques, \t1 est en rouge et \t2 en bleu.
  <ul class="inline">
  <li>\draw{400,400}{\graph1}<br />\embed{reply1,1,\methode[1;]}</li>
  <li>\draw{400,400}{\graph2}<br />\embed{reply1,2,\methode[2;]}</li>
  <li>\draw{400,200}{\graph3}<br />\draw{400,200}{\graph4}<br />\embed{reply1,3,\methode[3;]}</li>
  <li>\draw{400,400}{\graph5}<br />\embed{reply1,4,\methode[4;]}</li>
#if defined TARGET_compevol
  <li>\draw{400,400}{\graph6}<br />\embed{reply1,5,\methode[5;]}</li>
#endif
  </ul>
  }
\if{\step=2}{
  <p>
  Vous avez choisi le bon graphique !
  </p><p>
  Pour le réaliser, on doit compléter le tableau ci-dessous, obtenu à partir
  du tableau initial par proportionnalité.
  </p>
  \Mat2
  <ul><li><label for="reply2">
  Par quel nombre doit-on multiplier \t1 pour calculer l'indice de base 100 en 2010 ? \embed{reply2,10}<br />
#if defined TARGET_compevol
  </li><li>
  <label for="reply3">Par quel nombre doit-on multiplier \t2
pour calculer son indice de base 100 en 2010 ? </label>\embed{reply3,10}
#endif
  </li></ul>
  }
#if defined TARGET_comployer1
\if{\step=3}{
  <p>
  Bonne réponse !<br />
  Voici le tableau des indices de base 100 en 2010 des loyers et des prix.
  \Mat3
  <p>Voici le graphique où \t1 est en rouge et \t2 en bleu :</p>
  \draw{400,400}{\graph2}


  <p>Quel est votre avis :</p>
  <ul class="wims_nopuce"><li>
    \embed{reply3,1}</li><li>
    \embed{reply3,2}</li><li>
    \embed{reply3,3}</li>
  </ul>
  }
#endif
}

#if defined TARGET_compevol
\answer{Graphique}{2;A,B,C,D,E}{type=radio}
\answer{ Coefficient pour \t1 }{\k1}{type=numeric}
\answer{ Coefficient pour \t2 }{\k2}{type=numeric}
#endif
#if defined TARGET_comployer1
\answer{Graphique}{2;A,B,C,D}{type = radio}
\answer{ Coefficient liste 1 }{\k1}{type=numeric}
\answer{Analyse}{\rA;\Analyse}{type = radio}
#endif

\feedback{\reply1 issametext A }{
<p class="myred">
A : Ce graphique est facile à faire parce qu'il utilise les données brutes et n'utilise qu'un axe.<br />
Mais les valeurs des deux séries sont disproportionnées ce qui fait que les évolutions de la petite série sont écrasées et peu visibles.<br />
</p>
}

\feedback{\reply1 issametext C }{
<p class="myred">
C : Utiliser un repère adapté à chaque série et les placer l'un en dessous de l'autre est une bonne idée.<br />
Mais la distance entre les deux courbes ne facilite pas la comparaison.
</p>
}
\feedback{\reply1 issametext D }{
<p class="myred">
D : Réaliser un seul graphique avec deux axes est une bonne idée.<br />
Mais c'est difficile à réaliser et à lire et le point de départ en 2010
n'est pas automatiquement le même ce qui peut fausser la comparaison.
</p>
}
#if defined TARGET_compevol
\feedback{\reply1 issametext E }{
<p class="myred">
E : Utiliser les nombres de chaque série comme des coordonnées de points est une bonne idée.<br />
Mais cela permet surtout de déceler s'il y a une corrélation entre les nombres plutôt que leurs évolutions.
</p>
}
#endif
\solution{
  <p>
  B : Remplacer les données brutes par leur pourcentage par rapport à
  leur valeur de 2010 permet de bien comparer les évolutions des deux séries depuis 2010.
  </p><p>
  On appelle ces pourcentages les indices de base 100 en 2010.
  </p>
  <p>
  Les indices de base 100 en 2010 sont calculés par proportionnalité.<br />
  Pour obtenir l'indice de base 100 en 2010 d'une série de termes, il suffit de diviser
  chaque terme de la série par la valeur de l'année 2010 et de le multiplier par 100,
   par exemple pour  \t1 de multiplier chaque terme par 100/\a0.
  </p>
#if defined TARGET_comployer1
<p>
  \Analyse[\rA] car
  \if{\rA=1}{l'indice des loyers est toujours inférieur à l'indice des prix.}
  \if{\rA=2}{l'indice des loyers est parfois inférieur à l'indice des prix, parfois supérieur à l'indice des prix.}
  \if{\rA=3}{l'indice des loyers est toujours supérieur à l'indice des prix.}
  </p>
#endif

  <div class="wimscenter">\draw{400,400}{\graph2}</div>
  <ul class="inline wimscenter">
  <li class="myred">\t1 en rouge</li>
  <li class="myblue">\t2 en bleu</li>
  </ul>
}
