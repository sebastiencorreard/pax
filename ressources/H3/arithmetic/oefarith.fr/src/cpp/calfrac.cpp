target=calfrac1,calfrac2
#define TITRE Calcul avec des fractions
#if defined TARGET_calfrac1
 \title{TITRE 1}
 \text{donnees=slib(expnumeric fraction1)}
#endif

#if defined TARGET_calfrac2
 \title{TITRE 2}
 \text{donnees=slib(expnumeric fraction2)}
#endif

\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\text{A=randitem(A,B,C,D,E)}

\text{resultat=item(1,\donnees)}
\text{rep=maxima(\resultat;)}
\text{enonce=item(2,\donnees)}

\statement{
  Calculer l'expression suivante :
<div class="wimscenter">\(\A = \enonce)</div>

<div class="wims_instruction">Vous donnerez le résultat sous forme irréductible.</div>

<b><label for="reply1">Votre réponse :</label></b> \(\A =) \embed{r1,8}.
}

\answer{\A}{\rep}{type=numexp}
