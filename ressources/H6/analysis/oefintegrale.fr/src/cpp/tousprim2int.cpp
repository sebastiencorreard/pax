target=prim2int prim2int2 prim2int3 prim2int4 prim2intbis prim2int2bis prim2int3bis prim2int4bis

#if defined TARGET_prim2int
\title  {Primitive et intégrale (fraction exp ou ln)}
#endif
#if defined TARGET_prim2int2
\title  {Primitive et intégrale (exp)}
#endif
#if defined TARGET_prim2int3
\title  {Primitive et intégrale (exp ou ln)}
#endif
#if defined TARGET_prim2int4
\title  {Primitive et intégrale (ln)}
variante de l'exercice module=classes/fr&cmd=new&exo=prim2int
avec ln uniquement
#endif
#if defined TARGET_prim2intbis
\title  {Primitive et intégrale (fraction exp ou ln) à étapes}
#endif
#if defined TARGET_prim2int2bis
\title  {Primitive et intégrale (exp) à étapes}
#endif
#if defined TARGET_prim2int3bis
\title  {Primitive et intégrale (exp ou ln) à étapes}
#endif
#if defined TARGET_prim2int4bis
\title  {Primitive et intégrale (ln) à étapes}
#endif
\author {Chantal,Causse}
\email  {Chantal.Causse@noos.fr}
\format {html}
\range{1..10}

#if (defined TARGET_prim2int || defined TARGET_prim2intbis)
\integer{a=random(1..5)*random(1,-1)}
\integer{b=random(-5..5)}
\integer{c1=random(1..3)}
\integer{c2=random(1..5)}
\integer{c3=randint(1..3)*random(-1,1)}

\text{confparm1 = \confparm1 = ? 1,2,3 : \confparm1}

\integer{choix=randitem(\confparm1)}
\function{Forme= item(\choix,(a*x+b)*e^(\c3*x),(a*x+b)/(\c1*x^2+\c2),a*x*ln(x)+b*x)}
\text{FormeT=texmath(\Forme)}

\function{F= evalue(\Forme,a=\a,b=\b)}
\function{F1=maxima(expand(\F))}
\function{F2=simplify(\F)}
\function{F=item(\choix,\F2,\F2,\F1)}
\function{F=wims(replace internal log by ln in \F)}
\text{Ft=texmath(\F)}

\function{f=diff(\F,x)}
\function{f1=maxima(expand(\f))}
\function{f2=simplify(\f)}
\function{f=item(\choix,\f2,\f2,\f1)}
\text{ft=texmath(\f)}
\text{ft=wims(replace internal log by ln in \ft)}

\rational{inf=item(\choix,randint(-4..4)/2,randint(-4..4)/2,randint(1..8)/2)}
\rational{sup = \inf + randint(1..8)/4}

\text{Int=simplify(evalue(\F,x=\sup)) - simplify(evalue(\F,x=\inf))}
\text{Int=maxima(expand(\Int))}
\text{Int=wims(replace internal log by ln in \Int)}
#endif
#if (defined TARGET_prim2int2 || defined TARGET_prim2int2bis)
\integer{a=random(1..5)*random(1,-1)}
\integer{b=random(-5..5)}
\integer{c1=random(1..3)}
\integer{c2=random(1..5)}
\integer{c3=randint(1..3)*random(-1,1)}

\integer{choix=random(1,2)}
\function{Forme= item(\choix,(a*x+b)*e^(\c3*x),(x^2+a*x+b)*e^(\c3*x),a*x*ln(x)+b*x)}
\text{FormeT=texmath(\Forme)}

\function{F= evalue(\Forme,a=\a,b=\b)}
\function{F1=maxima(expand(\F))}
\function{F2=simplify(\F)}
\function{F=item(\choix,\F2,\F2,\F1)}
\function{F=wims(replace internal log by ln in \F)}
\text{Ft=texmath(\F)}

\function{f=diff(\F,x)}
\function{f1=maxima(expand(\f))}
\function{f2=simplify(\f)}
\function{f=item(\choix,\f2,\f2,\f1)}
\text{ft=texmath(\f)}
\text{ft=wims(replace internal log by ln in \ft)}

\rational{inf=item(\choix,randint(-4..4)/2,randint(-4..4)/2,randint(1..8)/2)}
\rational{sup = \inf + randint(1..8)/4}

\text{Int=simplify(evalue(\F,x=\sup)) - simplify(evalue(\F,x=\inf))}
\text{Int=maxima(expand(\Int))}
\text{Int=wims(replace internal log by ln in \Int)}
#endif
#if (defined TARGET_prim2int3 || defined TARGET_prim2int3bis)
\integer{a=random(1..5)*random(1,-1)}
\integer{b=random(-5..5)}
\integer{c1=random(1..3)}
\integer{c2=random(1..5)}
\integer{c3=randint(1..3)*random(-1,1)}

\integer{choix=random(1,2,3,3)}
\function{Forme= item(\choix,(a * x + b)*e^(\c3*x),(x^2+a*x+b)*e^(\c3*x),a * x *ln(x)+ b * x)}
\text{FormeT=texmath(\Forme)}

\function{F= evalue(\Forme,a=\a,b=\b)}
\function{F1=maxima(expand(\F))}
\function{F2=simplify(\F)}
\function{F=item(\choix,\F2,\F2,\F1)}
\function{F=wims(replace internal log by ln in \F)}
\text{Ft=texmath(\F)}


\function{f=diff(\F,x)}
\function{f1=maxima(expand(\f))}
\function{f2=simplify(\f)}
\function{f=item(\choix,\f2,\f2,\f1)}
\text{ft=texmath(\f)}
\text{ft=wims(replace internal log by ln in \ft)}


\rational{inf=item(\choix,randint(-4..4)/2,randint(-4..4)/2,randint(1..8)/2)}
\rational{sup = \inf + randint(1..8)/4}

\text{Int=simplify(evalue(\F,x=\sup)) - simplify(evalue(\F,x=\inf))}
\text{Int=maxima(expand(\Int))}
\text{Int=wims(replace internal log by ln in \Int)}
#endif


#if (defined TARGET_prim2int4 || defined TARGET_prim2int4bis)
\integer{a=random(1..5)*random(1,-1)}
\integer{b=random(-5..5)}
\integer{c1=random(1..3)}
\integer{c2=random(1..5)}
\integer{c3=randint(1..3)*random(-1,1)}

\integer{choix= 3 }
\function{Forme= item(\choix,(a * x + b)*e^(\c3*x),(x^2+a*x+b)*e^(\c3*x),a * x *ln(x)+ b * x)}
\text{FormeT=texmath(\Forme)}

\function{F= evalue(\Forme,a=\a,b=\b)}
\function{F1=maxima(expand(\F))}
\function{F2=simplify(\F)}
\function{F=item(\choix,\F2,\F2,\F1)}
\function{F=wims(replace internal log by ln in \F)}
\text{Ft=texmath(\F)}

\function{f=diff(\F,x)}
\function{f1=maxima(expand(\f))}
\function{f2=simplify(\f)}
\function{f=item(\choix,\f2,\f2,\f1)}
\text{ft=texmath(\f)}
\text{ft=wims(replace internal log by ln in \ft)}

\rational{inf=item(\choix,randint(-4..4)/2,randint(-4..4)/2,randint(1..8)/2)}
\rational{sup = \inf + randint(1..8)/4}

\text{Int=simplify(evalue(\F,x=\sup)) - simplify(evalue(\F,x=\inf))}
\text{Int=maxima(expand(\Int))}
\text{Int=wims(replace internal log by ln in \Int)}
#endif
#if (defined TARGET_prim2int || defined TARGET_prim2int2 || defined TARGET_prim2int3 || defined TARGET_prim2int4)
\statement{<ol><li>Déterminer les nombres \(a) et \(b) pour que la fonction \(F) définie par \(F(x) = \FormeT) soit une primitive de la fonction \(f) définie par \(f(x) = \ft).</li>
<li>En déduire l'expression de \(F(x)).</li>
<li>Calculer \(integrate(f(x),x=\inf..\sup)\).</li></ol>
}
#endif
#if (defined TARGET_prim2intbis || defined TARGET_prim2int2bis || defined TARGET_prim2int3bis ||defined TARGET_prim2int4bis)
\steps{reply1,reply2
reply3
reply4}
\statement{On considère les fonctions \(f) définie par \(f(x) = \ft) et \(F) définie par \(F(x) = \FormeT) (\(a\) et \(b\) sont des réels).
\if{\step=1}{<p>1. Déterminer les nombres \(a) et \(b) pour que la fonction \(F) soit une primitive de \(f).</p>}{<p>Effectivement, on doit choisir \(a=\a\) et \(b=\b\) pour la fonction \(F) soit une primitive de \(f).</p>}
\if{\step=2}{<div>2. L'<label for="reply3">expression de \(F(x))</label> est donc \embed{r3}.</div>}
\if{\step=3}{<p>La fonction \(F\) vérifie \(F(x)=\Ft\).</p>
<p>3. Calculer \(integrate(f(x),x=\inf..\sup)\).</p>}
}
#endif
#if (defined TARGET_prim2int || defined TARGET_prim2intbis || defined TARGET_prim2int2 || defined TARGET_prim2int2bis ||defined TARGET_prim2int3 || defined TARGET_prim2int3bis || defined TARGET_prim2int4 || defined TARGET_prim2int4bis)
\answer{a}{\a}{type=integer}
\answer{b}{\b}{type=integer}
\answer{F(x)}{\F}{type=function}
\answer{intégrale}{\Int}{type = function}

\hint{\(F) est une primitive de \(f) si et seulement si \(F'(x) = f(x)).<br>
En calculant \(F'(x)) et en l'identifiant à \(f(x)), on trouve des équations permettant de déterminer \(a) et \(b)}
#endif
#if (defined TARGET_prim2int  || defined TARGET_prim2int2 || defined TARGET_prim2int3 || defined TARGET_prim2int4 )
\feedback{1=1}{<p>La fonction \(F \) définie par \(F(x)=\Ft\) est une primitive de la fonction \(f) définie par \(f(x) = \ft).</p>
<p>L'intégrale \(integrate(f(x),x=\inf..\sup)\) vaut \(\Int\).</p> }
#endif
#if (defined TARGET_prim2intbis ||  defined TARGET_prim2int2bis || defined TARGET_prim2int3bis || defined TARGET_prim2int4bis)
\feedback{(\sc_reply1=1) and (\sc_reply2=1) and (\sc_reply3=1) and (\sc_reply4=1)}{Votre réponse est juste. L'intégrale \(integrate(f(x),x=\inf..\sup)\) s'écrit \(\Int\).}
\feedback{(\sc_reply1=1) and (\sc_reply2=1) and (\sc_reply3=1) and (\sc_reply4=0)}{Votre réponse est fausse. L'intégrale \(integrate(f(x),x=\inf..\sup)\) vaut \(\Int\).}
#endif
