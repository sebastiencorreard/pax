target=vocabulaire1 vocabulaire2 vocabulaire3 vocabulaire4 vocabulaire5

\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
#define TITRE Vocabulaire
\text{v=shuffle(2,3,4,5,6,7,8,9)}

#if defined TARGET_vocabulaire1
 \title{TITRE 1}
 \text{enonce1=\v[1] est }
 \text{enonce2=de la fraction \(\frac{\v[1]}{\v[2]})}
 \text{rep=le numérateur}
 \text{list=le dénominateur,la fraction,le quotient}
#endif

#if defined TARGET_vocabulaire2
 \title{TITRE 2}
 \text{enonce1=\v[2] est }
 \text{enonce2=de la fraction \(\frac{\v[1]}{\v[2]})}
 \text{rep=le dénominateur}
 \text{list=le numérateur,la fraction,le quotient}
#endif

#if defined TARGET_vocabulaire3
 \title{TITRE 3}
 \text{enonce1=\(\frac{\v[1]}{\v[2]}) est }
 \text{enonce2=de \v[1] par \v[2]}
 \text{rep=le quotient}
 \text{list=le numérateur,la fraction,le dénominateur}
#endif

#if defined TARGET_vocabulaire4
 \title{TITRE 4}
 \text{enonce=numérateur}
 \text{rep=\v[1]}
#endif

#if defined TARGET_vocabulaire5
 \title{TITRE 5}
 \text{enonce=dénominateur}
 \text{rep=\v[2]}
#endif

#if defined TARGET_vocabulaire1 || defined TARGET_vocabulaire2 || defined TARGET_vocabulaire3
 \statement{
Complétez la phrase suivante en utilisant l'une des étiquettes ci-dessous :
<div class="wimscenter">\enonce1 \embed{r1,130x30x1} \enonce2</div>}

\answer{}{\rep;\list}{type=dragfill}
#else
 \statement{
Quel est le \enonce de la fraction \(\frac{\v[1]}{\v[2]}) ?
<div>
<b>Votre réponse :</b> \embed{r1,6}
</div>}
 \answer{}{\rep}{type=numexp}
#endif
