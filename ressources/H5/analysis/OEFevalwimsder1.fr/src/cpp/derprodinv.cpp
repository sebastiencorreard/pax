target=derprodinv1 derprodinv2 derprodinv3 derprodinv4 derprodinv5
\author{Maguy, Bruno ; Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{100}
\computeanswer{yes}
#define TITRE Dérivée produit ou inverse
\integer{k=randint(-6..6)}
\text{ta=\a}
#if defined TARGET_derprodinv1
\title{TITRE 1}
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(1..5)*randint(1,-1)}
\integer{c=randint(1..5)*randint(1,-1)}
\integer{n=randint(2,3)}
\function{f=\a*x^\n*(\b*x+\c)}
\text{tf=texmath(maxima(\f))}
\integer{an=\a*\n}
\integer{abnp=\a*\b*(\n+1)}
\integer{acn=\a*\c*\n}
\integer{ab=\a*\b}
\integer{np=\n+1}
\integer{nm=\n-1}
\text{nm=\nm=1? :\nm}
\text{f1=\b>0?\an x^{\nm} \times \b:\an x^{\nm} \times (\b)}
\text{f2=texmath(\abnp*x^\n+\acn*x^\nm)}
\text{f3=texmath(\an*x^\nm*(\b*x+\c)+\ab*x^\n)}
\text{lstrep=\(f'(x)=\f1),\(f'(x)=\f2),\(f'(x)=\f3)}
\statement{
   Soit \(f) la fonction définie sue \(\RR) par:
<div class="wimscenter"> \(f(x)=\tf)</div>
   Cocher la ou les bonnes réponses&nbsp;:
<ul>
  <li>\embed{reply1,1}</li>
  <li>\embed{reply1,2}</li>
  <li>\embed{reply1,3}</li>
</ul>
}
\answer{}{2,3;\lstrep}{type=checkbox}{option=shuffle}
#else
\integer{n=randint(1..3)}
\integer{a=randint(1..6)*randint(1,-1)}
\integer{b=randint(1..6)*randint(1,-1)}

#if defined TARGET_derprodinv2
\title{TITRE 2}

\function{f=(\b+\a*x^\n)*sqrt(x)}
\text{tf=texmath(maxima(\f))}
#endif
#if defined TARGET_derprodinv3
\title{TITRE 3}
\text{ftrig=random(cos(x),sin(x))}
\function{f=(\b+\a*x^\n)*\ftrig}
\text{tf=texmath(maxima(\f))}
#endif
#if defined TARGET_derprodinv4
\title{TITRE 4}
\function{f=random((cos(x))^2,(sin(x))^2,(\a*x+\b)^2)}
\text{tf=texmath(maxima(\f))}
#endif
#if defined TARGET_derprodinv5
\title{TITRE 5}
\integer{k=randint(1..5)*randint(1,-1)}
\function{f=\k/(\a*x^\n+\b)}
\text{tf=\frac{\k}{texmath(maxima(\a*x^\n+\b))}}
#endif


\function{fp=diff(\f,x)}
\statement{
   Calculer \(f'(x)) pour \(f(x)=\tf)&nbsp;:
<div class="wimscenter"><label for="reply1">\(f'(x)=)</label>\embed{reply1}</div>
}
\answer{\(f'(x))}{\fp}{type=formal}
#endif
