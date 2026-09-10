target=brevet
\title{Le brevet des collèges}
\language{fr}
\range{-5..5}
\author{Rémi,Belloeil}
\email{remi.belloeil@orange.fr}
\computeanswer{yes}
\format{html}
\precision{10000}
#define TYPE 2
#define SOLUTION 1
%%Plusieurs méthodes sont proposées et peuvent être consultées sans réponses intermédiaires%%

%% Liste des méthodes et icones %%
\text{list=1,2,3,6,4}
\text{list2=1,2,3,6,4}
\integer{nb_meth=items(\list2)}
\text{rtotal=r2,r3,r4,r5} les vraies questions
%%Choix de la méthode%%
#include "method.inc"
#include "brevet_init.inc"
\text{MM=wims(makelist 0 for x=1 to \nb_meth)}
\text{W=}
\text{testsolution=}
\text{ETAPE=r1}
\text{COND=1}
\nextstep{\ETAPE}
\conditions{\COND}

\statement{
  <div class="wims_question">
#include "brevet_enonce.inc"
  </div>
  \if{\step=1}{
#include "listmethod.inc"
  }
  \if{\step>1}{
    \if{\W!=\trep[1]}{
      <p>\name_help <strong>\W</strong>.</p>
    }
    <div class="wims_question">
    \for{tt=1 to \nb_meth}{
      \if{\W=\trep[\tt]}{
        <div>
#include "brevet_question.inc"
        </div>
      }
    }
    </div>
    \if{\W!=\trep[1]}{
      <p>\consigne2</p>
#include "listmethod.inc"
    }
  }
}
\answer{\name_method}{\var1;\trep}{type=click}{option=nonstop}
\answer{Reçus au collège A}{\ar}{type=numeric}
\answer{Pourcentage au collège B}{\t2}{type=numeric}
\answer{Candidats du collège C}{\c}{type=numeric}
\answer{Pourcentage sur A, B et C}{\tg1,\tg2,\tg}{type=range}
\condition{\name_method}{1=1}

#include "method_step.inc"
\integer{testsolution=pari(M=[\MM]; sum(j=2,\nb_meth,M[j]))}
\text{solution=no}
\solution{
  \if{\testsolution<1 or \solution=no}{
    <h3>\name_reponse</h3>
    <div>
#include "brevet_reponse.inc"
    </div>
  }{
    <p>Méthodes utilisées :</p>
    \for{tt=2 to \nb_meth}{
      \if{\MM[\tt]=1}{
        <h3>\name_method <strong>\trep[\tt]</strong>.</h3>
      }
    }
#include "brevet_solution.inc"

  }
}
