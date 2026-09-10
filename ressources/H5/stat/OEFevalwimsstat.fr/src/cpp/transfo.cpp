target=transfo1 transfo2 transfo3 transfo4 transfo5
#include "author.inc"
#include "lang_titles.inc"

#if defined TARGET_transfo1
\integer{a=randint(10..20)}
\integer{off=randint(1..\a-1)}
\integer{b=\a+\off}
\integer{c=\a-\off}
\integer{d=\b+1}
\text{lstrep=La médiane ne change pas, La médiane change, La moyenne ne change pas, La moyenne change, Le mode ne change pas, Le mode change}
\text{data=On rajoute une valeur au dessus et une valeur en dessous de \a,1
On rajoute une valeur égale à \b et une valeur égale à \c,1,3
On rajoute une valeur égale à \d et une valeur égale à \c,1,4
On rajoute une valeur égale à \a,1,3,5
On retire une valeur égale à \a,3
On retire une valeur au dessus et une valeur en dessous de \a,1,5
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\text{rep=item(2..-1,\cedata)}

\statement{<p>
On considère une série statistique dont le mode, la médiane et la moyenne
ont pour valeur \a.
\quest
</p><p>
Cocher la ou les propositions que l'on peut affirmer:
</p>
<ul>\for{j=1 to 6}{<li>\embed{reply1,\j}</li>}</ul>
}
\answer{Affirmations vraies}{\rep;\lstrep}{type=checkbox}
#endif

#if defined TARGET_transfo2
\integer{rx=randint(2..5)}
\integer{x=\rx^2}
\integer{xc=\x^2}
\integer
\text{data=on augmente toutes les valeurs de la série de \x,2,2,1,2,1,1
on diminue toutes les valeurs de la série de \x,3,3,1,3,1,1
on multiplie toutes les valeurs de la série par \x,4,4,4,4,5,4
}sta
\text{lstrep=ne change pas, augmente de \x, diminue de \x, est multiplié(e) par \x, est multiplié(e) par \xc, est multiplié(e) par \rx}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}

\statement{<p>
Que deviennent les indicateurs d'une série statistique lorsqu'\quest?
</p>
<ul>
<li> La médiane \embed{reply1}</li>
<li> Le premier quartile \embed{reply2}</li>
<li> L'intervalle interquartile \embed{reply3}</li>
<li> La moyenne \embed{reply4}</li>
<li> La variance \embed{reply5}</li>
<li> l'écart-type \embed{reply6}</li>
</ul>
}
\answer{Médiane}{\cedata[2];\lstrep}{type=menu}
\answer{Q1}{\cedata[3];\lstrep}{type=menu}
\answer{Q3-Q1}{\cedata[4];\lstrep}{type=menu}
\answer{Moyenne}{\cedata[5];\lstrep}{type=menu}
\answer{Variance}{\cedata[6];\lstrep}{type=menu}
\answer{écart-type}{\cedata[7];\lstrep}{type=menu}
#endif

#if (defined TARGET_transfo3 || defined TARGET_transfo4 )
\real{m=randint(80..140)/10}
\real{s=randint(200..450)/100}
\integer{a=randint(2..9)*randint(1,-1)}
\text{signecoef=\a>0?positif:négatif}
\integer{b=randint(2..10)}
\real{my=\a*\m+\b}
\real{sy=abs(\a)*\s}
#if defined TARGET_transfo3
\statement{<p>
Soit une série statistique \((x_i)) de moyenne \m et d'écart type \s.
On pose \(y_i=\a x_i+ \b).</p>
<p>
Calculer la moyenne et l'écart type de la série \((y_i)).
</p>
<ul>
<li><label for="reply1">Moyenne de \((y_i)) =</label> \embed{reply1,3} </li>
<li><label for="reply1">Écart type de \((y_i)) =</label> \embed{reply2,3} </li>
</ul>
}
\answer{Moyenne}{\my}{type=numeric}
\answer{Ecart type}{\sy}{type=numeric}
#else
\function{rep=\a*x+\b}
\statement{<p>
La moyenne de la classe à un devoir de mathématique est de \m et l'écart-type est de \s.
</p><p>
 Quelle transformation affine de coefficient directeur \signecoef faut-il appliquer à la série de notes
afin de se ramener à une moyenne de \my et à un écart-type de \sy?
</p><div>
<label for="reply1">Transformation affine:</label> \embed{reply1}
</div>
<i> Donner votre réponse sous la forme a*x+b</i>
}
\answer{transformation}{\rep}{type=function}
# endif
#endif
#if defined TARGET_transfo5
\text{temp=randint(4..8),randint(4..8),randint(6..12),randint(10..15),randint(13..18),randint(18..24),randint(20..28),randint(20..28),randint(18..24),randint(15..20),randint(8..15),randint(4..10)}
\integer{sum=0}
\for{j=1 to 12}
  { \integer{sum=\sum+\temp[\j]}}
\real{m=\sum/12}
\integer{sum=0}
\for{j=1 to 12}
  { \integer{sum=\sum+(\temp[\j]-\m)^2}}
\real{s=sqrt(\sum/12)}
\real{m=round(\m*10)/10}
\real{s=round(\s*10)/10}
\real{mf=1.8*\m+32}
\real{mf=round(\mf*10)/10}
\real{sf=1.8*\s}
\real{sf=round(\sf*10)/10}
\statement{<p>
On a relevé les températures d'une ville de France le premier jour
 de chaque mois pendant une année.<br>
 Le tableau est exprimé en degré Celsius.</p>
<table class="wimscenter wimsborder">
<tr><th>Janvier</th><th>Février</th><th>Mars</th><th>Avril</th><th>Mai</th><th>Juin</th></tr>
<tr>
\for{i=1 to 6}{ <td>\temp[\i]</td> }
</tr>
<tr><th>Juillet</th><th>Août</th><th>Septembre</th><th>Octobre</th><th>Novembre</th><th>Décembre</th></tr>
<tr>
\for{i=7 to 12}{ <td>\temp[\i]</td> }
</tr></table>
<p>Calculer la moyenne et l'écart type de cette série:</p>
<ul>
<li> <label for="reply1">Moyenne =</label> \embed{reply1,3} <i> arrondie à 0.1 près</i></li>
<li> <label for="reply2">Écart type =</label> \embed{reply2,3} <i> arrondi à 0.1 près</i></li>
</ul><p>
Si les mesures avaient été faites par des anglais,
ils auraient exprimé les résultats en degré Fahrenheit.<br>
 La formule de conversion est \(\;T_F\;=\; 1.8t_c+32).<br>
Calculer la moyenne et l'écart type des températures en degré Fahrenheit.</p>
<ul>
<li><label for="reply3">Nouvelle moyenne = </label>\embed{reply3,3} <i> arrondie à 0.1 près</i></li>
<li><label for="reply4">Nouvel écart type = </label>\embed{reply4,3} <i> arrondi à 0.1 près</i></li>
</ul>
}
\answer{Moyenne}{\m}{type=numeric}
\answer{Écart type}{\s}{type=numeric}
\answer{Nouvelle moyenne}{\mf}{type=numeric}
\answer{Nouvel écart type}{\sf}{type=numeric}
#endif
