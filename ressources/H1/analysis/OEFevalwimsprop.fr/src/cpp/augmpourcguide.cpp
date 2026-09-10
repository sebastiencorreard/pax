target=augmpourcguide augmpourc

\author{Lionel,Verbecq}
\email{lionel.verbecq@ac-versailles.fr}
\precision{10000000}
\computeanswer{yes}
\format{html}

# define TITRE Montant après augmentation

#if defined TARGET_augmpourcguide
\title{TITRE (guidé)}
#endif
#if defined TARGET_augmpourc
\title{TITRE}
#endif

\integer{pourcent=randint(2..10)}
\integer{prix=randint(10..999)}
\text{nom=slib(lang/fname fr,boy)}
\text{objet=slib(life/frcommodity \prix)}
\text{article=item(1,\objet)}
\text{objet=item(2,\objet)}
\real{remise=\prix*\pourcent/100}
\real{final=\prix+\remise}
\text{enonce=\nom a acheté \article \objet à \prix euros en janvier,Les prix ont augmenté de \pourcent % en février}
\text{question=Quel est le montant de l'augmentation&nbsp;?,Quel est le prix final après l'augmentation&nbsp;?}

#if defined TARGET_augmpourcguide
\statement{\enonce[1].
<p>\enonce[2].</p>
\question[1]
<div class="spacer">
<label for="reply1"><b>Montant de l'augmentation</b>&nbsp;:</label>\embed{r1,5} &euro;. </div>
<div class="wims_instruction">Le point sera utilisé comme séparateur décimal au lieu de la virgule.</div>
\question[2]
<p><label for="reply2"><b>Montant final après augmentation</b>&nbsp;:</label>\embed{r2,7} &euro;.</p>
}
\answer{Montant de l'augmentation}{\remise}{type=numeric}
\answer{Montant après augmentation}{\final}{type=numeric}
#endif

#if defined TARGET_augmpourc
\statement{\enonce[1].
<p>\enonce[2].</p>
\question[2]
<div class="wims_instruction">Le point sera utilisé comme séparateur décimal au lieu de la virgule.</div>
<p><label for="reply1"><b>Montant final après augmentation</b>&nbsp;:</label>\embed{r1,7} &euro;.</p>
}
\answer{Montant après augmentation}{\final}{type=numeric}
#endif

\solution{On calcule d'abord le montant de l'augmentation.
<p>"\pourcent % de \prix" fait \(\frac{\pourcent \times \prix}{100} = \remise\).</p>
On calcule le prix final après l'augmentation.
<p>\(\prix + \remise = \final\)</p>
Le prix final après l'augmentation est \( \final \ \euro\).}
