target = integrale integrale0

#if defined TARGET_integrale
\title{Calcul d'une intégrale}
\observation{intégrale de divers polynômes parmi lesquels peut apparaître un carré (ax+b)²}
\author {Chantal,Causse}
\email  {Chantal.Causse@noos.fr}
\integer{choix=randint(1..6)}

#else
\title{Calcul d'une intégrale_0} 
\observation{variante de l'exercice integrale.oef évitant les primitives de (ax+b)²}
\author{Paul, Byache} 
\email{paul@byache.fr} 
\integer{choix=randint(1..5)}

#endif

\language{fr}
\range{-5..5}
\computeanswer{yes}
\format{html}
\precision{10000}

\integer{a=randint(1..4)*random(-1,1)}
\integer{b=randint(1..4)*random(-1,1)}
\integer{c=randint(1..4)*random(-1,1)}

\integer{p=random(2,3,4)}


\integer{sgn=random(-1,1)}
\integer{d= \choix > 3? random(1..5)*\sgn : random(-5..5)}
#pour éviter que 0 soit dans le domaine d'intégration de 1/x²
\integer{e= \choix > 3? random(1..5)*\sgn : random(-5..5)}
#pour éviter que 0 soit dans le domaine d'intégration de 1/x² et éviter que si \d = \e ils soient égaux à -1... 
\integer{e=(\e=\d)?\e+1:\e} #pour éviter que \d = \e
\if{\d > \e}{   #pour être sûr que \d < \e
\integer{tmp=\d}
\integer{d=\e}
\integer{e=\tmp}
} 

\function{f=item(\choix,
\a*x+\b,
\a*x^\p+\b*x+\c,
\a*x^2+\b*x+\c,
\a/x^2,
\b*x+\c+\a/x^2,
(\a*x+\b)^2
)}
\text{f1=texmath(\f)}
\function{g=int(\f,x)}
\text{g1=texmath(\g)}
\text{rep=maxima(subst(x=\e,\g)-subst(x=\d,\g);)}
\text{Fi=maxima(subst(x=\d,\g))}
\text{Fs=maxima(subst(x=\e,\g))}
\text{rep1=texmath(\rep)}
\statement{Calculer la valeur exacte de l'intégrale :
<div class="wimscenter">
\(I=integrate(\f,x=\d..\e)\).</div>
<div class=wims_instruction>Donner la valeur <b>exacte</b> sous forme de fraction, ou sous forme décimale utilisant le point comme séparateur.<br>
Ainsi, si la réponse juste est \(\frac{1}{100}), on acceptera 1/100 ou 0.01 mais pas 0,01 </div>
}

\hint{\(integrate(f(x),x=a..b)= F(b)-F(a)\) où \(F\) est une primitive de \(f\).
}

\answer{Valeur de I}{\rep}{type=auto}
\solution{Une primitive de la fonction \(f) :
\(x \mapsto \f1) est la fonction \(F) :
\(x \mapsto \g1).
<p class="wimscenter">
\(F(\d) = \Fi) et \(F(\e) = \Fs).
</p>
On en déduit que
\(integrate(f(x),x=\d..\e)\) vaut \(F(\e) - F(\d)\) \(= \Fs -(\Fi) = \rep1\)
}
