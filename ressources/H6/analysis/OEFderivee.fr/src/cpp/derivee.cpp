target = der1 der2 der3 der3_b der4 der5 der6 


#if defined TARGET_der1
\title{Dérivée de polynome 1}
#endif

#if defined TARGET_der2
\title{Dérivée de polynome 2}
#endif

#if defined TARGET_der3_b
\title{Produit avec exponentielle}
#endif
#if defined TARGET_der3
\title{Dérivée d'exponentielle}
#endif

#if defined TARGET_der4
\title{Dérivée de logarithme 1}
#endif

#if defined TARGET_der5
\title{Dérivée de logarithme 2}
#endif


#if defined TARGET_der6
\title{Dérivée de trinome degré2}
#endif

\author {Chantal, Causse}
\email  {Chantal.Causse@noos.fr}
\format {html}

\integer{a1=random(-4..4)}
\integer{a2=random(-4..4)}
\integer{a3=random(-4..4)}
\integer{c1=random(1..8)*random(1,-1)}
\integer{c2=random(1..8)*random(1,-1)}
\integer{c3=random(1..8)*random(1,-1)}
\integer{c4=random(1..8)*random(1,-1)}
\function{lin=\c1*x+\c2}
\function{lin1 = pari(\c3*x+\a1)}
\function{lin2=(\c3*x+\c4)/\c2}
\function{tri=\c1*x^2+\c2*x+\c3}
\function{tri2=pari(\c1*x^2+\a1*x+\a2)}
\function{pol = pari(\c1*x^3+\a1*x^2+\a2*x+\a3)}

#if defined TARGET_der1
\function{f=randitem(
\lin,
\tri,
\tri2,
\pol
)}
\function{f = simplify(\f)}
\function{F=diff(\f,x)}
\text{ft=texmath(\f)}
\function{F = pari(\F)}
\text{Ft = texmath(\F)}
#endif

#if defined TARGET_der2
\function{f=randitem(
(\lin)/(\c4),
(\tri)/(\c4),
(\pol)/(\c4),
(\tri2)/(\c4)
)}
\function{f = simplify(\f)}
\function{F=diff(\f,x)}
\text{ft=texmath(\f)}
\function{F = pari(\F)}
\text{Ft = texmath(\F)}
#endif

#if defined TARGET_der3 
\function{f=randitem(
 e^(\lin),
 e^(\c1*x^2 + \c2*x),
\c4*random(1,x)+\c3*e^(\c1*x^2 + \c2*x),
 \c3* e^(\lin),
 \c4+\c3* e^(\lin),
 \c3*x+\c4 + e^(\lin),
 \c2*e^(\c1+x),
 \c2*e^(\c1*x),
 (\c1*x^2+\c2*x+\c3)+ \c4*e^(\lin)
)}
\function{F=diff(\f,x)}
\text{ft=texmath(\f)}

\text{Ft = texmath(\F)}



\text{notation = <div class="wims_instruction">
Pour écrire \(e^{3x}) par exemple, vous avez le choix entre : e^(3x) et exp(3x).
 </div>}



\text{aide = La dérivée de \(e^{u}) est \(u' e^{u}).<br />}
#endif

#if defined TARGET_der3_b
\function{f=randitem(
 (\lin)*e^(x),
 (\lin1)*e^(x),
 (\lin2)*e^(x),
(\tri)*e^x,
(\tri2)*e^x
)}
\function{F=diff(\f,x)}
\text{ft=texmath(\f)}

\text{Ft = texmath(\F)}



\text{notation = <div class="wims_instruction">
Pour écrire \(e^{x}) par exemple, vous avez le choix entre : e^(x) et exp(x).
 </div>}



\text{aide = La dérivée de \(e^{x}) est \(e^{x}).<br />}
#endif



#if defined TARGET_der4
\function{f=randitem(
 ln(\pol),
 (\lin)+\c3*ln(x),
 \pol+ln(\lin),
  \tri2+\c4*ln(x),
 \c1*ln(x+\c2),
 \c3*ln(\lin)
)}

\function{F=diff(\f,x)}
\text{ft=texmath(\f)}
\text{Ft = texmath(\F)}

\text{aide = La dérivée de \(\ln(u)) est \(\frac{u'}{u}).<br />}

#endif


#if defined TARGET_der5
\function{f=randitem(

 (\lin)*ln(x),
 (\lin)*ln(\lin),
 (\lin1)*ln(\lin),
 (\tri2)*ln(x),
  \tri2+\c2*x*ln(x),
  \lin1+\c2*x*ln(x),
)}

\function{F=diff(\f,x)}
\text{ft=texmath(\f)}
\function{F = simplify(\F)}
\function{der=wims(replace internal log by ln in \F)}
\text{Ft = texmath(\der)}

\text{aide = La dérivée de \(\ln(u)) est \(\frac{u'}{u}).<br />
La dérivée de \(uv) est \(u'v + uv').<br />
La dérivée de \(\frac{u}{v}) est \(\frac{u'v - uv'}{v^{2}}).}
#endif


#if defined TARGET_der6
\function{f=randitem(
\tri,
\tri2
)}
\function{f = simplify(\f)}
\function{F=diff(\f,x)}
\text{ft=texmath(\f)}
\function{F = pari(\F)}
\text{Ft = texmath(\F)}
#endif



\statement{Calculer la <label for="reply1"> dérivée de la fonction \(f) définie par \(f(x) = \ft)</label>.<br />
\notation

}

\answer{\(f'(x))}{\F}{type=formal}

\hint{Si  \(f(x)=x^{n}), alors \(f'(x)=n x^{n - 1}).<br />
La dérivée de \(u + v) est \(u' + v').<br />
La dérivée de \(k u) est \(k u'), si \(k) est une constante.<br />\aide}
