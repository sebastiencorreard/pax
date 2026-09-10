target=ratio2confparm

%%mettre un lien vers completer un tableau d eproportionnalité

#include "avant_header.inc"
#include "css.inc"

\title{Ratio avec 2 grandeurs #}

%%Déclaration des variables%%
#include "nom.inc"
\integer{total=randint(5..20)}
\integer{eff=\total*randint(3..20)}
\integer{nbre1=randint(1..\total-1)}
\integer{nbre2=\total-\nbre1}
\while{\nbre2=\nbre1 or \nbre1<1}{\integer{haz=randint(1..3)}
\integer{nbre1=\nbre1-\haz}
\integer{nbre2=\nbre2+\haz}}
\integer{pgcd=gcd(\nbre1,\nbre2)}
\integer{nbre1=\nbre1/\pgcd}
\integer{nbre2=\nbre2/\pgcd}
\integer{total=\nbre1+\nbre2}
\integer{coef=\eff/\total}
\integer{rep1=\nbre1*\coef}
\integer{rep2=\eff-\rep1}
\text{liste=\nbre1,\nbre2}
\text{enonce=gâteaux,billes,&oelig;ufs,euros}
\if{\nbre1=1}{\text{enoncesing1=gâteau,bille,&oelig;uf,euro}
\text{partsing1=part}}{\text{enoncesing1=\enonce}
\text{partsing1=parts}}
\if{\nbre2=1}{\text{enoncesing2=gâteau,bille,&oelig;uf,euro}
\text{partsing2=part}}{\text{enoncesing2=\enonce}
\text{partsing2=parts}}
\integer{choix=randint(1..4)}
\text{article=\choix>2? d': de }
\text{ratio=\textcolor{red}{\nbre1} : \textcolor{blue}{\nbre2}}

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

%%Réalisation du dessin%%
#include "tableau.inc"

\text{ETAPE= \n=1 ? r1,r2,r3,r4,r5,r6}
\text{ETAPE= \n=2 ? wims(makelist r x for x=7 to 23)}
\text{ETAPE= \n=3 ? r24,r25,r26,r27,r28,r29,r30}
\if{\n=4 or \n=5 or \n=6}{\text{ETAPE=r31,r32}}
\steps{\ETAPE}

\statement{<div class="wims_question">\name1 et \name2 se partagent \(\eff\) \enonce[\choix] selon le ratio \(\ratio\).
<p>Déterminer le nombre \article\enonce[\choix] que recevra chaque personne.</div>

\if{\n=1}{
On commence par déterminer le nombre total de parts.
<br>On peut illustrer la situation par le dessin suivant :
<br>Part de \name1 <span class="unepart part_1 ecrit_1">AAA</span> Part de \name2 <span class="unepart part_2 ecrit_2">AAA</span>
\A
<br><label for="reply1">Avec le ratio \(\ratio\), \name1 reçoit \embed{r1,3} \partsing1</label><label for="reply2"> pendant que \name2 reçoit \embed{r2,3}\partsing2</label>.
<br><label for="reply3">Le partage est donc composé de</label>\embed{r3,3} parts égales.
<br>Comme il y a \eff \enonce[\choix],<label for="reply4"> chaque part est composée de</label> \embed{r4,3} \enonce[\choix].
<br><label for="reply5">\name1 reçoit</label> \embed{reply5,3} \enonce[\choix].
<br><label for="reply6">\name2 reçoit</label> \embed{reply6,3} \enonce[\choix].}

\if{\n=2}{
<p>Avec le ratio \( \nbre1 : \nbre2 \), on peut faire le dessin suivant :</p>
<br>Part de \name1 <span class="unepart part_1 ecrit_1">AAA</span> Part de \name2 <span class="unepart part_2 ecrit_2">AAA</span>
\A
<label for="reply7">le partage est composé de</label>\embed{r7,3} parts égales.<br>
<span class="unbreakable">\name1 reçoit alors
\special{mathmlinput [\frac{reply8}{reply9}], 3
reply8
reply9}
des \embed{r10,3} \enonce[\choix].</span><br>
<span class="unbreakable">C'est à dire \special{mathmlinput [\frac{reply11}{reply12} \times {reply13}={reply14}], 3
reply11
reply12
reply13
reply14}.</span><br>
<span class="unbreakable">De même, \name2 reçoit \special{mathmlinput [\frac{reply15}{reply16}], 3
reply15
reply16}
des \embed{r17,3} \enonce[\choix].</span><br>
<span class="unbreakable">C'est à dire \special{mathmlinput [\frac{reply18}{reply19} \times {reply20}={reply21}], 3
reply18
reply19
reply20
reply21}
.</span><br>
Ainsi,<label for="reply22"> \name1 reçoit</label>\embed{r22,3} \enonce[\choix] et<label for="reply23"> \name2 reçoit</label>\embed{r23,3} \enonce[\choix].}

\if{\n=3}{Comme le ratio est une situation de proportionnalité, on complète ce tableau de proportionnalité en commençant par le remplir grâce aux données de l'énoncé.
<div class="unbreakable">
<table class="wimscenter wimsborder">
<tr>
<td colspan="1"><label for="reply24">\name1</label></td>
<td colspan="1"><label for="reply25">\name2</label></td>
<td colspan="1"><label for="reply26">Total</label></td>
</tr>
<tr>
<td colspan="1">\embed{r24,3}</td>
<td colspan="1">\embed{r25,3}</td>
<td colspan="1">\embed{r26,3}</td>
</tr>
<tr>
<td colspan="1">\embed{r27,3}</td>
<td colspan="1">\embed{r28,3}</td>
<td colspan="1">\eff</td>
</tr>
</table>
</div>
puis on conclut :
<br class="spacer">
<label for="reply29">\name1 recevra</label> \embed{r29,3} \enonce[\choix]
<br class="spacer">
et <label for="reply30">\name2 recevra</label> \embed{r30,3} \enonce[\choix].}

\if{\n=4 or \n=5 or \n=6}{
<br><label for="reply31">\name1 reçoit</label> \embed{reply31,3} \enonce[\choix].
<br><label for="reply32">\name2 reçoit</label> \embed{reply32,3} \enonce[\choix].}
}

\answer{}{\nbre1}{type=numexp}
\answer{}{\nbre2}{type=numexp}
\answer{}{\total}{type=numexp}
\answer{}{\coef}{type=numexp}
\answer{}{\rep1}{type=numexp}
\answer{}{\rep2}{type=numexp}

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
\answer{}{\rep1}{type=numexp}
\answer{}{\rep2}{type=numexp}

\answer{}{\nbre1}{type=numexp}
\answer{}{\nbre2}{type=numexp}
\answer{}{\total}{type=numexp}
\answer{}{\rep1}{type=numexp}
\answer{}{\rep2}{type=numexp}
\answer{}{\rep1}{type=numexp}
\answer{}{\rep2}{type=numexp}

\answer{}{\rep1}{type=numexp}
\answer{}{\rep2}{type=numexp}


#include "feedback.inc"

\solution{
\if{\n=1 or \n=4}{
<br>Avec le ratio \( \nbre1 : \nbre2 \), le partage est composé de \(\nbre1 \plus \nbre2 = \total\) parts égales.
<br>Chaque part est composée de \(\frac{\eff}{\total}=\coef \) \enonce[\choix].
<br>\name1 reçoit \(\nbre1 \times \coef = \rep1\) \enonce[\choix].
<br>\name2 reçoit \(\nbre2 \times \coef = \rep2 \) \enonce[\choix].}
\if{\n=2 or \n=5}{
<p>Avec le ratio \( \nbre1 : \nbre2 \), le partage est composé de \(\nbre1 \plus \nbre2 = \total\) parts égales.<br>
\name1 reçoit alors \(\frac{\nbre1}{\total}\) des \eff \enonce[\choix].<br>
C'est à dire \(\frac{\nbre1}{\total} \times \eff = \rep1 \).<br>
De même, \name2 reçoit \(\frac{\nbre2}{\total} \) des \eff \enonce[\choix].<br>
C'est à dire \(\frac{\nbre2}{\total} \times \eff = \rep2.\)<br>
Ainsi,\name1 reçoit \rep1 \enonce[\choix] et \name2 reçoit \rep2 \enonce[\choix].}
\if{\n=3 or \n=6}{
"\name1 et \name2 se partagent \(\eff\) \enonce[\choix] selon le ratio \(\ratio\)" signifie que lorsque \name1 reçoit \( \nbre1\) \enoncesing1[\choix] alors
\name2 reçoit \( \nbre2\) \enoncesing2[\choix], ce qui permet de remplir la 1ère ligne du tableau.
<table class="wimscenter wimsborder">
<tr>
<td colspan="1">\name1</span></td>
<td colspan="1">\name2</span></td>
<td colspan="1">Total</span></td>
</tr>
<tr>
<td colspan="1">\nbre1</td>
<td colspan="1">\nbre2</td>
<td colspan="1">\total</td>
</tr>
<tr>
<td colspan="1"></td>
<td colspan="1"></td>
<td colspan="1">\eff</td>
</tr>
</table>
Le ratio traduisant une situation de proportionnalité, on détermine le coefficient de proportionnalité&nbsp;: \(\frac{\eff}{\total}=\coef\).
<p>\( \nbre1 \times \coef = \rep1\) et \( \nbre2 \times \coef = \rep2\).</p> <p>Cela permet de remplir la 2nde ligne du tableau et de conclure .<p>
<table class="wimscenter wimsborder">
<tr>
<td colspan="1">\name1</span></td>
<td colspan="1">\name2</span></td>
<td colspan="1">Total</span></td>
</tr>
<tr>
<td colspan="1">\nbre1</td>
<td colspan="1">\nbre2</td>
<td colspan="1">\total</td>
</tr>
<tr>
<td colspan="1">\rep1</td>
<td colspan="1">\rep2</td>
<td colspan="1">\eff</td>
</tr>
</table>
<p>\name1 recevra \rep1 \enonce[\choix] et \name2 recevra \rep2 \enonce[\choix].</p>}
}


