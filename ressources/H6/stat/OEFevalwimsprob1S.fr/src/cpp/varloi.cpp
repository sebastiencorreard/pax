target=varloi1 varloi2 varloi3 varloi4 varloi5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\computeanswer(yes)
\text{consigne=Donner les valeurs exactes.}

#if defined TARGET_varloi1
\title{Variable aléatoire, loi de probabilité 1}
\integer{a=randint(3..5)}
\integer{b=\a+randint(2..4)}
\integer{c=\b+randint(3..5)}
\rational{p1=(\a/\c)^2}
\rational{p2=(\b/\c)^2-\p1}
\rational{p3=1-\p1-\p2}
\rational{pg1=\p3}
\rational{pg2=\p2}
\rational{pg3=\p1}
\statement{<p>
On considère une cible comportant 3 cercles concentriques de rayon \a cm,
 \b cm et \c cm. </p>
On suppose que toutes les flèches lancées atteignent la cible,
et que la probabilité d'atteindre une zone de la cible est proportionnelle à l'aire
de cette zone.
<div class="wims_question">
Déterminer la probabilité de lancer la flèche à l'intérieur
du cercle de rayon \a cm (zone 1),
 entre les cercles de rayon \a cm et \b cm (zone 2),
 entre les cercles de rayon \b cm et \c cm (zone 3).
 <ul>
<li> <label for="reply1">probabilité de lancer la flèche dans la zone 1 :</label> \embed{reply1,5}</li>
<li> <label for="reply2">probabilité de lancer la flèche dans la zone 2 :</label> \embed{reply2,5}</li>
<li> <label for="reply3">probabilité de lancer la flèche dans la zone 3 :</label> \embed{reply3,5}</li>
</ul>
</div>
On considère la variable aléatoire \(G\) associée au gain de ce jeu,
 pour lequel le gain est de 10 euros lorsqu'on atteint la zone 1,
 de 3 euros lorsqu'on atteint la zone 2 et
 de 1 euro lorsqu'on atteint la zone 3.
<div class="wims_question">
Déterminer la loi de probabilité de \(G\).
<table class="wimsborder wimscenter">
<tr><td>\(g\)</td><td>1 euro</td><td> 3 euros </td><td> 10 euros</td></tr>
<tr><td>\(P(G=g)\)</td><td>\embed{reply4,5}</td><td>\embed{reply5,5}</td><td>\embed{reply6,5}</td></tr>
</table>
</div>
<div class="wims_instruction">\consigne</div>
}
\answer{Dans la zone 1}{\p1}{type=numexp}{option=noreduction}
\answer{Dans la zone 2}{\p2}{type=numexp}{option=noreduction}
\answer{Dans la zone 3}{\p3}{type=numexp}{option=noreduction}
\answer{\(P(G=1)\)}{\pg1}{type=numexp}{option=noreduction}
\answer{\(P(G=3)\)}{\pg2}{type=numexp}{option=noreduction}
\answer{\(P(G=10)\)}{\pg3}{type=numexp}{option=noreduction}
#endif

#if defined TARGET_varloi2
\title{Variable aléatoire, loi de probabilité 2}
\integer{n=randint(4..5)}
\text{val=}
\text{pval=}
\for{i=1 to \n}
 {
 \integer{s=4*\i-2*(\n-\i)}
 \integer{s=\s<0?0}
 \text{val=wims(append item \s to \val)}
 \integer{pv=binomial(\n,\i)}
 \text{pval=wims(append item \pv to \pval)}

 }
\text{xval=wims(listuniq \val)}
\integer{nbx=items(\xval)}
\text{p=}
\for{i=1 to \nbx}
 {
 \text{pos=position(\xval[\i],\val)}
 \rational{px=\xval[\i]=0?1/2^\n:0}
 \for{l in \pos}{
  \rational{px=\px+\pval[\l]/2^\n}
  }
 \text{p=wims(append item \px to \p)}
 }
\text{mstep=wims(makelist r x for x= 4 to \nbx+3)}
\text{mstep=wims(nospace \mstep)}
\steps{r1,r2,r3,\mstep}
\rational{esp=0}
\rational{var=0}
\for{i=1 to \nbx}
 {
   \rational{esp=\esp+\xval[\i]*\p[\i]}
   \rational{var=\var+\xval[\i]^2*\p[\i]}
 }
\rational{var=\var-(\esp)^2}
\real{sig=round(100*sqrt(\var))/100}
\statement{<p>
Un test est composé de \n questions auxquelles on doit répondre
 par Vrai ou Faux. </p><p>
On coche au hasard les réponses aux \n questions posées.</p>

Le barème est le suivant :
<ul>
<li> 4 points par réponse exacte.</li>
<li> -2 points pour une réponse inexacte.</li>
</ul>
 La note finale est le plus grand des deux nombres entre 0 et
 la somme des points obtenus.
<div class="wims_question">
Déterminer la loi de probabilité de la variable aléatoire \(N\),
 définie par la note d'un candidat ayant répondu au hasard.
<table class="wimsborder wimscenter">
<tr><td> \(n\) </td>
\for{j=4 to \nbx+3}
{
<td>\xval[\j-3]</td>
}
</tr><tr><td>\(P(N=n)\)</td>
\for{j=4 to \nbx+3}
{
<td>\embed{reply\j,4}</td>
}
</tr></table>
Calculer l'espérance mathématique, la variance et l'écart type de \(N\).
<table class="wimscenter">
<tr><td> Espérance = </td><td> \embed{reply1,7}</td><td><i> sous forme de fraction</i></td></tr>
<tr><td> Variance = </td><td> \embed{reply2,7}</td><td><i> sous forme de fraction</i></td></tr>
<tr><td> Ecart type = </td><td> \embed{reply3,7} </td><td><i> arrondi au centième</i></td></tr>
</table>
</div>
}
\answer{Espérance}{\esp}{type=numexp}{option=noreduction}
\answer{Variance}{\var}{type=numexp}{option=noreduction}
\answer{Ecart type}{\sig}{type=numeric}
\answer{\(P(N=\xval[1])\)}{\p[1]}{\type=numexp}{option=noreduction}
\answer{\(P(N=\xval[2])\)}{\p[2]}{\type=numexp}{option=noreduction}
\answer{\(P(N=\xval[3])\)}{\p[3]}{\type=numexp}{option=noreduction}
\answer{\(P(N=\xval[4])\)}{\p[4]}{\type=numexp}{option=noreduction}
\answer{\(P(N=\xval[5])\)}{\p[5]}{\type=numexp}{option=noreduction}

#endif

#if defined TARGET_varloi3
\title{Variable aléatoire, loi de probabilité 3}
\text{nombre=un,deux,trois,quatre,cinq}
\integer{k=randint(1..3)}
\integer{k=2}
\integer{d=\k=1?3:4}
\integer{m=\k=1?4:3}
\integer{d=\k=3?3}

\text{xval=1,2,3,4}
\integer{tot=\d^\m}

\if{\k=1}
{
\rational{p1=\d/\tot}
\rational{p2=binomial(\d,2)*(2^\m-2)/\tot}
\rational{p3=1-\p2-\p1}
\text{p=\p1,\p2,\p3}
text{p=\d/\tot,binomial(\d,2)*(2^\m-2)/\tot,1-\d*(2^m-1)/tot}
\rational{p2m=\p2+\p3}
}
\if{\k=2}
{
\rational{p1=\d/\tot}
\rational{p2=binomial(\d,2)*(2^\m-2)/\tot}
\rational{p4=0}
\rational{p3=1-\p1-\p2-\p4}
\text{p=\p1,\p2,\p3,\p4}
text{p=\d/\tot,binomial(\d,2)*(2^\m-2)/\tot,1-(\d*(2^m-1+\m!))/tot,\m!*\d/\tot}
\rational{p2m=\p3+\p4}
}
\if{\k=3}
{
\rational{p1=\d/\tot}
\rational{p2=binomial(\d,2)*(2^\m-2)/\tot}
\rational{p4=0}
\rational{p3=1-\p1-\p2-\p4}
\text{p=\p1,\p2,\p3,\p4}
text{p=\d/\tot,binomial(\d,2)*(2^\m-2)/\tot,1-(\d*(2^m-1+\m!))/tot,\m!*\d/\tot}
\rational{p2m=\p2+\p3}
}
\if{\k=4}
{
/* ce cas a été supprimé car trop compliqué: 4 médecins et 5 malades*/
\rational{p1=\d/\tot}
\rational{p2=binomial(\d,2)*(2^\m-2)/\tot}
\rational{p4=\m!*\d/(2*\tot)}
\rational{p3=1-\p1-\p2-\p4}
\text{p=\p1,\p2,\p3,\p4}
text{p=\d/\tot,binomial(\d,2)*(2^\m-2)/\tot,1-(\d*(2^m-1+\m!))/tot,\m!*\d/\tot}
\rational{p2m=\p3+\p4}
}
\text{mstep=wims(makelist r x for x= 2 to \d+1)}
\text{mstep=wims(nospace \mstep)}
\steps{r1,\mstep}

\statement{<p>
Dans une petite ville, \nombre[\d] médecins sont de garde le week-end
 et \nombre[\m] malades appellent au hasard l'un d'entre eux.
</p><p>
 On appelle \(T\) la variable aléatoire qui, à chaque configuration d'appels,
 associe le nombre de médecins appelés.</p>
<div class="wims_question">
Déterminer la loi de probabilité de \(T\).<br>
<table class="wimsborder wimscenter">
<tr><td> t </td>
\for{j=2 to \d+1}
{
<td>\xval[\j-1]</td>
}
</tr><tr><td>\(P(T=t)\)</td>
\for{j=2 to \d+1}
{
<td>\embed{reply\j,4}</td>
}
</tr></table>

<label for="reply1">Quelle est la probabilité qu'au moins \nombre[\d-1] des \nombre[\d] médecins soient appelés ?</label>
 <div class="wimscenter"> \embed{reply1,5}</div>
 <div class="wims_instruction">\consigne</div>
</div>
}
\answer{P(au moins 2 médecins sont appelés)}{\p2m}{type=numexp}{option=noreduction}
\answer{\(P(T=1)\)}{\p[1]}{type=numexp}{option=noreduction}
\answer{\(P(T=2)\)}{\p[2]}{type=numexp}{option=noreduction}
\answer{\(P(T=3)\)}{\p[3]}{type=numexp}{option=noreduction}
\answer{\(P(T=4)\)}{\p[4]}{type=numexp}{option=noreduction}
#endif

#if defined TARGET_varloi4
\title{Variable aléatoire, loi de probabilité 4}
\text{nombre=premier,deuxième,troisième,quatrième,cinquième}
\integer{k=randint(4,5)}
\text{o1=\k=4?1,2,3,4:1,2,3,4,5}
\text{o2=\k=4?G,FG,FFG,FFFG,FFFF:G,FG,FFG,FFFG,FFFFG,FFFFF}
\integer{esp1=0}
\for{i=1 to \k}
 {
 \integer{esp1=\esp1+\i}
 }
\rational{esp1=\esp1/\k}
\text{p=\k=4?1/2,1/4,1/8,1/8:1/2,1/4,1/8,1/16,1/16}
\integer{esp2=0}
\for{i=1 to \k}
 {
 \rational{esp2=\esp2+\i*\p[\i]}
 }
\text{xval=1,2,3,4,5}
\text{mstep=r1,r2,r3,r4,r5,r6}
\text{mstep=\k=5?\mstep,r7}
\steps{\mstep}
\statement{<p>
Dans un pays imaginaire, une loi décide que chaque famille s'arrête
 de procréer dès qu'elle a eu un garçon (G) et qu'elle continue sinon,
 en s'arrêtant de toute façon au \nombre[\k] enfant.</p><p>
 On note \(X\) le nombre d'enfants par famille, on code par G et F
la naissance d'un garçon et d'une fille.</p>
On suppose que la loi de \(X\) est équirépartie sur l'ensemble des issues \(\Omega_1=\{\o1 \}).
<div class="wims_question">
 Calculer \(E(X)\).
 
<div class="wimscenter"><label for="reply1"> \(E(X)=\)</label> \embed{reply1,4}</div>
</div>
On suppose maintenant qu'il y a à chaque naissance autant de chance
 d'avoir un garçon qu'une fille.
<div class="wims_question">
 En considérant l'ensemble \(\Omega_2=\{\o2\}) des issues
 possibles, déterminer la loi de probabilité de \(X\) et son espérance mathématique.
<table class="wimsborder wimscenter">
<tr><th> \(x\) </th>
\for{j=3 to \k+2}
{
<td>\xval[\j-2]</td>
}
</tr><tr><th>\(P(X=x)\)</th>
\for{j=3 to \k+2}
{
<td>\embed{reply\j,4}</td>
}
</tr></table>
<div class="wimscenter"> <label for="reply1">\(E(X)=\)</label> \embed{reply2,3}</div>
<div class="wims_instruction">\consigne</div>
</div>
}
\answer{\(E(X)\) sur \(Omega_1\)}{\esp1}{type=numexp}{option=noreduction}
\answer{\(E(X)\) sur \(Omega_2\)}{\esp2}{type=numexp}{option=noreduction}
\answer{\(P(X=1)\)}{\p[1]}{type=numexp}{option=noreduction}
\answer{\(P(X=2)\)}{\p[2]}{type=numexp}{option=noreduction}
\answer{\(P(X=3)\)}{\p[3]}{type=numexp}{option=noreduction}
\answer{\(P(X=4)\)}{\p[4]}{type=numexp}{option=noreduction}
\answer{\(P(X=5)\)}{\p[5]}{type=numexp}{option=noreduction}
#endif

#if defined TARGET_varloi5
\title{Variable aléatoire, loi de probabilité 5}
\integer{n=randint(4,5)}
\text{xval=0,1,2,3,4,5,6}
\text{mstep=wims(makelist r x for x= 2 to \n+2)}
\text{mstep=wims(nospace \mstep)}
\steps{r1,\mstep}
\integer{tot=\n !}
\if{\n=4}
 {
\rational{p5=1/\tot}
\rational{p4=0}
\rational{p3=6/\tot}
\rational{p2=8/\tot}
\rational{p1=9/\tot}
 }
\if{\n=5}
 {
\rational{p6=1/\tot}
\rational{p5=0}
\rational{p4=10/\tot}
\rational{p3=20/\tot}
\rational{p2=45/\tot}
\rational{p1=44/\tot}
 }

\text{p=\p1,\p2,\p3,\p4,\p5,\p6}
\integer{esp=0}
\for{i=2 to \k+1}
 {
 \rational{esp=\esp+\p[\i]*\xval[\i]}
 }

\statement{<p>
On place dans une urne \n boules numérotées de 1 à \n. On tire au hasard,
successivement et sans remise les \n boules de cette urne.</p><p>
 Soit \(X\) la variable aléatoire qui, à chaque issue,
 associe le nombre de boules pour lesquelles le numéro
coïncide avec le numléro de tirage.<br>
Exemple: tirer la boule n<sup>o</sup>1 au 1<sup>er</sup> tirage; la boule n<sup>o</sup>3 au 3<sup>ème</sup> tirage.
</p>
<div class="wims_question">
 Déterminer la loi de \(X\) et son espérance mathématique.
<table class="wimsborder wimscenter">
<tr><td> \(x\) </td>
\for{j=2 to \n+2}
{
<td>\xval[\j-1]</td>
}
</tr><tr><td>\(P(X=x)\)</td>
\for{j=2 to \n+2}
{
<td>\embed{reply\j,4}</td>
}
</tr></table>
<div class="wimscenter"><label for="reply1">\(E(X)=\)</label> \embed{reply1,7}</div>
<div class="wims_instruction">\consigne</div>
</div>

}
\answer{Espérance}{\esp}{type=numexp}{option=noreduction}
\answer{\(P(X=0)\)}{\p[1]}{type=numexp}{option=noreduction}
\answer{\(P(X=1)\)}{\p[2]}{type=numexp}{option=noreduction}
\answer{\(P(X=2)\)}{\p[3]}{type=numexp}{option=noreduction}
\answer{\(P(X=3)\)}{\p[4]}{type=numexp}{option=noreduction}
\answer{\(P(X=4)\)}{\p[5]}{type=numexp}{option=noreduction}
\answer{\(P(X=5)\)}{\p[6]}{type=numexp}{option=noreduction}
\answer{\(P(X=6)\)}{\p[7]}{type=numexp}{option=noreduction}

#endif
