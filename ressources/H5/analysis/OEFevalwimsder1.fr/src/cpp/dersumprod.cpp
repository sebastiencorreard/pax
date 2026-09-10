target=dersumprod1 dersumprod2 dersumprod3 dersumprod4 dersumprod5
\author{Maguy, Bruno ; Régine, Mangeard}
\email{regine@mangeard.Fr}
\format{html}
\precision{100}
\computeanswer{yes}
#define TITRE Dérivée somme ou produit par un réel
\integer{k=randint(-6..6)}
\text{ta=\a}
#if defined TARGET_dersumprod1
\title{TITRE 1}
\text{lpar=shuffle(1,1,0,0,0,0,0)}
\integer{a=\lpar[1]}
\integer{b=\lpar[2]}
\integer{c=\lpar[3]}
\integer{d=\lpar[4]}
\integer{e=\lpar[5]}
\integer{g=\lpar[6]}
\integer{h=\lpar[7]}

\function{f=\a*x^6+\b*x^3+\c*x^2+\d*x+\e*sqrt(x)+\g/x+\h*sin(x)+\k}
\text{tf=texmath(maxima(\f))}
#endif
#if defined TARGET_dersumprod2
\title{TITRE 2}
\text{lpar=shuffle(randint(2..6)*randint(1,-1),0,0,0,0)}
\integer{a=\lpar[1]}
\integer{b=\lpar[2]}
\integer{c=\lpar[3]}
\integer{d=\lpar[4]}
\integer{e=\lpar[5]}

\function{f=\a*x^3+\b*x^2+\c*x+\d/x+\e*sin(x)}
\text{tf=texmath(maxima(\f))}
#endif
#if defined TARGET_dersumprod3
\title{TITRE 3}
\text{lpar=shuffle(randint(2..6)*randint(1,-1),randint(2..6)*randint(1,-1),0,0,0)}
\integer{a=\lpar[1]}
\integer{b=\lpar[2]}
\integer{c=\lpar[3]}
\integer{d=\lpar[4]}
\integer{e=\lpar[5]}

\function{f=\a*x^5+\b*x^3+\c*x^2+\d*x+\e*sqrt(x)+\k}
\text{tf=texmath(maxima(\f))}
#endif
#if defined TARGET_dersumprod4
\title{TITRE 4}
\text{lpar=shuffle(randint(2..6)*randint(1,-1),randint(2..6)*randint(1,-1),randint(2..6)*randint(1,-1))}
\integer{a=\lpar[1]}
\integer{b=\lpar[2]}
\integer{c=\lpar[3]}
\rational{k=random(\k,simplify(randint(1..6)/randint(2..6)))}
\function{f=x^2/\a+x/\b+\c/x+\k}
\text{tf=texmath(maxima(\f))}
#endif
#if defined TARGET_dersumprod5
\title{TITRE 5}
\integer{a=randint(1..6)*randint(1,-1)}
\integer{b=randint(1..6)*randint(1,-1)}
\integer{c=randint(1..6)*randint(1,-1)}
\rational{k=randint(2..9)}
\function{f=(\a*x^4+\b*x^2+\c*x)/\k}
\text{tf=\frac{texmath(maxima(\a*x^4+\b*x^2+\c*x))}{\k}}
#endif


\function{fp=diff(\f,x)}
\statement{
   Calculer \(f'(x)) pour \(f(x)=\tf)&nbsp;:
<div class="wimscenter"><label for="reply1">\(f'(x)=)</label>\embed{reply1}</div>
}
\answer{\(f'(x))}{\fp}{type=formal}
