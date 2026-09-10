target=courb1 courb2 courb3
#define TITRE Détermination d'une fonction
#if defined TARGET_courb1
# define NUM
#endif
#if defined TARGET_courb2
# define NUM *
#endif
#if defined TARGET_courb3
# define NUM **
#endif
\title{TITRE NUM}
#include "author.inc"
\precision{10000}
#if defined TARGET_courb3
\steps{reply1,reply2,reply3,reply4,reply5,reply6,reply10,reply11,reply12
reply7,reply8,reply9}
#endif
\text{choix=wims(replace internal A by 1,2 in \confparm1)}
\text{choix=wims(replace internal B by 3 in \choix)}
\text{choix=wims(replace internal C by 4,5,6 in \choix)}
\text{choix=wims(replace internal D by 8 in \choix)}
\text{choix=wims(replace internal E by 7,9 in \choix)}

\integer{n = \choix = ? randint(1..9): randitem(\choix)}

\integer{a = \n >=7 ? random(1..4)*random(-1,1):random(1..5)*random(-1,1)}
\integer{b=random(-5..5)}
\integer{c=random(-5..5)}

\function{f=item(\n,\a*(x)^2 + \b*x + \c,
\a*x^3 + \b*(x)^2 + \c*x,
\b*x + \c + \a/(x + 1),
\b*x + \c + \a*ln(x + 1),
\a*ln(x) + \b*x + \c,
\a*ln(2*x + 1) + \b*x + \c,
\b*x + \c + \a*sqrt(x + 1),
\a*sqrt(x) + \b*x + \c,
\a*sqrt(2*x + 1) + \b*x + \c)}

\text{ft=item(\n,a*x^2 + b*x + c,
a*x^3 + b*x^2 + c*x,
a/(x + 1) + b*x + c,
a*ln(x + 1) + b*x + c,
a*ln(x) + b*x + c,
a*ln(2*x + 1) + b*x + c,
a*sqrt(x + 1) + b*x + c,
a*sqrt(x) + b*x + c,
a*sqrt(2*x + 1) + b*x + c)
}
a supprimer
text{ft=item(\n,a x^2 + b x + c,
a x^3 + b x^2 + c x,
a/(x + 1) + b x + c,
a*ln(x + 1) + b x + c,
a*ln(x) + b x + c,
a*ln(2*x + 1) + b x + c,
a*sqrt(x + 1) + b x + c,
a*sqrt(x) + b x + c,
a*sqrt(2*x + 1) + b x + c)
}
\text{ft=texmath(\ft)}
\integer{x0=item(\n,0,1,0,0,1,0,0,4,4)}
\integer{x1=item(\n,random(-1,1)*random(1,2),random(-2,-1,2),random(-3,-2,1,2),random(1,2,3),random(2,3,4,8,9),random(1,2,3,4),random(-1,3,6,4),random(0,1,7,5),random(0,2,3))}
\function{fp=diff(\f,x)}

\function{y0=wims(mathsubst x=\x0 in \f)}
\function{y0=simplify(\y0)}
\function{y1=wims(mathsubst x=\x1 in \f)}
\function{y1=simplify(\y1)}
\function{y1=wims(replace internal log(4) by 2*log(2) in \y1)}
\function{y1=wims(replace internal log(8) by 3*log(2) in \y1)}
\function{y1=wims(replace internal log(9) by 2*log(3) in \y1)}
#if defined TARGET_courb1 || defined TARGET_courb2
\function{y1=simplify(\y1)}
#else
\function{y1=maxima(expand((\y1)))}
#endif
\function{y1=wims(replace internal log by ln in \y1)}
\text{ty1=texmath(\y1)}

\real{xmin=min(min(\x0-2,\x1-1),-1)}
\real{xmax=max(max(\x0+2,\x1+1),1)}
\real{ymin=min(min(\y0-1,\y1-1),-1)}
\real{ymax=max(max(\y0+1,\y1+1),1)}

\function{yp0=wims(mathsubst x=\x0 in \fp)}
\function{yp0=simplify(\yp0)}

\real{ymin= \y0-\yp0 <\ymin+1 and \y0+\yp0>\ymax-1 ? \y0-\yp0 -1 : \ymin}
\real{ymin= \y0+\yp0 <\ymin+1 and \y0-\yp0>\ymax-1 ? \y0+\yp0 -1 : \ymin}

\real{ymin= \ymax-\ymin > 40 ? \ymin-1}

\real{xt= \y0-\yp0 >\ymin and \y0-\yp0<\ymax ? \x0-1 : \x0+1}
\real{yt= \y0-\yp0 >\ymin and \y0-\yp0<\ymax ? \y0-\yp0 : \y0+\yp0}

Tracés complémentaires pour aider à la lecture dans certains cas

\text{aidetg= abs(\yp0)>8 or (abs(\yp0)> 3 and \ymax-\ymin >25) ?
fcircle \xt,\yt,5, red
dsegment 0,\yt,\xt,\yt,red
text red , 0.1 , \yt, medium,\yt}

\text{aideb= floor(\y1)<>\y1 or \ymax - \ymin > 25?
text blue, 0.1,\y1,medium,\y1
dsegment 0,\y1,\x1,\y1,blue
}

\text{aidea= \ymax - \ymin >25 ?
dsegment 0,\y0,\x0,\y0,blue
text blue, 0.1,\y0,medium,\y0
}

\integer{ymi=floor(\ymin)}
\integer{yma=floor(\ymax)+1}
#if defined TARGET_courb1
\text{name_enonce=<p>La fonction \(f) représentée par la courbe bleue ci-dessous
est de la forme : \(f(x)) = \(\ft).</p>
<p>Cette courbe passe par \(A) et \(B) et sa tangente en \(A) est tracée
en vert.</p>
<p>Déterminer graphiquement le coefficient directeur de
cette tangente, puis calculer \(a), \(b) et \(c).</p>
}
#endif
#if defined TARGET_courb2
\text{name_enonce=<p>La courbe bleue ci-dessous représente une fonction \(f)
de la forme : \(f(x) =) \(\ft).</p>
<p>
Elle passe par \(A(\x0 ; \y0)) et \(B (\x1 ; \ty1)).
La tangente à la courbe en \(A) est tracée en vert ;
son coefficient directeur est \(\yp0).</p>
<p>Calculer \(a), \(b) et \(c).</p>
}
#endif
#if defined TARGET_courb3
\text{name_enonce=<p>La courbe bleue ci-dessous représente une fonction
\(f) de la forme : \(f(x) = \ft).</p>}
#endif

\text{aide=}
#if defined TARGET_courb1
\text{aide=\aidea
\aideb
\aidetg}
#endif
#if defined TARGET_courb3
\text{listerep = \x0,\x1,\y0,\y1,\yp0,0,\(f),\(f')}
\text{aide=\aideb}
#endif
\statement{\name_enonce
#if defined TARGET_courb3
\if{\step=2}{<ul class="wims_nopuce"><li>On sait que \(f(\x0)=\y0) ; \(f(\x1) = \ty1) et \(f'(\x0) = \yp0).
</li><li><b>Calculer \(a), \(b) et \(c).</b></li></ul>}
#endif
\draw{500,300}{
  xrange \xmin, \xmax
  yrange \ymin,\ymax
  parallel \xmin,\ymi,\xmin,\yma,1,0,\xmax - \xmin +1,grey
  parallel \xmin,\ymi,\xmax,\ymi,0,1,\yma -\ymi +1,grey
  hline 0,0,black
  arrow  0,0,1,0,6,black
  arrow 0,0,0,1,6,black
  vline 0,0,black
  plot blue, \f
  fcircle \x0,\y0,7, green
  fcircle \x1,\y1,7 , green

  plot green, \y0+(x-\x0)*\yp0

  text black,\x0,\y0,medium,A
  text black,\x1,\y1,medium,B
\aide
}
#if defined TARGET_courb1 || defined TARGET_courb2
<ul class="wims_nopuce">
# if defined TARGET_courb1
<li><label for="reply4">Coefficient directeur de la tangente :</label> \embed{reply4,7} </li>
# endif
<li><label for="reply1">\(a) =</label> \embed{reply1,7} </li>
<li><label for="reply2">\(b) =</label> \embed{reply2,7} </li>
<li><label for="reply3">\(c) =</label> \embed{reply3,7} </li>
</ul>
#endif
#if defined TARGET_courb3
\if{\step=1}{<p>Interpréter les renseignements tirés de l'observation de la courbe : </p>
<ul><li>
<b><i>La courbe passe par \(A (\x0 ; \y0))</i></b> se traduit par :
<div style="text-align:center">\embed{reply10} ( \embed{reply1} ) = \embed{reply2}</div></li>
<li><b><i>La courbe passe par \(B (\x1 ; \ty1))</i></b> se traduit par :
<div style="text-align:center">\embed{reply11}( \embed{reply3} ) = \embed{reply4}</div></li>
<li><b><i>La tangente tracée en vert a comme coefficient directeur \(\yp0) </i></b> se traduit par :
<div style="text-align:center">\embed{reply12}( \embed{reply5} ) = \embed{reply6}</div></li>
</ul>
}

\if{\step=2}{
<div class="wims_center"><label for="reply7">\(a) =</label> \embed{reply7,7} ;
<label for="reply8">\(b) =</label> \embed{reply8,7}  ;
<label for="reply9">\(c) =</label> \embed{reply9,7}</div>
}
#endif
}
#if defined TARGET_courb1
\hint{<p>Le coefficient directeur d'une droite est égal à
\(\frac{\Delta y}{\Delta x}).</p>
Exprimer les trois conditions sur la courbe en utilisant \(f) et \(f').
<p>
Calculer \(f'(x)) pour pouvoir transformer ces conditions
en système de trois équations à trois inconnues.</p>
}
#endif
#if defined TARGET_courb2
\hint{<ul class="wims_nopuce"><li>
La courbe représentant la fonction \(f) <b> passe par </b>
les points \(M(x;y)) qui vérifient <b>\(y = f(x))</b>.
</li><li>
<b>\(f'(x))</b> est le <b>coefficient directeur de la tangente</b>
à la courbe au point <b> d'abscisse x</b>.</li><li>N'oubliez pas de regarder <b>en quel point</b> la droite verte est <b>tangente</b> (c'est à dire "touche") à la courbe.</li><li>
Vous obtenez ainsi trois conditions sur \(f(x)) ou \(f'(x))</li><li>
Calculer ensuite <b>\(f'(x))</b> en dérivant \(f(x) = \ft).
\if{\n=3}{On rappelle que la dérivée de
\(\frac{1}{u}) est \(\frac{-u'}{u^2}) et que la dérivée de
\(\frac{u}{v})est \(\frac{u'v-uv'}{v^2}) }
\if{\n>3}{On rappelle que la dérivée de \(ln(u)) est \(\frac{u'}{u}) et que la dérivée de \(sqrt(u)) est \(\frac{u'}{2 sqrt(u)}). }</li><li>
Exprimer alors les trois conditions en utilisant les
expressions de \(f(x)) et \(f'(x)).</li><li>
Vous obtenez un système de trois équations à trois
inconnues (\(a), \(b) et \(c)). Bien le regarder pour
choisir la méthode la plus simple pour le résoudre.</li><li>
\if{\n>3}{Vous aurez peut-être besoin d'utiliser
la propriété de la fonction \(ln) : \(ln(a^n) = n*ln(a)).
}</li></ul>}
#endif
#if defined TARGET_courb3
\hint{
 \if{\step=1}{<ul class="wims_nopuce"><li>La courbe représentant la fonction \(f)
<b> passe par </b> les points \(M(x;y)) qui vérifient <b>\(y = f(x))</b>.</li><li>

<b>\(f'(x))</b> est le <b>coefficient directeur de la tangente</b>
à la courbe au point <b> d'abscisse x</b>.</li><li>
N'oubliez pas de regarder <b>en quel point</b> la droite verte
est <b>tangente</b> (c'est à dire "touche") à la courbe.</li></ul>}

 \if{\step=2}{<ul class="wims_nopuce"><li>Calculer d'abord <b>\(f'(x))</b> en dérivant \(f(x) = \ft).
   \if{\n=3}{On rappelle que la dérivée de \(\frac{1}{u}) est
\(\frac{-u'}{u^2})et que la dérivée de \(\frac{u}{v}) est
\(\frac{u'v-u v'}{v^2}) }
   \if{\n>3}{On rappelle que la dérivée de \(ln(u)) est \(\frac{u'}{u}) et que la dérivée de \(sqrt(u)) est \(\frac{u'}{2 sqrt(u)}). }</li><li>
Exprimer ensuite les trois conditions <b>(\(f(\x0) = \y0) ;
\(f(\x1)=\ty1) et \(f'(\x0) = \yp0))</b> en utilisant les expressions
de \(f(x)) et \(f'(x)).</li><li>
Vous obtenez ainsi un système de trois équations à trois inconnues
(\(a), \(b) et \(c)). Bien le regarder pour choisir la méthode la plus simple pour le résoudre.</li><li>
   \if{\n>3}{Vous aurez peut-être besoin d'utiliser la propriété de la fonction \(ln) :
\(ln(a^n)=n*ln(a)).
   }</li></ul>
  }
}
#endif
#if defined TARGET_courb3
\answer{}{\x0;\listerep}{type = clickfill}
\answer{}{\y0;\listerep}{type = clickfill}
\answer{}{\x1;\listerep}{type = clickfill}
\answer{}{\y1;\listerep}{type = clickfill}
\answer{}{\x0;\listerep}{type = clickfill}
\answer{}{\yp0;\listerep}{type = clickfill}
#endif
\answer{\(a)}{\a}{type=numeric}
\answer{\(b)}{\b}{type=numeric}
\answer{\(c)}{\c}{type=numeric}
#if defined TARGET_courb1
\answer{coefficient directeur}{\yp0}{type = numeric}
#endif
#if defined TARGET_courb3
\answer{}{\(f);\listerep}{type = clickfill}
\answer{}{\(f);\listerep}{type = clickfill}
\answer{}{\(f');\listerep}{type = clickfill}
#endif
