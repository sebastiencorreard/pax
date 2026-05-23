target= classer1 classer2
#define TITRE Classer des fonctions
#if #TARGET (classer1)
\title{TITRE (4 fonctions).}
\integer{nbfnct=2}
\text{size=175x50x3}
#endif

#if #TARGET (classer2)
\title{TITRE (6 fonctions).}
\integer{nbfnct=3}
\text{size=175x50x4}
#endif

\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{a=random(2..10)}
\integer{b=random(-1,1)*random(2..10)}
\integer{c=random(2..11)}
\integer{d=random(-1,1)*random(2..100)}
\real{d=\d/10}
\integer{e=random(2..100)}
\real{e=\e/10}
\integer{f=random(-1,1)*random(3,5,9,15)}
\integer{g=random(-1,1)*random(2,7,4,8,14)}

\matrix{donnees=\sqrt{\a}x,\b x,\e x,\frac{\f}{\g}x,\frac{\sqrt{\a}}{\g}x
\sqrt{\a}x+\c,\sqrt{\a}x-\c,\b x+\a,\b x-\a,\f x+\e,\f x-\e,\frac{\f}{\g}x+\a,\frac{\sqrt{\a}}{\g} x-\c,\frac{\f}{\g}x+\frac{\a}{\c},\b(x+\c),\cos(\a x),\sin(\b x),tan(\c x),\b x^2+\a x+\c,\sqrt{\a}x^2+\e x+\c, \frac{\f}{\g}x^2+\frac{\a}{\b} x+\c,\b x^2,(x+\c)(x+\a),(x+\e)^2,(x-\c)^2}

\matrix{sortie=}
\for{i=1 to 2}{
\text{tmp=row(\i,\donnees)}
\text{tmp=shuffle(\tmp)}
\text{line=}
\for{j=1 to \nbfnct}{
\text{tmp1=item(\j,\tmp)}
\text{tmp1=\(x\mapsto \tmp1)}
\text{line=wims(append item \tmp1 to \line)}
}
\text{sortie=wims(append line \line to \sortie)}
}

\text{goodlin=row(1,\sortie)}
\text{goodaut=row(2,\sortie)}
\text{list=\goodlin,\goodaut}

\statement{Parmi les fonctions suivantes, lesquelles sont linéaires ?
<div class="wimscenter">
\embed{r1,\size}
</div>}

\reply{Liste des fonctions linéaires}{\replin;\list}{type=clickfill}

\text{tmplin=\replin,\goodlin}
\text{tmplin=wims(listuniq \tmplin)}
\integer{lin1=items(\tmplin)}
\text{replin=wims(listuniq \replin)}
\integer{lin2=items(\replin)}
\condition{Fonctions linéaires :}{\lin1=\nbfnct and \lin2=\nbfnct}

\solution{Fonctions linéaires : \goodlin}
