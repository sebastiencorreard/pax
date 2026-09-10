target = form1 form2 form3 form4 form5 form6


#if defined TARGET_form1
\title{Formules1 (monomes)}
#endif

#if defined TARGET_form2
\title{Formules2 (polynomes)}
#endif

#if defined TARGET_form3
\title{Formules3 (exponentielles)}
#endif

#if defined TARGET_form4
\title{Formules4 (logarithmes)}
#endif

#if defined TARGET_form5
\title{Formules5 (sqrt,1/x)}
#endif

#if defined TARGET_form6
\title{Formules6 (sin et cos)}
#endif


\author {Chantal, Causse}
\email  {Chantal.Causse@noos.fr}
\format {html}

\integer{k=random(1..8)*random(-1,1)}
\integer{a1=random(1..5)*random(-1,1)}
\integer{a2=random(1..5)*random(-1,1)}
\integer{a3=random(1..5)*random(-1,1)}
\integer{a4=random(1..5)*random(-1,1)}
\integer{b1=random(1..8)}
\integer{b2=random(1..8)}
\integer{b3=random(1..8)}
\integer{b4=random(1..8)}

************
#if defined TARGET_form1
\text{liste = \k,x,x^2,x^3,x^4}
\text{liste = shuffle(\liste)}
\text{f1 = \liste[1]}
\text{f2 = \liste[2]}
\text{f3 = \liste[3]}

\text{liste2 = \a1*x,\a2*x^2,\a3*x^3,\a4*x^4}
\text{Liste = shuffle(\liste2)}
\text{f4 = \Liste[1]}
\text{f5 = \Liste[2]}
\text{f6 = \Liste[3]}
#endif
**************
#if defined TARGET_form2

\text{liste = \k,\a1*x,\a2*x^2,\a3*x^3,\a4*x^4,-x/\a1,-x^2/\a2,-x^3/\a3,-x^4/\a4}
\text{liste = random(\k,1/\k),random(\a1*x,x/\a1),random(\a2*x^2,x^2/\a2),random(\a3*x^3,x^3/\a3),random(\a4*x^4,x^4/\a4)}
\text{liste = shuffle(\liste)}
\text{f1 = \liste[1]}
\text{f2 = \liste[2]}
\text{f3 = \liste[3]}

\text{liste2 = random(\k,1/\k),random(\a1*x,\a1*x,x/\a1),random(\a2*x^2,\a2*x^2,x^2/\a2),random(\a3*x^3,\a3*x^3,x^3/\a3),random(\a4*x^4,\a4*x^4,x^4/\a4)}
\text{Liste = shuffle(\liste2)}
\text{f4 = \Liste[1]+\Liste[4]}
\text{f5 = \Liste[2]+\Liste[5]}
\text{f6 = \Liste[3]+\Liste[1]}
#endif

***********
#if defined TARGET_form3
\text{liste = e^(\a1*x),e^(\b1*x),e^(\a2*x+\a3),e^(\a4*x^2)} 
\text{liste = shuffle(\liste)}
\text{f1 = \liste[1]}
\text{f2 = \liste[2]}
\text{liste =\k*e^(\a2*x),e^(\a3*x)/\k,\b1*e^(\a1*x+\b2),e^(\a3*x+\b3)/\b4}
\text{f3 = \liste[3]}
\text{f4 = \liste[4]}

\text{liste = e^(\a1*x),e^(\b1*x),e^(\a2*x+\a3),e^(\a4*x^2),\k*e^(\a2*x),e^(\a3*x)/\k,\b1*e^(\a4*x+\b3),e^(\b1*x+\b3)/\b4} 
\text{Liste = \a1*x,x/\a2,\a1*x + \a2,pari(\a3/\a4)*x,\a2*x^2+\a3*x }
\text{liste = shuffle(\liste)}
\text{Liste = shuffle(\Liste)}
\text{f5 = \liste[1]+\Liste[1]}
\text{f6 = \liste[2]+\Liste[2]}

\text{indication = La dérivée de \(e^{u}) est \(u' \times e^{u})}
\text{notation = <div class="wims_instruction">
Pour taper \(e^{3x}) par exemple, vous avez le choix entre : e^(3x) et exp(3x).
 </div>}

#endif
***************************
#if defined TARGET_form4

\text{liste = ln(x),ln(\b1*x+\a2),ln(\b1*x^2+\a3*x-\b2), \k*ln(x)}
\text{liste = shuffle(\liste)}
\text{f1 = \liste[1]}
\text{f2 = \liste[2]}
\text{f3 = \liste[3]}
\text{f4 = \liste[4]}

\text{Liste = \a1*x+\a2,random(\k*ln(x),ln(x)/\k),random(\a1*ln(\b1*x+\a2),ln(\b1*x+\a2)/\a1),random(\b4*ln(x+\a2),ln(x+\a2)/\b4)}
\text{Liste = shuffle(\Liste)}

\text{f5 = \Liste[1]+\Liste[2]}
\text{f6 = \Liste[3]+\Liste[4]}


\text{indication = La dérivée de \(\ln(u)) est \(\frac{u'}{u})}

#endif

********************

#if defined TARGET_form5
\text{liste = \a1/x,\a2*sqrt(x),1/(\a3*x),sqrt(x)/\a4}
\text{liste = shuffle(\liste)}
\text{f1 = \liste[1]}
\text{f2 = \liste[2]}
\text{f3 = \liste[3]}

\text{liste2 = \k,\a1*x,\a2*x^2,\a3*x^3,\a4*x^4}
\text{Liste = shuffle(\liste2)}
\text{f4 = \Liste[1]+\liste[4]}
\text{f5 = \Liste[2]-\liste[3]}
\text{f6 = \liste[1]- \Liste[3]}

\text{notation = <div class="wims_instruction">
Pour écrire \(sqrt(3x)) par exemple, taper : sqrt(3x).
 </div>}

\text{indication = Si \(f(x)=\frac{1}{x}), alors \(f'(x)=\frac{-1}{x^{2}})<br />
Si \(f(x)=\sqrt{x}), alors \(f'(x)=\frac{1}{2\sqrt{x}})
}
#endif


#if defined TARGET_form6
\text{liste = cos(x),sin(x),cos(x+\a1),sin(x+\a2),cos(x+random(1,3,5)*random(-1,1)*pi/4),sin(x+random(1,3,5)*random(-1,1)*pi/4)}
\text{liste = shuffle(\liste)}
\text{f1 = \liste[1]}
\text{f2 = \liste[2]}
\text{f3 = \liste[3]}

\text{liste2 = cos(\b1*x),sin(\b2*x),cos(\b3*x+\a2),sin(\b3*x+\a2),\k*cos(\b3*x+random(1,3,5)*random(-1,1)*pi/4),\k*sin(\a1*x+random(1,3,5)*random(-1,1)*pi/4)}
\text{Liste = shuffle(\liste2)}
\text{f4 = \Liste[1]}
\text{f5 = \Liste[2]}
\text{f6 =  \Liste[3]}

#endif

**********************
\text{f1t = texmath(\f1)}
\text{f2t = texmath(\f2)}
\text{f3t = texmath(\f3)}
\text{f4t = texmath(\f4)}
\text{f5t = texmath(\f5)}
\text{f6t = texmath(\f6)}

\text{fonctions=\f1t, \f2t, \f3t, \f4t, \f5t, \f6t}

\function{d1 = diff(\f1,x)}
\function{d2 = diff(\f2,x)}
\function{d3 = diff(\f3,x)}
\function{d4=diff(\f4,x)}
\function{d5=diff(\f5,x)}
\function{d6=diff(\f6,x)}

\function{derivees=\d1,\d2,\d3,\d4,\d5,\d6}

\statement{

<ul>
\for{ j = 1 to 6 }
{<li> Si \(f(x)=\fonctions[\j]), <label for="reply\j"> alors \(f'(x))=</label>\embed{reply\j,15}</li>}
</ul>
\notation
}

\answer{Dérivée de \(\f1t)}{\d1}{type=formal}
\answer{Dérivée de \(\f2t)}{\d2}{type=formal}
\answer{Dérivée de \(\f3t)}{\d3}{type=formal}
\answer{Dérivée de \(\f4t)}{\d4}{type=formal}
\answer{Dérivée de \(\f5t)}{\d5}{type=formal}
\answer{Dérivée de \(\f6t)}{\d6}{type=formal}



\solution{<p>
\for{ j = 1 to 3}
{Si \(f(x)=\fonctions[\j]), alors \(f'(x))= \(\derivees[\j]).<br />
}</p><p>
\for{ j = 4 to 6}
{Si \(f(x)=\fonctions[\j]), alors \(f'(x))= \(\derivees[\j]).<br />
}</p>
}

\hint{Si \(f(x)=ax + b), alors \(f'(x)=a).<br />
Si \(f(x)=x^{n}), alors \(f'(x)=n x^{n-1})<br />\indication.

}
