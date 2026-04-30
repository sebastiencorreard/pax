target=interpret1 interpret2 interpret3 interpret4 interpret5

\author{Régine, Mangeard; Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
\precision{10000}
\range{-5..5}
\computeanswer{yes}
\format{html}

#if defined TARGET_interpret1
\title{Interpréter un résultat 1}
\integer{a=random(2,3,5,6,7,8,10,11,12,13,14)}
\real{x=sqrt(\a)}
\real{xm=\x-10^-7}
\integer{cinq=5}
\text{b1=\xm\cinq}
\text{b2=\x\cinq}
\text{lstrep=\(\sqrt{\a}) = \x, \(\sqrt{\a} \ge \x), \(\sqrt{\a} \le \x),\(\b1 \le \sqrt{\a} < \b2),\(\b1 < \sqrt{\a} \le \b2) }
\statement{
  Je tape sur ma calculatrice \(\sqrt{\a}) et la calculatrice m'affiche le nombre \x.
<p>
  Que puis-je en déduire?
</p>
<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
<li>\embed{reply1,5}</li>
</ul>
}
\answer{Déduction}{4;\lstrep}{type=radio}{option=shuffle}
#endif

#if defined TARGET_interpret2
\title{Interpréter un résultat 2}
\integer{d=randint(3..9)}
\integer{p=randint(1,2)*10000+randint(1..999)*10+\d}
\text{b=wims(text copy \p mask 01000)}
\integer{p=\b=\d?\p+1000}
\integer{b=\b=\d?\b+1}
integer{d=6}
integer{p=123456}
\real{q=floor(\p^2/10)}
\real{r=\q/10^5}
\text{r=\r}
\text{r=wims(replace internal . by in \r)0}
\real{q=\q/10^7}
\integer{bc=\b^2}
\integer{dc=\d^2}
\integer{d2=\d*2}
\integer{c=\dc<10?\dc:\dc-floor(\dc/10)*10}
\integer{e=\d2-floor(\d2/10)*10}
\integer{a=\bc-floor(\bc/100)*100}
\integer{a=\bc<10?\bc:floor(\a/10)}
\text{lstrep=Le résultat est certainement exact&#44; vu le prix de la calculatrice,
  Le second chiffre devrait être un \a &#44; car \(\b^2 = \bc),
  Le dernier chiffre devrait être un \c &#44; car \(\d \times \d = \dc),
  Le dernier chiffre devrait être un \e &#44; car \(\d \times 2 = \d2)}
\statement{
  Je tape sur ma calculatrice \p^2 et la réponse est :
<div class="wimscenter">\q E8,</div>
  ce qui signifie
<div class="wimscenter">\r</div>
  Que penser de ce résultat?
<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
</ul>
}
\answer{Expilcation}{3;\lstrep}{type=radio}{option=shuffle}
#endif


#if defined TARGET_interpret3
\title{Interpréter un résultat 3}
\integer{a=randint(10000000..99999999)}
\integer{b=randint(10000000..99999999)}
\integer{b=\a=\b?\a-1}
\integer{c=randint(123..999)}
\integer{ap=\a*\c+1}
\integer{bp=\b*\c+1}
\text{lstrep=\(A=B),
  En faisant la soustraction&#44; je peux faire apparaitre les décimales cachées. Si la calculatrice affiche 0 c'est que \(A=B),
  Pour être absolument certain&#44; je peux comparer le chiffre des unités de \(a \times b') avec celui de \(a' \times b) et si c'est le même alors \(A=B),
  Si les tests 2 ou 3 échouent&#44; c'est que \(A) est différent de \(B)}
\statement{
  On souhaite comparer \(A=\frac{a}{b}= \frac{\a}{\b}) et \(B=\frac{a'}{b'}=\frac{\a \times \c+1}{\b \times \c + 1}).<p>
  La calculatrice affiche les mêmes chiffres.
</p>
  Quelles affirmations sont certainement vraies ?
<ol>
<li> \embed{reply1,1}</li>
<li> \embed{reply1,2}</li>
<li> \embed{reply1,3}</li>
<li> \embed{reply1,4}</li>
</ol>
}
\answer{bonnes affirmations}{4;\lstrep}{type=checkbox}
#endif

#if defined TARGET_interpret4
\title{Interpréter un résultat 4}
\integer{p=randint(15..19)}
\integer{p2=2*\p}
\integer{a=randint(1,2,3)}
\integer{a2=\a^2}
\text{form=\a=1?\(\frac{(1+10^{-\p})^2-1}{10^{-\p2}}):\(\frac{(1+\a\times 10^{-\p})^2-1}{\a2\times 10^{-\p2}})}
\text{form2=\a=1?\(\frac{(1+x)^2-1}{x^2}):\(\frac{(1+\a x)^2-1}{\a2 x^2})}
\integer{p2=2*\p}
\text{exp=1+2*\a/(\a2*x)}
\real{val=1+2*10^\p}
\real{rep1=0}
\text{rep2=\exp}
\text{rep3l=2,1,7}
\integer{rep3=\rep3l[\a]}
\integer{rep4=\a=3?\p-1:\p}
\statement{
  Lorsqu'on évalue l'expression \(A)=\form à la calculatrice, on obtient 0!
<ol>
<li> <label for="reply1">Simplifier \form2</label>
=\embed{reply1,10}</li>
<li> Puis donner l'ordre de grandeur \(A) en remplaçant \(x) par \(10^{-\p}) dans l'expression précédente:<br>
<div class="wimscenter">\(A)=\embed{reply2,2}10<sup>\embed{reply3,3}</sup></div></li>
<li> Pouvait-on faire confiance au résultat affiché par la calculatrice? \embed{reply4}</li>
</ol>
}
\answer{expression simplifiée}{\rep2}{type=formal}
\answer{matice}{\rep3}{type=numeric}
\answer{exposant}{\rep4}{type=numeric}
\answer{Confiance}{2;Oui,Non}{type=radio}
#endif
#if defined TARGET_interpret5
\title{Interpréter un résultat 5}
\integer{a=randint(31..39)}
\integer{b=randint(21..29)}
\integer{a=3*\b-2*\a=0?\a+1}
\integer{d=3*\b-2*\a}
\integer{c=-4*\b+3*\a}
\function{exp=\c-\d*sqrt(2)}
\real{val=(\a-\b*sqrt(2))/(3-2*sqrt(2))-\c+\d*sqrt(2)}
\text{s1=\c>0?-:+}
\text{s2=\d>0?+:-}
\integer{c=\c<0?-\c}
\integer{d=\d<0?-\d}
\real{rep1=\val}
\function{rep2=\exp}
\real{rep3=0}
\statement{
  Lorsqu'on évalue \(A)=\(\frac{\a-\b\sqrt{2}}{3-2\sqrt{2}}\s1\c \s2 \d\sqrt{2}) à la calculatrice,<br>
  on obtient \(A)=\rep1.
<p>
  Que faut-il en penser?
</p>
<ol>
<li> Simplifier \(\frac{\a-\b\sqrt{2}}{3-2\sqrt{2}})=\embed{reply1,10}<br>
<i> Taper "sqrt(2)" pour \(\sqrt{2})</i></li>
<li> En déduire la valeur exacte de \(A):
\(A)=\embed{reply2,10}</li>
<li> Pouvait-on faire confiance au résultat affiché par la calculatrice? \embed{reply3}</li>
</ol>
}
\answer{expression simplifiée}{\rep2}{type=formal}
\answer{Valeur exacte}{\rep3}{type=numeric}
\answer{Confiance}{2;Oui,Non}{type=radio}
#endif

#if defined TARGET_interpret6
\title{Interpréter un résultat 6}
\text{lstquest=30,45,60,90,120,135,150,180,210,225,240,270}
\integer{p=randitem(\lstquest)}
\real{q=sin(\p)}
\real{t=sin(\p*pi/180)}
\text{lstrep=Le résultat est certainement exact&#44; c'est ma mémoire qui flanche,
  La calculatrice est en mode degré&#44; et elle devrait être en mode radian,
  La calculatrice est en mode radian&#44; et elle devrait être en mode degré,
  Les touches fonctionnent sans doute mal}
\statement{
  Je tape sur ma calculatrice \(\sin{(\p)}) et je trouve \q.<p>
  Je m'attendais plutôt à trouver \t.
</p><p>
  Quelle est la bonne explication:
</p>
<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
</ul>
}
\answer{Expilcation}{3;\lstrep}{type=radio}{option=shuffle}
#endif
