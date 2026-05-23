target=progB1 progB2 progB3 progB4 progB5
#define TITRE Suivre un programme de calcul

\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\text{v=wims(values v/10 for v=11 to 99)}
\text{v=shuffle(\v)}

#if defined TARGET_progB1
 \title{TITRE 1}
 \integer{ch=randint(1..4)}
 \text{ltphrase=Le double de la somme de \v[1] et \v[2]
La somme du double de \v[1] et \v[2]
Le double de la différence entre \v[1] et \v[2]
La différence entre le double de \v[1] et \v[2]}
 \text{phrase=row(\ch,\ltphrase)}
 \text{good=\ch}
 \text{bad=\(2\times(\v[1]+\v[2])),\(2\times\v[1]+\v[2]),\(2\times(\v[1]-\v[2])),\(2\times\v[1]-\v[2]),\(\v[1]+2\times\v[2])}
#endif

#if defined TARGET_progB2
 \title{TITRE 2}
 \integer{ch=randint(1..4)}
 \text{ltphrase=L'inverse de la somme de \v[1] et \v[2]
La somme de l'inverse de \v[1] et \v[2]
L'inverse de la différence entre \v[1] et \v[2]
La différence entre l'inverse de \v[1] et \v[2]}
 \text{phrase=row(\ch,\ltphrase)}
 \text{good=\ch}
 \text{bad=\(\frac{1}{\v[1]+\v[2]}),\(\frac{1}{\v[1]}+\v[2]),\(\frac{1}{\v[1]-\v[2]}),\(\frac{1}{\v[1]}-\v[2]),\(-(\v[1]+\v[2])),\(-(\v[1]-\v[2]))}
#endif

#if defined TARGET_progB3
 \title{TITRE 3}
 \integer{ch=randint(1..2)}
 \text{ltphrase=Soit le nombre \v[1] multiplie le par \v[2] puis ajoute \v[3]
Soit le nombre \v[1] ajoute \v[3] puis multiplie par \v[2]}
 \text{phrase=row(\ch,\ltphrase)}
 \text{good=\ch}
\text{bad=\(\v[1]\times\v[2]+\v[3]),\((\v[1]+\v[3])\times \v[2]),\(\v[1]\times(\v[2]+\v[3])),\(\v[1]+\v[3]\times \v[2])}
#endif

#if defined TARGET_progB4
 \title{TITRE 4}
 \integer{ch=randint(1..4)}
 \text{ltphrase=Soit le nombre \v[1] ajoute lui \v[2] puis calcule l'inverse
Soit le nombre \v[1] calcule son inverse puis ajoute \v[2]
Soit le nombre \v[1] ajoute lui \v[2] puis prend l'opposé
Soit le nombre \v[1] prend son opposé puis ajoute \v[2]}
 \text{phrase=row(\ch,\ltphrase)}
 \text{good=\ch}
\text{bad=\(\frac{1}{\v[1]+\v[2]}),\(\frac{1}{\v[1]}+\v[2]),\(-(\v[1]+\v[2])),\(-\v[1]+\v[2])}
#endif

#if defined TARGET_progB5
 \title{TITRE 5}
 \integer{ch=randint(1..4)}
 \text{ltphrase=La somme du produit de \v[1] par \v[2] et de \v[3]
Le produit de \v[1] par la somme de \v[2] et \v[3]
La différence entre le produit de \v[1] par \v[2] et \v[3]
Le produit de \v[1] par la différence entre \v[2] et \v[3]}
 \text{phrase=row(\ch,\ltphrase)}
 \text{good=\ch}
 \text{bad=\(\v[1]\times \v[2]+\v[3]),\(\v[1]\times (\v[2]+\v[3])),\(\v[1]\times \v[2]-\v[3]),\(\v[1]\times (\v[2]-\v[3]))}
#endif

\integer{nb=items(\bad)}
\text{ltgood=item(\good[1],\bad)}
\text{bad=shuffle(\bad)}
\text{good=position(\ltgood,\bad)}


\statement{
A quel calcul correspond la phrase suivante :
<div class="wimscenter">\phrase</div>
<blockquote>
 <ul>
\for{k=1 to \nb}{
 <li>\embed{r1,\k}</li>
}
</ul>
</blockquote>}

\answer{}{\good;\bad}{type=radio}
