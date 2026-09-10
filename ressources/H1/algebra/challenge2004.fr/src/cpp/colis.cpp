target=colis

#include "header.inc"

\title{Colis}

\text{sh=shuffle(2,3,4,5,6)}
\text{sh=1,wims(sort numeric items \sh[1..3])}
\real{l1=randint(90..110)/10}
\real{h1=randint(50..80)/10}
\real{p1=randint(25..45)/10}
\text{l=wims(values \l1*x for x in \sh)}
\text{h=wims(values \h1*x for x in \sh)}
\text{p=wims(values \p1*x for x in \sh)}
\text{sh2=shuffle(2,3,4)}
\text{sh2=wims(sort numeric items \sh2[1,2])}
\text{rap=simplify(\sh[\sh2[2]]^3/\sh[\sh2[1]]^3)}

\statement{
  Pour l'expédition de colis, la poste vend plusieurs boites en carton&nbsp;:

<table class="wimscenter wimsborder">
<tr><th>Numéro de la boite</th><th>N°1</th><th>N°2</th><th>N°3</th><th>N°4</th></tr>
<tr><th>Largeur</th>
\for{i=1 to 4}{<td>\l[\i]</td>}
</tr>
<tr><th>Hauteur</th>
\for{i=1 to 4}{<td>\h[\i]</td>}
</tr>
<tr><th>Profondeur</th>
\for{i=1 to 4}{<td>\p[\i]</td>}
</tr>
<tr><th>Coefficient d'agrandissement</th>
<td>1</td>
\for{i=1 to 3}{<td>\embed{r\i,3}</td>}
</tr>
</table>
<p>
  Remplissez les coefficients d'agrandissement dans le tableau.
</p>
  Quel est le rapport du volume de la boite \sh2[2] par rapport à la boite
\sh2[1] ? \embed{r4,9}
}

\reply{Coefficient N°2}{\sh[2]}
\reply{Coefficient N°3}{\sh[3]}
\reply{Coefficient N°4}{\sh[4]}
\reply{Rapport du volume}{\rap}{type=default}

