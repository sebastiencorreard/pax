target=inverse1 inverse2 inverse3 inverse4 inverse5
#define TITRE Notion d'inverse

\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}

#if defined TARGET_inverse1
 \title{TITRE 1}
 \text{A=randitem(A,B,C,D,E,F)}
 \text{enonce=L'inverse d'un nombre non nul \A, c'est le nombre qui}
 \text{good=1}
 \text{bad=multiplié par \A donne 1,divisé par \A donne 1,ajouté à \A donne 1,divisé par \A donne 0,ajouté à \A donne 0,multiplié par \A donne 0}
#endif

#if defined TARGET_inverse2
 \title{TITRE 2}
 \text{A=randitem(A,B,C,D,E,F)}
 \text{enonce=L'inverse du nombre \A peut se noter}
 \text{good=1,2}
 \text{bad=\(\A^{-1}),\(\frac{1}{\A}),\(-\A),\(-\frac{1}{\A}),\(\A-1)}
#endif

#if defined TARGET_inverse3
 \title{TITRE 3}
 \integer{A=randint(2..15)}
 \text{enonce=L'inverse du nombre \A est}
 \text{good=1,2}
 \text{bad=\(\A^{-1}),\(\frac{1}{\A}),\(-\A),\(-\frac{1}{\A}),\(\A-1)}
#endif

#if defined TARGET_inverse4
 \title{TITRE 4}
 \integer{A=randitem(2,4,8,5,10)}
 \text{enonce=L'inverse du nombre \A est}
 \text{good=1,2}
 \real{B=1/\A}
 \text{bad=\(\B),\(\frac{1}{\A}),\(-\A),\(-\frac{1}{\A}),\(\A-1)}
#endif

#if defined TARGET_inverse5
 \title{TITRE 5}
 \integer{A=randint(2..20)}
 \text{enonce=Diviser un nombre par \A revient à}
 \text{good=1}
 \text{bad=le multiplier par l'inverse de \A,le diviser par l'inverse de \A,le multiplier par l'opposé de \A,lui ajouter l'inverse de \A,lui ajouter l'opposé de \A}
#endif

\integer{nb=items(\bad)}
\text{ltgood1=item(\good[1],\bad)}
\text{ltgood2=item(\good[2],\bad)}
\text{bad=shuffle(\bad)}
\text{good=position(\ltgood1,\bad),position(\ltgood2,\bad)}
\text{good=wims(nonempty item \good)}

\statement{
Quelle est la fin de la phrase suivante :
<div class="wimscenter" style="font-style:italic">\enonce...</div>
<blockquote>
 <ul>
\for{k=1 to \nb}{
 <li>\embed{r1,\k}</li>
}
</ul>
</blockquote>
<div class="wims_instruction">Si plusieurs réponses conviennent, les cocher toutes.</div>}
\answer{}{\good;\bad}{type=checkbox}
