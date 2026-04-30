target=transfineg1 transfineg2 transfineg3 transfineg4 transfineg5
#define TITRE Transformation d'une inégalité
\author{Régine, Mangeard;Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
#if defined TARGET_transfineg1
\title{TITRE 1}
\integer{a=randint(-5..-1)}
\integer{k=randint(1..9)}
\integer{b=randint(3..9)}
\integer{c=randint(1..9)}
\text{eq1=\(texmath(\a*x+2*pi > 0)\)}
\text{eq2=\((t+1)(t^2+\k)<0\)}
\text{eq3=\((y+\b)(2-y)>0\)}
\text{eq4=\(x^2+2*\c*x-\c>0\)}
\text{lstrep=-2,-1,0,1,2}
\text{rep1=\a<-3?-2,-1,0,1:-2,-1,0,1,2}
\text{rep2=-2}
\text{rep3=-2,-1,0,1}
\text{rep4=1,2}
\text{size=60x40x5}
\statement{
  Pour chacune de ces inéquations et chacun de ces nombres, dites s'ils satisfont
  à l'inéquation&nbsp;:
<ul>
<li>\eq1 \embed{reply1,\size}</li>
<li>\eq2 \embed{reply2,\size}</li>
<li>\eq3 \embed{reply3,\size}</li>
<li>\eq4 \embed{reply4,\size}</li>
</ul>
}
\answer{inéquation 1}{\vrep1;\lstrep}{type=clickfill}
\answer{inéquation 2}{\vrep2;\lstrep}{type=clickfill}
\answer{inéquation 3}{\vrep3;\lstrep}{type=clickfill}
\answer{inéquation 4}{\vrep4;\lstrep}{type=clickfill}
\text{tmp1=\vrep1,\rep1}
\text{tmp1=wims(listuniq \tmp1)}
\text{vrep1=wims(listuniq \vrep1)}
\integer{ir1=items(\tmp1)}
\integer{it1=items(\vrep1)}
\integer{nb1=items(\rep1)}
\condition{Inéquation 1 }{\ir1=\nb1 and \it1=\nb1}
\text{tmp2=\vrep2,\rep2}
\text{tmp2=wims(listuniq \tmp2)}
\text{vrep2=wims(listuniq \vrep2)}
\integer{ir2=items(\tmp2)}
\integer{it2=items(\vrep2)}
\integer{nb2=items(\rep2)}
\condition{Inéquation 2 }{\ir2=\nb2 and \it2=\nb2}
\text{tmp3=\vrep3,\rep3}
\text{tmp3=wims(listuniq \tmp3)}
\text{vrep3=wims(listuniq \vrep3)}
\integer{ir3=items(\tmp3)}
\integer{it3=items(\vrep3)}
\integer{nb3=items(\rep3)}
\condition{Inéquation 3 }{\ir3=\nb3 and \it3=\nb3}
\text{tmp4=\vrep4,\rep4}
\text{tmp4=wims(listuniq \tmp4)}
\text{vrep4=wims(listuniq \vrep4)}
\integer{ir4=items(\tmp4)}
\integer{it4=items(\vrep4)}
\integer{nb4=items(\rep4)}
\condition{Inéquation 4 }{\ir4=\nb4 and \it4=\nb4}

#endif
#if defined TARGET_transfineg2
\title{TITRE 2}
\integer{a=randint(2..9)*randint(1,-1)}
\integer{b=randint(2..9)*randint(1,-1)}
\integer{b=\a=\b?-1*\a}
\integer{c=\a+\b}
\integer{d=\b-\a}
\text{equat=\(texmath(\a*x+\b <= \c*x+\d)\)}
\text{eq1g=\a-\b*x}
\text{eq2g=\b*x-\a}
\statement{
<ol>
<li>Transformez l'inéquation suivante en une inéquation équivalente,
  de manière à ce que votre résultat soit de la forme <span class="nowrap">\(A <= 0\).</span>
<div class="wimscenter"><label for="reply1">\equat équivaut à</label>
\embed{reply1,7}\(<=0)</div>
</li><li>
  Transformez à nouveau cette inéquation en une inéquation
  équivalente, de manière à ce que votre résultat soit de la forme <span class="nowrap">\(B >= 0\).</span>
<div class="wimscenter"><label for="reply2">\equat équivaut à </label>
\embed{reply2,7}\(>=0)</div></li>
</ol>
}
\answer{équation 1 gauche}{\eq1g}{type=algexp}
\answer{équation 2 gauche}{\eq2g}{type=algexp}
#endif
#if defined TARGET_transfineg3
\title{TITRE 3}
\integer{a=randint(-8..-2)}
\integer{b=randint(2..8)}
\integer{c=randint(2..8)}
\integer{ab=\a*\b}
\integer{ac=\a*\c}
\text{lstsymb=<,>,<=,>=}
\text{lstswap=>,<,>=,<=}
\integer{k=randint(1..4)}
\text{equat=\(texmath(\a*x+\ab \lstsymb[\k] \ac)\)}
\text{eq1g=x+\b}
\text{eq1d=\c}
\integer{rep2=position(\lstswap[\k],\lstsymb)}
\statement{
<div class="wimscenter">\equat</div><p>
  Transformez cette inéquation en une inéquation équivalente simplifiée.
</p>
<div class="wims_instruction">
 \(x\) n'apparait qu'une fois à gauche et son coefficient est 1.</div>
 <div class="wimscenter">\eq1g \embed{reply2} \embed{reply1,5}</div>

}
%%%%answer{membre de gauche}{\eq1g}{type=algexp}
\answer{membre de droite}{\eq1d}{type=algexp}
\answer{symbole}{\rep2;\lstsymb}{type=menu}
#endif

#if defined TARGET_transfineg4
\title{TITRE 4}
\integer{a=randint(2..9)}
\integer{b=randint(2..9)}
\integer{d=randint(2..9)}
\text{equat=\(texmath(\a/(x+\b) < \a/(x-\d))\)}
\text{equat2=\(texmath(\a*(x-\d) < \a*(x+\b))\)}
\integer{ad=\a*\d}
\integer{ab=\a*\b}
\text{equat3=\(texmath(\a*x-\ad < \a*x+\ab)\)}
\text{equat4=\(texmath(-\ad < \ab)\)}
\text{eq1d=1/(\a+1)}
\text{lstrep=C'est correct,C'est faux&#44; l'inégalité est fausse pour \(x = 0\),L'inégalité est fausse pour une infinité de valeurs,L'inégalité est vraie seulement pour \(x > 0\)}
\text{lstprenom=Caroline,Charlotte,Johanna,Kevin,Jacques,Pierre,Gaspard}
\integer{k=randint(1..7)}
\text{prenom=\lstprenom[\k]}
\text{sexe=\k<4?Elle:Il}
\text{rep=2,3}
\statement{
\prenom a cru résoudre cette inéquation&nbsp;:
<div class="wimscenter">\equat</div>
<ul>
<li>en la transformant en <span class="nowrap">\equat2 ;</span></li>
<li>c'est-à-dire <span class="nowrap">\equat3 ;</span></li>
<li>soit encore <span class="nowrap">\equat4 ;</span></li>
<li> qui est toujours vrai.</li>
</ul>
\sexe a donc conclu que la solution est l'ensemble des réels.

  Qu'en pensez-vous&nbsp;?
<div class="wims_instruction">Cocher la (ou les) bonne(s) réponse(s).</div>
<ul><li>\embed{reply1,1}.</li>
<li>\embed{reply1,2}.</li>
<li>\embed{reply1,3}.</li>
<li>\embed{reply1,4}.</li>
</ul>
}
\answer{Votre réponse}{\rep;\lstrep}{type=checkbox}
#endif
#if defined TARGET_transfineg5
\title{TITRE 5}
\integer{a=randint(2..9)}
\integer{b=randint(2..9)}
\integer{d=randint(2..9)}
\text{equat=\(texmath(\a/(x+\b) < \a/(x-\d))\)}
\text{equat2=\(texmath(\a*(x-\d) < \a*(x+\b))\)}
\integer{ad=\a*\d}
\integer{ab=\a*\b}
\text{equat3=\(texmath(\a*x-\ad < \a*x+\ab)\)}
\text{equat4=\(texmath(-\ad < \ab)\)}
\text{eq1d=1/(\a+1)}
\text{lstprenom=Caroline,Charlotte,Johanna,Kevin,Jacques,Pierre,Gaspard}
\integer{k=randint(1..7)}
\text{prenom=\lstprenom[\k]}
\text{sexe=\k<4?Elle:Il}
\text{sexe2=\k<4?elle:il}
\text{rep=2}
\text{lstrep=L'inégalité finale ne comportant pas \(x\)&#44; on ne peut pas conclure,Si on multiplie les deux membres par \((x-\d)\) ou par \((x+\b)\)&#44; on n'a pas une inégalité équivalente,Il y a une faute de signe dans le calcul quand \sexe2 a développé et réduit puis simplifié,Une inégalité n'est vraie que si \(x > 0\) }
\statement{
\prenom a cru résoudre cette inéquation&nbsp;:
<div class="wimscenter">\equat</div>
<ul><li>en la transformant en \equat2 </li>
<li>c'est-à-dire \equat3 </li>
<li>soit encore \equat4</li>
<li> qui est toujours vrai. </li>
</ul>
\sexe a donc conclu que la solution est l'ensemble des réels.

\sexe a commis une faute, laquelle&nbsp;?
<ul><li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
</ul>
}
\answer{Votre réponse}{\rep;\lstrep}{type=checkbox}
#endif
