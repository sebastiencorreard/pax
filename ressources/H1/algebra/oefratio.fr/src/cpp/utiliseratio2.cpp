target=utilratio2

%%aide

#include "avant_header.inc"
#include "css.inc"

\title{Trouver 1 grandeur à partir d'un ratio et d'une autre grandeur}

%%Choix de la méthode%%
\text{list=1,2,3,4}
\text{list2=1,2,3,4}
#include "method.inc"
\text{ListChoix=répondre,part,tableau}

%%Variables
#include "nom.inc"
\integer{nbre1=randint(1..10)}
\integer{nbre2=randint(1..10)}
\if{\nbre2=\nbre1}{\integer{nbre2=\nbre2+1}}
\integer{pgcd=gcd(\nbre1,\nbre2)}
\integer{nbre1=\nbre1/\pgcd}
\integer{nbre2=\nbre2/\pgcd}
\integer{don=randint(\nbre1..10)*\nbre1}
\integer{coef=\don/\nbre1}
\integer{rep1=\nbre2*\coef}
\text{liste=\nbre1,\nbre2}
\text{enonce=gâteaux,billes,&oelig;ufs de Pâques,euros}
\if{\nbre1=1}{\text{enoncesing1=gâteau,bille,&oelig;uf,euro}
\text{partsing1=part}}{\text{enoncesing1=\enonce}
\text{partsing1=parts}}
\if{\nbre2=1}{\text{enoncesing2=gâteau,bille,&oelig;uf,euro}
\text{partsing2=part}}{\text{enoncesing2=\enonce}
\text{partsing2=parts}}
\integer{choix=randint(1..4)}
\text{article=\choix>2? d': de }
\text{ratio=\textcolor{red}{\nbre1} : \textcolor{blue}{\nbre2}}
\text{COND=1}
\text{ETAPE=r1}
\nextstep{\ETAPE}
\conditions{\COND}

%%Réalisation du tableau
\text{entetes=Nombre total de parts}
\text{ligne=}
\for{ k1=1 to \nbre1 }{
  \text{ligne=\ligne<div class="unepart part_1" title=""> </div>}
  \if{ \k1 < \nbre1 }{
    text{entetes=\entetes,*}
    \text{ligne=\ligne,}
  }
}
\for{ k2=1 to \nbre2}{
    \if{ \k2 < \nbre2 }{
    text{entetes=\entetes,*}
    }
    \text{ligne=\ligne,<div class="unepart part_2" title=""> </div>}
  }
\text{A=slib(text/matrixhtml
  [\ligne],
  wimscenter wimsborder,
  TH=1
  CAPTION="Nombre total de parts"
  COLSPAN=[1,1,\nbre1;1,\k1\nbre2]
)}

\statement{<div class="wims_question"><span style="font-weight:bold">\name1</span> et
<span style="font-weight:bold">\name2</span> se partagent des \enonce[\choix] selon le ratio
<span class="nowrap" style="font-weight:bold">\(\ratio\)</span>.
<p> Sachant que \name1 a reçu \don \enonce[\choix], on veut déterminer
le nombre \article\enonce[\choix] que recevra \name2.</p></div>
\if{\step=1}{
#include "listmethodb.inc"
}
\if{\step=2 and \var1=répondre}{
<br><label for="reply2">\name2 reçoit</label> \embed{reply2,3} \enonce[\choix].}
\if{\step=2 and \var1==part}{
<br>On commence par déterminer la quantité \article\enonce[\choix] que représente une part.
<br>On peut illustrer la situation par le dessin suivant&nbsp;:
<br>Part de \name1 <span class="unepart part_1 ecrit_1">AAA</span> Part de \name2 <span class="unepart part_2 ecrit_2">AAA</span>
\A
<br><label for="reply3">Avec le ratio \(\ratio\), \name1 reçoit \embed{r3,3} \partsing1</label><label for="reply4"> pendant que \name2 reçoit \embed{r4,3}\partsing2</label>.
<br><label for="reply5">Comme \name1 reçoit \don \enonce[\choix] et que cela représente</label>\embed{r5,3} \partsing1 alors <label for="reply6"><b>une part</b> représente \embed{r6,3} \enonce[\choix].</label>
<br><label for="reply7">Donc \name2 a reçu \embed{reply7,3} \enonce[\choix].</label>}
\if{\step=2 and \var1==tableau}{Comme le ratio est une situation de proportionnalité, on complète ce tableau de proportionnalité en commençant par le remplir grâce aux données de l'énoncé.
<table class="wimscenter wimsborder">
<tr>
<td colspan="1"><label for="reply8">\name1</label></td>
<td colspan="1"><label for="reply9">\name2</label></td>
</tr>
<tr>
<td colspan="1">\embed{r8,3}</td>
<td colspan="1">\embed{r9,3}</td>
</tr>
<tr>
<td colspan="1">\embed{r10,3}</td>
<td colspan="1">\embed{r11,3}</td>
</tr>
</table>
Puis conclure&nbsp;:<div> <label for="reply12">\name2 va recevoir</label> \embed{r12,3} \enonce[\choix].</div>
}

}

\answer{Méthode}{\var1;\ListChoix}{type=click}{option=nonstop}{weight=0}
\answer{}{\rep1}{type=numexp}

\answer{}{\nbre1}{type=numexp}
\answer{}{\nbre2}{type=numexp}
\answer{}{\nbre1}{type=numexp}
\answer{}{\coef}{type=numexp}
\answer{}{\rep1}{type=numexp}

\answer{}{\nbre1}{type=numexp}
\answer{}{\nbre2}{type=numexp}
\answer{}{\don}{type=numexp}
\answer{}{\rep1}{type=numexp}
\answer{}{\rep1}{type=numexp}


\condition{Choix de la méthode}{1=1}

#include"method_step.inc"

%%hint{Le ratio traduit une situation de proportionnalité. Une fois le tableau complété des données de l'énoncé,
calculer le coefficient de proportionnalité qui permet de passer de la première ligne à la seconde ligne.}

\feedback{\reply1==\liste[2] or \reply2==\liste[1]}{<div class="macss"><span style="font-weight:bold;color:red">Attention</span>, vous n'avez pas respecté l'ordre : le premier nombre du ratio correspond à la première personne et le deuxième nombre correspond à la deuxième personne.</div>}

\solution{
\if{\var1=~3}{On complète le tableau grâce aux données de l'énoncé.
<div class="unbreakable">
<table class="wimscenter wimsborder">
<tr>
<td colspan="1">\name1</td>
<td colspan="1">\name2</td>
</tr><tr>
<td colspan="1">\liste[1]</td>
<td colspan="1">\liste[2]</td>
</tr><tr>
<td colspan="1">\don</td>
<td colspan="1"></td>
</tr>
</table>
</div>
<p>Le ratio traduisant une situation de proportionnalité, ce tableau est un tableau de proportionnalité
dont le coefficient est égal à <span class="nowrap">\(\frac{\don}{\nbre1}=\coef\).</span></p>
<p>On multiplie \nbre2 par \coef : <span class="nowrap">\( \nbre2 \times \coef = \rep1 \).</span></p>
On finit de compléter le tableau&nbsp;:
<div class="unbreakable">
<table class="wimscenter wimsborder">
<tr>
<td colspan="1">\name1</td>
<td colspan="1">\name2</td>
</tr>
<tr>
<td colspan="1">\liste[1]</td>
<td colspan="1">\liste[2]</td>
</tr>
<tr>
<td colspan="1">\don</td>
<td colspan="1">\rep1</td>
</tr>
</table>
</div>
Puis on conclut : \name2 va recevoir \rep1 \enonce[\choix].}
\if{\var1=~1 or \var1=~2}{On commence par déterminer la quantité \article\enonce[\choix] que représente une part.
<br>Avec le ratio \(\ratio\), \name1 reçoit \nbre1 \partsing1 pendant que \name2 reçoit \nbre2 \partsing2.
<br>Comme \name1 reçoit \don \enonce[\choix] et que cela représente \nbre1 \partsing1 alors <b>une part</b> représente \(\frac{\don}{\nbre1}=\coef\) \enonce[\choix].
<br>Donc \name2 a reçu \( \coef \times \nbre2 = \rep1\) \enonce[\choix].}
}
