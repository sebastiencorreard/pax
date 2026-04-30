target=notascient1 notascient2 notascient3 notascient4 notascient5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard; Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}


#if defined TARGET_notascient1
 \title{Notation scientifique I}
 \integer{p=randint(150000..750000)}
 \integer{a=randint(2..4)}
 \integer{b=10^\a}
 \integer{a2=\a-1}
 \real{c=\p/10^5}
 \real{c2=\p/10^\a}
 \text{data=\(\frac{\p}{\b}),\(\c \times 10^\a2),\(\p \times 10^{-\a}),\(\c2)}
\statement{
  Laquelle de ces écritures est l'écriture scientifique du nombre?
<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
</ul>
}
\answer{}{2;\data}{type=radio}{option=shuffle}
#endif

#if defined TARGET_notascient2
 \title{ Notation scientifique II}
 \integer{p=randint(21..89)}
 \integer{p=(\p isitemof(30,40,50,60,70,80))?\p+1}
 \real{p=\p /10}
 \integer{q=randint(3..6)}
 \integer{sol=\p*10^\q}
\statement{
  Écrire en écriture décimale le nombre affiché par la calculatrice comme:
<div class="wimscenter">\p E \q</div>
}
\answer{Solution}{\sol}{type=text}
#endif

#if defined TARGET_notascient3
 \title{ Notation scientifique III}
 \integer{k=randint(12..25)}
 \real{b=randint(0..49)/100}
 \real{c=randint(0..49)/100}
 \integer{a=random(0..9)}
 \integer{d=random(0..9-\a)}
 \real{p=\a+\b}
 \real{q=\d+\c}
 \real{sol=\p+\q}
 \text{sol=\sol*10^\k}
 \integer{k2=\k}
#endif

#if defined TARGET_notascient4
 \title{ Notation scientifique IV}
 \integer{k=randint(12..25)}
 \real{b=randint(0..49)/100}
 \real{c=randint(0..49)/100}
 \integer{a=random(1..9)}
 \integer{d=random(10-\a..9)}
 \real{p=\a+\b}
 \real{q=\d+\c}
 \real{sol=(\p+\q)/10}
 \integer{k2=\k+1}
 \text{sol=\sol*10^\k2}
 \integer{k2=\k}
#endif

#if defined TARGET_notascient5
 \title{ Notation scientifique V}
 \integer{k=randint(12..25)}
 \real{b=randint(0..49)/100}
 \real{c=randint(0..49)/100}
 \integer{a=random(1..9)}
 \integer{d=random(0..9-\a)}
 \real{p=\a+\b}
 \real{q=\d+\c}
 \real{sol=\p+\q/1000}
 \text{sol=\sol*10^\k}
 \integer{k2=\k-3}
#endif


#if ( defined TARGET_notascient3 || defined TARGET_notascient4 || defined TARGET_notascient5 )
\statement{
  Déterminer l'écriture scientifique de:
<div class="wimscenter"> \(\p \times 10^{\k} + \q \times 10^{\k2}).</div>
}
\answer{Écriture scientifique}{\sol}{type=text}
#endif
