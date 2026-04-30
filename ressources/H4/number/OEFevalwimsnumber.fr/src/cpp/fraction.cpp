target=fraction1 fraction2 fraction3 fraction4 fraction5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard; Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}

#define TITRE Calcul avec des fractions
\text{infocalc=A faire sans calculatrice!}
#if defined TARGET_fraction1
 \title{TITRE I}
 \integer{n=randint(2..11)}
 \integer{p=randint(3..8)}
 \text{x=\n+\frac{1}{\p}}
 \rational{sol=simplify(\n+1/\p)}

#endif
#if defined TARGET_fraction2
 \title{TITRE II}
 \integer{a=randint(2..8)}
 \integer{p=randint(3..5)}
 \integer{q=randint(6..11)}
 \text{x=\frac{1}{\a}+(\frac{\p}{\q})^2}
 \rational{sol=simplify(1/\a+ (\p / \q)^2)}
#endif

#if defined TARGET_fraction3
 \title{TITRE III}
 \integer{a=randint(2..11)}
 \integer{b=randint(2..11)}
 \integer{c=randint(2..7)}
 \integer{n=\a*\b}
 \integer{d=randint(3..8)}
 \integer{k=randint(1,2)}
 \if{\k=1}
 {
  \text{x=\n\times\frac{\c}{\b}}
  \rational{sol=simplify(\n*\c/\b)}
 }{
  \text{x=\frac{\c}{\b}\times\frac{\n}{\d}}
  \rational{sol=simplify(\c/\b*\n/\d)}
 }

#endif

#if defined TARGET_fraction4
 \title{TITRE IV}
 \integer{a=randint(1..4)}
 \integer{b=randint(3..7)}
 \integer{c=randint(1..5)}
 \integer{d=randint(6..9)}
 \integer{e=randint(3..6)}
 \text{x=\frac{\a}{\b}-\frac{\c}{\d}+\frac{7 \times \e}{7}}
 \rational{sol=simplify(\a/\b- \c / \d + \e)}
#endif

#if defined TARGET_fraction5
 \title{TITRE V}
 \integer{a=randint(2..6)}
 \integer{b=randint(3..11)}
 \integer{c=randint(4..13)}
 \text{x=\frac{\frac{\a}{-\b}}{\frac{\c}{\a}}}
 \rational{sol=simplify((\a/(-\b))/ ( \c / \a))}
#endif

#if defined TARGET_fraction6
 \title{TITRE V}
 \integer{b=randint(2..11)}
 \integer{c=randint(5..13)}
 \integer{d=randint(2..8)}
 \integer{e=randint(2..5)}
 \integer{f=randint(2..8)}
 \integer{g=randint(2..5)}
 \text{x=\frac{(\frac{1}{\b}-\frac{\c}{\d})\times \frac{\e}{\f}}{\g}}
 \rational{sol=simplify((1/\b- \c / \d)*( \e/ \f) / \g)}
#endif


\statement{
<div class="wims_warning">\infocalc</div>
  Calculer :
<div class="wimscenter">\(A=\x)</div>
  Exprimer le résultat sous forme d'une fraction irréductible.
<div class="wimscenter"><label for="reply1">Votre solution</label> : \embed{reply1,5}</div>
}
\answer{}{\sol}{type=numexp}
