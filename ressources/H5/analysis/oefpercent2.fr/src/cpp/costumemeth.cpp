target=costume
\author{Rémi,Belloeil}
\email{remi.belloeil@orange.fr}
\format{html}
\precision{100}

%% Type 2-> Plusieurs méthodes sont présentées sans réponses intermédiaires.%%
#define TYPE 2

\title{Le costume d'André}
\text{\list=1,2,3,4,6}
\text{\list2=1,2,3,4,9}
\text{ListChoix=répondre,tableau,opérateur,schéma,lettre}

#include "method.inc"

\integer{av=randint(100..300)}
\integer{p1=randint(5..24)}
\real{cm1=1+\p1/100}
\integer{nv1=100*\av*\cm1}
\real{nv1=0.01*\nv1}

\integer{p2=randint(20..30)}
\real{cm2=1-\p2/100}
\real{cm=\cm1*\cm2}
\real{t=\cm-1}
\integer{p=(1-\cm)*100}
\integer{pr=-\p}

\integer{nv=100*\av*\cm}
\real{nv=0.01*\nv}

\text{tcm1=\(CM1= 1+\frac{\p1}{100}=\cm1) (hausse)}
\text{tcm2=\(CM2= 1-\frac{\p2}{100}=\cm2) (baisse)}
\text{tcm=\(CM= CM1 \times CM2 = \cm < 1) donc baisse}
 \text{tsol=Dans le cas d'évolutions successives, il faut calculer les différents coefficients multiplicateurs, puis calculer le coefficient multiplicateur global.<br>
Ici, \tcm1 et \tcm2<br>
Donc le coefficient global est \tcm<br>}
\text{tsol=\tsol Le nouveau prix est donc \(NV = AV \times CM1 =\av \times \cm1 = \nv1) &euro;<br><br>}

\text{tsol=\tsol Et le prix pour André est \(NV = AV \times CM =\av \times \cm = \nv) &euro;<br><br><br>}
\text{tsol=\tsol Le pourcentage d'évolution pour André est \(\frac{NV - AV}{AV} = \frac{\nv - \av}{ \av} = \t \approx \pr) %<br>}
\text{tsol=\tsol Soit une réduction de \p %. <br><br>}
\text{tsol=\tsol Par ailleurs \(\frac{NV - AV}{AV} =  \frac{AV \times CM - AV}{AV} = CM-1= \cm - 1 = \t \approx \pr) %.<br>}
\text{tsol=\tsol Le pourcentage de réduction ne dépend que du coefficient multiplicateur, donc il est indépendant du prix initial.}
\text{name_head=Augmentation, Remise}

\text{W=}
\text{ETAPE = r1}
\text{COND = 1}
\nextstep{ \ETAPE}
\conditions{ \COND}

\statement{
  <p>
  Les produits d'un grand magasin ont augmenté de \p1 %.<br>
  Les employés ont droit à une remise de \p2 % sur tout achat.<br>
  André qui travaille dans ce grand magasin achète un costume qui valait \av &euro; avant l'augmentation.<br>
  </p>
  <ol>
  \if{\W=répondre}{
    <li><label for="reply2">Quel est son nouveau prix ? </label> \embed{reply2} &euro;
      <i>arrondir à un centime d'euro </i></li>
    <li><label for="reply3">Combien André payera-t-il ce costume ?</label> \embed{reply3} &euro;
      <i>arrondir à un centime d'euro </i></li>
    <li><label for="reply4">Quel est en pourcentage, la remise qu'il a obtenu par rapport à l'ancien prix ?</label> \embed{reply4} %
      <i>arrondir à 1 % près. </i></li>
    <li>Ce pourcentage serait-il le même pour un autre article dans les mêmes conditions ? \embed{reply5}</li>
  }{
    <li>Quel est son nouveau prix (à un centime d'euro près)?</li>
    <li>Combien André payera-t-il ce costume (à un centime d'euro près) ?</li>
    <li>Quel est en pourcentage, la remise qu'il a obtenu par rapport à l'ancien prix ( à 1 % près) ?</li>
    <li>Ce pourcentage serait-il le même pour un autre article dans les mêmes conditions ?</li>
  }
  </ol>
  \if{\step=1}{
    <p>Des méthodes sont proposées mais on peut chercher les réponses par soi-même.</p>
  }
  \if{\step>1}{
    <div class="wims_instruction">Arrondir toutes les valeurs en euros à 0,01 près.</div>
    \if{\W=tableau}{
      Voici la méthode des tableaux de proportionnalité à reproduire sur une feuille pour la compléter.
      <table class="wimscenter wimsborder"><caption>Augmentation de \p1%</caption>
      <tr><td></td><td>Valeur</td><td>Pourcentage</td></tr>
      <tr><td>Avant</td><td>\av</td><td>100</td></tr>
      <tr><td>Après</td><td></td><td>\pf1</td></tr>
      </table>

      <table class="wimscenter wimsborder"><caption>Remise de \p2%</caption>
      <tr><td></td><td>Valeur</td><td>Pourcentage</td></tr>
      <tr><td>Avant</td><td></td><td>100</td></tr>
      <tr><td>Après</td><td></td><td>\pf2</td></tr>
      </table>

      <table class="wimscenter wimsborder"><caption>Évolution globale</caption>
      <tr><td></td><td>Valeur</td><td>Pourcentage</td></tr>
      <tr><td>Avant</td><td></td><td>100</td></tr>
      <tr><td>Après</td><td></td><td></td></tr>
      </table>
    }
    \if{\W=opérateur}{
      Voici la méthode des coefficients multiplicateurs à reproduire sur une feuille pour la compléter.

      <ul class="wims_nopuce">
      <li>Le coefficient multiplicateur correspondant à une augmentation de \p1 % est : ________</li>
      <li>Le nouveau prix est : ____________ (à 0,01 près)</li>
      <li>Le coefficient multiplicateur correspondant à une diminution de \p2 % est : __________</li>
      <li>Le coefficient multiplicateur global est : _________________ (valeur exacte)</li>
      <li>Le prix du costume pour Jean est : ___________ (à 0,01 près)</li>
      <li>D'après le coefficient multiplicateur global, le pourcentage de la remise par rapport à l'ancien prix est : ____________</li>
      </ul>
    }
    \if{\W=schéma}{
      Voici la méthode à l'aide d'un schéma à reproduire sur une feuille pour le compléter.

      <div class="wimscenter">
      \(\large{\av &euro; \overset{\name_head[1]}{\overset{+ \p1 \%}{\underset{\times \phantom{\cm1}}{\mapsto}}} \phantom{\nv1} &euro;
      \overset{\name_head[2]}{\overset{- \p2 \%}{\underset{\times \phantom{\cm2}}{\mapsto}}} \phantom{\nv} &euro;}
      \)
      <br />
      \(\large{\av &euro; \overset{\phantom{\name_head[1]}-\phantom{\p} \%\phantom{\name_head[1]}}{\underset{\times \phantom{\cm}}{\mapsto}} \phantom{\nv} &euro;}\)
      </div>
    }
    \if{\W=lettre}{
      Voici la méthode à l'aide d'une lettre pour justifier la dernière réponse. Réaliser ce schéma sur une feuille et le compléter.
      <div class="wimscenter">
      \(\large{x &euro; \overset{\name_head[1]}{\overset{+ \p1 \%}{\underset{\times \phantom{\cm1}}{\mapsto}}} \phantom{\nv1} &euro;
      \overset{\name_head[2]}{\overset{- \p2 \%}{\underset{\times \phantom{\cm2}}{\mapsto}}} \phantom{\nv} &euro;}
      \)
      <br />
      \(\large{x &euro; \overset{\phantom{\name_head[1]}-\phantom{\p} \%\phantom{\name_head[1]}}{\underset{\times \phantom{\cm}}{\mapsto}} \phantom{\nv} &euro;}\)
      </div>

      Si \(x=\av),
      <ul class="wims_nopuce">
       <li>alors le nouveau prix est _____________&euro;</li>
       <li>le coût pour Jean sera __________ à 0,01 près</li>
       <li>le pourcentage de la remise par rapport à l'ancien prix sera ______ %</li>
       <li>Ce pourcentage est-il indépendant de la valeur de \(x) ? _______<li>
      </ul>
    }
  }
  \if{\W!=répondre}{
    #include "listmethod.inc"
  }
}
\answer{Méthode}{\var1;\ListChoix}{type=click}{option=nonstop}
\answer{Nouveau prix}{\nv1}{type=numeric}
\answer{Coût pour André}{\nv}{type=numeric}
\answer{Pourcentage global}{\p}{type=numeric}
\answer{}{1;oui,non}{type=radio}
\condition{Choix de la méthode}{1=1}

\text{ETAPE=}
\if{\var1=répondre}{
  \if{\W=répondre}{
    \text{ETAPE=}
  }{
    \text{ETAPE=r2,r3,r4,r5}
    \text{W=répondre}
  }
}{
  \text{ETAPE=r1}
  \text{W=\var1}
}

\solution{\tsol

  <h3>Schématiquement</h3>
  <div class="wimscenter">
  \(\large{\av &euro; \overset{\name_head[1]}{\overset{+ \p1 \%}{\underset{\times \cm1}{\mapsto}}} \nv1 &euro;
  \overset{\name_head[2]}{\overset{- \p2 \%}{\underset{\times \cm2}{\mapsto}}} \nv &euro;}
  \)
  <br />
  \(\large{\av &euro; \overset{\phantom{\name_head[1]}-\p \%\phantom{\name_head[1]}}{\underset{\times \cm}{\mapsto}} \nv &euro;}\)
  </div>
}
