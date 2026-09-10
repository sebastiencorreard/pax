target=1k_exp 2aff_exp 3secdeg_exp 4Qexp_k 5Qexp_aff 6Qexp_secdeg

#include "lang_title.inc"
#include "avant_header.inc"
#include "lang_descobs.inc"

%%%%% TEXTES DE L'EXERCICE DANS LA LANGUE %%%%%
#include "data_generation.inc"
#include "lang.inc"
#include "lang_help.inc"
#include "lang_hint.inc"

\statement{
<div class ="euler_quest">
\enonce
<br class="spacer"> \question
</div>

<div class =\if {\sc_reply1=}
 {"euler_answer"}
 {\if{\sc_reply1=1 }
  {"tick euler_rep_good"}
  {\if{\sc_reply1=0.5}
    {"approx euler_rep_prec"}
    {"cross euler_rep_bad"}
  }
 }>
 \if {\sc_reply1!=}{\retour}
  
 <div class="unbreakable">
  <label for="reply1">\(\forall \x \in \Int,\,\f^{'}(\x)=\)</label>
  \embed{reply1,\largeur}
 </div>
</div>
}

\answer{}{\rep1,\x}{type=formal}{option=noanalyzeprint}

%%%% FEEDBACK %%%%%
\function{rep=\reply1}
\text{Delta2=Init}
\text{Delta3=Init} 
    
\if{\sc_reply1!=1}
  {# Comparer la rep à l'erreur sur dérivée produit ou quotient
   \text{Delta2 = maxima(print(ratsimp(trigreduce(trigsimp(((\rep)-(\rep2))/(e^(\m*\x+\p))))));)}
   \if{abs(\Delta2)<10^(-10)}
     {\text{Delta2 =0}}
     {\text{Delta2 =NOP}}
   \if{\Delta2!=0}
     {# Comparer la rep à l'erreur sur dérivée fction exp
      \text{Delta3 = maxima(print(ratsimp(trigreduce(trigsimp(((\rep)-(\rep3))/(e^(\m*\x+\p))))));)}
      \if{abs(\Delta3)<10^(-10)}
        {\text{Delta3 =0}}
        {\text{Delta3 =NOP}}
     }
  }

\text{reponse = texmath(\reply1)}

\feedback{\sc_reply1=1}{
<div class ="euler_rep_good">\rep_good_0
<br>\rep_good_1 <span class="nowrap">\(\forall{\x} \in \Int,\f^'(\x)=\dfonc_disp\).</span>
</div>
}

\feedback{\sc_reply1!=1}{
<div class ="euler_rep_bad">\rep_bad_0 <span class="nowrap">\(\forall{\x} \in \Int,\f^'(\x)=\dfonc_disp\).</span></div>
}

\feedback{\sc_reply1!=1 and \Delta2=0}{<div class ="euler_rep_bad">\feed1</div>}

\feedback{\sc_reply1!=1 and \Delta3=0}{<div class ="euler_rep_bad">\feed2</div>}

\feedback{\sc_reply1!=1 and \Delta2!=0 and \Delta3!=0 }{<div class ="euler_rep_bad ">
<ul class="euler_ul">
  <li>
    \hint_1  
  </li>
  <li>
    \hint_2
  </li>
</ul>
</div>}
%%%%% HELP %%%%%
\help{
 \aide
}
%%%%% HINT %%%%%
\hint{
<ul class="euler_ul">
  <li>
    \hint_1  
  </li>
  <li>
    \hint_2
  </li>
</ul>
}
%%% BLOC SOLUTION %%%
\solution{
<div class = "euler_quest_nobg">
\enonce
</div>
<div class ="euler_rep_good_nobg unbreakable" >
\soluce
</div>
}
