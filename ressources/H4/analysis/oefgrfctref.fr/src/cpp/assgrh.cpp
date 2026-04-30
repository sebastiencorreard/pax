target=assgrhyper
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

## couleur des grilles
\text{gridcolor=lightblue}

### cadre générique ###
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
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
}
## fin du cadre générique ##

## liste des fonctions ##
## on va considérer des fonctions s'écrivant: a/(bx+c) +d ##
\text{a=random(-2,-3/2,-1,-1/2,1/2,1,3/2,2)}
\text{bList=-4,-3,-2,-1,1,2,3,4}
\text{singList=-3/2,-5/4,-1,-3/4,-1/2,-1/4,0,1/4,1/2,3/4,1,5/4,3/2}
\text{d=random(-1,-3/4,-1/2,-1/4,0,1/4,1/2,3/4,1)}
\text{foncsList=}

\for{b in \bList}{
  \for{r in \singList}{
    \text{g=((\a)/((\b)*x+(-(\b)*(\r))))+(\d)}
    \text{foncsList=wims(append item \g to \foncsList)}
  }
}

## choix aléatoire de 4 fonctions dans la liste ci-dessus ##
\text{foncsList=shuffle(\foncsList)}
\text{permutfoncs=shuffle(4)}
\integer{f1=item(1,\permutfoncs)}
\integer{f2=item(2,\permutfoncs)}
\integer{f3=item(3,\permutfoncs)}
\integer{f4=item(4,\permutfoncs)}

## choix aléatoire de 4 fonctions dans la liste ci-dessus ##
\text{foncsList=shuffle(\foncsList)}
\text{permutfoncs=shuffle(4)}
\integer{f1=item(1,\permutfoncs)}
\integer{f2=item(2,\permutfoncs)}
\integer{f3=item(3,\permutfoncs)}
\integer{f4=item(4,\permutfoncs)}

\text{chList=}
\for{k=1 to 4}{
  \text{f=\foncsList[\k]}
  \text{f=maxima(\f)}
  \text{f=\(texmath(\f))}
  \text{chList=wims(append item \f to \chList)}
}

## codes des quatre graphes à afficher ##
\text{couleurs=shuffle(red,blue,orange,green)}
\text{size=160}

\text{graphList=}

\for{k=1 to 4}{
  \text{graph=
    <img src="
    draw(\size,\size
    \cadre
    plot \couleurs[\k],\foncsList[\k]
    )"
    width="\size"
    height="\size"
    alt="">
    }

  \text{graphList=wims(append item \graph to \graphList)}
}

\text{taille=\size x\size x\size}
####### enoncé de l'exo #######
\statement{
\name_enonce
<div class="wimscenter">
  \embed{reply 1,\taille}
</div>
}
#### soumission de réponse ####
\reply{\name_answer}{\graphList;\chList}{type=correspond}
