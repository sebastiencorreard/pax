target=calcder1 calcder2 calcder3 calcder4 calcder5
\language{fr}
\range{-5..5}
\author{Régine,Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}


#if (defined TARGET_calcder1  || defined TARGET_calcder2  || defined TARGET_calcder3 )

#if defined TARGET_calcder1 
\title{Dérivée avec exponentielle 1}
\integer{a = randint(1..5)*randint(1,-1)}
\integer{d = randint(1..5)*randint(1,-1)}
\integer{b = randint(-5..5)}
\integer{c = randint(-5..5)}
\text{data=\a*x+\b,\a*x^2+\b*x+\c,\d/x,(\d*x+\c)/(\a*x+\b)}
\text{cedata=randitem(\data)}
\text{u=texmath(maxima(\cedata))}
\text{ft=e^{\displaystyle \u}}
\function{fder=maxima(diff(exp(\cedata),x))}
#endif

#if defined TARGET_calcder2 
\title{Dérivée avec exponentielle 2}
\integer{a = randint(1..5)*randint(1,-1)}
\integer{d = randint(1..5)*randint(1,-1)}
\integer{b = randint(-5..5)}
\integer{c = randint(-5..5)}
\text{data=\a*x+\b,\a*x^2+\b*x+\c,\d/x,(\d*x+\c)/(\a*x+\b)}
\text{cedata=randitem(\data)}
\text{u=texmath(maxima(\cedata))}
\text{ft=(\u)e^{x}}
\function{fder=maxima(diff((\cedata)*exp(x),x))}
#endif

#if defined TARGET_calcder3 
\title{Dérivée avec exponentielle 3}
\integer{a = randint(1..5)*randint(1,-1)}
\integer{d = randint(1..5)*randint(1,-1)}
\integer{b = randint(-5..5)}
\integer{c = randint(-5..5)}
\text{u=texmath(maxima(\d*x+\c))}
\text{v=texmath(maxima(\a*x+\b))}
\text{data=(\d*x+\c)*exp(\a*x+\b),(\d*x+\c)/exp(\a*x+\b),exp(\a*x+\b)/(\d*x+\c)}
\text{fdata=(\u)e^{\v},\frac{\u}{e^{\v}},\frac{e^{\v}}{\u}}
\integer{i=randint(1..3)}
\text{cedata=item(\i,\data)}
\text{ft=item(\i,\fdata)}
\function{fder=maxima(diff(\cedata,x))}

#endif
\statement{<p>
  On considère la fonction \(f) définie par \(f(x)=\displaystyle \ft).</p>
  Calculer \(f'(x))=\embed{reply1}
}
\answer{dérivée}{\fder}{type=formal}

#endif

#if defined TARGET_calcder4 
\title{Dérivée avec exponentielle 4}
\integer{a = random(1,randint(1..5)*randint(1,-1))}
\integer{d = randint(1..5)*randint(1,-1)}
\integer{b = randint(-5..5)}
\integer{c = randint(-5..5)}
\text{u=texmath(maxima(\d*x+\c))}
\text{v=texmath(maxima(\a*x+\b))}
\text{cedata=(\d*x+\c)*exp(\a*x+\b)}
\text{ft=(\u)e^{\v}}
\text{ftn=(a_n x+b_n)e^{\v}}
\function{fder=maxima(diff(\cedata,x))}
\function{fder2=maxima(diff(\fder,x))}
\text{arecur=\a=1?a_n:\a*a_n}
\text{brecur=\a=1?b_n+\d:\a*b_n+a_n}
\integer{nata=\a=1?1:3}
\integer{natb=\a=1?2:5}
\text{lstnat=constante, arithmétique, géométrique, arithmético-géométrique, quelconque}
\statement{<p>
  On considère la fonction \(f) définie par \(f(x)=\displaystyle \ft).</p>
<ol>
<li>Calculer \(f'(x)) et \(f''(x)):
<div class="wimscenter">\(f'(x))=\embed{reply1}</div>
<div class="wimscenter">\(f''(x))=\embed{reply2}</div>
</li>
<li>En supposant qu'il existe des suites \((a_n)) et \((b_n)), telles que pour tout
  entier \(n), la dérivée d'ordre \(n) est donnée par \(f^{(n)}(x)=\ftn),
  exprimer les termes \(a_{n+1}) et \(b_{n+1}) en fonction de \(a_n) et \(b_n):
<div class="wims_instruction">Taper <span class="tt">a_n</span> pour \(a_n) et
<span class="tt">b_n</span> pour \(b_n)</div>
<div class="wimscenter">\(a_{n+1})=\embed{reply3}</div>
<div class="wimscenter">\(b_{n+1})=\embed{reply4}</div>
</li>
<li>En déduire la nature des suites \((a_n)) et \((b_n)):
<div class="wimscenter">la suite \((a_n)) est une suite \embed{reply5}</div>
<div class="wimscenter">la suite \((b_n)) est une suite \embed{reply6}</div>
</li></ol>
}

\answer{dérivée}{\fder}{type=formal}
\answer{dérivée seconde}{\fder2}{type=formal}
\answer{\(a_{n+1})}{\arecur}{type=formal}
\answer{\(b_{n+1})}{\brecur}{type=formal}
\answer{nature de \((a_n))}{\nata;\lstnat}{type=menu}
\answer{nature de \((b_n))}{\natb;\lstnat}{type=menu}
#endif

#if defined TARGET_calcder5 
\title{Dérivée avec exponentielle 5}
\integer{a = random(1,randint(1..5)*randint(1,-1))}
\integer{d = randint(1..5)*randint(1,-1)}
\integer{b = randint(-5..5)}
\integer{c = randint(-5..5)}
\integer{e = randint(-5..5)}
\text{u=texmath(maxima(\d*x^2+\c*x+\e))}
\text{v=texmath(maxima(x+\b))}
\text{cedata=(\d*x^2+\c*x+\e)*exp(x+\b)}
\text{ft=(\u)e^{\v}}
\text{ftn=(a_n x^2+b_n x+c_n)e^{\v}}
\function{fder=maxima(diff(\cedata,x))}
\function{fder2=maxima(diff(\fder,x))}
\text{arecur=a_n}
\text{brecur=b_n+2*a_n}
\text{crecur=c_n+b_n}
\integer{nata=1}
\integer{natb=2}
\integer{natc=5}
\text{lstnat=constante, arithmétique, géométrique, arithmético-géométrique, quelconque}
\statement{<p>
  On considère la fonction \(f) définie par \(f(x)=\displaystyle \ft).</p>
<ol>
<li>Calculer \(f'(x)) et \(f''(x)):
<div class="wimscenter">\(f'(x))=\embed{reply1}</div>
<div class="wimscenter">\(f''(x))=\embed{reply2}</div>
</li><li>
  En supposant qu'il existe des suites \((a_n),(b_n)) et \((c_n)), telles que pour tout entier
  \(n), la dérivée d'ordre \(n) est donnée par \(f^{(n)}(x)=\ftn),
  exprimer les termes \(a_{n+1},b_{n+1}) et \(c_{n+1}) en fonction de \(a_n,b_n) et \(c_n).
<div class="wimscenter">\(a_{n+1})=\embed{reply3}</div>
<div class="wimscenter">\(b_{n+1})=\embed{reply4}</div>
<div class="wimscenter">\(c_{n+1})=\embed{reply5}</div>
<div class="wims_instruction"> Taper <span class="tt">a_n</span>
  pour \(a_n) et <span class="tt">b_n</span> pour \(b_n)</div>
</li><li>En déduire la nature des suites \((a_n), (b_n)) et \((c_n)):
<div class="wimscenter">la suite \((a_n)) est une suite \embed{reply6}</div>
<div class="wimscenter">la suite \((b_n)) est une suite \embed{reply7}</div>
<div class="wimscenter">la suite \((c_n)) est une suite \embed{reply8}</div>
</li></ol>
}

\answer{dérivée}{\fder}{type=formal}
\answer{dérivée seconde}{\fder2}{type=formal}
\answer{\(a_{n+1})}{\arecur}{type=formal}
\answer{\(b_{n+1})}{\brecur}{type=formal}
\answer{\(c_{n+1})}{\crecur}{type=formal}
\answer{nature de \((a_n))}{\nata;\lstnat}{type=menu}
\answer{nature de \((b_n))}{\natb;\lstnat}{type=menu}
\answer{nature de \((c_n))}{\natc;\lstnat}{type=menu}
#endif
