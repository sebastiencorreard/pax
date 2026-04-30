target=solveineq1 solveineq2 solveineq3 solveineq4 solveineq5
#define TITRE Résoudre une inéquation
\author{Régine, Mangeard;Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
#if defined TARGET_solveineq1
\title{TITRE 1}
\integer{a=randint(-9..-2)}
\integer{b=randint(2..9)}
\text{lstsymb=<,>,<=,>=}
\text{swapsymb=>,<,>=,<=}
\integer{k=randint(1..4)}
\text{equat=\(texmath(\a*x(x^2+\b) \lstsymb[\k] 0)\)}
\text{lstrep=\(x >= \a\) ,\(x = 0\) ,Pas de solutions,\(x \swapsymb[\k] 0\), \(x \lstsymb[\k] 0\),\(\a <= x <= \b\)}
\integer{rep=4}
\statement{
  Parmi les choix proposés, lequel correspond à la résolution de l'inéquation&nbsp;:
<div class="wimscenter"> \equat</div>
<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
<li>\embed{reply1,5}</li>
<li>\embed{reply1,6}</li>
</ul>
}
\answer{Votre réponse}{\rep;\lstrep}{type=radio}
#endif
#if defined TARGET_solveineq2
\title{TITRE 2}
\real{a=randint(1..20)*random(1,-1)/10}
\real{b=randint(1..20)*random(1,-1)/10}
\real{d=randint(1..20)*random(1,-1)/10}
\real{d=\b=\d?-1*\b}
\real{c=random(\a+0.5,\a-0.5)}
\text{lstsymb=<,>,<=,>=}
\integer{rep1=\c>\a?4:3}

\text{equat=\(texmath(\a*x+\b <= \c*x+ \d)\)}
\text{lstcroc=&#91;,&#93;}
integer{rep1=1}
integer{rep4=1}
\real{rep2=\c<\a?2*(\d-\b):2*(\b-\d)}
text{rep3=+inf}
\statement{
  Résoudre l'inéquation :
<div class="wimscenter"> \equat</div>
<div class="wimscenter"><label for="reply2">\(x\)</label>\embed{reply1}\embed{reply2,4}</div>
}
\answer{symbole}{\rep1;\lstsymb}{type=menu}
\answer{valeur}{\rep2}
#endif
#if defined TARGET_solveineq3
\title{TITRE 3}
\integer{a=randint(10..15)}
\integer{b=randint(2,3,5,6,7,8)}
\real{u=floor(sqrt(\a)*100)/100}
\real{v=ceil(sqrt(\a)*100)/100}
\real{r=floor(sqrt(\b)*100)/100}
\real{s=ceil(sqrt(\b)*100)/100}
\real{ur=\u*\r}
\real{vs=\v*\s}

\statement{
<b>Multiplier deux inégalités</b>&nbsp;:<p>
  On a \(\u < sqrt(\a) < \v\)<br>
  et
\(\r < sqrt(\b) < \s\)</p>
  Déduisez-en un encadrement de <span class="nowrap">\(\sqrt{\a} \times \sqrt{\b}\).</span>
<div class="wimscenter">\embed{reply1,3} \(< \sqrt{\a} \times \sqrt{\b} <\) \embed{reply2,3}</div>
}
\answer{borne gauche}{\ur}{type=numeric}
\answer{borne gauche}{\vs}{type=numeric}
#endif
#if defined TARGET_solveineq4
\title{TITRE 4}
\text{mstep=r1,r2}
\text{cond=1 2}
\nextstep{\mstep}
\statement{
  On a : \(a <= b\) et <span class="nowrap">\(c <= d\).</span>
<ul><li>Est-il vrai en général que \(a + c <= b + d\) ? \embed{reply1}</li>
<li>Est-il vrai en général que \(a - c <= b - d \) ? \embed{reply2}</li>
</ul>
\if{\step=2 and \reply2 issametext Oui}
 {
  Non, on n'a pas toujours \(a - c <= b - d\).<br>
  Donnez un exemple numérique simple où \(a <= b\) et \(c <= d\),
  alors que <span class="nowrap">\(a - c >= b - d\) :</span>
<ul>
<li><label for="reply3">a=</label>\embed{reply3,3}</li>
<li><label for="reply4">b=</label>\embed{reply4,3}</li>
<li><label for="reply5">c=</label>\embed{reply5,3}</li>
<li><label for="reply6">d=</label>\embed{reply6,3}</li>
</ul>
 }
}
\answer{addition}{1;Oui,Non}{type=radio}{weight=5}
\answer{soustraction}{\rep;Oui,Non}{type=radio}
\answer{a}{\ra}{type=numeric}
\answer{b}{\rb}{type=numeric}
\answer{c}{\rc}{type=numeric}
\answer{d}{\rd}{type=numeric}
\if{\step=2}
{
\if{\reply2 issametext Oui}
 {
 \text{mstep=r3,r4,r5,r6}
 \text{cond=1 2}
 }
 {\text{cond=2}
 \text{mstep=}
 }
}{
 \text{mstep=}
 }
\conditions{\cond}
\condition{exemples}{(\reply3 <= \reply4) and (\reply5 <= \reply6) and (\reply3 -\reply5) >= (\reply4 -\reply6)}{weight=2}
\condition{soustraction}{\reply2 issametext Non}{weight=3}
#endif
#if defined TARGET_solveineq5
\title{TITRE 5}
\integer{a=randint(10..15)}
\integer{b=randint(2,3,5,6,7,8)}
\real{u=floor(sqrt(\a)*100)/100}
\real{v=ceil(sqrt(\a)*100)/100}
\real{r=floor(sqrt(\b)*100)/100}
\real{s=ceil(sqrt(\b)*100)/100}
\real{us=\u-\s}
\real{vr=\v-\r}
\statement{
<b>Soustraire deux inégalités</b>&nbsp;:<p>
  On a \(\u < sqrt(\a) < \v\)<br>
  et
\(\r < sqrt(\b) < \s\)</p>
  Déduisez-en un encadrement de <span class="nowrap">\(sqrt(\a) - sqrt(\b)\).</span>
<div class="wimscenter">\embed{reply1,3} \(< \sqrt{\a} - \sqrt{\b} <\) \embed{reply2,3}</div>
}
\answer{borne gauche}{\us}{type=numeric}
\answer{borne gauche}{\vr}{type=numeric}
#endif
