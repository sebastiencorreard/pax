target=fderref1 fderref2 fderref3 fderref4 fderref5
\author{Maguy, Bruno ; Régine, Mangeard}
\email{regine@mangeard.Fr}
\format{html}
\precision{100}
\computeanswer{yes}
#define TITRE Dérivée de fonction de référence
\text{typev=numexp}
\integer{a=randint(-5..5)}
\text{ta=\a}
#if defined TARGET_fderref1
\title{TITRE 1}
\function{f=x^2}
\text{tf=texmath(\f)}
\function{fp=diff(\f,x)}
\rational{nder=evalue(\fp,x=\a)}
#endif
#if defined TARGET_fderref2
\title{TITRE 2}
\function{f=x^3}
\text{tf=texmath(\f)}
\function{fp=diff(\f,x)}
\rational{nder=evalue(\fp,x=\a)}
#endif
#if defined TARGET_fderref3
\title{TITRE 3}
\function{f=sqrt(x)}
\text{tf=texmath(\f)}
\integer{a=randint(1..10)}
\text{ta=\a}
\text{typev=numeric}
\function{fp=diff(\f,x)}
\real{nder=evalue(\fp,x=\a)}
#endif
#if defined TARGET_fderref4
\title{TITRE 4}
\function{f=1/x}
\text{tf=\frac{1}{x}}
\integer{a=randint(1..5)*randint(1,-1)}
\text{ta=\a}
\function{fp=diff(\f,x)}
\rational{nder=evalue(\fp,x=\a)}
#endif
#if defined TARGET_fderref5
\title{TITRE 5}
\text{al=0,pi/6,pi/4,pi/3,pi/2,pi}
\text{tal=0,\frac{\pi}{6},\frac{\pi}{4},\frac{\pi}{3},\frac{\pi}{2},\pi}
\integer{i=randint(1..6)}
\real{a=\al[\i]}
\text{ta=\tal[\i]}
\function{f=random(cos(x),sin(x))}
\text{tf=texmath(\f)}
\text{typev=numeric}
\function{fp=diff(\f,x)}
\real{nder=evalue(\fp,x=\a)}
#endif
\statement{
   Calculer \(f'(a)) pour \(f(x)=\tf) et \(a=\ta)&nbsp;:
<div class="wimscenter"><label for="reply1">\(f'(a)=)</label>\embed{reply1,8}</div>
<div class="wims_instruction">Taper "sqrt(a)" pour \(\sqrt{a}).</div>
}
\answer{\(f'(a))}{\nder}{type=\typev}
