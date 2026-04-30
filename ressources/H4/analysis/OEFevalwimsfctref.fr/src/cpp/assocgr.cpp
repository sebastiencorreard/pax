target=assocgr1 assocgr2 assocgr3 assocgr4 assocgr5
#if defined TARGET_assocgr1
# define NUM 1
#endif
#if defined TARGET_assocgr2
# define NUM 2
#endif
#if defined TARGET_assocgr3
# define NUM 3
#endif
#if defined TARGET_assocgr4
# define NUM 4
#endif
#if defined TARGET_assocgr5
# define NUM 5
#endif
#include "lang_titles.inc"
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}Modifié par fabien.sommier@gmail.com
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}

%%%% couleur des grilles
\text{gridcolor=lightblue}

%%%% cadre générique ###
\text{cadre=
xrange -3,3
yrange -3.5,3.5
gridfill 0,0,5,5,\gridcolor
linewidth 3
vline 1,0,\gridcolor
vline 2,0,\gridcolor
vline 3,0,\gridcolor
vline -1,0,\gridcolor
vline -2,0,\gridcolor
vline -3,0,\gridcolor
hline 0,1,\gridcolor
hline 0,2,\gridcolor
hline 0,3,\gridcolor
hline 0,-1,\gridcolor
hline 0,-2,\gridcolor
hline 0,-3,\gridcolor
linewidth 1
vline 0,0,black
hline 0,0,black
linewidth 3
points red,1,0,0,1,0,0
text red,1,-0.1,medium,I
text red,-0.3,1.2,medium,J
text red,-0.2,-0.1,medium,O
linewidth 1
}
%%%% fin du cadre générique ##

\text{a=random(-2,-3/2,-1,-1/2,1/2,1,3/2,2)}
\text{bList=1/2,1,2,3/2}
\text{r=random(-3/2,-5/4,-1,-3/4,-1/2,-1/4,0,1/4,1/2,3/4,1,5/4,3/2)}
\text{d=random(-1,-3/4,-1/2,-1/4,0,1/4,1/2,3/4,1)}
\text{trigcos=cos}
\text{trigsin=sin}
\text{foncsList=}
\text{g=}
#if defined TARGET_assocgr1
\for{b in \bList}{
    \text{g=\(1/(x+(\b)))}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\(1/x+(\b))}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\((\b)*x+(\a))}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\(x^2+(\b))}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\((x+(\b))^2)}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\(\trigcos(x)+\b)}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\(\trigsin(x)+\b)}
    \text{foncsList=wims(append item \g to \foncsList)}
 }
#endif
#if defined TARGET_assocgr2
\for{b in \bList}{
    \text{g=(\(\a)/((\b)*x+(-(\b)*(\r))))}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\((\b)*x+(\a))}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=(\(\b)*x^2)}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=(\trigcos(\b*x))}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=(\trigsin(\b*x))}
    \text{foncsList=wims(append item \g to \foncsList)}
 }
#endif
#if defined TARGET_assocgr3
\for{b in \bList}{
    \text{g=\((x+\b)^2+\a)}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\((x-\b)^2+\a)}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\((x+\b)^2-\a)}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\((x-\b)^2-\a)}
    \text{foncsList=wims(append item \g to \foncsList)}
  }
#endif
#if defined TARGET_assocgr4
\for{b in \bList}{
    \text{g=\(1/(x+\b)+\b)}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\(1/(x-\b)+\b)}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\(1/(x+\b)-\b)}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\(1/(x-\b)-\b)}
    \text{foncsList=wims(append item \g to \foncsList)}
  }
#endif
#if defined TARGET_assocgr5
\for{b in \bList}{
    \text{g=\(\trigcos(\b*x)+\a)}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\(\trigsin(\b*x)+\a)}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\(\trigcos(\b*x)-\a)}
    \text{foncsList=wims(append item \g to \foncsList)}
    \text{g=\(\trigsin(\b*x)-\a)}
    \text{foncsList=wims(append item \g to \foncsList)}
  }
#endif

%%%% choix aléatoire de 4 fonctions dans la liste ci-dessus ##
%%%% \text{foncsList2=shuffle(\foncsList)} ##
\integer{n=items(\foncsList)}
\text{permutfoncs=shuffle(\n)}

\text{chList=}
\for{k=1 to 4}{
  \integer{kk=\permutfoncs[\k]}
  \text{f=\foncsList[\kk]}
  \text{f=maxima(\f)}
  \text{f=\(texmath(\f))}
  \text{chList=wims(append item \f to \chList)}
}

%%%% codes des quatre graphes à afficher ##
\text{couleurs=shuffle(red,blue,orange,green)}
\text{size=180}

\text{graphList=}

\for{k=1 to 4}{
  \integer{kk=\permutfoncs[\k]}
  \text{graph=
    <img src="
    draw(\size,\size
    \cadre
    linewidth 2
    plot \couleurs[\k],\foncsList[\kk]
    )"
    width="\size"
    height="\size"
    alt="">
    }

  \text{graphList=wims(append item \graph to \graphList)}
}

\text{taille=\size x\size x\size}
%%%% enoncé de l'exo #######
\statement{
  Dans le plan muni d'un repère orthonormé \((O,I,J)\), associez à chacune
  des fonctions ci-dessous, sa représentation graphique.
<div class="wimscenter">
  \embed{reply 1,\taille}
</div>
}
%%%% soumission de réponse ####
\reply{Correspondance graphe/fonction}{\graphList;\chList}{type=correspond}

### Solution (proposée par Fabien)###
\solution{Chaque expression algébrique est donnée sous forme canonique. <br>

Rappel (propriétés) : Si, pour tout réel \(x\), \(f(x)=a\left(x-\alpha\right)^2+\beta\), alors
<ul>
<li>La droite d'équation \(x=\alpha\) est l'axe de symétrie de la parabole qui représente \(f\);
<li>Si \(a>0\), la fonction \(f\) admet pour minimum \(\beta\), et il est atteint en \(x=\alpha\);
<li>Si \(a<0\), la fonction \(f\) admet pour maximum \(\beta\), et il est atteint en \(x=\alpha\).
</ul>
}
