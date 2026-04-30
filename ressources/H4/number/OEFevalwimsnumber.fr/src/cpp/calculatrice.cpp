target=calculatrice1 calculatrice2 calculatrice3 calculatrice4 calculatrice5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard; Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Utilisation de la calculatrice
#if defined TARGET_calculatrice5
\title{TITRE 5}
\text{size=80x300x200}
\integer{a=randint(5..20)}
\integer{b=randint(5..20)}
\integer{c=randint(5..20)}
\integer{d=randint(5..20)}
\integer{k=randint(5..20)}
\text{lstexp=\(-\a^2\times \b - \frac{\k}{(-\c)^3 + \d}),
\(\frac{-\a^2\times \b - \k}{(-\c)^3 + \d}),
\((-\a^2)\times \frac{\b}{(-\c)^3 + \d}- \k),
\((\frac{\a}{(-\c)^3})\times \b - \frac{\k}{\d})}
\real{c1=-\a^2* \b - \k/((-\c)^3 + \d)}
\real{c2=(-\a^2*\b - \k)/((-\c)^3 + \d)}
\real{c3=(-\a^2)* \b/((-\c)^3 + \d)- \k}
\real{c4=(\a/(-\c)^3)* \b - \k/\d}
\text{lstres=\c1,\c2,\c3,\c4}

\statement{
  Associer calculs et résultats:
  <div>\embed{reply1,\size}</div>
}
\answer{Correspondance}{\lstexp;\lstres}{type=correspond}
#else

#if (defined TARGET_calculatrice1 || defined TARGET_calculatrice2 )

#if defined TARGET_calculatrice1
 \title{TITRE 1}
\integer{a=randint(11..19)}
\integer{b=randint(11..19)}
\integer{c=randint(11..19)}
\integer{n=2}
\real{u=100*((\a*\b)^2-sqrt(\a))/(1+sqrt(\c))}
\text{A=\(\frac{(\a\times \b)^2 - \sqrt{\a}}{1+\sqrt{\c}})}
\integer{v=ceil(\u)}
\real{sol=\v/100}
#endif

#if defined TARGET_calculatrice2
 \title{TITRE 2}
\integer{a=randint(7..19)}
\integer{b=randint(7..19)}
\integer{c=randint(7..19)}
\integer{n=4}
\real{u=10000*((\a/\b)^2+sqrt(\a+\b))/(1/\b+1/(\c)^2)}
\text{A=\(\frac{(\frac{\a}{\b})^2 + \sqrt{\a+\b}}{\frac{1}{\b}+\frac{1}{\c^2}})}
\integer{v=ceil(\u)}
\real{sol=\v/10000}
#endif
\statement{
  Donner à l'aide de votre calculatrice, la valeur approchée à
 \n décimales par excès de:
<div class="wimscenter"><label for="reply1">\A</label></div>
<div class="wimscenter">\embed{reply1}</div>
}
#endif


#if (defined TARGET_calculatrice3 || defined TARGET_calculatrice4 )
#if defined TARGET_calculatrice3
 \title{TITRE 3}
\integer{n=4}
\text{typear=excès}
\integer{a=randint(3..8)}
\integer{b=randint(3..8)}
\integer{c=randint(3..8)}
\integer{d=random(7,8,10,11,12,13,14,15,17,19)}
\text{data=\(A=\a x^2+ \b x +\c)}
\text{quest=\(1+\sqrt{\d})}
\text{q=A}
\function{A=\a*(x)^2+\b*(x)+\c}
\real{u=evalue(\A,x=1+sqrt(\d))}
\integer{v=ceil(\u*10000)}
\real{sol=\v/10000}
#endif
#if defined TARGET_calculatrice4
 \title{TITRE 4}
\integer{n=3}
\text{typear=defaut}
\text{quest=\(\pi -4)}
\integer{a=randint(3..8)}
\integer{b=randint(3..8)}
\integer{c=randint(3..8)}
\text{data=\(B=\a x - \frac{\b}{x^2}+ \c)}
\text{q=B}
\function{B=\a*(x)-\b/(x)^2+\c}
\real{u=evalue(\B,x=pi -4)}
\integer{v=floor(\u*1000)}
\real{sol=\v/1000}
#endif
\statement{
  Soit \data;<p>
  A l'aide de la calculatrice, calculer \q en remplaçant \(x) par \quest et donner
  sa <label for="reply1">valeur approchée</label> par \typear à \n décimales.
</p>
<div class="wimscenter">\embed{reply1}</div>
}
#endif
\answer{}{\sol}{type=numeric}
#endif
