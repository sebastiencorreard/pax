target=radical1 radical2 radical3 radical4 radical5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard; Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}

\text{infocalc=A faire sans calculatrice!}

#if defined TARGET_radical1
 \title{Calcul avec des radicaux I}
\integer{a=randint(3..8)}
\integer{a2=\a^2}
\integer{b=random(2,3,5,6,7,8)}
\text{data=\(\sqrt{\a2}=\a\; ou\; -\a),2
\(\sqrt{-x}) existe si \(x \le 0),1
  Si \(x>0)&#44; \(\sqrt{1+x^2}=1+x),2
  Racine carrée de 0 n'existe pas,2
\(\sqrt{\frac{1}{\a}}=\frac{\sqrt{\a}}{\a}),1}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{
<div class="wims_warning">\infocalc</div>
  Cocher la bonne réponse :
<div class="wimscenter">\quest</div>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\rep ;Vrai,Faux}{type=checkbox}
#endif

#if defined TARGET_radical2
 \title{ Calcul avec des radicaux II}
\integer{p=random(2,3,5,7)}
\integer{u=randint(3..7)}
\integer{v=\u+1}
\integer{u2=\u^2*\p}
\integer{v2=\v^2*\p}
\text{rep=(\u+\v)*sqrt(\p)}
\statement{
<div class="wims_warning">\infocalc</div>
  Écrire sous la forme \(a \sqrt{b}), \(a) et \(b) entiers, \(a) le plus grand possible :
<div class="wimscenter"><label for="reply1">\(\sqrt{\u2}+\sqrt{\v2})</label></div>
<div class="wims_instruction">
 Pour saisir une racine carrée, taper <span class="tt">sqrt(..)</span>,
  exemple taper <span class="tt">sqrt(2)</span> pour \(\sqrt{2})
</div>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\rep}{type=formal}
#endif

#if defined TARGET_radical3
 \title{ Calcul avec des radicaux III}
\integer{k=randint(3..9)}
\integer{m=randint(11..19)}
\real{a=\k^2 / 100}
\real{b=\m^2 / 100}
\real{rep=(\k+\m)/10}
\statement{
<div class="wims_warning">\infocalc</div>
  Calculer :
 <div class="wimscenter"><label for="reply1">\(\sqrt{\a}+\sqrt{\b})</label></div>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\rep}{type=formal}
#endif

#if defined TARGET_radical4
 \title{ Calcul avec des radicaux IV}
\integer{a=randint(2..9)}
\integer{b=randint(3..8)}
\integer{b2=\b^2}
\integer{c= randint(3..8)}
\text{rep=(\a*\b-\c)*x}
\statement{
<div class="wims_warning">\infocalc</div>
  Sachant que \(x \ge 0), calculer :
 <div class="wimscenter"><label for="reply1">\(\a\times \sqrt{\b2 \times x^2}-\c x)</label></div>
<div class="wimscenter">\embed{reply1,5}</div>
}
\answer{}{\rep}{type=formal}
#endif

#if defined TARGET_radical5
 \title{ Calcul avec des radicaux V}
\integer{a=randint(1..7)}
\integer{b=random(5,6,7,8,10,11,13)}
\integer{c=\b-2}
\text{rep=\a*(sqrt(\b)+sqrt(\c))/2}
\statement{
<div class="wims_warning">\infocalc</div>
  Rendre rationnel le dénominateur de :
 <div class="wimscenter">\(\frac{\a}{\sqrt{\b}-\sqrt{\c}})</div>
<em>C'est-à-dire écrire ce nombre sous la forme d'une fraction ne contenant
pas de racine carrée au dénominateur.</em>
<div class="wims_instruction">
Pour saisir une racine carrée, taper <span class="tt">sqrt(..)</span>,
exemple taper <span class="tt">sqrt(2)</span>
pour \(\sqrt{2}).</div>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\rep}{type=formal}
\hint{Regardez ces trois exemples:
<ol>
<li> \(\frac{1}{\sqrt{2}}=\frac{1 \times \sqrt{2}}{\sqrt{2} \times \sqrt{2}}=\frac{\sqrt{2}}{2})</li>
<li> \(\frac{1}{1+\sqrt{2}}=\frac{1 \times (1 - \sqrt{2})}{(1+\sqrt{2})\times(1-\sqrt{2})}=\frac{1-\sqrt{2}}{1-2}=\sqrt{2}-1)</li>
<li> \(\frac{1}{\sqrt{5}-\sqrt{2}}=\frac{1 \times (\sqrt{5}+\sqrt{2})}{(\sqrt{5}-\sqrt{2})\times (\sqrt{5}+\sqrt{2})}=\frac{\sqrt{5}+\sqrt{2}}{5-2}=\frac{\sqrt{5}+\sqrt{2}}{3})</li>
</ol>}
#endif
