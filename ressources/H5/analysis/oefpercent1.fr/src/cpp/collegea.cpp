target=college
\title{Le collège A}
\language{fr}
\range{-5..5}
\author{Rémi,Belloeil}
\email{remi.belloeil@orange.fr}
\computeanswer{yes}
\format{html}
\precision{500}
#include "style.inc"
#define TYPE 2
%%Plusieurs méthodes sont proposées et peuvent être consultées sans réponses intermédiaires%%

%% Liste des méthodes et icones %%
\text{list=1,2,3,5,4}
\text{list2=1,2,3,5,4}
\integer{nb_meth=items(\list2)}
\text{rtotal=r2,r3,r4,r5} les vraies questions
%%Choix de la méthode%%
#include "method.inc"
#include "college_init.inc"
\text{MM=wims(makelist 0 for x=1 to \nb_meth)}
\text{W=}
\text{testsolution=}
\text{ETAPE=r1}
\text{COND=1}
\nextstep{\ETAPE}
\conditions{\COND}

\statement{
  <div class="wims_question">
#include "college_enonce.inc"
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
#include "college_question.inc"
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

\answer{\name_method}{\var1;\trep}{type=click}{option=nonstop}{weight=0}
\answer{Reçus au collège A  }{\Ar}{type=numeric}{weight=10}
\answer{Pourcentage de reçues parmi les filles}{\tfr}{type=numeric}{weight=30}
\answer{Garçons reçus}{\gr}{type=numeric}{weight=20}
\answer{Pourcentage de reçus parmi les garçons}{\tgr}{type=numeric}{weight=40}
\condition{\name_method}{1=1}

#include "method_step.inc"

\solution{
#include "college_solution.inc"
}
