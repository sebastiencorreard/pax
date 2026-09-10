target=
\language{fr}
\range{-5..5}
\author{Rémi,Belloeil}
\email{remi.belloeil@orange.fr}
\computeanswer{yes}
\format{html}
\precision{10000}

#if defined TARGET_solde1
\title{Ancien Les soldes avec choix de méthode et schémas dans l'ordre}
\text{T = 1,2,3}
\text{Rq=Ils sont dans le même ordre que les questions.}
#endif

#if defined TARGET_solde2
\title{Ancien Les soldes avec choix de méthode et schémas mélangés}
\text{T = shuffle(3)}
\text{Rq=Attention ils ne sont peut-être pas dans l'ordre des questions.}
#endif

%%Choix de la méthode%%
%% Type 1-> Une seule méthode est développée %%
#define TYPE 1

%% Liste des méthodes et icones %%
\text{list=1,2,3,4}
\text{list2=1,2,3,4}
\integer{nb_meth=items(\list2)}
\matrix{rtotal=r15,r16,r17
r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14
r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14
r2,r3,r4,r5,r6,r8,r9,r10,r11,r13,r14} les vraies questions
%%Choix de la méthode%%
#include "method.inc"
#include "soldes_init.inc"

\text{MM=wims(makelist 0 for x=1 to \nb_meth)}
\text{W=}
\text{ETAPE = r1}
\text{COND = 1}
\nextstep{\ETAPE}
\conditions{\COND}

\statement{
  <ol>
  <li>\Er1
<br />
  \if{\W=\trep[1]}{\embed{reply15,3} \sr1}
  </li>
  <li>\Er2
<br />
  \if{\W=\trep[1]}{\embed{reply16,3} \sr2}
  </li>
  <li>\Er3
<br />
  \if{\W=\trep[1]}{\embed{reply17,3} \sr3}
  </li>
  </ol>
  \if{\step=1}{
#include "listmethod.inc"
  }

  \if{\step=2}{
    \if{\W !=\trep[1]}{
      <p>
      La méthode choisie est développée ci-dessous et comporte les réponses aux questions.
      </p>
      \if{\W=\trep[2]}{
        Compléter les schémas suivants.
        <div class="wims_instruction">\Rq</div>
        \special{imageinput \url1, 1000x350, 3
        reply2, 60x240
        reply3, 140x290,1
        reply4, 210x300
        reply5, 350x240
        reply6, 430x100,1
        reply7, 510x110
        reply8, 510x220
        reply9, 590x200,1
        reply10, 710x240
        reply11, 790x160,1
        reply12, 860x170
        reply13, 860x310
        reply14, 950x270,1
      }
    }
    \if{\W=\trep[3]}{
      Compléter les tableaux de proportionnalité.
      <div class="wims_instruction">\Rq</div>
      <table class="wimscenter wimsborder">
      <tr><td></td><th>valeurs</th><th>pourcentage</th></tr>
      <tr><th>Tout</th><td>\embed{reply 2,3}</td><td>100 %</td></tr>
      <tr><th>Partie</th><td>\embed{reply 4,3}</td><td>\embed{reply 3,3} %</td></tr>
      </table>

      <table class="wimscenter wimsborder">
      <tr><td></td><th>valeurs</th><th>pourcentage</th></tr>
      <tr><th>Valeur initiale</th><td>\embed{reply 5,3}</td><td>100 %</td></tr>
      <tr><th>Augmentation</th><td>\embed{reply 7,3}</td><td>\embed{reply 6,2} %</td></tr>
      <tr><th>Valeur finale</th><td>\embed{reply 8,3}</td><td>\embed{reply 9,2} %</td></tr>
      </table>
      <table class="wimscenter wimsborder">
      <tr><td></td><th>valeurs</th><th>pourcentage</th></tr>
      <tr><th>Valeur initiale</th><td>\embed{reply 10,3}</td><td>100 %</td></tr>
      <tr><th>Diminution</th><td>\embed{reply 12,3}</td><td>\embed{reply 11,2} %</td></tr>
      <tr><th>Valeur finale</th><td>\embed{reply 13,3}</td><td>\embed{reply 14,2} %</td></tr>
      </table>
    }
    \if{\W=\trep[4]}{
      <p>Compléter les schémas suivants.</p>
      <div class="wims_instruction">\Rq</div>
      <p>
      Pourcentage proportion<br>
      \special{mathmlinput [\large{ reply2\; \overset{\phantom{xxx}reply3\%\phantom{xxxx}}{\mapsto}\; reply4}],5
reply2
reply3
reply4} </p>
      <p>
      Pourcentage d'augmentation<br>
      \special{mathmlinput [\large{ reply5\; \overset{\phantom{xxx}+ reply6\%\phantom{xxxx}}{\underset{\times reply9 /100}{\mapsto}}\; reply8}],5
reply5
reply6
reply9
reply8} </p>
      <p>
      Pourcentage de diminution<br>
      \special{mathmlinput [\large{ reply10\; \overset{\phantom{xxx}- reply11\%\phantom{xxxx}}{\underset{\times reply14 /100}{\mapsto}}\; reply13}],5
reply10
reply11
reply14
reply13} </p>
    }
  }
}
\if{\step>2}{
  \if{\MM[2]=1}{<img src="\url2">}
  \if{\MM[3]=1}{
    <table class="wimscenter wimsborder">
    <tr><td></td><th>valeurs</th><th>pourcentage</th></tr>
    <tr><th>Tout</th><td>\vi1</td><td>100 %</td></tr>
    <tr><th>Partie</th><td>\vp1</td><td>\p1 %</td></tr>
    </table>
    <table class="wimscenter wimsborder">
    <tr><td></td><th>valeurs</th><th>pourcentage</th></tr>
    <tr><th>Valeur initiale</th><td>\vi2</td><td>100 %</td></tr>
    <tr><th>Augmentation</th><td>\vp2</td><td>\p2 %</td></tr>
    <tr><th>Valeur finale</th><td>\va2</td><td>\pa2 %</td></tr>
    </table>
    <table class="wimscenter wimsborder">
    <tr><td></td><th>valeurs</th><th>pourcentage</th></tr>
    <tr><th>Valeur initiale</th><td>\vi3</td><td>100 %</td></tr>
    <tr><th>Diminution</th><td>\vp3</td><td>\p3 %</td></tr>
    <tr><th>Valeur finale</th><td>\vd3</td><td>\pd3 %</td></tr>
    </table>
  }
  \if{\MM[4]=1}{
   <ul class="inline">
    <li>\(\large{ \vi1\; \overset{\phantom{xxx} \p1 \%\phantom{xxx}}{\mapsto}\; \vp1})</li>
    <li>\(\large{ \vi2\; \overset{\phantom{xx}+\p2 \%\phantom{xx}}{\underset{\times \pa2/100}{\mapsto}}\; \va2})</li>
    <li>\(\large{ \vi3\; \overset{\phantom{xx}-\p3 \%\phantom{xx}}{\underset{\times \pd3/100}{\mapsto}}\; \vd3})</li>
   </ul>
    }
  }
}

\answer{Méthode}{\var1;\trep}{type=click}{option=nonstop}
\answer{ }{\vi1}{type=default}
\answer{ }{\p1}{type=default}
\answer{ }{\vp1}{type=default}
\answer{ }{\vi2}{type=default}
\answer{ }{\p2}{type=default}
\answer{ }{\vp2}{type=default}
\answer{ }{\va2}{type=default}
\answer{ }{\pa2}{type=default}
\answer{ }{\vi3}{type=default}
\answer{ }{\p3}{type=default}
\answer{ }{\vp3}{type=default}
\answer{ }{\vd3}{type=default}
\answer{ }{\pd3}{type=default}
\answer{ Question 1}{\vr1}
\answer{ Question 2}{\vr2}
\answer{ Question 3}{\vr3}
\condition{Choix de la méthode}{1=1}

#include "method_step.inc"
\solution{
<ol>
<li>réponse : \vr1
<br />Type : \ListeTy[\T[1]]
<br />Question : Rechercher \ListeQ[\TQ[\T[1]]]</li>
<li>réponse : \vr2
<br />Type : \ListeTy[\T[2]]
<br />Question : Rechercher \ListeQ[\TQ[\T[2]]]</li>
<li>réponse : \vr3
<br />Type : \ListeTy[\T[3]]
<br />Question : Rechercher \ListeQ[\TQ[\T[3]]]</li>
</ol>
<img src="\url2">
<p>
Pourcentage proportion
</p>
<div class="wimscenter">
\(\large{ \vi1\; \overset{\phantom{xxx} \p1 \%\phantom{xxx}}{\mapsto}\; \vp1})
</div>
<p>
Pourcentage d'augmentation
</p>
<div class="wimscenter">
\(\large{ \vi2\; \overset{\phantom{xx}+\p2 \%\phantom{xx}}{\underset{\times \pa2/100}{\mapsto}}\; \va2})
</div>
<p>
Pourcentage de diminution
</p>
<div class="wimscenter">
\(\large{ \vi3\; \overset{\phantom{xx}-\p3 \%\phantom{xx}}{\underset{\times \pd3/100}{\mapsto}}\; \vd3})</p>
</div>
}
