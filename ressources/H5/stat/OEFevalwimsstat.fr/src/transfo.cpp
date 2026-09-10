target=transfo1
\author{Régine MANGEARD}
\email{regine@mangeard.fr}
\format{html}


#if #TARGET(transfo1)
\title{influence d'une transformation}
\integer{a=randint(10..20)}
\integer{off=randint(1..\a-1)}
\integer{b=\a+\off}
\integer{c=\a-\off}
\text{lstrep=La médiane change, La médiane ne change pas, La moyenne change, La moyenne ne change pas, Le mode change, Le mode ne change pas}
\text{data=On rajoute une valeur au dessus et une valeur en dessous de \a,1
On rajoute une valeur égale à \b et une valeur égale à \c,1,3
On rajoute une valeur égale à \a,1,3,5
On retire une valeur égale à \a,3
On retire une valeur au dessus et une valeur en dessous de \a,1,5
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\text{rep=item(2..-1,\cedata)}

\statement{<p>
On considère une série statistique dont le mode, la médiane et la moyenne ont pour valeur \a.<p>
\quest
<p>
Cocher la ou les propositions que l'on peut affirmer:
<p>
<table cellpadding="10">
<tr><td>\embed{reply1,1}</>td><td>\embed{reply1,2}</td></tr>
<tr><td>\embed{reply1,1}</>td><td>\embed{reply1,2}</td></tr>
<tr><td>\embed{reply1,1}</>td><td>\embed{reply1,2}</td></tr>
</table>
}
\answer{affirmations vraies}{\rep;\lstrep}{type=checkbox}
#endif