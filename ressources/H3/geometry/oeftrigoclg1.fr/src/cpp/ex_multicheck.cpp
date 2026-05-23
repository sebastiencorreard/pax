target=05ReconTrRect3

#include "lang_title.inc"
#include "avant_header.inc"
#include "lang_descobs.inc"

#include "avant_css.inc"

%%%% DATA
#include "data_triangle.inc"



%%%%% Les cotés 

\text{Cat1=randint(1,2)=1?\Sommet\Hyp[1]:\Hyp[1]\Sommet}
\text{Cat2=randint(1,2)=1?\Sommet\Hyp[2]:\Hyp[2]\Sommet}

\text{NomAngle1=randint(1,2)=1?\Sommet\Hyp[1]\Hyp[2]:\Hyp[2]\Hyp[1]\Sommet}
\text{NomAngle2=randint(1,2)=1?\Sommet\Hyp[2]\Hyp[1]:\Hyp[1]\Hyp[2]\Sommet}

\matrix{ListeCotes=\Hyp[1]\Hyp[2]
\Cat1
\Cat2
}



%%%%% TEXTES DE L'EXERCICE DANS LA LANGUE %%%%%
#include "lang.inc"
%%%% FIGURES JSXGRAPH
#include "data_JsxGraph.inc"


%%%%%%%%%HINT %%%%%%%%%%
#include "lang_hint.inc"


\text{ListeReponses=\hypot,
\caa \(\widehat{\NomAngle1}\),\coa \(\widehat{\NomAngle2}\),
\caa \(\widehat{\NomAngle2}\),\coa \(\widehat{\NomAngle1}\)
}

\matrix{NumeroReponses=1
2,3
4,5
}

\text{OrdreCotes=shuffle(3)}

\matrix{shf=shuffle(5)
shuffle(5)
shuffle(5)}

\matrix{liste=\ListeReponses[\shf[1;]]
\ListeReponses[\shf[2;]]
\ListeReponses[\shf[3;]]}

\matrix{numrep=}
\for{bloc=1 to 3}
  {\text{line=}
   \text{num=\NumeroReponses[\OrdreCotes[\bloc];]}
   \integer{nb=wims(itemcnt \num)}
   \for{col=1 to \nb}
     {\text{line=wims(append item position(\num[\col],\shf[\bloc;]) to \line)}}
   \matrix{numrep=\numrep
   \line}
  }

\matrix{checked=}
\text{sc_rep=}
%%%%%%%%%%%%%%%%%%%%%
%%%%% STATEMENT %%%%%
%%%%%%%%%%%%%%%%%%%%%

\statement{

<div class="grid-x grid-margin-x">
 <div class="cell small-12 large-6 medium-6">
   <div class="euler_quest"> 
    \if{1 notin \confparm1}
    {<p>\enonce1</p>
     \if{\sc_reply1=}{<p class="quest">\consigne1</p>}
     \FigEnonce}
    {<p>\enonce1</p>
     \if{\sc_reply1=}{<p class="quest">\consigne1</p>}}
   </div>
 </div>
 
 <div class="cell medium-6 small-12 flex-dir-column">
   \for{c=1 to 3}{
   <div class ="flex-child-auto \if{\sc_reply1=}{euler_answer}{\if{\sc_rep[\c]=1}{euler_rep_good}{\if{\sc_rep[\c]=0}{euler_rep_bad}{euler_rep_prec}}}">
     \if{\sc_reply1!=}{<p>\phrase</p>}
     <fieldset class="euler_field">
      <legend>\quest[1] [\ListeCotes[\OrdreCotes[\c];1]] \quest[2]</legend>
        <ul class="wims_nopuce euler_ul_check">
         \for{n=1 to 5}{<li \if{\sc_reply1 !=}{\if { \n isitemof \checked[\c;]}{class="euler_box_checked"}{class="euler_box_nochecked"}}> \embed{reply\c,\n,\liste[\c;\n]}</li>}
        </ul>
     </fieldset>
   </div>}
 </div>
 
</div>
}

%%%%%%%%%%%%%%%%%%
%%%%% ANSWER %%%%%
%%%%%%%%%%%%%%%%%%
\answer{}{\numrep[1;];\shf[1;]}{type=checkbox}{option=split }
\answer{}{\numrep[2;];\shf[2;]}{type=checkbox}{option=split }
\answer{}{\numrep[3;];\shf[3;]}{type=checkbox}{option=split }

%%%%%%%%%%%%%%%%%%%%
%%%%% FEEDBACK %%%%%
%%%%%%%%%%%%%%%%%%%%

\matrix{rep=\reply1
\reply2
\reply3}

\text{sc_rep=\sc_reply1,\sc_reply2,\sc_reply3}


\matrix{checked=}
\for{i=1 to 3}
  {\text{ligne=}
   \integer{nbrep=wims(itemcnt \rep[\i;])}
   \for {k=1 to \nbrep}
    {\text{posi=position(\rep[\i;\k],\shf[\i;])}
     \text{ligne=wims(append item \posi to \ligne)}
    }
    \matrix{checked=\checked
    \ligne}
   } 
    

%%%%%%%%%%%%%%%%
%%%%% HINT %%%%%
%%%%%%%%%%%%%%%%

\hint{
  <div class="grid-x grid-margin-x">
    <div class="cell small-12 medium-12 large-8">
       <div class="indication">\hint_title2</div>
       <div>\hint_text2</div>
    </div>
    <div class="cell small-12 medium-12 large-4">
      \FigIndic
    </div>
  </div>
}

%%%%%%%%%%%%%%%%%%%%
%%%%% SOLUTION %%%%%
%%%%%%%%%%%%%%%%%%%%

\solution{

<div class ="euler_quest_nobg">
 <div class="grid-x grid-margin-x">
  <div class="cell small-12 \if{2 notin \confparm1}{medium-6 large-6}{medium-12 large-12}">
   <p>\enonce2</p>
   <p class="quest">\consigne2</p>
  </div>
  \if{2 notin \confparm1}{
    <div class="cell small-12 medium-5 large-4">
      \FigSol
    </div>
    }
  </div>
</div>
  
<div class ="euler_rep_good_nobg">
  \SolDetails
</div>
}
