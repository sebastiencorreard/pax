target=lait evolution
\author{Rémi,Belloeil}
\email{remi.belloeil@orange.fr}
\format{html}
\precision{100}
%% Type 1-> Une seule méthode est développée %%
#define TYPE 1

%% Liste des méthodes et icones %%
#if defined TARGET_lait
\title{Le litre de lait}
\text{\list=1,2,3,4}
\text{\list2=1,2,3,4}
\text{ListChoix=répondre,tableau,opérateur,schéma}
#endif
#if defined TARGET_evolution
\title{Évolutions successives}
\text{\list=1,3,5,6}
\text{\list2=1,3,5,6}
\text{ListChoix=répondre,opérateur,particulier,lettre}
#endif

#include "method.inc"

#if defined TARGET_lait
\real{av=0.01*randint(25..35)}
\integer{p1=randint(60..90)}
\integer{pf1=100+\p1}
\integer{p2=randint(60..80)}
\integer{pf2=100+\p2}
\integer{p3=randint(4..8)}
\integer{pf3=100+\p3}
\text{tcm2=\(CM2= 1+\frac{\p2}{100})}
\text{ev2=augmentation}
#endif
#if defined TARGET_evolution
\integer{\av=100}
\integer{p1=randint(40..80)}
\integer{pf1=100+\p1}
\integer{p3=randint(4..8)}
\integer{pf3=100+\p3}
\text{ev2=diminution}

\integer{k=randint(0..8)}
\integer{pa=\pf1*\pf3*0.01-100}
\integer{m=100*\pa/(100+\pa)}
%%hausse prévisible%%
\if{\k=0}{
  \integer{n1=\m-7}
  \integer{p2=randint(\n1..\m)-1}
}
%%baisse prévisible%%
\if{\k=1}{
  \integer{p2=randint(\pa..80)}
}
%%2 fois sur 8 baisse alors que la somme algébrique est positive %%
\if{\k>1}{
  \integer{p2=randint(\m..\pa)}
}
\integer{pf2=100-\p2}
\text{tcm2=\(CM2= 1-\frac{\p2}{100})}
#endif

\real{cm1=\pf1/100}
\real{nv1=0.01*round(100*\av*\cm1)}
\real{cm2=\pf2/100}
\real{nv2=0.01*round(100*\nv1*\cm2)}
\real{nv4=\nv2}
\real{nv5=\nv1}
\real{cm3=\pf3/100}
\real{nv3=0.01*round(100*\nv2*\cm3)}

\real{cm=\cm1*\cm2*\cm3}
\real{cma=0.01*round(100*\cm)}
\integer{pf=round(100*\cm)}
\integer{p=abs(\pf-100)}
\integer{nv=100*\av*\cm}
\real{nv=0.01*\nv}

\text{tcm1=\(CM1= 1+\frac{\p1}{100}=\cm1)}
\text{tcm2=\tcm2=\cm2}
\text{tcm3=\(CM3= 1+\frac{\p3}{100}=\cm3)}

\text{tcm=\(CM= CM1 \times CM2 \times CM3 = \cm)}
\text{tsol=<ul><li>
  Dans le cas d'évolutions successives,
  il faut calculer les différents coefficients multiplicateurs,
  puis calculer le coefficient multiplicateur global.</li><li>
  Ici, successivement : \tcm1, \tcm2, \tcm3.</li><li>
  Donc le coefficient global est \tcm \(\approx) \cma.</li>
  }

#if defined TARGET_lait
  \text{tsol=\tsol
  <li>Le nouveau prix représente \pf % du prix initial.</li>
  <li>Et le pourcentage d'augmentation est \p % à 1 % près.
  </li></ul>
   Le nouveau prix est donc \(NV =\av \times \cm \approx \nv) &euro; à 0,01 près.}
#endif
#if defined TARGET_evolution
\real{nv4=\cm1*\cm2}
\real{nv5=\cm1}
\text{trep=a diminué, a augmenté,est identique}
\if{\cm<1}{\integer{ns=1}}
\if{\cm=1}{\integer{ns=3}}
\if{\cm>1}{\integer{ns=2}}
\text{evol=\trep[\ns]}
\text{tsol=\tsol
  <li>Par rapport au 1er janvier, la valeur de l'action \evol}
  \if{\ns<3}{\text{tsol=\tsol de \p %}}
  \text{tsol=\tsol.</li></ul>}
#endif

\text{W=}
\text{ETAPE = r1}
\text{COND = 1}
\nextstep{ \ETAPE}
\conditions{ \COND}

\statement{

#if defined TARGET_lait
  <ul class="wims_nopuce">
  <li>
  Un litre de lait est vendu \av &euro; HT à la laiterie.
  </li><li>
  Celle-ci le revend avec une augmentation de \p1 % à un hypermarché.
  </li><li>
  L'hypermarché met le produit en rayon avec une augmentation de \p2 %.
  </li><li>
  Et bien sûr, le client doit payer en plus la taxe de \p3 %.
  </li></ul>
  Quel est le prix TTC payé par le client pour ce litre de lait ?
  \if{\W=répondre}{\embed{reply11} &euro;.
  <div class="wims_instruction">Arrondir à 0,01 &euro; près.</div>}
  Et quel est le pourcentage d'augmentation entre le prix HT payé par la laiterie
  (\av &euro;) et le prix final TTC payé par le client ?
  \if{\W=répondre}{\embed{reply12,4}%.
  <div class="wims_instruction">Arrondir à 1% près.</div>}
#endif
#if defined TARGET_evolution
  <ul class="wims_nopuce">
  <li>
  La valeur d'une action a augmenté de \p1 % en janvier, puis a diminué de \p2 % en février
  et elle a augmenté de \p3 % en mars.</li>
  <li>Comment a évolué la valeur de cette action entre le 1er janvier et le 31 mars ?</li></ul>
#endif
\if{\step=1}{
#include "listmethod.inc"
}
\if{\step>1}{
#if defined TARGET_lait
  <div class="wims_instruction">Arrondir toutes les valeurs en euros à 0,01 près.</div>
  \if{\W=tableau}{
    Vous avez choisi de répondre à l'aide de tableaux de proportionnalité.
    <table class="wimscenter wimsborder"><caption>Augmentation de \p1%</caption>
    <tr><td></td><td>Valeur</td><td>Pourcentage</td></tr>
    <tr><td>Avant</td><td>\av</td><td>100</td></tr>
    <tr><td>Après</td><td>\embed{reply3}</td><td>\pf1</td></tr>
    </table>
    <br/>
    <table class="wimscenter wimsborder"><caption>Augmentation de \p2%</caption>
    <tr><td></td><td>Valeur</td><td>Pourcentage</td></tr>
    <tr><td>Avant</td><td>\embed{reply4}</td><td>100</td></tr>
    <tr><td>Après</td><td>\embed{reply6}</td><td>\pf2</td></tr>
    </table>
    <br/>
    <table class="wimscenter wimsborder"><caption>Augmentation de \p3%</caption>
    <tr><td></td><td>Valeur</td><td>Pourcentage</td></tr>
    <tr><td>Avant</td><td>\embed{reply7}</td><td>100</td></tr>
    <tr><td>Après</td><td>\embed{reply10}</td><td>\pf3</td></tr>
    </table>
  }
#endif
  \if{\W=opérateur}{
    Vous avez choisi de répondre à l'aide des coefficients multiplicateurs.
    <ul class="wims_nopuce">
    <li>Le coefficient multiplicateur correspondant à une augmentation de \p1% est : \embed{reply2}</li>
    <li>Le coefficient multiplicateur correspondant à une \ev2 de \p2% est : \embed{reply5}</li>
    <li>Le coefficient multiplicateur correspondant à une augmentation de \p3% est : \embed{reply8}</li>
    <li>Le coefficient multiplicateur global est : \embed{reply9} (valeur exacte)</li>
#if defined TARGET_lait
    <li>Le prix final est : \embed{reply11} (à 0,01 près)</li>
#endif
    </ul>
  }
#if defined TARGET_lait
  \if{\W=schéma}{
    Vous avez choisi de répondre à l'aide d'un schéma.
    <ul class="wims_nopuce">
    <li>\special{mathmlinput [\large{ \av\; \overset{\phantom{xx}+\p1\%\phantom{xx}}{\underset{\times reply2}{\mapsto}}\; reply3\; \overset{\phantom{xx}+\p2\%\phantom{xx}}{\underset{\times reply5}{\mapsto}}\; reply6\;
\overset{\phantom{xx}+\p3\%\phantom{xx}}{\underset{\times reply8}{\mapsto}}\; reply10}],5
reply2
reply3
reply5
reply6
reply8
reply10}
</li></ul>
}
\if{\W !=répondre}{
  Le pourcentage d'augmentation entre le prix HT payé par la laiterie
  (\av &euro;) et le prix final TTC payé par le client est \embed{reply12,4} % (à 1% près)
}
#endif
#if defined TARGET_evolution
\if{\W=particulier}{
   Vous avez choisi de répondre à l'aide d'un cas particulier.
     <ul class="wims_nopuce">
<li>La valeur initiale n'étant pas connue, on choisit une valeur particulière. Il est judicieux de prendre la valeur 100 comme 100 %.</li>
<li>\special{mathmlinput [\large{ 100\; \overset{\phantom{xx}+\p1\%\phantom{xx}}{\underset{\times reply2}{\mapsto}}\; reply3\; \overset{\phantom{xx}-\p2\%\phantom{xx}}{\underset{\times reply5}{\mapsto}}\; reply6\;
\overset{\phantom{xx}+\p3\%\phantom{xx}}{\underset{\times reply8}{\mapsto}}\; reply10}],5
reply2
reply3
reply5
reply6
reply8
reply10}
</li></ul>
}
\if{\W=lettre}{
  Vous avez choisi de répondre à l'aide d'une lettre.
  <ul class="wims_nopuce">
  <li>La valeur initiale n'étant pas connu, on utilise la lettre \(x) pour la désigner.</li>
  <li>\special{mathmlinput [\large{ x\; \overset{\phantom{xx}+\p1\%\phantom{xx}}{\underset{\times reply2}{\mapsto}}\; reply4 x\; \overset{\phantom{xx}-\p2\%\phantom{xx}}{\underset{\times reply5}{\mapsto}}\; reply7 x\;
  \overset{\phantom{xx}+\p3\%\phantom{xx}}{\underset{\times reply8}{\mapsto}}\; reply9 x}],5
  reply2
  reply4
  reply5
  reply7
  reply8
  reply9}
  </li></ul>
}

Par rapport au 1er janvier, la valeur de l'action \embed{reply11} et
l'écart est de \embed{reply12} % à 1 % près.
#endif
 }
}

\answer{Méthode}{\var1;\ListChoix}{type=click}{option=nonstop}
\answer{CM1}{\cm1}{type=numeric}
\answer{Valeur 1}{\nv1}{type=numeric}
\answer{Valeur 1}{\nv5}{type=numeric}
\answer{CM2}{\cm2}{type=numeric}
\answer{Valeur 2}{\nv2}{type=numeric}
\answer{Valeur 2}{\nv4}{type=numeric}
\answer{CM3}{\cm3}{type=numeric}
\answer{CM global}{\cm}{type=numeric}
\answer{Valeur finale}{\nv3}{type=numeric}

#if defined TARGET_lait
\answer{Valeur finale}{\nv}{type=numeric}
#endif
#if defined TARGET_evolution
\answer{Évolution}{\ns;\trep}{type=menu}
#endif
\answer{Pourcentage global}{\p}{type=numeric}

\condition{Choix de la méthode}{1=1}
\text{ETAPE =}
\if{\step=2}{
  \text{W=\var1}
  \text{ETAPE=\W issametext répondre? r11,r12}
  \text{ETAPE=\W issametext tableau? r3,r4,r6,r7,r10,r12}
  \text{ETAPE=\W issametext opérateur? r2,r5,r8,r9,r11,r12}
  \text{ETAPE=\W issametext schéma? r2,r3,r5,r6,r8,r10,r12}
  \text{ETAPE=\W issametext particulier? r2,r3,r5,r6,r8,r10,r11,r12}
  \text{ETAPE=\W issametext lettre? r2,r4,r5,r7,r8,r9,r11,r12}

}
  \if{\step=3}{\text{ETAPE=}}

\solution{
   <ul class="wims_nopuce">
#if defined TARGET_lait
<li>Pourcentage d'augmentation</li>
<li>\(\large{ \av\; \overset{\phantom{xx}+\p1\%\phantom{xx}}{\underset{\times \cm1}{\mapsto}}\; \nv1\; \overset{\phantom{xx}+\p2\%\phantom{xx}}{\underset{\times \cm2}{\mapsto}}\; \nv2\;
\overset{\phantom{xx}+\p3\%\phantom{xx}}{\underset{\times \cm3}{\mapsto}}\; \nv3})</li>
#endif
#if defined TARGET_evolution
<li>\(\large{ \av\; \overset{\phantom{xx}+\p1\%\phantom{xx}}{\underset{\times \cm1}{\mapsto}}\; \nv1\; \overset{\phantom{xx}-\p2\%\phantom{xx}}{\underset{\times \cm2}{\mapsto}}\; \nv2\;
\overset{\phantom{xx}+\p3\%\phantom{xx}}{\underset{\times \cm3}{\mapsto}}\; \nv3})</li>
#endif
  </ul>
\tsol
}
