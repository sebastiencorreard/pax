target=01a 01b 02a 02b 03a 03b 04a 04b 05a 05b
#include "lang_title.inc"
#include "avant_header.inc"
#include "lang_obsdesc.inc"
#include "avant_css.inc"
#include "data.inc"
#include "fig.inc"

#include "lang_fr.inc"
#include "lang_hint_fr.inc"
#include "lang_help_fr.inc"

%%%%% STATEMENT %%%%%%%
\statement{
#if defined TARGET_01a || defined TARGET_02a || defined TARGET_03a || TARGET_04a || defined TARGET_05a
  <div class="grid-x grid-margin-x">
    <div class="cell small-12 medium-6 large-6">
#endif
     <div class="euler_quest"> 
       \enonce1 <br class="spacer">
       <span class="quest">\enonce0</span>
     </div>
      #if defined TARGET_01a || defined TARGET_01b
        <div class =\if{\sc_reply1=}{"euler_answer"}{\if{\sc_reply1=1}{"euler_rep_good"}{"euler_rep_bad"}}>
          \if{\sc_reply1!=}{\reprise_rep}
          <fieldset class="euler_field">
           <legend> </legend>
            <ul class="wims_nopuce euler_ul_check">
              \for{n=1 to 3}
              {<li \if{\sc_reply1!=}{class="\checked[\n]"}>
               \embed{reply1,\n,\propo[\n] }
               \if {\sc_reply1!=}{<span class="\sigle[\n]" title="\sigle_title[\n]"></span>}
              </li>}
            </ul>
          </fieldset>
      #else
        <div class =\if{\sc_reply1=}{"euler_answer"}{"\sigle"}>
          \if{\sc_reply1!=}{\reprise_rep}
          <label for="reply1">\enonce_saisie</label> 
          <span class="nowrap">\embed{r1,10}.</span>
      #endif
        \if{\sc_reply1!=}
         {\if {\sc_reply1=1}
          {<br><span class="oef_indgood">\rep_exacte</span>}
          {<p><span class="oef_indbad">\rep_fausse</span> \enonce1_cor</p>}
         }
        </div>
#if defined TARGET_01a || defined TARGET_02a || defined TARGET_03a || TARGET_04a || defined TARGET_05a
    </div>
    <div class="cell small-12 medium-6 large-6" style="text-align:center">
      \fig_enonce
      \credits_JSX
    </div>
  </div>
#endif
}

%%%%% ANSWER %%%%%%%

#if defined TARGET_01a || defined TARGET_01b
  \answer{}{\solution1;\shuf}{type=radio}
  
  \for {j=1 to 3}
  {\if{\shuf[\j] isitemof \reply1}
    {\text{temp1=euler_radio_checked}
    \if{\sc_reply1=1}
      {\text{temp2=oef_indgood tick}
       \text{temp3=\title_good}
      }
      {\text{temp2=oef_indbad cross}
       \text{temp3=\title_bad}
      }
    }
    {\text{temp1=euler_radio_nochecked}
     \text{temp2=oef_indneutral}
     \text{temp3=0}
    }
    \text{checked=wims(append item \temp1 to \checked)}
    \text{sigle=wims(append item \temp2 to \sigle)}
    \text{sigle_title=wims(append item \temp3 to \sigle_title)}
 }
 
#else
  \answer{}{\solution1}{type=formal}
  
  \if{\sc_reply1=1}
   {\text{sigle=euler_rep_good tick}}
   {\text{sigle=euler_rep_bad cross}}
#endif

#if !defined TARGET_01b
%%%%%  HELP %%%%% 
\help{\aide}
#endif

%%%%%  HINT %%%%%
\hint{

#if defined TARGET_01a || defined TARGET_01b
\indic1
#endif
#if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b || defined TARGET_04a || defined TARGET_04b || defined TARGET_05a || defined TARGET_05b
<div class="indication">\titre_indic2</div>
<div class="spacer">\indic2</div>
#endif
#if defined TARGET_04a || defined TARGET_04b || defined TARGET_05a || defined TARGET_05b
<div class="spacer indication"><br class="spacer">\titre_indic3</div>
<div >\indic3</div>
#endif
#if defined TARGET_03a || defined TARGET_03b || defined TARGET_05a || defined TARGET_05b
<div class="spacer indication"><br class="spacer">\titre_rem</div>
<div >\rem</div>
#endif
}


%%%%% FEEDBACK %%%%%
#include "lang_feed_fr.inc"

#if defined TARGET_01a || defined TARGET_01b 
\feedback{\sc_reply1!=1}{<div class="wims_msg warning">\retour_sommet_hyp</div>}
#endif

#if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b ||  defined TARGET_04a || defined TARGET_04b ||  defined TARGET_05a || defined TARGET_05b
\feedback{\sc_reply1!=1 and (sqrt isin \reply1) and (i isin \reply1)}{<div class="wims_msg warning">\err_rac</div>}
\feedback{\sc_reply1!=1 and \reply1<=0 and (i notin \reply1) and (sqrt notin \reply1)}{<div class="wims_msg warning">\grand_pos</div>}

#endif 
#if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b
\feedback{\sc_reply1!=1 and \reply1=sqrt(\solution1)}{<div class="wims_msg warning">\confusion_long</div>}
#endif 
#if defined TARGET_04a || defined TARGET_04b || defined TARGET_05a || defined TARGET_05b
\feedback{\sc_reply1!=1 and \reply1=(\solution1)^2}{<div class="wims_msg warning">\confusion_aire</div>}
#endif
#if defined TARGET_02a || defined TARGET_02b
\feedback{\sc_reply1!=1 and \reply1>0 and (\reply1<=\A_B or \reply1<=\A_C)}{<div class="wims_msg warning">\retour_aire</div>}
#endif
#if defined TARGET_03a || defined TARGET_03b
\feedback{\sc_reply1!=1  and \reply1>=\A_Hyp}{<div class="wims_msg warning">\retour_aire</div>}
#endif
#if defined TARGET_04a || defined TARGET_04b
\feedback{\sc_reply1!=1 and \reply1>0 and (\reply1<=sqrt(\A_B) or \reply1<=sqrt(\A_C))}{<div class="wims_msg warning">\retour_long</div>}
#endif
#if defined TARGET_05a || defined TARGET_05b
\feedback{\sc_reply1!=1  and \reply1>=sqrt(\A_Hyp)}{<div class="wims_msg warning">\retour_long</div>}
#endif

%%%%% BLOC SOLUTION %%%%%

\solution{
<div class="grid-x grid-margin-x">
  <div class="cell small-12 medium-12 large-6">
    <div class ="euler_quest_nobg">
      <p>\enonce1_sol</p>
      \enonce_saisie_sol
    </div>
    <div class ="euler_rep_good_nobg">
    \sol_sol1
    </div>
  </div>
  <div class="cell small-12 medium-12 large-6" style="text-align:center">
    \fig_sol
    \credits_JSX
  </div>
</div>
}
