target=nbder1 nbder2 nbder3 nbder4 nbder5
\author{Maguy, Bruno ; Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{100}
#define TITRE Nombre dérivé
#if (defined TARGET_nbder1 || defined TARGET_nbder2 || defined TARGET_nbder3 || defined TARGET_nbder4 )
\integer{a=random(1..5)*random(-1,1)}
\integer{b=random(-5..5)}
\integer{c=random(-5..5)}

#if (defined TARGET_nbder1 || defined TARGET_nbder3 )
#if defined TARGET_nbder1
\title{Nombre Dérivé 1}
\text{mstep=r1,r2,r3,r4}
#else
\title{TITRE 3}
\text{mstep=r1,r2,r3,r4,r5,r6}
#endif
\function{f=\a*x^2+\b*x+\c}
\text{ft=texmath(maxima(\f))}
\text{defdom=\(\RR)}
\integer{x0=random(-3..3)}
#endif

#if (defined TARGET_nbder2 || defined TARGET_nbder4 )
#if defined TARGET_nbder2
\title{TITRE 2}
\text{mstep=r1,r2,r3,r4}
#else
\title{TITRE 4}
\text{mstep=r1,r2,r3,r4,r5,r6}
#endif
\function{f=(\a*x+\b)/(x-\c)}
\text{ft=texmath(maxima(\f))}
\text{defdom=\(\RR \setminus) &#123;\c&#125;}
\integer{x0=random(-3..3)}
\integer{x0=\x0=\c?\x0+1}
#endif

\function{fp=diff(\f,x)}
\rational{nder=evalue(\fp,x=\x0)}

\function{y0=wims(mathsubst x=(\x0) in \f)}
\function{y0=simplify(\y0)}
\function{y0h=wims(mathsubst x=(\x0+h) in \f)}
\function{y0h=simplify(\y0h)}
\function{y1=(\y0h - (\y0))/h}
\function{y1=simplify(\y1)}

\text{eqtgte=simplify(y= \nder*(x-(\x0))+(\y0))}

\steps{\mstep}
\statement{Soit la fonction \(f) définie sur \defdom par \(f(x)=) \(\ft).<br>
   On veut calculer le nombre dérivé de \(f) en \(x=\x0), en utilisant la définition.
<ol>
<li>Calculer <label for="reply1">\(f(\x0))=</label>\embed{reply1}</li>
<li>Exprimer <label for="reply2">\(f(\x0+h)) en fonction de \(h)&nbsp;: </label>\embed{reply2}</li>
<li>Calculer <label for="reply3">le rapport \(\frac{f(\x0+h)-f(\x0)}{h})
  en fonction de \(h\)&nbsp;:</label> \embed{reply3}</li>
<li>En déduire <label for="reply4">la valeur du nombre dérivé de \(f) en \(x=\x0)&nbsp;:
  </label>\embed{reply4}</li>
#if (defined TARGET_nbder3 || defined TARGET_nbder4 )
<li>Compléter&nbsp;:
<div class="wimscenter"> La tangente à la courbe représentative de \(f)
   au point d'abscisse \(\x0) est <label for="reply5">la droite
 qui passe par </label>A(\x0;\embed{reply5,3}) et qui a
   pour <label for="reply6">coefficient directeur</label> \embed{reply6,5}.</div>
</li>
#endif
</ol>
}

\answer{}{\y0}{type = numeric}
\answer{}{\y0h}{type = formal}
\answer{}{\y1}{type = formal}
\answer{}{\nder}{type = numeric}
\answer{}{\y0}{type = numeric}
\answer{}{\nder}{type = numeric}
#endif

#if defined TARGET_nbder5
\title{TITRE 5}
\integer{i=randint(1..4)}
integer{i=3}
\text{filename=nbder5\i.ggb}
\text{appletcommand=}
\text{appletcommand2=\appletcommand
}

\text{option=file=\filename
width=500
height=400
showToolBar=true
customToolBar="0|1|3|2|5|38|50|40|41|42|"
showAlgebraInput=false}

\text{option2=\option
}
\text{applet=slib(geo2D/geogebra \appletcommand, \option)}
\text{mstep=\i=1?r1,r2,r3:r1,r2,r3,r4}

\text{lstfunc=x^3/96-x^2/8+14/3,-0.25*x^2+2*x,2*x^3/15-x^2/5-4*x/5+3,-0.25*x^3+3*x+1}
\function{f=item(\i,\lstfunc)}
\function{fp=diff(\f,x)}
\if{\i=1}{
 \integer{x1=-4}
 \integer{x2=1}
 \integer{x3=8}
 \integer{x4=0}
 }{
 \text{xl=-2,-1,0,1,2,3,4}
 \text{xl=shuffle(\xl)}
 \text{xl=item(1..4,\xl)}
 \text{xl=wims(sort numeric list \xl)}
 \integer{x1=\xl[1]}
 \integer{x2=\xl[2]}
 \integer{x3=\xl[3]}
 \integer{x4=\xl[4]}
 }
\rational{n1=evalue(\fp,x=\x1)}
\rational{n2=evalue(\fp,x=\x2)}
\rational{n3=evalue(\fp,x=\x3)}
\rational{n4=evalue(\fp,x=\x4)}
\precision{10}
\steps{\mstep}
\statement{
<div class="float_left">\applet</div>
<div class="float_left">
\if{\i=1}{
   On a tracé la courbe représentative d'une fonction \(f) et certaines de ses tangentes.<br>
   Lire graphiquement&nbsp;:
<ol>
<li> <label for="reply1">\(f'(-4)) =</label> \embed{reply1,3}</li>
<li> <label for="reply2">\(f'(1)) =</label> \embed{reply2,3}</li>
<li> <label for="reply3">\(f'(8)) =</label> \embed{reply3,3}</li>
</ol>
}
{
   On a tracé la courbe représentative d'une fonction \(f).<br> Déplacer le point \(A\)
   sur la courbe et lire graphiquement les valeurs de \(f'(x))
   pour compléter le tableau suivant&nbsp;:
<table class="wimscenter wimsborder">
<tr><th>\(x)</th><td> \x1 </td><td> \x2 </td><td> \x3 </td><td> \x4 </td></tr>
<tr><th>\(f'(x))</th><td> \embed{reply1,3} </td><td> \embed{reply2,3}</td>
<td> \embed{reply3,3} </td><td> \embed{reply4,3} </td></tr>
</table>
<div class="wims_instruction">
   Donner des valeurs décimales avec 2 décimales ou bien des fractions irréductibles.
</div>
}
</div>
}
\answer{}{\n1}{type=numeric}
\answer{}{\n2}{type=numeric}
\answer{}{\n3}{type=numeric}
\answer{}{\n4}{type=numeric}
#endif
