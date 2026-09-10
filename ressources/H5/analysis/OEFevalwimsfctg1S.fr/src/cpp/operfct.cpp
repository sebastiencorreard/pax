target=operfct1 operfct2 operfct3 operfct4 operfct5
#include "author.inc"
#include "lang_titles.inc"
#if defined TARGET_operfct1
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(1..5)*randint(1,-1)}
\integer{c=randint(1..5)*randint(1,-1)}
\integer{d=randint(1..5)*randint(1,-1)}
\integer{e=randint(1..5)*randint(1,-1)}
\text{dataf=\a*x+\b,\a/x+\b,\a*sqrt(x)+\b}
\text{defdom=\RR,\RR^*,\rbrack 0; +\infty \lbrack}
\integer{i=randint(1..items(\dataf))}
\function{f=maxima(\dataf[\i])}
\function{g=maxima(\c*x^2+\d*x+\e)}
\integer{m=randint(1..5)*randint(1,-1)}
\function{f1=maxima(expand(\m*(\f)))}
\function{f2=maxima(expand(\m*(\f)+\g))}
\function{f3=maxima(expand((\f)*(\g)))}
\function{f4=maxima(expand((\f)^2))}
\text{ft=texmath(\f)}
\text{gt=texmath(\g)}
\text{defdomf=\defdom[\i]}
\statement{
  On considère les fonctions \(f) et \(g) définies sur \(\,\defdomf) par
<div class="wimscenter"> \(f(x)=\ft) et \(g(x)=\gt) </div>
  Donner l'expression algébrique des fonctions suivantes :
 <table class="wimscenter wimsborder"><tr><td>\(h_1=\m f)</td><td>
 <label for="reply1">\(h_1(x)=)</label> \embed{reply1}</td></tr>
<tr><td>
\(h_2=\m f + g)</td><td> <label for="reply2">\(h_2(x)=)</label> \embed{reply2} </td></tr>
<tr><td>
\(h_3=f \times g)</td><td> <label for="reply3">\(h_3(x)=)</label> \embed{reply3} </td></tr>
<tr><td>\(h_4=f^2)</td><td> <label for="reply4">\(h_4(x)=)</label> \embed{reply4} </td></tr></table>
}
\answer{\(h_1(x))}{\f1}{type=formal}
\answer{\(h_2(x))}{\f2}{type=formal}
\answer{\(h_3(x))}{\f3}{type=formal}
\answer{\(h_4(x))}{\f4}{type=formal}
#endif

#if defined TARGET_operfct2
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(1..5)*randint(1,-1)}
\integer{c=randint(1..5)*randint(1,-1)}
\integer{d=randint(1..5)*randint(1,-1)}
\integer{e=randint(1..5)*randint(1,-1)}
\text{dataf=\a*x+\b,\c*x+\d}
\text{defdomf=\RR}
\text{f=\dataf[1]}
\text{g=\dataf[2]}
\function{f1=maxima((\f)/(\g))}
\text{ft=texmath(\f)}
\text{gt=texmath(\g)}
\rational{r=simplify(-\d/\c)}
\statement{
  On considère les fonctions \(f) et \(g) définies sur \(\,\defdomf) par
<div class="wimscenter"> \(f(x) = \ft) et \(g(x) = \gt) </div>
  Donner l'expression algébrique de la fonction \(h=\frac{f}{g}) ainsi que son ensemble de définition.
<ol>
<li> <label for="reply1">\(h(x)=)</label> \embed{reply1} </li>
<li> Ensemble de définition : <label for="reply2">\(\RR \setminus)</label> \embed{reply2,3} </li>
</ol>
}
\answer{\(h(x))}{\f1}{type=formal}
\answer{Ensemble de définition}{\r}{type=fset}
#endif

#if defined TARGET_operfct3
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(1..5)*randint(1,-1)}
\integer{c=randint(1..5)*randint(1,-1)}
\integer{d=randint(1..5)*randint(1,-1)}
\integer{e=randint(1..5)*randint(1,-1)}
\function{f=maxima(\a*x+\b)}
\function{g=maxima(\c*x^2+\d*x+\e)}
\integer{m=randint(1..3)*randint(1,-1)}
\integer{n=randint(1..3)*randint(1,-1)}
\function{h=maxima(expand(\m*(\f)+\n*(\g)))}
\text{ft=texmath(\f)}
\text{gt=texmath(\g)}
\text{ht=texmath(\h)}
\text{rel=\m*f+\n*g}

\statement{
  On considère les fonctions \(f,g) et \(h) définies sur \(\,\RR) par
<div class="wimscenter"> \(f(x)=\ft) , \(g(x)=\gt) et \(h(x)=\ht) </div>
<p>
  Trouver une relation fonctionnelle exprimant \(h) en fonction de \(f) et \(g):
</p>
<div class="wimscenter"><label for="reply1">\(h=)</label> \embed{reply1} </div>
}
\answer{relation fonctionnelle}{\rel}{type=formal}
#endif

#if defined TARGET_operfct4
\text{data=La somme de deux fonctions croissantes est une fonction croissante,1,
  La somme de deux fonctions décroissantes est une fonction décroissante,1,
  La somme de deux fonctions décroissantes est une fonction croissante,2,
  La somme d'une fonction croissante et d'une fonction décroissante est une fonction décroissante,2,
  Le produit de deux fonctions croissantes est une fonction croissante,2,
  Le produit de deux fonctions décroissantes est une fonction décroissante,2,
  Le produit de deux fonctions décroissantes est une fonction croissante,2,
  Le produit d'une fonction croissante et d'une fonction décroissante est une fonction décroissante,2,

  La somme de deux fonctions positives est une fonction positive,1,
  La somme de deux fonctions négatives est une fonction négative,1,
  La somme de deux fonctions négatives est une fonction positive,2,
  La somme d'une fonction positive et d'une fonction négative est une fonction négative,2,
  Le produit de deux fonctions positives est une fonction positive,1,
  Le produit de deux fonctions négatives est une fonction négative,2,
  Le produit de deux fonctions négatives est une fonction positive,1,
  Le produit d'une fonction positive et d'une fonction négative est une fonction négative,1,

  La somme de deux fonctions positives est une fonction croissante,2,
  La somme de deux fonctions négatives est une fonction décroissante,2,
  La somme de deux fonctions négatives est une fonction croissante,2,
  Le produit de deux fonctions positives est une fonction croissante,2,
  Le produit de deux fonctions négatives est une fonction décroissante,2,
  Le produit de deux fonctions négatives est une fonction croissante,2,
  Le produit d'une fonction positive et d'une fonction négative est une fonction décroissante,2,
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{
  L'affirmation suivante est-elle toujours vraie?
<div class="wimscenter"> \quest<br>
\embed{reply1}</div>
}
\answer{Vrai-faux}{\rep;Oui,Non}{type=radio}
#endif

#if defined TARGET_operfct5
%%%% couleur des grilles
\text{gridcolor=lightblue}

%%%% cadre générique ###
\text{cadre=
xrange -5,5
yrange -5,5
gridfill 0,0,5,5,\gridcolor
linewidth 3
parallel -5,-5,5,-5,0,1,11,\gridcolor
parallel -5,-5,-5,5,1,0,11,\gridcolor
linewidth 1
vline 0,0,black
hline 0,0,black
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
}
%%%% fin du cadre générique ##

%%%% liste de trinomes ##
%%%% on va considérer des trinomes s'écrivant: a(x-b)^2+c ##
\text{a=random(-1/2,-1/3,-3,-2,1/3,1/2,2,3)}
\text{b=random(-1,-1/2,-2,1/2,1,2,1/3)}
\text{c=random(-1,-1/2,-2,1/2,1,2,1/3)}
\text{d=random(2,-2,-1/2,1/2)}

\text{foncsList=}
\text{chList=}
\text{f=random(\a*x+\b,(\a*x+\b)*(x+\c))}
\text{fref=texmath(\f)}

\text{tempf=abs(\f)}
\text{tempch=\(|f(x)|)}
\text{foncsList=wims(append item \tempf to \foncsList)}
\text{chList=wims(append item \tempch to \chList)}

\text{tempf=-(\f)}
\text{tempch=\(-f(x))}
\text{foncsList=wims(append item \tempf to \foncsList)}
\text{chList=wims(append item \tempch to \chList)}

\text{tempf=\d*(\f)}
\text{tempch=\(\d f(x))}
\text{foncsList=wims(append item \tempf to \foncsList)}
\text{chList=wims(append item \tempch to \chList)}

\text{tempf=\f+\d}
\text{tempch=\(\d+f(x))}
\text{foncsList=wims(append item \tempf to \foncsList)}
\text{chList=wims(append item \tempch to \chList)}

%%%% choix aléatoire de 4 fonctions dans la liste ci-dessus ##

%%%% codes des quatre graphes à afficher ##
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
  \text{graphref=
    <img src="
    draw(\size,\size
    \cadre
    plot black,\f
    )"
    width="\size"
    height="\size"
    alt="">
    }

\text{taille=\size x\size x\size}
%%%%%% enoncé de l'exo %%%%%%
\statement{
 Dans le plan muni d'un repère orthonormé \((O,i,j)\), on a tracé
 le graphe de la fonction \(f(x)= \fref\)
<div class="wimscenter"> \graphref </div>
  Associez à chacune des fonctions ci-contre son graphe.
<div class="wimscenter">
  \embed{reply 1,\taille}
</div>

}
%%%%%% soumission de réponse %%%%%%
\reply{Correspondance graphe/fonction}{\graphList;\chList}{type=correspond}
#endif
