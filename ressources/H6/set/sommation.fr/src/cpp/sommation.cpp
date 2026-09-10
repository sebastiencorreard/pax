target= sommedouble2 sommegraphe
#include "author.inc"
#include "lang_titles.inc"
#if defined TARGET_sommedouble2
\computeanswer{no}
\description{Ecrire une somme indexée par des couples d'entiers à l'aide d'une double somme}
#endif
#if defined TARGET_sommegraphe
\computeanswer{yes}
\precision{10000}
\description{Se familiariser avec les ensembles d'indices utilisés dans les sommes doubles}
#endif
\integer{m=randint(7..12)}
\integer{n=randint(7..12)}
\integer{M=max(\m,\n)}
\text{sgn=randitem(-,+)}
\integer{ar=randint(-4..4)}
\integer{br=randint(\M-2..\M+2)}
\integer{choix1=random(1,2)}
\integer{choix2=random(1,2)}
\text{s1=item(\choix1, \leq , < )}
\text{s2=item(\choix2, \leq , < )}
\integer{R=random(1,2)}
\text{i1= \R=1? i: j}
\text{i2= \R=1? j: i}
\integer{a= \choix1=1? \ar: \ar+1}
\integer{b= \choix2=1? \br: \br-1}

\if{\R=1}{
  \if{\sgn issametext +}{
   \integer{rep1= max(1,\a-\n) }
   \integer{rep2= min(\m,\b-1) }
   \function{f3=simplify(\a-i)}\function{f4=simplify(\b-i)}
   \text{rep31= max(1,\f3)}
   \text{rep41= min(\n,\f4)}
    }
   {\integer{rep1= max(1+\a,1)}
   \integer{rep2= min(\b+\n,\m)}
   \function{f3=simplify(i-\b)}\function{f4=simplify(i-(\a))}
   \text{rep31= max(1,\f3)}
   \text{rep41= min(\n,\f4)}
   }
 \real{u31=evalue(\rep31,i=\rep1)}
 \real{v31=evalue(\rep31,i=\rep2)}
 \if{\u31=\v31}
   {\integer{rep3=1}}
   {\real{u31=evalue(\f3,i=\rep1)}
    \real{v31=evalue(\f3,i=\rep2)}
    \if{\u31>=1 and \v31>=1}{\text{rep3=\f3}}
       {\text{rep3=\rep31}}
   }
\real{u41=evalue(\rep41,i=\rep1)}
\real{v41=evalue(\rep41,i=\rep2)}
\if{\u41=\v41}
   {\integer{rep4=\n}}
   {\real{u41=evalue(\f4,i=\rep1)}
    \real{v41=evalue(\f4,i=\rep2)}
    \if{\u41<=\n and \v41<=\n}{\text{rep4=\f4}}
       {\text{rep4=\rep41}}
   }
}{
 \if{\sgn issametext +}{
    \integer{rep1= max(1,\a-\m) }
    \integer{rep2= min(\n,\b-1) }
    \function{f3=simplify(\a-j)}
    \function{f4=simplify(\b-j)}
    \text{rep31= max(1,\f3)}
    \text{rep41= min(\m,\f4)}
    }
   {\integer{rep1= max(1-\b,1)}
    \integer{rep2= min(\m-\a,\n)}
    \function{f3=simplify(\a+j)}
    \function{f4=simplify(\b+j)}
    \text{rep31= max(1,\f3)}
    \text{rep41= min(\m,\f4)}
    }

\real{u31=evalue(\rep31,j=\rep1)}
\real{v31=evalue(\rep31,j=\rep2)}
\if{\u31=\v31}{
  \integer{rep3=1}}{
    \real{u31=evalue(\f3,j=\rep1)}
    \real{v31=evalue(\f3,j=\rep2)}
    \if{\u31>=1 and \v31 >=1}{\text{rep3=\f3}}
      {\text{rep3=\rep31}}}
  \real{u41=evalue(\rep41,j=\rep1)}
  \real{v41=evalue(\rep41,j=\rep2)}
  \if{\u41=\v41}{\integer{rep4=\m}}
    {\real{u41=evalue(\f4,j=\rep1)}
  \real{v41=evalue(\f4,j=\rep2)}
  \if{\u41<=\m and \v41<=\m}{\text{rep4=\f4}}
  {\text{rep4=\rep41}}}
}
\text{condition= \sgn issametext +? i+j: i-j}
\text{ncondition= \sgn issametext +? i-j: i+j}
\text{dessin1=xrange -1,\M+1
yrange -1,\M+1
parallel 0,0,0,\M, 1,0,\M+1,grey
parallel 0,0,\M, 0,0,1,\M+1,grey
text black,-1,\M,medium,j
text black,\M,0, medium,i
hline 0,0,black
vline 0,0,black}
#if defined TARGET_sommedouble2
\for{i=1 to \m}{
  \for{j=1 to \n}{
    \real{r=evalue(\condition, i=\i,j=\j)}
    \real{nr=evalue(\ncondition, i=\i,j=\j)}
    \if{\r >=\a and \r<=\b}{
      \text{dessin1= \dessin1
        disk \i,\j, 8,red}
    }
  }
}
\if{\R=1}{
  \text{dessin1=\dessin1
arrow 1,-1,1,-0.1,8,blue}
}{
  \text{dessin1=\dessin1
arrow -1,1,-0.1,1,8,blue}
}
\text{des1=draw(200,200
 \dessin1)}
\statement{<div>On considère l'ensemble \(E\) des couples \((i , j) \in \NN^2\)
  tels que
  \(1 \leq i \leq \m\) et \(1 \leq j \leq \n\)
  avec la condition :
  \(\ar \s1 i \sgn j \s2 \br\). <br>
  On note \(S\) la somme des nombres \(p_(i , j)\) pour \((i , j ) \in E\) :
  \(\displaystyle{S = \sum_{(i, j) \in E}p_{i, j}}\). </div>
<div class="wims_question">
  Écrire \(S\) sous la forme d'une somme double :

\special{mathmlinput [\displaystyle{S=\sum_{\i1= reply1}^{reply2}\left(\sum_{\i2=reply3}^{reply4}p_{i,j}\right)}],4
reply 1
reply 2
reply 3
reply 4
}
</div>
<div class="wims_instruction">Consigne : la borne d'en bas doit être inférieure à celle d'en haut.
  On pourra utiliser les fonctions <span class="tt">min</span>
  et <span class="tt">max</span> sous la forme <span class="tt">max(i,2)</span> par exemple.
  Mais les formules devront être simplifiées : par exemple,
  on n'écrira pas <span class="tt">max(6,13)</span> à la place de 13.
</div>
}

\answer{}{\rep1}{type=formal}
\answer{}{\rep2}{type=formal}
\answer{}{\rep3}{type=formal}
\answer{}{\rep4}{type=formal}

\feedback{\i2 isin \reply1 or \i2 isin \reply1}{Attention, cela n'a pas de sens
  de faire dépendre les bornes de la première somme de \i2 qui est
   l'indice de sommation de la seconde somme.}
  \feedback{max isin \reply1 or min isin \reply1 or max isin \reply2 or min isin \reply2}{Attention,
  ça n'a pas de sens de mettre un <span class="tt">min</span> ou un <span class="tt">max</span> dans la première somme.}
  \solution{(indications) Les éléments de \(E\) sont représentés par des points rouges sur la figure :
  <div class="wimscenter"><img src="\des1" alt="">
  </div>
  En parcourant l'ensemble de ces points rouges
  \if{\i1 issametext j}{de bas en haut, ligne après ligne,}{de gauche à droite, colonne après colonne,} on obtient : <div class="wimscenter">\(\displaystyle{\sum_{(i,j) \in E}p_{i,j}}\) = \(\displaystyle{\sum_{\i1 = \rep1}^{\rep2}\Big(\sum_{ \i2 = \rep3}^{\rep4} p_{i,j} \Big)}\).
  </p>}
#elif defined TARGET_sommegraphe
\integer{A=random(1,2)}

\integer{da=randint(1..2)*random(-1,1)}
\integer{db=randint(1..2)}

\text{dessin2=\dessin1}
\text{dessin3=\dessin1}
\text{dessin4=\dessin1}
\for{i=1 to \m}{
  \for{j=1 to \n}{
    \real{r=evalue(\condition, i=\i,j=\j)}
    \real{nr=evalue(\ncondition, i=\i,j=\j)}
    \if{\r >=\a and \r<=\b}{
      \text{dessin1= \dessin1
      disk  \i,\j, 8,red}
    }
    \if{\r >=\a+\da and \r<=\b+\db }{
      \text{dessin2= \dessin2
      disk  \i,\j, 8,red}
    }
    \if{\nr >=\a and \nr <=\b}{
      \text{dessin3= \dessin3
        disk  \i,\j, 8,red}
    }
    \if{\nr >=\a+\da and \nr <=\b+\db}{
      \text{dessin4= \dessin4
        disk  \i,\j, 8,red}
    }
  }
}

\text{des1=draw(200,200
 \dessin1)}

\integer{X=random(1,2)}
\integer{Y=random(1,2)}

\text{des2= \X=1? draw(200,200
 \dessin4)}
\text{des3= \X=1? draw(200,200
 \dessin3)}
\if{\X=2 and \Y=1}{
\text{des2=draw(200,200
 \dessin2)}
\text{des3=draw(200,200
 \dessin3)}}
\if{\X=2 and \Y=2}{
\text{des2=draw(200,200
 \dessin2)}
\text{des3=draw(200,200
 \dessin4)}}

 \text{a=shuffle(1,2,3)}
 \text{reponse=<img src="\des1" alt="">,<img src="\des2" alt="">,<img src="\des3" alt="">}
 \text{reponse=\reponse[\a]}
 \text{rep=position(1,\a)}

\statement{\if{\A=1}{
 <div>On considère la somme double suivante sur un ensemble fini \(E\) : </div>
  <div class="wimscenter">
\(\displaystyle{\sum_{(i,j) \in E} p_{i,j} =
  \sum_{\i1=\rep1}^{\rep2}\Big( \sum_{\i2 = \rep3}^{\rep4}p_{i,j}\Big)}\)
</div>
}{
<div>On considère l'ensemble \(E\) des couples \((i, j) \in \NN^2\)
  tels que \(1 \leq i \leq \m\) et \(1 \leq j \leq \n\)
  et tels que </div>
<div class="wimscenter">\(\ar \s1 i \sgn j \s2 \br\). </div>
}
<div class="wims_question">
  Sur l'un des dessins, l'ensemble des  points rouges représente
  l'ensemble des éléments de \(E\). Cliquez sur ce dessin :
<div class="wimscenter">\embed{reply1}</div>
</div>
}

\answer{}{\rep;\reponse}{type=click}{option=noanalyzeprint}

\feedback{1=1}{Vous aviez le choix entre ces trois dessins :
<div class="wimscenter">\reponse</div>}
\solution{
  \if{\A=1}{L'ensemble \(E\) est l'ensemble des couples \((i, j) \in\NN^2\)
  tels que \(\rep1 \leq \i1 \leq \rep2\) et \(\rep3 \leq \i2 \leq \rep4.\) Il
  }
  {L'ensemble \(E\)}
  est représenté sur le dessin \if{\rep=1}{de gauche.}\if{\rep=2}{du milieu.}\if{\rep=3}{de droite.}
}
#endif
