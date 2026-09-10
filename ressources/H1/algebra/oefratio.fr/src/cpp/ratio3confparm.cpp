target=ratio3confparm

%% pb à régler aide, feedback

#include "avant_header.inc"
#include "css.inc"

\title{Ratio avec 3 grandeurs #}

%%Variables
#include "nom.inc"
\while{\name2==\name3}{
\text{name2=<span class="ecrit_2">slib(lang/fname fr,girl)</span>}
\text{name3=<span class="ecrit_3">slib(lang/fname fr,girl)</span>}}
\integer{nbre1=randint(1..10)}
\integer{nbre2=randint(1..10)}
\integer{nbre3=randint(1..10)}
\while{\nbre1=\nbre2 and \nbre2=\nbre3}{
\integer{nbre1=randint(1..10)}
\integer{nbre2=randint(1..10)}
\integer{nbre3=randint(1..10)}}
\integer{pgcd=gcd(\nbre1,\nbre2)}
\integer{pgcd=gcd(\nbre3,\pgcd)}
\integer{nbre1=\nbre1/\pgcd}
\integer{nbre2=\nbre2/\pgcd}
\integer{nbre3=\nbre3/\pgcd}
\integer{total=\nbre1+\nbre2+\nbre3}
\integer{eff=\total*randint(3..20)}
\integer{coef=\eff/\total}
\integer{rep1=\nbre1*\coef}
\integer{rep2=\nbre2*\coef}
\integer{rep3=\nbre3*\coef}
\text{liste=\nbre1,\nbre2,\nbre3}
\text{enonce=gâteaux,billes,&oelig;ufs de Pâques,euros}
\if{\nbre1=1}{\text{enoncesing1=gâteau,bille,&oelig;uf,euro}
\text{partsing1=part}
}{\text{enoncesing1=\enonce}
\text{partsing1=parts}}
\if{\nbre2=1}{\text{enoncesing2=gâteau,bille,&oelig;uf,euro}
\text{partsing2=part}
}{\text{enoncesing2=\enonce}
\text{partsing2=parts}}
\if{\nbre3=1}{\text{enoncesing3=gâteau,bille,&oelig;uf,euro}
\text{partsing3=part}}{\text{enoncesing3=\enonce}
\text{partsing3=parts}}
\integer{choix=randint(1..4)}
\text{article=\choix>2? d': de }
\text{ratio=\textcolor{red}{\nbre1} : \textcolor{blue}{\nbre2} : \textcolor{maroon}{\nbre3}}

%%% GESTION CONFPARM %%%
\if{\confparm1=}{\text{confparm1=1}}
\if{\confparm2=}{\text{confparm2=1}}
\if{\confparm3=}{\text{confparm3=2}}
\if{(\confparm1=1 and \confparm2=1)}{\integer{n=1}}
\if{\confparm1=1 and \confparm2=2}{\integer{n=2}}
\if{\confparm1=1 and \confparm2=3}{\integer{n=3}}
\if{\confparm1=2 and \confparm2=1}{\integer{n=4}}
\if{\confparm1=2 and \confparm2=2}{\integer{n=5}}
\if{\confparm1=2 and \confparm2=3}{\integer{n=6}}

%%Mise en place des étapes
\text{ETAPE= \n=1 ? r1,r2,r3,r4,r5,r6,r7,r8}
\text{ETAPE= \n=2 ? wims(makelist r x for x=9 to 36)}
\text{ETAPE= \n=3 ? wims(makelist r x for x=37 to 46) }
\if{\n=4 or \n=5 or \n=6}{\text{ETAPE=r47,r48,r49}}
\steps{\ETAPE}

%%Réalisation du tableau
#include "tableau.inc"

\statement{<div class="wims_question"><b>\name1</b>, <b>\name2</b> et <b>\name3</b> se partagent <b>\eff</b> \enonce[\choix] selon le ratio \(\ratio.\)
<p> Déterminer le nombre \article\enonce[\choix] que recevra chaque personne.</p></div>
\if{\n=1}{<ul class="wims_nopuce">
<li>On commence par déterminer le nombre total de parts.</li>
<li>On peut illustrer la situation par le dessin suivant :</li>
<li>Part de \name1 <span class="unepart part_1 ecrit_1">AAA</span> Part de \name2 <span class="unepart part_2 ecrit_2">AAA</span>
Part de \name3 <span class="unepart part_3 ecrit_3">AAA</span>
\A</li>
<li><label for="reply1">Avec le ratio \(\ratio\), \name1 reçoit \embed{r1,3} \partsing1 </label><label for="reply2"> pendant que \name2 reçoit \embed{r2,3} \partsing2 </label> et
<label for="reply3">\name3 reçoit \embed{r3,3} \partsing3 </label>.</li>
<li><label for="reply4">Le partage est donc composé de </label>\embed{r4,3} parts égales.</li>
<li>Comme il y a \eff \enonce[\choix],<label for="reply5"> chaque part est composée de</label>
\embed{r5,3} \enonce[\choix].</li>
<li><label for="reply6">\name1 reçoit</label> \embed{reply6,3} \enonce[\choix].</li>
<li><label for="reply7">\name2 reçoit</label> \embed{reply7,3} \enonce[\choix].</li>
<li><label for="reply8">\name3 reçoit</label> \embed{reply8,3} \enonce[\choix].</li>
</ul>
}
\if{\n=2}{<br>On peut illustrer la situation par le dessin suivant :
<br>Part de \name1 <span class="unepart part_1 ecrit_1">AAA</span> Part de \name2
<span class="unepart part_2 ecrit_2">AAA</span>
Part de \name3 <span class="unepart part_3 ecrit_3">AAA</span></span>
\A
<br><label for="reply9">Avec le ratio \(\ratio\), \name1 reçoit</label> \embed{r9,3} \partsing1,<label for="reply10">\name2 reçoit</label> \embed{r10,3} \partsing2
et <label for="reply11">\name3 reçoit</label> \embed{r11,3} \partsing3.
<br><label for="reply12">Par conséquent, le partage est composé de</label>\embed{r12,3} parts égales.

<span class="unbreakable">\name1 reçoit alors
\special{mathmlinput [\frac{reply13}{reply14}], 3
reply13
reply14}
des \embed{r15,3} \enonce[\choix].</span><br>
<span class="unbreakable">C'est à dire \special{mathmlinput [\frac{reply16}{reply17} \times {reply18}={reply19}], 3
reply16
reply17
reply18
reply19}.</span><br>
<span class="unbreakable">De même, \name2 reçoit \special{mathmlinput [\frac{reply20}{reply21}], 3
reply20
reply21}
des \embed{r22,3} \enonce[\choix].<br></span>
<span class="unbreakable">C'est à dire \special{mathmlinput [\frac{reply23}{reply24} \times {reply25}={reply26}], 3
reply23
reply24
reply25
reply26}
.</span><br>
Et \name3 reçoit \special{mathmlinput [\frac{reply27}{reply28}], 3
reply27
reply28}
des \embed{r29,3} \enonce[\choix].</span><br>
<span class="unbreakable">C'est à dire \special{mathmlinput [\frac{reply30}{reply31} \times {reply32}={reply33}], 3
reply30
reply31
reply32
reply33}
.</span><br>
Ainsi,<label for="reply34"> \name1 reçoit</label>\embed{r34,3} \enonce[\choix],<label for="reply35"> \name2 reçoit</label>\embed{r35,3} \enonce[\choix]
et <label for="reply36"> \name3 reçoit</label>\embed{r36,3} \enonce[\choix].<br>}
\if{\n=3}{Comme le ratio est une situation de proportionnalité, on complète ce tableau de proportionnalité en commençant par le remplir grâce aux données de l'énoncé.
<div class="unbreakable">
<table class="wimscenter wimsborder">
<tr>
<td colspan="1"><label for="reply37">\name1</label></td>
<td colspan="1"><label for="reply38">\name2</label></td>
<td colspan="1"><label for="reply39">\name3</label></td>
<td colspan="1"><label for="reply40">Total</label></td>
</tr>
<tr>
<td colspan="1">\embed{r37,3}</td>
<td colspan="1">\embed{r38,3}</td>
<td colspan="1">\embed{r39,3}</td>
<td colspan="1">\embed{r40,3}</td>
</tr>
<tr>
<td colspan="1">\embed{r41,3}</td>
<td colspan="1">\embed{r42,3}</td>
<td colspan="1">\embed{r43,3}</td>
<td colspan="1">\eff</td>
</tr>
</table>
</div>
puis on conclut :
<br class="spacer">
<label for="reply44">\name1 recevra</label> \embed{r44,3} \enonce[\choix],
<br class="spacer">
<label for="reply45">\name2 recevra</label> \embed{r45,3} \enonce[\choix],
<br class="spacer">
<label for="reply46">\name3 recevra</label> \embed{r46,3} \enonce[\choix].
}
\if{\n=4 or \n=5 or \n=6}{
<br><label for="reply47">\name1 reçoit</label> \embed{reply47,3} \enonce[\choix].
<br><label for="reply48">\name2 reçoit</label> \embed{reply48,3} \enonce[\choix].
<br><label for="reply49">\name3 reçoit</label> \embed{reply49,3} \enonce[\choix].}
}

\answer{}{\nbre1}{type=numexp}
\answer{}{\nbre2}{type=numexp}
\answer{}{\nbre3}{type=numexp}
\answer{}{\total}{type=numexp}
\answer{}{\coef}{type=numexp}
\answer{}{\rep1}{type=numexp}
\answer{}{\rep2}{type=numexp}
\answer{}{\rep3}{type=numexp}

\answer{}{\nbre1}{type=numexp}
\answer{}{\nbre2}{type=numexp}
\answer{}{\nbre3}{type=numexp}
\answer{}{\total}{type=numexp}
\answer{}{\nbre1}{type=numexp}
\answer{}{\total}{type=numexp}
\answer{}{\eff}{type=numexp}
\answer{}{\nbre1}{type=numexp}
\answer{}{\total}{type=numexp}
\answer{}{\eff}{type=numexp}
\answer{}{\rep1}{type=numexp}

\answer{}{\nbre2}{type=numexp}
\answer{}{\total}{type=numexp}
\answer{}{\eff}{type=numexp}
\answer{}{\nbre2}{type=numexp}
\answer{}{\total}{type=numexp}
\answer{}{\eff}{type=numexp}
\answer{}{\rep2}{type=numexp}

\answer{}{\nbre3}{type=numexp}
\answer{}{\total}{type=numexp}
\answer{}{\eff}{type=numexp}
\answer{}{\nbre3}{type=numexp}
\answer{}{\total}{type=numexp}
\answer{}{\eff}{type=numexp}
\answer{}{\rep3}{type=numexp}

\answer{}{\rep1}{type=numexp}
\answer{}{\rep2}{type=numexp}
\answer{}{\rep3}{type=numexp}

\answer{}{\nbre1}{type=numexp}
\answer{}{\nbre2}{type=numexp}
\answer{}{\nbre3}{type=numexp}
\answer{}{\total}{type=numexp}
\answer{}{\rep1}{type=numexp}
\answer{}{\rep2}{type=numexp}
\answer{}{\rep3}{type=numexp}
\answer{}{\rep1}{type=numexp}
\answer{}{\rep2}{type=numexp}
\answer{}{\rep3}{type=numexp}

\answer{}{\rep1}{type=numexp}
\answer{}{\rep2}{type=numexp}
\answer{}{\rep3}{type=numexp}

%%#include "feedback.inc"

\solution{
\if{\n=1 or \n=4}{
<p>Avec le ratio \(\ratio\), le partage est composé de \(\nbre1 \plus \nbre2 \plus \nbre3 = \total\) parts égales.</p>
<p>Chaque part est composée de \(\frac{\eff}{\total}=\coef\) \enonce[\choix].</p>
<p>\name1 reçoit \(\nbre1 \times \coef=\rep1\) \enonce[\choix].</p>
<p>\name2 reçoit \(\nbre2 \times \coef=\rep2\) \enonce[\choix].</p>
<p>\name3 reçoit \( \nbre3 \times \coef=\rep3\) \enonce[\choix].</p>}

\if{\n=2 or \n=5}{<br>Avec le ratio \(\ratio\), \name1 reçoit \nbre1 \partsing1, \name2 reçoit \nbre2 \partsing2 et \name3 reçoit \nbre3 \partsing3.
<br>Par conséquent, le partage est composé de \total parts égales.<br>
\name1 reçoit alors \(\frac{\nbre1}{\total}\) des \eff \enonce[\choix].<br>
C'est à dire \(\frac{\nbre1}{\total} \times \eff = \rep1 .\)<br>
De même, \name2 reçoit \({\nbre2}{\total}\) des \eff \enonce[\choix].<br>
C'est à dire \(\frac{\nbre2}{\total} \times \eff=\rep2 .\)<br>
Et \name3 reçoit \(\frac{\nbre3}{\total} \) des \eff \enonce[\choix].<br>
C'est à dire, \(\frac{\nbre3}{\total} \times \eff=\rep3.\)<br>
Ainsi, \name1 reçoit \rep1 \enonce[\choix], \name2 reçoit \rep2 \enonce[\choix]
et \name3 reçoit \rep3 \enonce[\choix].<br>}

\if{\n=3 or \n=6}{"<b>\name1</b>,<b>\name2</b>,<b>\name3</b> se partagent <b>\(\eff\)</b> \enonce[\choix] selon le ratio <b>\( \ratio \)</b>" signifie que lorsque \name1 reçoit <b>\( \nbre1\)</b> \enoncesing1[\choix] alors
\name2 reçoit <b>\( \nbre2\)</b> \enoncesing2[\choix] et \name3 reçoit<b>\( \nbre3\)</b> \enoncesing3[\choix] , ce qui permet de remplir la 1ère ligne du tableau.
<table class="wimscenter wimsborder">
<tr>
<td colspan="1">\name1</td>
<td colspan="1">\name2</td>
<td colspan="1">\name3</td>
<td colspan="1">Total</td>
</tr>
<tr>
<td colspan="1">\liste[1]</td>
<td colspan="1">\liste[2]</td>
<td colspan="1">\liste[3]</td>
<td colspan="1">\total</td>
</tr>
<tr>
<td colspan="1"></td>
<td colspan="1"></td>
<td colspan="1"></td>
<td colspan="1">\eff</td>
</tr>
</table>
Le ratio traduisant une situation de proportionnalité, on détermine le coefficient de proportionnalité&nbsp;: \(\frac{\eff}{\total}=\coef\).
<p>\( \nbre1 \times \coef = \rep1\) ,\( \nbre2 \times \coef = \rep2\) et \( \nbre3 \times \coef = \rep3\) .</p> <p>Cela permet de remplir la 2nde ligne du tableau et de conclure .<p>
<table class="wimscenter wimsborder">
<tr>
<td colspan="1">\name1</td>
<td colspan="1">\name2</td>
<td colspan="1">\name3</td>
<td colspan="1">Total</td>
</tr>
<tr>
<td colspan="1">\liste[1]</td>
<td colspan="1">\liste[2]</td>
<td colspan="1">\liste[3]</td>
<td colspan="1">\total</td>
</tr>
<tr>
<td colspan="1">\rep1</td>
<td colspan="1">\rep2</td>
<td colspan="1">\rep3</td>
<td colspan="1">\eff</td>
</tr>
</table>
<ul class="wims_nopuce" style="padding-left:0px">
  <li>\name1 recevra \rep1 \enonce[\choix],</li>
  <li>\name2 recevra \rep2 \enonce[\choix],</li>
  <li>\name3 recevra \rep3 \enonce[\choix].</li>
</ul>}
}
