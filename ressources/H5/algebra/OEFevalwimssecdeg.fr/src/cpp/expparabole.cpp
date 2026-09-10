target=expparabole1 expparabole2 expparabole3 expparabole4 expparabole5
\author{Régine, Mangeard;Maguy, Bruno}
\email{regine@mangeard.fr}
\format{html}
\keywords{parabola}

#if defined TARGET_expparabole1
# define NUM 1
#endif
#if defined TARGET_expparabole2
# define NUM 2
#endif
#if defined TARGET_expparabole3
# define NUM 3
#endif
#if defined TARGET_expparabole4
# define NUM 4
#endif
#if defined TARGET_expparabole5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{dessin=
 xrange -15,15
 yrange -15,15
 parallel -15,-15,-15,15,1,0,30,gray
 parallel -15,-15,15,-15,0,1,30,gray
 linewidth 2
 arrow 0,-15,0,15,10,blue
 arrow -15,0,15,0,10,blue
 segment -0.2,1,0.2,1,black
 segment 1,-0.2,1,0.2,black
 text black,-0.7,1.5,small,1
 text black,0.7,-0.5,small,1

}
#if defined TARGET_expparabole1
\title{TITLE 1}
\integer{xs=randint(-3..3)}
\integer{ys=random(-3,-2,-1,0,0,0,1,2,3)}
\integer{a=randint(1..3)*randint(1,-1)}
\integer{rep2=\a>0?1:3}
\integer{ay=\a*\ys}
\integer{rep1=\ay>0?3:1}
\integer{rep1=\ys=0?2}
\text{f=\a*(x-\xs)^2+\ys}
\text{p=texmath(a*x^2+b*x+c)}
\text{p=wims(text expand \p using 01)}
\text{dessin=\dessin
 plot red,\f
}
\statement{<div class="wims_columns">
 <div class="medium_size img_col">\draw{300,300}{\dessin}</div>
 <div class="medium_size text_col">
  On a représenté une parabole \(\mathcal{P}) d'équation:
<div class="wimscenter"> \(\mathcal{P}:y=\p)</div>
<p>
  Cocher les affirmations que vous pouvez déduire de ce dessin:</p>
<ol>
<li><label for="reply1">Le discriminant \(\Delta)</label> est: \embed{reply1}</li>
<li><label for="reply2">Le coefficient dominant \(a)</label> est: \embed{reply2}</li>
</ol>
 </div>
</div>

}
\answer{\(\Delta\)}{\rep1;strictement positif, nul, strictement négatif}{type=radio}
\answer{a}{\rep2;strictement positif, nul, strictement négatif}{type=radio}
#endif

#if defined TARGET_expparabole2
\integer{x1=randint(1..5)*randint(1,-1)}
\integer{x2=randint(1..5)*randint(1,-1)}
\integer{a=randint(1..3)*randint(1,-1)}
\integer{k=randint(2..3)*randint(1,-1)}
\text{ffact=texmath(maxima(\a*(x-\x1)*(x-\x2)))}
\text{fdev=texmath(maxima(expand(\a*(x-\x1)*(x-\x2))))}
\text{fbad1=\a=1?texmath(maxima(\k*(x-\x1)*(x-\x2))):texmath(maxima((x-\x1)*(x-\x2)))}
\text{fbad2=texmath(maxima(-\a*(x-\x1)*(x-\x2)))}
\text{fbad3=texmath(maxima(-\a*(x+\x1)*(x+\x2)))}
\text{fbad4=\a=1?texmath(maxima(expand(\k*(x-\x1)*(x-\x2)))):texmath(maxima(expand((x-\x1)*(x-\x2))))}
\text{lstrep=\(y=\ffact),\(y=\fdev),\(y=\fbad1),\(y=\fbad2),\(y=\fbad3),\(y=\fbad4)}
\text{rep=1,2}
\text{dessin=\dessin
 plot red,\a*(x-\x1)*(x-\x2)
}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{300,300}{\dessin}</div>
 <div class="medium_size text_col">
  On considère la parabole \(\mathcal{P}\) représentée ci-contre.
  Une équation de cette parabole est:
<ul>
 <li>\embed{reply1,1}</li>
 <li>\embed{reply1,2}</li>
 <li>\embed{reply1,3}</li>
 <li>\embed{reply1,4}</li>
 <li>\embed{reply1,5}</li>
 <li>\embed{reply1,6}</li>
 </ul>
</div></div>
<div class="wims_instruction"> Cocher toutes les réponses possibles.</div>
}
\answer{équation de P}{\rep;\lstrep}{type=checkbox}{option=shuffle}
#endif

#if (defined TARGET_expparabole3 || defined TARGET_expparabole4 || defined TARGET_expparabole5)
#if defined TARGET_expparabole3
\integer{x1=randint(1..3)*randint(1,-1)}
\integer{x2=randint(1..3)*randint(1,-1)}
\integer{y0=randint(1..9)}
\rational{a=\y0/(\x1*\x2)}
\text{f=\a*(x-\x1)*(x-\x2)}
\text{consigne=des points d'intersection avec les axes de coordonnées}
\text{indic=<div class="wims_instruction">Donner une forme factorisée de préférence.</div>}
\text{tsol=Les points d'intersection avec l'axe des abscisses permettent
 de déterminer que la parabole a une équation de la forme:<br>
\(y=a(x-\x1)(x-\x2))<p>
  Le point d'intersection avec l'axe des ordonnées donne \(\y0=a(\x1)(\x2))<br>
  Donc \(y=\a(x-\x1)(x-\x2)) </p>}
#endif
#if defined TARGET_expparabole4
\integer{xs=randint(1..4)*randint(1,-1)}
\integer{ys=random(-3,-2,-1,0,0,0,1,2,3)}
\rational{a=randint(1..3)/\xs}
\text{f=\a*(x-\xs)^2+\ys}
\integer{y0=\a*(\xs)^2+\ys}
\text{consigne=des coordonnées du sommet et du point d'intersection avec l'axe des oordonnées}
\text{indic=<div class="wims_instruction">Donner de préférence une forme canonique.</div>}
\text{tsol=Le sommet a pour coordonnées (\xs;\ys) donc la parabole a une équation de la forme:<br>
\(y=a(x-\xs)^2+\ys)<p>
  Le point d'intersection avec l'axe des ordonnées donne \(\y0=a(\xs)^2+\ys)<br>
  Donc \(y=\a(x-\xs)^2+\ys)
</p>}

#endif
#if defined TARGET_expparabole5
\integer{x1=randint(1..3)*randint(1,-1)}
\integer{x2=randint(1..3)*randint(1,-1)}
\integer{x2=\x1=\x2?\x2+1}
\integer{y0=randint(1..9)}
\rational{a=\y0/(\x1*\x2)}
\integer{cas=randint(1,2)}
\integer{k=\cas=1?randint(1..14-\y0):-randint(1..12)}
\text{f=\a*(x-\x1)*(x-\x2)+\k}
\text{consigne=des points d'intersection avec les droites d'équation \(y=\k) et \(x=0)}
\text{indic=<div class="wims_instruction">Donner une forme semi-factorisée de préférence du type \(\alpha(x-\beta)(x-\gamma)+\delta).</div>}
\text{dessin=\dessin
 dsegment -15,\k,15,\k,blue
}
\text{tsol=Soit \(f) la fonction dont la parabole \(\mathcal{P}) est la courbe représentative.<br>
  Considérons la fonction \(g) définie par \(g(x)=f(x)-\k).<br>
  Il vient \(g(\x1)=g(\x2)=0) donc \(g(x)=a(x-\x1)(x-\x2)).<br>
  De plus \(g(0)=f(0)-\k=\y0=a(\x1)(\x2)) donc \(g(x)=\a(x-\x1)(x-\x2)).<br>
  Donc \(f(x)=\a(x-\x1)(x-\x2)+\k).}
#endif
\text{p=texmath(a*x^2+b*x+c)}
\text{p=wims(text expand \p using 01)}
\text{dessin=\dessin
 plot red,\f
}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{300,300}{\dessin}</div>
 <div class="medium_size text_col">
  On a représenté ci-dessous une parabole \(\mathcal{P}) d'équation:
<div class="wimscenter"> \(\mathcal{P}: y=\p)</div>
<div>
  Par lecture graphique \consigne, déterminer une équation de \(\mathcal{P}):
<br>\indic</div>
<div class="wimscenter"> <label for="reply1">\(\mathcal{P})</label>:y= \embed{reply1}</div>
</div></div>}
\answer{équation de P}{\f}{type=function}
\solution{\tsol}
#endif
