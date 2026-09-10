target=correspobjspace
#include "author.inc"
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{100}
\text{size=confparm1=1 ? :x-large}
\matrix{axeliste=(Ox),(Oy),(Oz)}
\text{coeflist=\frac{1}{3},1, 3}
\text{anglelist= 30, 45, 60}
\text{equatsList=}
\text{natureList=}

\integer{maxobj=20}
\for{i=1 to \maxobj}{
\integer{r=random(1..5)}
\integer{x=random(-5..5)}
\integer{y=random(-5..5)}
\integer{z=random(-5..5)}
\integer{d1=random(1..3)}
\integer{d2=random(1..3)}
\integer{d3=random(1..3)}
\rational{xc=(\x)/(\d1)}
\rational{xc=(\x)}
\rational{yc=(\y)/(\d2)}
\rational{yc=(\y)}
\rational{zc=maxima((\z)/(\d3);)}
\rational{zc=(\z)}
\text{kanglelist = 1,2,3,1,2,3,1,2,3}
\integer{axe=random(1..3)}
*** test integer{axe=1}

\if{\i<6}{
  \integer{k=1}
   on choisit des sphères
  \rational{rep2=\xc}
  \rational{rep3=\yc}
  \rational{rep4=\zc}
  \rational{rep5=\r}
  \text{equat=simplify((x-\xc)^2+(y-\yc)^2+(z-\zc)^2-\r^2=0)}
  \text{nature= sphère de centre (\xc;\yc;\zc) et de rayon \r}
}
\if{\i>5 and \i<12}{
  \integer{k=2}
 on choisit des cylindres

  \if{\i==6 or \i==7}{\integer{axe=1}
    \text{equat=simplify((y-\yc)^2+(z-\zc)^2-(\r)^2=0)}
    \text{rep7= texmath(y=\yc)}
    \text{rep8= texmath(z=\zc)}
  }
  \if{\i==8 or \i==9}{\integer{axe=2}
    \text{equat=simplify((x-\xc)^2+(z-\zc)^2-(\r)^2=0)}
    \text{rep7= texmath(x=\xc)}
    \text{rep8= texmath(z=\zc)}
  }
  \if{\i==10 or \i==11}{\integer{axe=3}
    \text{equat=simplify((x-\xc)^2+(y-\yc)^2-(\r)^2=0)}
    \text{rep7= texmath(x=\xc)}
    \text{rep8= texmath(y=\yc)}
  }
  \text{rep6=\axeliste[\axe]}
  \rational{rep9=\r}
  \text{nature= cylindre d'axe parallèle à \rep6 d'équations \rep7 et \rep8 et de rayon \r}
}
\if{\i>11}{
   on choisit des cones
  \integer{k=3}
  \integer{j=\i-11}
  \integer{kangle=\kanglelist[\j]}

  \text{coef=\coeflist[\kangle]}
  \text{deg=\anglelist[\kangle]}
  \text{rep11=\deg}

  \if{\i==12 or \i==13 or \i==14}{
    \integer{axe=1}
    \text{equat=\coef=1?y^2+z^2=x^2:y^2+z^2=\coef x^2}
  }
  \if{\i==15 or \i==16 or \i==17}{
    \integer{axe=2}
    \text{equat=\coef=1?x^2+z^2=y^2:x^2+z^2=\coef y^2}
  }
  \if{\i==18 or \i==19 or \i==20}{
    \integer{axe=3}
    \text{equat=\coef=1?x^2+y^2=z^2:x^2+y^2=\coef z^2}
  }
  \text{rep10=\axeliste[\axe]}
  \text{nature=cône d'axe parallèle à \rep10 et d'angle \deg degré}
}
  \text{equatsList=wims(append item \equat to \equatsList)}
  \text{natureList=wims(append item \nature to \natureList)}
} fin de la boucle for

%% choix aléatoire de 4 objets dans la liste ci-dessus ##
\text{permutequats=shuffle(\maxobj)}
\text{chList=}
\text{ch2List=}
\for{k=1 to 4}{
\integer{indobj=item(\k,\permutequats)}
\text{uneequat=\(\equatsList[\indobj])}
\text{chList=wims(append item \uneequat to \chList)}
\text{unenature=\natureList[\indobj]}
\text{ch2List=wims(append item \unenature to \ch2List)}
}
%% mélange des 2 listes à mettre en correspondance
\text{taille=80x300x300}

%%##### enoncé de l'exo #######

\statement{<p>\name_enonce</p>
<div class="wimscenter">
  \embed{reply 1,\taille}
</div>
}

%%## soumission de réponse ####
\reply{\name_answer}{\ch2List;\chList}{type=correspond}
