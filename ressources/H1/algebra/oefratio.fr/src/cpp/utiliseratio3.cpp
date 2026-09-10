target=utilratio3

#include "avant_header.inc"
#include "css.inc"

\title{Trouver 2 grandeurs à partir d'un ratio et d'une autre grandeur}

%%Choix de la méthode%%
\text{list=1,2,,4}
\text{list2=1,2,,4}
#include "method.inc"
\text{ListChoix=répondre,part,tableau}

%%Variables
#include "nom.inc"
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
%%MISE EN PLACE DES ETAPES
\text{COND=1}
\text{ETAPE=r1}
\nextstep{\ETAPE}
\conditions{\COND}

%%Réalisation du tableau
#include "tableau.inc"


\statement{<div class="wims_question"><span style="font-weight:bold">\name1</span>,
<span style="font-weight:bold">\name2</span> et <span style="font-weight:bold">\name3</span>
se partagent des \enonce[\choix] selon le ratio
<span class="nowrap" style="font-weight:bold">\(\ratio\)</span>.
<p> Sachant que \name1 reçoit \rep1 \enonce[\choix], on veut déterminer le nombre \article\enonce[\choix] que recevront \name2 et \name3.</p></div>
\if{\step=1}{
#include "listmethodb.inc"
}
\if{\step=2 and \var1=répondre}{
<br><label for="reply2">\name2 reçoit</label> \embed{reply2,3} \enonce[\choix].
<br><label for="reply3">\name3 reçoit</label> \embed{reply3,3} \enonce[\choix].}
\if{\step=2 and \var1==part}{
<br>On commence par déterminer la quantité \article\enonce[\choix] que représente une part.
<p>On peut illustrer la situation par le dessin suivant&nbsp;:</p>
<br>Part de \name1 <span class="unepart part_1 ecrit_1">AAA</span> Part de \name2 <span class="unepart part_2 ecrit_2">AAA</span>Part de \name3 <span class="unepart part_3 ecrit_3">AAA</span>
<br>\A
<br><label for="reply4">Avec le ratio \(\ratio\), \name1 reçoit \embed{r4,3} \partsing1</label><label for="reply5"> pendant que \name2 reçoit \embed{r5,3}\partsing2</label> et<label for="reply6"> \name3 reçoit \embed{r6,3}\partsing3</label>.
<br><label for="reply7">Comme \name1 a reçu \embed{r7,3} \enonce[\choix]</label> et que<label for="reply8"> cela représente</label>\embed{r8,3} \partsing1 alors <label for="reply9"><b>une part</b> représente \embed{r9,3} \enonce[\choix].</label>
<br><label for="reply10">Donc \name2 a reçu \embed{reply10,3} \enonce[\choix] et <label for="reply11">\name3 a reçu \embed{reply11,3} \enonce[\choix].</label>}
\if{\step=2 and \var1==tableau}{Comme le ratio est une situation de proportionnalité, on complète ce tableau de proportionnalité en commençant par le remplir grâce aux données de l'énoncé.</li>
<table class="wimscenter wimsborder">
<tr>
<td colspan="1"><label for="reply12">\name1</label></td>
<td colspan="1"><label for="reply13">\name2</label></td>
<td colspan="1"><label for="reply14">\name3</label></td>
</tr>
<tr>
<td colspan="1">\embed{r12,3}</td>
<td colspan="1">\embed{r13,3}</td>
<td colspan="1">\embed{r14,3}</td>
</tr>
<tr>
<td colspan="1">\embed{r15,3}</td>
<td colspan="1">\embed{r16,3}</td>
<td colspan="1">\embed{r17,3}</td>
</tr>
</table>
Puis on conclut <label for="reply18">\name2 va recevoir</label> \embed{r18,3} \enonce[\choix] et <label for="reply19">\name3 va recevoir</label> \embed{r19,3} \enonce[\choix].</div>
}}

\answer{Méthode}{\var1;\ListChoix}{type=click}{option=nonstop}{weight=0}

\answer{}{\rep2}{type=numexp}
\answer{}{\rep3}{type=numexp}

\answer{}{\nbre1}{type=numexp}
\answer{}{\nbre2}{type=numexp}
\answer{}{\nbre3}{type=numexp}
\answer{}{\rep1}{type=numexp}
\answer{}{\nbre1}{type=numexp}
\answer{}{\coef}{type=numexp}
\answer{}{\rep2}{type=numexp}
\answer{}{\rep3}{type=numexp}

\answer{}{\nbre1}{type=numexp}
\answer{}{\nbre2}{type=numexp}
\answer{}{\nbre3}{type=numexp}
\answer{}{\rep1}{type=numexp}
\answer{}{\rep2}{type=numexp}
\answer{}{\rep3}{type=numexp}
\answer{}{\rep2}{type=numexp}
\answer{}{\rep3}{type=numexp}

\condition{Choix de la méthode}{1=1}

#include"method_step.inc"

\feedback{\reply2==\liste[1] or \reply3==\liste[2]}{<div class="macss"><span style="font-weight:bold;color:red">Attention</span>, vous n'avez pas respecté l'ordre : le premier nombre du ratio correspond à la première personne et le deuxième nombre correspond à la deuxième personne.</div>}

\solution{
\if{\var1=~3}{On complète le tableau grâce aux données de l'énoncé.
<div class="unbreakable">
<table class="wimscenter wimsborder">
<tr>
<td colspan="1">\name1</td>
<td colspan="1">\name2</td>
<td colspan="1">\name3</td>
</tr><tr>
<td colspan="1">\liste[1]</td>
<td colspan="1">\liste[2]</td>
<td colspan="1">\liste[3]</td>
</tr><tr>
<td colspan="1">\rep1</td>
<td colspan="1"></td>
</tr>
</table>
</div>
<p>Le ratio traduisant une situation de proportionnalité, ce tableau est un tableau
  de proportionnalité dont le coefficient est égal à \(\frac{\rep1}{\nbre1}=\coef\).</p>
<p>On multiplie \nbre2 par \coef&nbsp;: \( \nbre2 \times \coef = \rep2 \)
  et \nbre3 par \coef&nbsp;: \( \nbre3 \times \coef = \rep3 \) pour finir de compléter le tableau.</p>
<div class="unbreakable">
<table class="wimscenter wimsborder">
<tr>
<td colspan="1">\name1</td>
<td colspan="1">\name2</td>
<td colspan="1">\name3</td>
</tr><tr>
<td colspan="1">\liste[1]</td>
<td colspan="1">\liste[2]</td>
<td colspan="1">\liste[3]</td>
</tr><tr>
<td colspan="1">\rep1</td>
<td colspan="1">\rep2</td>
<td colspan="1">\rep3</td>
</tr>
</table>
</div>
Puis on conclut&nbsp;: \name2 va recevoir \rep2 \enonce[\choix] et \name3 va recevoir \rep3 \enonce[\choix].}
\if{\var1=~1 or \var1=~2}{
<ul class="wims_nopuce">
<li>On commence par déterminer la quantité \article\enonce[\choix] que représente une part.
<li>Avec le ratio \(\ratio\), \name1 reçoit \nbre1 \partsing1 pendant que \name2 reçoit \nbre2 \partsing2 et \name3 reçoit \nbre3 \partsing3.</li>
<li>Comme \name1 a reçu \rep1 \enonce[\choix] et que cela représente \nbre1 \partsing1 alors <b>une part</b> représente \(\frac{\rep1}{\nbre1}=\coef\) \enonce[\choix].</li>
<li>Donc \name2 a reçu \( \coef \times \nbre2 = \rep2\) \enonce[\choix] et \name3 a reçu \( \coef \times \nbre3 = \rep3\) \enonce[\choix].
</li></ul>}
}
