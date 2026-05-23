target=augmentation
#include "lang_titles.inc"
#include "author.inc"

\precision{10000}

\text{pourcent=randint(2..5).randint(1..9)}
\real{price=randint(10..999)}
\text{name=slib(lang/fname fr,boy)}
\text{objet=slib(life/frcommodity \price)}
\text{article=item(1,\objet)}
\text{objet=item(2,\objet)}

\integer{year=randitem(2000,2001,2002,2003,2004)}

\real{remise=\price*\pourcent/100}
\real{final=\price+\remise}

\matrix{enonce=Entre janvier \year et décembre \year, les prix ont augmenté de \pourcent %. \name a acheté \article \objet à \price euros en janvier}

\text{enonce=randrow(\enonce)}

\integer{ch=randint(1..2)}
\if{\ch=1}{
 \text{question=Quelle économie a-t-il fait par rapport à un achat en Décembre}
 \real{rep=\remise}
}{
 \text{question=Quel prix aurait-il payé s'il l'avait acheté en Décembre&nbsp;}
 \real{rep=\final}
}

\real{min=floor(\rep*100)/100}
\real{max=ceil(\rep*100)/100}
\real{rep=rint(\rep*100)/100}
\text{enoncelatex=wims(replace internal % by \% in \enonce)}
\statement{\enonce.
\question?
<div class="spacer">
<label for="reply1"><b>Votre réponse</b> :</label> \embed{r1} euro.</div>
<div class="wims_instruction">Arrondir si nécessaire le résultat au centième d'euros.</div>}

\answer{Réponse}{\eleve}{type=auto}

\condition{Calcul}{\eleve>=\min and \eleve<=\max}{weight=8}
\condition{Arrondi correct}{\rep=\eleve}{weight=2}

\latex{
\begin{statement}
\enoncelatex.
\question?
\end{statement}
}
