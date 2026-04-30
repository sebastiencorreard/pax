target=exposant1 exposant2 exposant3 exposant4 exposant5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard; Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{10000}
#define TITRE Calcul avec des exposants
\text{infocalc=Calculatrice autorisée}
#if defined TARGET_exposant1
 \title{Calcul avec des exposants I}
\integer{a=randint(4..9)}
\integer{b=randint(3..5)}
\integer{a1=2^\a}
\integer{b1=10^\b}

\text{A=2^{\a}-10^{\b}\times u}
\text{taction=\(\text{Effectuer}\; \A) }
\text{sol=\a1-\b1*u}
\statement{
<div class="wims_warning">\infocalc</div>
<div class="wimscenter">\taction</div>
<div class="wimscenter"><label for="reply1">Votre solution</label>:\embed{reply1}
</div>
}
\answer{}{\sol}{type=formal}
#endif

#if defined TARGET_exposant2
 \title{TITRE II}
\text{infocalc=A faire sans calculatrice!}
\integer{a=randint(4..7)}
\integer{a1=\a-1}
\integer{a2=\a-2}
\text{A=(5^{\a}) \times 2^{\a1}+10^{\a2}}
\text{taction=\(\text{Effectuer}\; \A) }
\integer{sol=5^\a*2^\a1+10^\a2}
\statement{
<div class="wims_warning">\infocalc</div>
<div class="wimscenter">\taction</div>
<div class="wimscenter"><label for="reply1">Votre solution</label>:\embed{reply1}
</div>
}
\answer{}{\sol}{type=numeric}
#endif

#if defined TARGET_exposant3
 \title{TITRE III}
\text{infocalc=A faire sans calculatrice!}
\integer{a=randint(5..11)}
\integer{b=randint(2..5)}
\integer{b2=\b*4}
\integer{a1=-2*\a}
\text{A=(\b2^{\a}) \times 2^{\a1}}
\text{taction=\(\text{Effectuer}\; \A) }
\integer{sol=\b^(\a)}
\text{tsol=\(texmath(\b^\a))}
\statement{
<div class="wims_warning">\infocalc</div>
<div class="wimscenter">\taction</div>
<div class="wimscenter"><label for="reply1">Votre solution</label>:\embed{reply1,3}<sup>\embed{reply2,3}</sup>
</div>
}
\answer{}{\bb}{type=numeric}
\answer{}{\aa}{type=numeric}
\integer{rep=\reply1^\reply2}
\condition{\rep=\sol}
\feedback{\rep <>\sol}{Il fallait répondre \tsol}
#endif

#if defined TARGET_exposant4
 \title{TITRE IV}
\text{infocalc=A faire sans calculatrice!}
\integer{a=randint(2..7)}
\integer{b=randint(2..7)}
\integer{a1=\a+1}
\integer{b2=2*\b}
\text{A=\frac{(33^{\a}) \times (75^{\b})}{(11^{\a1})\times (21^{\b})}}
\text{taction=\(\text{Simplifier}\; \A) }
\text{sol=(3^\a*5^\b2)/(11*7^\b)}
\integer{rep1=\a}
\integer{rep2=\b2}
\integer{rep3=1}
\integer{rep4=\b}
\statement{
<div class="wims_warning">\infocalc</div>
<div class="wimscenter">\taction</div>
  Votre solution:
<table class="wimscenter wimsnoborder">
<tr style="border-bottom:solid 2px"><td>3<sup>\embed{reply1,3}</sup>\(\times)5<sup>\embed{reply2,3}</sup></td></tr>
<tr><td>11<sup>\embed{reply3,3}</sup>\(\times)7<sup>\embed{reply4,3}</sup></td></tr>
</table>

}
\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
\answer{}{\rep3}{type=numeric}
\answer{}{\rep4}{type=numeric}

#endif

#if defined TARGET_exposant5
 \title{TITRE V}
\text{infocalc=A faire sans calculatrice!}
\integer{a=randint(2..7)}
\integer{b=randint(2..7)}
\integer{a2=2*\a}
\integer{b2=2*\b-1}
\integer{b3=2*\b}
\text{A=\frac{((8^{\a}) \times (21^{\b} \times x))^2}{(16^{\a})\times 7 \times (x^{3})}}
\text{taction=\(\text{Simplifier}\; \A) }
\text{sol=2^(\a2)*7^(\b2)*3^(\b3)/x}
\integer{rep1=\a2}
\integer{rep2=\b3}
\integer{rep3=\b2}
\integer{rep4=-1}
\statement{
<div class="wims_warning">\infocalc</div>
<div class="wimscenter">\taction</div>
<div class="wimscenter">Votre solution:<label for="reply1">2</label><sup>\embed{reply1,3}</sup>
\(\times) <label for="reply2">3</label><sup>\embed{reply2,3}</sup>\(\times)
<label for="reply3">7</label><sup>\embed{reply3,3}</sup>
<label for="reply4">\(\times x)</label><sup>\embed{reply4,3}</sup>
</div>
}
\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
\answer{}{\rep3}{type=numeric}
\answer{}{\rep4}{type=numeric}
#endif
