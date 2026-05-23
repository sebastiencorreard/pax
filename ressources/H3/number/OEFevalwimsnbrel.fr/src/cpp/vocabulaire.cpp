target=vocabulaire1 vocabulaire2 vocabulaire3
#define TITRE Vocabulaire

\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}

\text{v=wims(values v for v=2 to 15)}
\text{v=shuffle(\v)}

#if defined TARGET_vocabulaire1
 \title{TITRE 1}
 \integer{ch=randint(1..2)}
 \text{ltsg=+,-}
 \integer{s=\v[1]+\v[2]}
 \text{v=\ch=1?\v[1],\v[2],\s:\s,\v[2],\v[1]}
 \text{sg=item(\ch,\ltsg)}
 \text{mathenonce=\v[1]\sg\v[2] = \v[3]}
 \text{enonce1=On dit que \v[3] est }
 \text{enonce2=de \v[1] et \v[2]}
 \text{bad=la somme,la différence,le quotient,le produit,un terme,un facteur}
 \text{good=item(\ch,\bad)}
#endif

#if defined TARGET_vocabulaire2
 \title{TITRE 2}
 \integer{ch=randint(1..2)}
 \integer{p=\v[1]*\v[2]}
 \text{v=\ch=1?\v[1],\v[2],\p:\p,\v[2],\v[1]}
 \text{ltsg=*,/}
 \text{ltsg2=\times, \div }
 \text{mathenonce=\v[1]\ltsg2[\ch]\v[2] = \v[3]}
 \text{enonce1=On dit que \v[3] est }
 \text{enonce2=de \v[1] par \v[2]}
 \text{bad=le produit,le quotient,la somme,la différence,un terme,un facteur}
 \text{good=item(\ch,\bad)}
#endif

#if defined TARGET_vocabulaire3
 \title{TITRE 3}
 \integer{ch=randint(1..2)}
 \text{ltsg=+,*}
 \text{ltsg2=+, \times }
 \integer{p=\v[1]\ltsg[\ch]\v[2]}
 \text{mathenonce=\v[1]\ltsg2[\ch]\v[2] = \p}
 \integer{r=randitem(\v[1],\v[2])}
 \text{enonce1=On dit que \r est }
 \text{enonce2=\ch=1?de la somme de \v[1] et \v[2]:du produit de \v[1] par \v[2]}
 \text{bad=un terme,un facteur,le produit,le quotient,la somme,la différence}
 \text{good=item(\ch,\bad)}
#endif


\statement{
<div class="wimscenter">\(\mathenonce)</div>
Complétez la phrase suivante :
<div class="wimscenter">
\enonce1 \embed{r1} \enonce2</div>
}
\answer{}{\good;\bad}{type=dragfill}
