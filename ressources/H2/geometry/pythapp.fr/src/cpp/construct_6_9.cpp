target=06 07 08 09
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
#if defined TARGET_06 || defined TARGET_07 || defined TARGET_08
<div class="euler_quest">
\enonce0
</div>

\if{\reply1!=}{<div class="spacer">\reprise_rep</div>}
<div class="wims_scrollable">
<table class="tab_sol">
  <tr>
    <th >\th2</th>
    <th>\def_triangle</th>
  </tr>
  \for{k=1 to 3}
   {<tr>
     #if defined TARGET_06 || defined TARGET_07
     <th scope="row">\data_egalites[\mix[\k];1]</th>
     #endif
     #if defined TARGET_08
     <th scope="row">\liste_egalites[\k;1]</th>
     #endif
      <td>
        <fieldset class="euler_field">
         <legend> </legend>
        <ul class="wims_nopuce euler_ul_check">
          \for{n=1 to 3}
          {<li \if{\sc_reply1!=}{class="\checked[\k;\n]"}>
           \embed{reply\k,\n,\liste_sommets[\n] }
           \if {\sc_reply1!=}{<span class="\sigle[\k;\n]" title="\sigle_title[\k;\n]"></span>}
          </li>}
        </ul>
        </fieldset>
      </td>    
    </tr>
   }
</table>
</div>
#endif

#if defined TARGET_09
<div \if{\figure=1}{\if{\sc_reply1=}{class="grid-x grid-margin-x"}}>
  <div \if{\figure=1}{\if{\sc_reply1=}{class="cell small-12 medium-12 large-6"}}>
    <div class="euler_quest">
     \enonce0
    </div>
    <div class="\if{\sc_reply1=}{euler_answer}{\if{\sc_reply1=1}{euler_rep_good}{\if{\sc_reply1=0}{euler_rep_bad}{euler_rep_prec}}} ">
      <fieldset class="euler_field">
       <legend>\if{\sc_reply1=}{}{\reprise_rep}</legend>
        <ul class="wims_nopuce euler_ul_check">
          \for{n=1 to \tot}
          {<li \if{\sc_reply1!=}{class="\checked[\n]"}> 
            \embed{reply1,\n,\propo[\n;1]}
            \if {\sc_reply1!=}{<span class="\sigle[\n]" title="\sigle_title[\n]"></span>}
          </li>}
          </ul>
      </fieldset>
    </div>
  </div>
\if{\figure=1}
 {\if{\sc_reply1=}
   {<div class="cell small-12 medium-12 large-6" style="text-align:center">
     <div id="fig" >
      \fig_enonce
      \credits_JSX
     </div>
   </div>
 </div>
 }
}
#endif
}

%%%%% ANSWER %%%%%%
#if defined TARGET_06 || defined TARGET_07 || defined TARGET_08
\answer{}{\rep1;\data2[1;]}{type=radio}
\answer{}{\rep2;\data2[2;]}{type=radio}
\answer{}{\rep3;\data2[3;]}{type=radio}

\text{screply=\sc_reply1,\sc_reply2,\sc_reply3}
\text{repons=\reply1,\reply2,\reply3}

\for {r=1 to 3}
  {\text{ligne1=}
   \text{ligne2=}
   \text{ligne3=}
   \for {j=1 to 3}
    {\if{\data2[\r;\j] isitemof \repons[\r]}
      {\text{temp1=euler_radio_checked}
      \if{\screply[\r]=1}
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
     \text{ligne1=wims(append item \temp1 to \ligne1)}
     \text{ligne2=wims(append item \temp2 to \ligne2)}
     \text{ligne3=wims(append item \temp3 to \ligne3)}
    }
    \matrix{checked=\checked
    \ligne1}
    \matrix{sigle=\sigle
    \ligne2}
    \matrix{sigle_title=\sigle_title
    \ligne3}
}

#endif
#if defined TARGET_09
\answer{La réponse}{\goodrep;\psh}{type=checkbox}{option=split}

\text{screply=\sc_reply1}
\text{repons=\reply1}
\for {j=1 to \tot}
  {\if{\psh[\j] isitemof \repons}
    {\text{temp1=euler_box_checked}
     \if{\ind[\j]=1}
      {\text{temp2=oef_indgood tick}
       \text{temp3=\title_good}
      }
      {\text{temp2=oef_indbad cross}
       \text{temp3=\title_bad}
      } 
    }
    {\text{temp1=euler_box_nochecked}
     \if{\ind[\j]=1}
      {\text{temp2=oef_indforget forget}
       \text{temp3=\title_forget}
      }
      {\text{temp2=oef_indneutral}
       \text{temp3=0}
      } 
    }
   \text{checked=wims(append item \temp1 to \checked)}
   \text{sigle=wims(append item \temp2 to \sigle)}
   \text{sigle_title=wims(append item \temp3 to \sigle_title)}
  }
#endif


%%%%% HINT %%%%%
\hint{
<div class="indication">\titre_indic1</div>
<div>\indic1</div>
<div class="spacer indication">\titre_indic2</div>
<div>\indic2</div>
}
%%%%% SOLUTION %%%%%
\solution{
#if defined TARGET_06 || defined TARGET_07 ||  defined TARGET_08
 #if defined TARGET_06
  <div class="indication">\titre_indic1</div>
  <div>\indic1</div>
  <div class="spacer indication">\titre_indic2</div>
  <div>\indic2</div>
  <div class="spacer">
  <p>\sol_liaison</p>
   <table class="tab_sol">
    <tr>
     <th>\th2</th>
     <th>\th1</th>
    </tr>
    \for{i=1 to 3}{
      <tr>
       <td>
        <span class="oef_indgood">\data_egalites[\mix[\i];1]</span>
      </td>
      <td>
       \def_triangle <span class="oef_indgood">\liste_sommets[\mix[\i]]</span>
      </td>
     </tr>
       }
    </table>
  </div>
 #endif
 #if defined TARGET_07
\for{i=1 to 3}{
   <ul class="euler_ul wims_scrollable spacer">
     <li>\th2 n°\i&nbsp;:<br>
     <span class="oef_indgood">\def_triangle2</span> <span><span class="oef_indgood">\liste_sommets[\mix[\i]]</span>,</span>
     \sol1, 
     \if{\data_egalites[\mix[\i];2]=}
       {<span class="nowrap"><span class="oef_indgood">\data_egalites[\mix[\i];1]</span>.</span>}
       {\sol2<br>\data_egalites[\mix[\i];2]<br><span class="oef_indgood">\data_egalites[\mix[\i];1]</span>} 
     </li>
   </ul>
}
 #endif
 #if defined TARGET_08
\for{i=1 to 3}{
   <ul class="euler_ul wims_scrollable spacer">
     <li>\th2 n°\i&nbsp;:<br>
     <span class="oef_indgood">\def_triangle2</span> <span><span class="oef_indgood">\liste_sommets_sol[\i]</span>,</span>
     \sol1, 
     \if{\liste_egalites[\i;2]=}
       {<span class="nowrap"><span class="oef_indgood">\liste_egalites[\i;1]</span>.</span>}
       {\sol2<br>\liste_egalites[\i;2]<br><span class="oef_indgood">\liste_egalites[\i;1]</span>} 
     </li>
   </ul>
}
 #endif
#endif

#if defined TARGET_09
 \def_triangle <span class="nowrap">\liste_sommets[\config].</span>
<div class="grid-x grid-margin-x">
  <div class="cell small-12 small-order-2 medium-7 medium-order-1 large-8 large-order-1">
   
    <ul class="euler_ul wims_scrollable spacer">
     \for{i=1 to \tot}
     {
       <li>
        \if{\ind[\i]=1}
          {\if{\propo[\i;2]=}
            {\def_triangle <span class="nowrap"><span class="oef_indgood">\liste_sommets[\config]</span>,</span> \sol1, <span><span class="nowrap">\propo[\i;1]</span>.</span>}
            {\def_triangle <span class="nowrap"><span class="oef_indgood">\liste_sommets[\config]</span>,</span> \sol1, \sol2<br>\propo[\i;2]<br>\propo[\i;1]}
            <br>\sol3 <span class="oef_indgood">\propo[\i;1]</span> \sol4.
          } 
          { \sol3 <span class="oef_indbad">\propo[\i;1]</span> \sol5.
            \sol6 
            \if{\fsh[\psh[\i]-\truepick]<=\truecnt}{\liste_sommets[\autres_config[1]]}{\liste_sommets[\autres_config[2]]}
            \sol7 
            \if{\propo[\i;2]=}
              {\sol8}
              {\sol9<br>\propo[\i;2]<br>\propo[\i;1]} 
          }
       </li>
     }
   </ul>
  </div>
  
  <div class="cell small-12 small-order-1 medium-5  medium-order-2 large-4 large-order-2" style="text-align:center">
    <div id="fig" >
      \fig_enonce
      \credits_JSX
    </div>
  </div>
</div>
#endif
}
