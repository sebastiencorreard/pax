target=vocabulaire4 vocabulaire5
#define TITRE Vocabulaire
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}

\text{v=wims(values v for v=2 to 10)}
\text{v=shuffle(\v)}

#if defined TARGET_vocabulaire4
 \title{TITRE 4}
 \integer{ch=randint(1..2)}
 \integer{s=\v[1]+\v[2]}
 \text{v=\ch=1?\v[1],\v[2],\s:\s,\v[2],\v[1]}
 \text{type=item(\ch,la somme,la différence)}
 \text{enonce=Quelle est \type de \v[1] et \v[2]}
 \text{rep=\v[3]}
#endif

#if defined TARGET_vocabulaire5
 \title{TITRE 5}
 \integer{ch=randint(1..2)}
 \integer{p=\v[1]*\v[2]}
 \text{v=\ch=1?\v[1],\v[2],\p:\p,\v[2],\v[1]}
 \text{type=item(\ch,le produit,le quotient)}
 \text{enonce=Quel est \type de \v[1] par \v[2]}
 \text{rep=\v[3]}
#endif

\statement{
\enonce ?
<div>
<b>Votre réponse</b>: \embed{r1,8}
</div>}
\answer{}{\rep}{type=numexp}
