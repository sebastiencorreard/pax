target=soldes
#include "lang_titles.inc"
#include "author.inc"
\precision{10000}

\integer{pourcent=randitem(5,10,15,20,25,30,35)}
\real{price=randint(10..999)}
\text{name=slib(lang/fname fr,boy)}
\text{objet=slib(life/frcommodity \price)}
\text{article=item(1,\objet)}
\text{objet=item(2,\objet)}

\real{remise=\price*\pourcent/100}
\real{final=\price-\remise}

\matrix{enonce=\name achète \article \objet à \price euros dans une boutique. Le vendeur décide de lui faire une remise de \pourcent %
Un magasin propose une remise de \pourcent % sur tous ses articles. \name achète \article \objet à \price euros}
\text{enonce=randrow(\enonce)}

\integer{ch=randint(1..2)}
\if{\ch=1}{
 \text{question=Quel sera le montant de la remise&nbsp;}
 \real{rep=\remise}
}{
 \text{question=Quel sera le prix payé par \name}
 \real{rep=\final}
}
\text{enoncelatex=wims(replace internal % by \% in \enonce)}

\statement{\enonce.
\question?
<div class="spacer">
<label for="reply1"><b>Votre réponse</b> :</label> \embed{r1} euro.</div>
<div class="wims_instruction">Arrondir si nécessaire le résultat au centième d'euros.</div>}

\answer{Réponse}{\rep}{type=numexp}

\latex{
\begin{statement}
\enoncelatex.
\question?
\end{statement}
}

