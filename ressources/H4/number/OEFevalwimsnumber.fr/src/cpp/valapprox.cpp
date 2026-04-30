target=valapprox1 valapprox2 valapprox3 valapprox4 valapprox5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard; Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}

#if (defined TARGET_valapprox1 || defined TARGET_valapprox2 || defined TARGET_valapprox3 )
 \integer{a=randint(2,3,5,6,7,8,10,11,12,13,14)}
 \real{x=sqrt(\a)*100000}
 \integer{x=\x}
 \rational{x1=\x/10000}
 \rational{x2=\x1/100}
 \rational{x3=-\x1}
\text{xlist=(randint(1001..9999)*10+randint(1..9))/10000,randint(101..999)/10000,-(randint(1001..9999)*10+randint(1..9))/10000,randint(1001..9999)/1000}
\text{xlist=\x1,\x2,\x3}
\real{x=randitem(\xlist)}
\integer{p=randint(2,3)}
\real{y=\x*10^\p}

#if defined TARGET_valapprox1
 \title{Valeur décimale I}
\integer{val=\y}
\real{sol=\val/10^\p}
\text{typeval=la valeur décimale arrondie à \p décimales}
#endif
#if defined TARGET_valapprox2
 \title{Valeur décimale II}
\integer{k=randint(1,2)}
\text{approx=par excès, par défaut}
\integer{val=\k=1?ceil(\y):floor(\y)}
\real{sol=\val/10^\p}
\text{typeval=une valeur décimale approchée à \(10^{-\p}) près \approx[\k]}
#endif
#if defined TARGET_valapprox3
 \title{Valeur décimale III}
\text{ty=\y}
\text{ty=wims(replace internal . by , in \ty)}
\real{sol=\ty[1]/10^\p}
\text{typeval=la toncature à \p décimales}
#endif
\statement{
  Donner un nombre décimal qui soit \typeval de:
<div class="wimscenter">A=\x </div>
  <label for="reply1">Votre réponse</label>:
<div class="wimscenter">\embed{reply1,5}
</div>
}
\answer{}{\sol}{type=numeric}
#endif


#if (defined TARGET_valapprox4 || defined TARGET_valapprox5 )
\text{xlist=randint(10001..99999)/10000,randint(101..999)/10000,-randint(10001..99999)/10000,randint(1001..9999)/1000}
\real{x=randitem(\xlist)}
\integer{p=randint(2.,3)}
\real{y=\x*10^\p}

#if defined TARGET_valapprox4
 \title{Valeur décimale IV}
 \integer{a=randint(11..40)}
 \integer{b=randint(3,7,11,13)}
 \real{x=\a/ \b}
 \text{n=\frac{\a}{\b}}
#endif
#if defined TARGET_valapprox5
 \title{Valeur décimale V}
 \integer{a=randint(2,3,5,6,7,8,10,11,12,13,14)}
 \real{x=sqrt(\a)}
 \text{n=\sqrt{\a}}
#endif
\integer{p1=randint(2,3)}
\integer{p2=randint(2,3)}
\integer{p3=randint(2,3)}
\integer{k=randint(1,2)}
\text{approx=par excès, par défaut}
\text{typeapp=\approx[\k]}
%%% arrondi
\real{y=\x*10^\p1}
\integer{val=\y}
\real{ar=\val/10^\p1}
%%%% approché
\real{y=\x*10^\p2}
\integer{val=\k=1?ceil(\y):floor(\y)}
\real{ap=\val/10^\p2}
%%%% troncature
\real{y=\x*10^\p3}
\text{ty=\y}
\text{ty=wims(replace internal . by , in \ty)}
\real{tr=\ty[1]/10^\p3}

\statement{ On considère le nombre réel \(n=\n).
  A l'aide de la calculatrice, donner:
<ol>
<li>La <label for="reply1">valeur arrondie à \p1 décimales de \(n)</label>: \embed{reply1}</li>
<li>Une <label for="reply2">valeur approchée à \(10^{-\p2}) près \typeapp de \(n)</label>: \embed{reply2}</li>
<li>La <label for="reply3"></label>troncature à \p3 décimales de \(n)</label>: \embed{reply3}</li>
</ol>
}
\answer{arrondi}{\ar}{type=numeric}
\answer{\typeapp}{\ap}{type=numeric}
\answer{toncature}{\tr}{type=numeric}
#endif

#if defined TARGET_valapprox6
 \title{Valeur décimale 6}
 \integer{n=2}
 \text{typeval=à \(10^{-2}) par excès}
 \integer{a=randint(2..8)}
 \integer{b=\a+4}
 \text{x=\(\frac{\a+\pi}{\b})}
 \real{u=(\a+pi)/\b}
 \real{u=\u*100}
 \integer{sol=ceil(\u)}
 \real{sol=\sol/100}

#endif
#if defined TARGET_valapprox7
 \title{ Valeur décimale 7}
 \integer{n=3}
 \text{typeval=à \(10^{-3}) par défaut}
 \integer{k=randint(2..8)}
 \integer{b=randint(3..9)}
 \integer{a=10*\k}
 \text{x=\(\a \sqrt{\b^2+1})}
 \real{u=\a*sqrt(\b^2+1)}
 \real{u=\u*1000}
 \integer{sol=floor(\u)}
 \real{sol=\sol/1000}
#endif

#if defined TARGET_valapprox8
 \title{ Valeur décimale 8}
 \integer{n=2}
 \text{typeval=à \(10^{-2}) par défaut}
 \integer{k=randint(2..9)}
 \integer{m=randint(2..9)}
 \integer{p=randint(2..9)}
 \integer{b=randint(3..9)}
 \real{a=\k/10}
 \real{b=\m/10}
 \real{c=\p/10}
 \text{x=\(\frac{\a \times 10^3 - \b \times 10^4}{\c \times 10^5} )}
 \real{u=(\a*10^3-\b*10^4)/(\c*10^5)}
 \real{u=\u*100}
 \integer{sol=floor(\u)}
 \real{sol=\sol/100}
#endif

#if defined TARGET_valapprox9
 \title{ Valeur décimale 9}
 \integer{n=3}
 \text{typeval=par excès}
 \integer{a=randint(2..9)}
 \integer{b=randint(2..9)}
 \integer{c=randint(2..9)}
 \text{x=\(1+\frac{1}{4}+\frac{1}{\a^2}+\frac{1}{16}+\frac{1}{\b^2}+\frac{1}{36}+\frac{1}{\c^2}+\frac{1}{64}+\frac{1}{81}+\frac{1}{100})}
 \real{u=1+1/4+1/(\a^2)+1/16+1/(\b^2)+1/36+1/(\c^2)+1/64+1/81+1/100}
 \real{u=\u*1000}
 \integer{sol=ceil(\u)}
 \real{sol=\sol/1000}
#endif

#if defined TARGET_valapprox10
 \title{ Valeur décimale 10}
 \integer{n=4}
 \text{typeval=par défaut}
 \integer{a=randint(2..9)}
 \integer{b=randint(2..9)}
 \integer{c=randint(2..9)}
 \text{x=\(\frac{\pi}{\a}+\frac{\pi^2}{\b}+\frac{\pi^3}{\c})}
 \real{u=pi/\a+ (pi)^2/\b+ (pi)^3/\c}
 \real{u=\u*10000}
 \integer{sol=floor(\u)}
 \real{sol=\sol/10000}
#endif
