target=augm coeff1 percentref2
\language{fr}
\range{-5..5}
\author{Rémi,Belloeil}
\email{remi.belloeil@orange.fr}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "style.inc"
#if defined TARGET_augm
\title{Pourcentage d'augmentation}
#endif
#if defined TARGET_coeff1
\title{Coefficient multiplicateur d'un pourcentage d'augmentation}
#endif
#if defined TARGET_percentref2
\title{Référence d'un pourcentage d'augmentation}
#endif

%% Type 1-> Une seule méthode est développée %%
#define TYPE 1
%% Liste des méthodes et icones %%
\text{list=1,2,3,4}
\text{list2=1,2,3,4}
\integer{nb_meth=items(\list2)}
%%Choix de la méthode%%
#include "method.inc"
#include "augma_init.inc"
les reponses demandees pour chaque methode
\matrix{rtotal=r7,r8,r9
r2,r3,r4,r5,r6
r2,r3,r4,r5,r6
r2,r3,r5,r6}

\text{MM=wims(makelist 0 for x=1 to \nb_meth)}
\text{W=}
\text{ETAPE=r1}
\text{COND=1}
\nextstep{\ETAPE}
\conditions{\COND}

\statement{
  <div class="wims_question">
  <ol>
  <li>\L1
  <br />
  \if{\W=\trep[1]}{\embed{reply7,3} \sy1}
  </li>
  <li>\L2
  <br />
  \if{\W=\trep[1]}{\embed{reply8,10} \sy2}
  </li>
  <li>\L3
  <br />
  \if{\W=\trep[1]}{\ax \embed{reply9,10} \sy3}
  </li>
  </ol>
  </div>
  \if{\step=1}{
#include "listmethod.inc"
  }

  \if{\step=2}{
    \if{\W !=\trep[1]}{
      <p class="myred">
      \consigne2
      </p>
      <div class="wims_question">
      \for{tt=2 to \nb_meth}{
        \if{\W=\trep[\tt]}{
          <div>
#include "augma_question.inc"
          </div>
        }
      }
      </div>
    }
  }
  \if{\step>2}{
    \if{\MM[2]=1}{<img src="\url2" alt="\turl2" />}
    \if{\MM[3]=1}{
      <table class="wimscenter wimsborder">
      <tr><td>1.</td><th>\name_header[1]</th><th>\name_header[2]</th></tr>
      <tr><th>\name_header[3]</th><td>\vi</td><td>100 %</td></tr>
      <tr><th>\name_header[4]</th><td>\vp</td><td>\p %</td></tr>
      <tr><th>\name_header[5]</th><td>\vf</td><td>\pa %</td></tr>
      </table>
    }
    \if{\MM[4]=1}{
      Pourcentage d'augmentation
      <div class="wimscenter">
      \(\large{ \vi\; \overset{\phantom{xx}+\p\%\phantom{xx}}{\underset{\times \pa/100}{\mapsto}}\; \vf})
      </div>
    }
  }
}

\answer{Méthode}{\var1;\trep}{type=click}{option=nonstop}
\answer{ }{\vi}{type=default}
\answer{ }{\p}{type=default}
\answer{ }{\vp}{type=default}
\answer{ }{\vf}{type=default}
\answer{ }{\pa}{type=default}

#if defined TARGET_augm
\answer{ Question 1}{\p}{type=default}
\answer{ Question 2}{\fd}{type=function}
\answer{ Question 3}{\fp}{type=function}
#endif
#if defined TARGET_coeff1
\answer{ Question 1}{\vf}{type=default}
\answer{ Question 2}{\k}{type=default}
\answer{ Question 3}{\fk}{type=function}
#endif
#if defined TARGET_percentref2
\answer{ Question 1}{\vi}{type=default}
\answer{ Question 2}{\fk}{type=function}
\answer{ Question 3}{\fi}{type=function}
#endif

\condition{Choix de la méthode}{1=1}

#include "method_step.inc"

\solution{
#include "augma_solution.inc"
}
