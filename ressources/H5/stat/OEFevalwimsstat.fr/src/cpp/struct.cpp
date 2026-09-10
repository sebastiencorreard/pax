target=struct1 struct2 struct3 struct4 struct5
#include "author.inc"
#include "lang_titles.inc"
#if defined TARGET_struct1
\integer{pj=randint(18..23)}
\integer{pm=randint(60..65)}
\integer{pv=100-\pj-\pm}
\real{tj=randint(8..12)/10}
\real{tm=randint(20..24)/10}
\real{tv=randint(50..60)}
\rational{tf=(\pj*\tj+\pm*\tm+\pv*\tv)/100}
\integer{p2j=randint(50..60)}
\integer{p2v=randint(1..4)}
\integer{p2m=100-\p2j-\p2v}
\rational{ti=3*(\p2j*\tj+\p2m*\tm+\p2v*\tv)/100}

\statement{<p>
On étudie le taux de mortalité dans la population française:
</p>
<table class="wimsborder wimscenter">
<tr><th> Âge</th><th>- de 15 ans</th><th> 15-65 ans</th><th> + de 65 ans</th></tr>
<tr><th> Proportion en %</th><td> \pj</td><td> \pm </td><td> \pv</td></tr>
<tr><th> taux de mortalité en %</th><td> \tj</td><td> \tm </td><td> \tv </td></tr>
</table>
<div>
<label for="reply1">Calculer le taux de mortalité moyen en France:</label>
  \embed{reply1,4} %.
</div><div>
On imagine un pays dont le taux de mortalité serait le triple de celui de la France
pour chaque tranche d'âge et dont la répartition serait la suivante:
<table class="wimsborder wimscenter">
<tr><th> Âge</th><th>- de 15 ans</th><th> 15-65 ans</th><th> + de 65 ans</th></tr>
<tr><th> Proportion en %</th><td> \p2j</td><td> \p2m </td><td> \p2v</td></tr>
</table>
</div>
<div>
<label for="reply2">Calculer le taux de mortalité moyen de ce pays imaginaire:</label>
  \embed{reply2,4} %.
</div>

}
\answer{taux en France}{\tf}{type=numexp}
\answer{taux au pays imaginaire}{\ti}{type=numexp}
#endif
#if defined TARGET_struct2
\text{prenom=Albert,Claude,Emilie,Lucie,Jean,Fadia,Kevin,Chady}
\text{prenom=shuffle(\prenom)}
\text{lstr=item(1..5,\prenom)}
\text{rep=3,4}
\statement{<p>
5 copains lisent un journal économique:
</p><p style="font-style:italic">
Le revenu moyen global des individus actifs de la ville ....
a augmenté l'an dernier de 3 %, alors que dans le même temps,
et dans toutes les catégories socioprofessionnelles, le revenu a baissé.
</p>
<ol>
<li> \prenom[1] pense que c'est impossible et qu'il y a une erreur dans cet article.</li>
<li> \prenom[2] pense que c'est possible si la répartition socioprofessionnelle a changé,<br>
 en particulier, si une partie des gros salaires a déménagé en banlieue.</li>
<li> \prenom[3] pense que c'est possible si la répartition socioprofessionnelle a changé,<br>
 en particulier, si la proportion de gros salaires a augmenté.</li>
<li> \prenom[4] pense que c'est possible si la répartition socioprofessionnelle a changé,<br>
 en particulier, si si une partie des petits salaires a déménagé en banlieue.</li>
<li> \prenom[5] affirme que c'est possible sans changement de la répartition
  des classes socioprofessionnelles.</li>
</ol>

Cocher la (ou les) personne(s) avec qui vous êtes d'accord:
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\rep;\lstr}{type=checkbox}

#endif

#if defined TARGET_struct3
\integer{p1=randint(5..15)}
\integer{p2=randint(5..20)}
\integer{p1=\p1=\p2?\p1+randint(2..5)}
\rational{np1=(\p1+\p2)/2}
\rational{np2=\p1*0.8+\p2*0.2}
\rational{np3=\p2*0.8+\p1*0.2}
\integer{rep=randint(1,2)}
\integer{pm=\p1<\p2?\p1:\p2}
\integer{pM=\p1<\p2?\p2:\p1}

\real{q=\rep=1?randint(\pm*10..\pM*10)/10:randint(10..\pm*10)/10}

\statement{<p>
Un mélange de café est constitué d'une partie d'Arabica
et d'une autre de Robusta.
</p><p>
Le prix de l'Arabica a subi une augmentation de
\p1% et celui du Robusta de \p2% à la suite de mauvaises conditions
 climatiques dans les pays producteurs.
 </p>
<ol>
<li>
<label for="reply1">Quelle sera l'augmentation du prix de revient si le mélange
 est constitué pour moitié de Robusta et pour moitié d'Arabica ?</label>
<div class="wimscenter">\embed{reply1,4} %.</div></li>
<li>
<label for="reply2">Quelle sera l'augmentation du prix de revient si le mélange
 est constitué de 80% de Robusta et de 20% d'Arabica&nbsp;?</label>
<div class="wimscenter">\embed{reply2,4} %.</div></li>
<li>
<label for="reply3">Quelle sera l'augmentation du prix de revient si le mélange
 est constitué de 20% de Robusta et de 80% d'Arabica&nbsp;?</label>
<div class="wimscenter">\embed{reply3,4} %.</div></li>
<li>
Peut-on trouver un mélange qui permet de limiter la hausse à \q%&nbsp;?
<div class="wimscenter">\embed{reply4}</div></li>
</ol>
}
\answer{augmentation 50/50}{\np1}{type=numeric}
\answer{augmentation 80/20}{\np2}{type=numeric}
\answer{augmentation 20/80}{\np3}{type=numeric}
\answer{mélange possible}{\rep;Oui,Non}{type=radio}
#endif
#if defined TARGET_struct4
\integer{ah=randint(35..45)}
\integer{bh=randint(1..5)+\ah}
\integer{bf=randint(25..34)}
\integer{af=-randint(1..5)+\bf}
\text{mstep=r1,r2
r3,r4,r5,r6}
\steps{\mstep}
\statement{<p>
On s'intéresse à l'âge moyen des adhérents à deux clubs de
sports.
 Les résultats, par sexe, sont regroupés dans les
tableaux suivants:
</p>
<table class="wimsborder wimscenter">
<tr><th> &nbsp;</th><th>Hommes</th><th>Femmes</th></tr>
<tr><th> Âge moyen dans le club A</th><td> \ah</td><td> \af </td></tr>
<tr><th> Âge moyen dans le club B</th><td> \bh</td><td> \bf </td></tr>
</table>
\if{\step=1}
 {
<ol>
<li> Peut-on trouver une répartition Hommes/Femmes dans les deux clubs
telle que la moyenne d'âge globale soit plus élevée
dans le club A que dans le club B&nbsp;?
<div class="wimscenter"> \embed{reply1} </div></li>
<li> Peut-on trouver une répartition Hommes/Femmes dans les deux clubs
telle que la moyenne d'âge globale soit plus élevée
chez les femmes que chez les hommes&nbsp;?
<div class="wimscenter"> \embed{reply2} </div></li>
</ol>
}{
Remplir les tableaux suivants avec une répartition Hommes/Femmes dans les deux clubs
telle que la moyenne d'âge globale soit plus élevée
dans le club A que dans le club B:
<table class="wimsborder wimscenter">
<tr><th> Club A</th><th>Hommes</th><th>Femmes</th></tr>
<tr><th> <label for="reply3">Effectif</label></th><td> \embed{reply3,4}</td>
<td> \embed{reply4,4} </td></tr>
<tr><th> Âge moyen dans le club A</th><td> \ah</td><td> \af </td></tr>
</table>
<table class="wimsborder wimscenter">
<tr><th> Club B</th><th>Hommes</th><th>Femmes</th></tr>
<tr><th><label for="reply5">Effectif</label> </th><td> \embed{reply5,4}</td><td> \embed{reply6,4} </td></tr>
<tr><th> Âge moyen dans le club B</th><td> \bh</td><td> \bf </td></tr>
</table>
}
}
\answer{}{1;Oui,Non}{type=radio}
\answer{}{2;Oui,Non}{type=radio}
\answer{}{\eah}{type=numeric}
\answer{}{\eaf}{type=numeric}
\answer{}{\ebh}{type=numeric}
\answer{}{\ebf}{type=numeric}
\condition{(\eah*\ah+\eaf*\af)*(\ebh+\ebf) > (\ebh*\bh+\ebf*\bf)*(\eah+\eaf)}
#endif
#if defined TARGET_struct5
\integer{n=randint(100,150,200)}
\integer{c=randint(10,15,20)/100*\n}
\integer{o=\n-\c}
\integer{sc=randint(3..8)*1000}
\integer{so=randint(10..15)*100}
\integer{nc=floor((\c*\sc+\o*\so-\n*\so*1.05)/(\sc*1.05-\so*1.05))}
\integer{nbc=\c-\nc}
\steps{r1
r2}
\statement{<p>
En 2000, le personnel d'une petite entreprise est constitué de \c
cadres dont le salaire moyen est de \sc euros et de \o ouvriers
dont le salaire moyen est de \so euros.
</p><p>
En 2001, la composition du personnel a changé mais le nombre d'employés est resté constant et tous
les salariés sont augmentés de 5%.
</p>
\if{\step=1}{
  Peut-on en conclure que la masse salariale a augmenté en 2001&nbsp;?
<div class="wimscenter">\embed{reply1}</div>
 }{
<label for="reply2">Combien au minimum de cadres ont dû être remplacés par des ouvriers pour
obtenir une masse salariale inférieure en 2001 à celle de 2000&nbsp;?</label>
<div class="wimscenter">\embed{reply2,4}</div>
}
}
\answer{}{2;Oui,Non}{type=radio}
\answer{}{\nbc}{type=numeric}
condition{\nbc*10500+(\n-\nbc)*1050 < \c*10000+\o*1000}
#endif
