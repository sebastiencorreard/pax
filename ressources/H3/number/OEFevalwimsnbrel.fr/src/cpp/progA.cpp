target=progA1 progA2 progA3 progA4 progA5
#define TITRE Ecrire un programme de calcul

\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\text{v=wims(values v/10 for v=11 to 99)}
\text{v=shuffle(\v)}

#if defined TARGET_progA1
 \title{TITRE 1}
 \integer{ch=randitem(1,2)}
 \text{calcul=item(\ch,\v[1]\times\v[2]+\v[3],\v[1]\times(\v[2]+\v[3]))}
 \text{good=\ch}
 \text{bad=La somme du produit de \v[1] par \v[2] et de \v[3],Le produit de \v[1] par la somme de \v[2] et \v[3],La différence du produit de \v[1] par \v[2] et de \v[3],Le quotient de \v[1] par la somme de \v[2] et \v[3]}
#endif

#if defined TARGET_progA2
 \title{TITRE 2}
 \integer{ch=randitem(1,2)}
 \text{calcul=item(\ch,\v[1]-(\v[2]-\v[3]),\v[1]-\v[2]-\v[3])}
 \text{good=\ch}
 \text{bad=La différence entre \v[1] et la différence entre \v[2] et \v[3], La différence entre&#44; la différence entre \v[1] et \v[2]&#44; et \v[3],La différence de \v[1]&#44; \v[2] et \v[3],La somme entre \v[1] et la somme de \v[2] et \v[3]}
#endif

#if defined TARGET_progA3
 \title{TITRE 3}
 \integer{ch=randitem(1,2)}
 \text{calcul=item(\ch,\frac{1}{\v[1]}+\frac{1}{\v[2]},\frac{1}{\v[1]+\v[2]})}
 \text{good=\ch}
 \text{bad=La somme des inverses de \v[1] et \v[2],L'inverse de la somme de \v[1] et \v[2],La différence entre les inverses de \v[1] et \v[2],L'inverse de la différence entre \v[1] et \v[2]}
#endif


#if defined TARGET_progA4
 \title{TITRE 4}
 \integer{ch=randitem(1,2)}
 \text{calcul=item(\ch,\v[1]-\v[2]\times \v[3],(\v[1]-\v[2])\times \v[3])}
 \text{good=\ch}
 \text{bad=La différence entre \v[1] et le produit de \v[2] par \v[3],Le produit de la différence entre \v[1] et \v[2] par \v[3], La somme entre \v[1] et le produit de \v[2] par \v[3],Le quotient de la différence entre \v[1] et \v[2] par \v[3]}
#endif

#if defined TARGET_progA5
 \title{TITRE 5}
 \integer{ch=randitem(1,2)}
 \text{calcul=item(\ch,-(\v[1]+\v[2]),-\v[1]+\v[2])}
 \text{good=\ch}
 \text{bad=L'opposé de la somme de \v[1] et \v[2],La somme de l'opposé de \v[1] et de \v[2],L'inverse de la somme de \v[1] et \v[2],La somme de l'inverse de \v[1] et de \v[2]}
#endif

\integer{nb=items(\bad)}
\text{ltgood=item(\good[1],\bad)}
\text{bad=shuffle(\bad)}
\text{good=position(\ltgood,\bad)}
\text{calcul=\(\calcul)}

\statement{
A quelle phrase correspond le calcul suivant :
<div class="wimscenter">\calcul</div>
<blockquote>
<ul>\for{k=1 to \nb}{
 <li>\embed{r1,\k}</li>
}
</ul>
</blockquote>}

\answer{}{\good;\bad}{type=radio}
