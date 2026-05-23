target=04ReconTrRect1 04ReconTrRect2

#include "lang_title.inc"
#include "avant_header.inc"
#include "lang_descobs.inc"

#include "avant_css.inc"

%%%%% DATA
#include "data_triangle.inc"

#if defined TARGET_04ReconTrRect1

%%%%% CHOIX ALEATOIRES NOMS DES COTES
\text{choix1=randitem(\Hyp[1]\Hyp[2],\Hyp[2]\Hyp[1])}
\text{choix2=randitem(\Hyp[1]\Sommet,\Sommet\Hyp[1])}
\text{choix3=randitem(\Hyp[2]\Sommet,\Sommet\Hyp[2])}

%%%%% REPONSES ET PROPOSITIONS

\text{Bon_rep=\([\choix1]\),\([\choix2]\),\([\choix3]\)}
\text{propo=wims(shuffle \Bon_rep)}

#endif

%%%%% VARIABLES POUR ANALYSES SOUS CONDITIONS

\text{test1=}
\text{test2=}
\text{test3=}

%%%%% FIGURES JSXGRAPH
#include "data_JsxGraph.inc"


%%%%% TEXTES DE L'EXERCICE DANS LA LANGUE %%%%%
#include "lang.inc"

%%%%% HINT / HELP %%%%%%%
#include "lang_hint.inc"
#include "lang_help.inc"


%%%%%%%%%%%%%%%%%%%%%
%%%%% STATEMENT %%%%%
%%%%%%%%%%%%%%%%%%%%%

\statement{
<div class="euler_quest">
  <div class="grid-x grid-margin-x">
    <div class=" cell small-12 \if{1 notin \confparm1}{medium-6 large-6}{medium-12 large-12}">
      <p>\phrase1</p>
      <p class="quest">\phrase2</p>
    </div>
    \if{1 notin \confparm1}{
    <div class="cell small-12 medium-6 large-6">
      \FigEnonce
    </div>
    }
  </div>
</div>

#if defined TARGET_04ReconTrRect1

<div class =\if{\test1=}{"euler_answer"}{\if{\test1=0}{"euler_rep_bad"}{"euler_rep_good"}}>
  \quest1 \embed{reply1,40x25x1}
</div>
<div class =\if{\test2=}{"euler_answer"}{\if{\test2=0}{"euler_rep_bad"}{"euler_rep_good"}}>
 \quest2 \embed{reply2,40x25x1}
</div>
<div class =\if{\test3=}{"euler_answer"}{\if{\test3=0}{"euler_rep_bad"}{"euler_rep_good"}}>
 \quest3 \embed{reply3,40x25x1}</div> 
</div>

#endif

#if defined TARGET_04ReconTrRect2

<div class =\if{\test1=}{"euler_answer"}{\if {\test1=1}{"euler_rep_good"}{\if {\test1=0}{"euler_rep_bad"}{"euler_rep_prec"}}}>
 <label for="reply1">\quest1</label>
 <span class="nowrap \if{\test1=}{}{\if {\test1=1}{oef_indgood}{\if{\test1=0}{oef_indbad}{oef_indprec}}}">[\embed{r1,1}].</span>
</div>
<div class =\if{\test1=}{"euler_answer"}{\if {\test2=1}{"euler_rep_good"}{\if {\test2=0}{"euler_rep_bad"}{"euler_rep_prec"}}}>  
 <label for="reply2">\quest2</label>
 <span class="nowrap \if{\test2=}{}{\if {\test2=1}{oef_indgood}{\if{\test2=0}{oef_indbad}{oef_indprec}}}">[\embed{r2,1}].</span>
</div>
<div class =\if{\test1=}{"euler_answer"}{\if {\test3=1}{"euler_rep_good"}{\if {\test3=0}{"euler_rep_bad"}{"euler_rep_prec"}}}>
 <label for="reply3">\quest3</label>
  <span class="nowrap \if{\test3=}{}{\if {\test3=1}{oef_indgood}{\if{\test3=0}{oef_indbad}{oef_indprec}}}">[\embed{r3,1}].</span>
</div>

#endif
}

%%%%%%%%%%%%%%%%%%
%%%%% ANSWER %%%%%
%%%%%%%%%%%%%%%%%%

#if defined TARGET_04ReconTrRect1

\answer{}{\Bon1;\propo[1;]}{type=dragfill}{option=shuffle noanalyzeprint}
\answer{}{\Bon2;\propo[2;]}{type=dragfill}{option=shuffle noanalyzeprint}
\answer{}{\Bon3;\propo[3;]}{type=dragfill}{option=shuffle noanalyzeprint}

\text{test1=\Bon1 issametext \Bon_rep[1] ? 1:0}
\text{test2=\Bon2 issametext \Bon_rep[2] ? 1:0}
\text{test3=\Bon3 issametext \Bon_rep[3] ? 1:0}


\condition{\cond1}{\test1=1}
\condition{\cond2}{\test2=1}
\condition{\cond3}{\test3=1}

#endif

#if defined TARGET_04ReconTrRect2

\answer{}{\rep1}{type=raw}{option=noanalyzeprint}
\answer{}{\rep2}{type=raw}{option=noanalyzeprint}
\answer{}{\rep3}{type=raw}{option=noanalyzeprint}

\text{rep1=wims(nospace \reply1)}
\text{rep2=wims(nospace \reply2)}
\text{rep3=wims(nospace \reply3)}

\text{rep1_net=wims(upper \rep1)}
\text{rep2_net=wims(upper \rep2)}
\text{rep3_net=wims(upper \rep3)}

\if{(\rep1 issamecase \Hyp[1]\Hyp[2]) or (\rep1 issamecase \Hyp[2]\Hyp[1])}
 {\text{test1=1}}
 {\if{(\rep1_net issamecase \Hyp[1]\Hyp[2]) or (\rep1_net issamecase \Hyp[2]\Hyp[1])}
  {\text{test1=0.5}}
  {\text{test1=0}}
 }

\if{(\rep2 issamecase \Hyp[1]\Sommet) or (\rep2 issamecase \Sommet\Hyp[1])}
 {\text{test2=1}}
 {\if{(\rep2_net issamecase \Hyp[1]\Sommet) or (\rep2_net issamecase \Sommet\Hyp[1])}
  {\text{test2=0.5}}
  {\text{test2=0}}
 }

\if{(\rep3 issamecase \Hyp[2]\Sommet) or (\rep3 issamecase \Sommet\Hyp[2])}
 {\text{test3=1}}
 {\if{(\rep3_net issamecase \Hyp[2]\Sommet) or (\rep3_net issamecase \Sommet\Hyp[2])}
  {\text{test3=0.5}}
  {\text{test3=0}}
 }

\text{ens_sommets=wims(lower \Triangle)}
\text{ens_sommets=wims(append item \Triangle to \ens_sommets)}


\integer{nb1=wims(charcnt \rep1)}
\integer{nb2=wims(charcnt \rep2)}
\integer{nb3=wims(charcnt \rep3)}
\if{\nb1=2 and \nb2= 2 and \nb3=2}{\integer{nb_ok=1}}{\integer{nb_ok=0}}

\text{rev1=wims(text reverse \rep1)}
\text{rev2=wims(text reverse \rep2)}
\text{rev3=wims(text reverse \rep3)}

\if{\rev1 issametext \rep1 and \nb1=2}{\text{sing1=1}}{\text{sing1=0}}
\if{\rev2 issametext \rep2 and \nb2=2}{\text{sing2=1}}{\text{sing2=0}}
\if{\rev3 issametext \rep3 and \nb3=2}{\text{sing3=1}}{\text{sing3=0}}
\if{\sing1=1 or \sing2=1 or \sing3=1}{\text{sing=1}}{\text{sing=0}}

\if{\rep1_net issamecase \Hyp[1]\Sommet or \rep1_net issamecase \Sommet\Hyp[1] or \rep1_net issamecase \Hyp[2]\Sommet or \rep1_net issamecase \Sommet\Hyp[2]}
 {\text{err_hypo=1}}
 {\text{err_hypo=0}}

\if{(\rep2_net issamecase \Hyp[2]\Sommet or \rep2_net issamecase \Sommet\Hyp[2]) and
 (\rep3_net issamecase \Hyp[1]\Sommet or \rep3_net issamecase \Sommet\Hyp[1])}
 {\text{confusion=1}}
 {\text{confusion=0}}

\text{autres=}
\text{autres1=wims(text remove \ens_sommets in \rep1)}
\text{autres2=wims(text remove \ens_sommets in \rep2)}
\text{autres3=wims(text remove \ens_sommets in \rep3)}
\text{autres=wims(append word \autres1 to \autres)}
\text{autres=wims(append word \autres2 to \autres)}
\text{autres=wims(append word \autres3 to \autres)}
\text{autres=wims(nospace \autres)}
\integer{nb_autres=wims(charcnt \autres)}

\if{\rep1=\rep2 or \rep1=\rev2}
  {\if{\rep1=\rep3 or \rep1=\rev3}
    {\text{rep_id=3}}
    {\text{rep_id=2}}
  }
  {\if{\rep2=\rep3 or \rep2=\rev3}
   {\text{rep_id=2}}
   {\text{rep_id=0}}
  }

\condition{}{\test1>=0.5}{option=hide}
\condition{\cond1}{\test1=1}
\condition{}{\test2>=0.5}{option=hide}
\condition{\cond2}{\test2=1}
\condition{}{\test3>=0.5}{option=hide}
\condition{\cond3}{\test3=1}

#endif

%%%%%%%%%%%%%%%%%%%%
%%%%% FEEDBACK %%%%%
%%%%%%%%%%%%%%%%%%%%

#if defined TARGET_04ReconTrRect1

\feedback{\Sommet isin \reply1}{<div class="wims_msg warning">\feed1</div>}

\feedback{(\Hyp[1] isin \reply3) and (\Hyp[2] isin \reply2)}{<div class="wims_msg warning">\feed2</div>}

#endif


#if defined TARGET_04ReconTrRect2

\feedback{\test1=0.5}
{<div class="wims_msg warning">\feed3</div>}

\feedback{\test2=0.5}
{<div class="wims_msg warning">\feed4</div>}

\feedback{\test3=0.5}
{<div class="wims_msg warning">\feed5</div>}
 
\feedback{\err_hypo=1}{<div class="wims_msg warning">\feed1</div>}

\feedback{\confusion=1}
 {<div class="wims_msg warning">\feed2</div>}

\feedback{\nb_autres>0 or \nb_ok=0 or \sing=1}
 {<div class="wims_msg warning">\feed6</div>}

\feedback{\rep_id>0}
 {<div class="wims_msg warning">\(\rep_id\) \feed7</div>}

#endif


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

%%%%%%%%%%%%%%%%
%%%%% HELP %%%%%
%%%%%%%%%%%%%%%%
\help{
  \aide
}

%%%%%%%%%%%%%%%%%%%%
%%%%% SOLUTION %%%%%
%%%%%%%%%%%%%%%%%%%%

\solution{

<div class ="euler_rep_good_nobg">
  <div class="grid-x grid-margin-x">
    <div class="cell small-12 \if{2 notin \confparm1}{medium-6 large-6}{medium-12 large-12}">
      \SolDetails
    </div>
    \if{2 notin \confparm1}{
    <div class="cell small-12 medium-6 large-6">
      \FigSol
    </div>
    }
  </div>
</div>
}
