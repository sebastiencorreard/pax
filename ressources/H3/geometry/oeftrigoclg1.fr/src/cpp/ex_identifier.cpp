target=07IdentifierLigneTrigo1 08IdentifierLigneTrigo2 09DonnerLigneTrigo

#include "lang_title.inc"
#include "avant_header.inc"
#include "lang_descobs.inc"
\text{\etap1=}
\text{\etap2=}
#include "avant_css.inc"

%%%% DATA
#include "data_triangle.inc"

#if defined TARGET_07IdentifierLigneTrigo1
\text{shf=shuffle(3)}
\text{listechoix=\BonsCotes[\shf;1]}
\text{posirep=position(\BonsCotesSol[1],\shf),position(\BonsCotesSol[2],\shf)}
#endif

#if defined TARGET_09DonnerLigneTrigo
\text{ListeExpressions=\(\frac{\NomNum}{\NomDen}\),\(\frac{\NomDen}{\NomNum}\),\(\NomNum \times \NomDen\)}

\text{shf=shuffle(3)}
\text{listechoix=\ListeExpressions[\shf]}
\text{posirep=position(1,\shf)}

%%%%%% EXERCICE A ETAPES
\matrix{etap= r1
r2
 }
\nextstep{\etap}

\text{rep1=}
#endif

#if defined TARGET_07IdentifierLigneTrigo1 || defined TARGET_09DonnerLigneTrigo
%%%%% RECUPERATION CASES COCHEES
\text{checked=}
#endif

%%%%% TEXTES DE L'EXERCICE DANS LA LANGUE %%%%%
#include "lang.inc"

%%%% FIGURES JSXGRAPH

#include "data_JsxGraph.inc"

%%%%%%%%% HINT %%%%%%%%%
#include "lang_hint.inc"

%%%%%%%%%%%%%%%%%%%%%
%%%%% STATEMENT %%%%%
%%%%%%%%%%%%%%%%%%%%%


\statement{
<div class="euler_quest">
\if{1 notin \confparm1}{
 <div class="grid-x grid-margin-x">
  <div class="cell small-12 large-6 medium-6">
   <div>
#if defined TARGET_09DonnerLigneTrigo
    <p class="quest">
     \enonce0
     <br>
    \if{\conf3=1}{\introetap}
    </p>
#endif
    <p>\enonce1</p>
    <p>\enonce2</p>
   </div>
  </div>
  <div class="cell small-12 large-6 medium-6">
   \FigEnonce
  </div>
  <div class="cell small-12 large-12 medium-12">
#if defined TARGET_07IdentifierLigneTrigo1 || defined TARGET_08IdentifierLigneTrigo2
    <p class="quest">\enonce3</p>
#endif
#if defined TARGET_09DonnerLigneTrigo
    <p class="quest">\etap1 - \enonce3</p>
#endif
  </div>
 </div>
}
{
 <div>
#if defined TARGET_09DonnerLigneTrigo
  <p class="quest">
     \enonce0
     <br>
    \introetap
  </p>
#endif
  <p>\enonce1</p>
  <p>\enonce2</p>
#if defined TARGET_07IdentifierLigneTrigo1 || defined TARGET_08IdentifierLigneTrigo2
    <p class="quest">\enonce3</p>
#endif
#if defined TARGET_09DonnerLigneTrigo
    <p class="quest">\etap1 - \enonce3</p>
#endif
 </div>
}
</div>

#if defined TARGET_07IdentifierLigneTrigo1
<div class=\if{\sc_reply1=}{"euler_answer"}{\if{\sc_reply1=1}{"euler_rep_good"}{\if{\sc_reply1=0}{"euler_rep_bad"}{"euler_rep_prec"}}}>
  \if{\sc_reply1!=}{<p>\phrase</p>}
  <fieldset class="euler_field">
   <legend>\quest1</legend>
    <ul class="wims_nopuce euler_ul_check">
     \for{n=1 to 3}{<li \if{\sc_reply1 !=}{\if {\checked[\n]=1}{class="euler_box_checked"}{class="euler_box_nochecked"}}> \embed{reply1,\n,\listechoix[\n]}</li>}
    </ul>
  </fieldset>
</div>
<div class=\if{\sc_reply2=}{"euler_answer"}{\if{\sc_reply2=1}{"euler_rep_good"}{"euler_rep_bad"}}>
 <label for="reply2">\quest2</label> \embed{reply2} \quest3
</div>
#endif

#if defined TARGET_08IdentifierLigneTrigo2
<div class=\if{\sc_reply1=}{"euler_answer"}{\if{\sc_reply1=1}{"euler_rep_good"}{"euler_rep_bad"}}>
 \if{\sc_reply1!=}{<p>\phrase</p>}
 \if{\sc_reply1=}
   {<label for="reply1">\quest2</label> \embed{reply1,1} \quest3}
   {\quest2 <span class="\if{\sc_reply1=1}{oef_indgood}{oef_indbad}">\reply1</span> \quest3}

</div>
#endif

# if defined TARGET_09DonnerLigneTrigo
\if{\step = 1}
{
<div class="\if{\conf3=1}{\if {\sc_reply1=0}{euler_rep_bad}{euler_answer}}{euler_answer}">
  \if{\conf3=1 and \sc_reply1=0}{<p>\phrase</p>}
   <label for="reply1">\quest2</label> \embed{reply1} \quest3
</div>
}
\if{\step >1 }
{
<div class =\if{\conf3!=4}{\if{\sc_reply1=1}{"euler_rep_good"}{"euler_rep_bad"}}{\if{\step>2}{\if{\sc_reply1=1}{"euler_rep_good"}{"euler_rep_bad"}}{"euler_answer"}}>
 <p>\phrase</p>
  \quest2 <span class="\if {\conf3!=4}{\if{\sc_reply1=1}{oef_indgood}{oef_indbad}}{oef_indneutral}">\reply1</span> \quest3
  \if{\conf3!=4}{<p>\if {\sc_reply1=1}{<span class="oef_indgood">\rep_exacte</span>}{<span class="oef_indbad">\rep_fausse</span>}</p>}
  \if{\conf3=2 and \sc_reply1!=1}{<p><strong>\la_sol</strong> \quest2 <span class="oef_indgood">\trigo[1;\typeLigne]</span> \quest3</p>}
</div>
}

\if{\step >=2 }
{
<div class="euler_quest">
 <p class="quest">\etap2 - \enonce4</p>
</div>
}
\if{\step =2 }
{
<div class ="euler_answer">
 <fieldset class="euler_field">
   <legend>\quest4 <strong>\trigo[2;\typeLigne] \((\widehat{\NomAngle})\)</strong> \quest5</legend>
    <ul class="wims_nopuce euler_ul_check">
      \for{e=1 to 3}{<li> \embed{reply2,\e,\listechoix[\e]}</li>}
    </ul>
 </fieldset>
</div>
}

\if{\step >2 }
{
<div class =\if{\sc_reply2=1}{"euler_rep_good"}{"euler_rep_bad"}>
 <p>\phrase</p>
 \quest4 <strong>\trigo[2;\typeLigne] \((\widehat{\NomAngle})\)</strong> \quest5
 <ul class="wims_nopuce euler_ul_check">
   \for{ee=1 to 3}
    {<li \if {\checked[\ee]=1}{class="euler_radio_checked"}{class="euler_radio_nochecked"}>
      <span class="\if{\checked[\ee]=1 and \conf3!=4}{\if {\sc_reply2=1}{oef_indgood}{oef_indbad}}">\listechoix[\ee]</span>
     </li>}
 </ul>

</div>

}
#endif

}

%%%%%%%%%%%%%%%%%%
%%%%% ANSWER %%%%%
%%%%%%%%%%%%%%%%%%

#if defined TARGET_07IdentifierLigneTrigo1
\answer{}{\posirep;\shf}{type=checkbox}{option=split}
\answer{}{\typeLigne;\trigo[1;]}{type=menu}{option=shuffle}

\text{rep1=\reply1}
\integer{nb_prop=wims(itemcnt \shf)}

\text{checked=}
\for {k=1 to \nb_prop}
  {\if{\shf[\k] isitemof \rep1}
    {\text{temp=1}}
    {\text{temp=0}}
   \text{checked=wims(append item \temp to \checked)}
  }
#endif

#if defined TARGET_08IdentifierLigneTrigo2
\answer{}{\typeLigne;\trigo[1;]}{type=menu}{option=shuffle }
#endif

#if defined TARGET_09DonnerLigneTrigo
\answer{\etap1&nbsp;:}{\typeLigne;\trigo[1;]}{type=menu}{option=shuffle \opt}
\answer{\etap2&nbsp;:}{\posirep;\shf}{type=radio}{option=nonstop}

\text{rep2=\reply2}
\integer{nb_prop=wims(itemcnt \shf)}

\text{checked=}
\for {kk=1 to \nb_prop}
  {\if{\shf[\kk] isitemof \rep2}
    {\text{temp=1}}
    {\text{temp=0}}
   \text{checked=wims(append item \temp to \checked)}
  }

#endif

%%%%%%%%%%%%%%%%
%%%%% HINT %%%%%
%%%%%%%%%%%%%%%%
\hint{
  <div class="grid-x grid-margin-x">
    <div class="cell small-12 medium-12 large-8">
       <div class="indication">\hint_title4</div>
         \hint_text4
       <div class="indication">\hint_title3</div>
       <div>\hint_text3</div>
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
  <div class="cell small-12 \if{2 notin \confparm1}{medium-7 large-8}{medium-12 large-12}">
   <p>\enonce1</p>
   <p>\enonceSol2</p>

#if !defined TARGET_08IdentifierLigneTrigo2
   <p> \enonceSol3</p>
#endif
  </div>
  \if{2 notin \confparm1}{
  <div class="cell small-12 medium-5 large-4">
    \FigSol
  </div>}
 </div>
</div>
<div class ="euler_rep_good_nobg">
  <p>\SolDetails1</p>
  <p>\SolDetails2</p>
  <p>\if{\typeLigne=3}{
      \(\trigo[2;\typeLigne](\widehat{\NomAngle})=
      \frac{\text{\long \NUM[6]}\;\widehat{\text{\NomAngle}}}{\text{\long \DEN[6]}\;\widehat{\text{\NomAngle}}}\)}
      {\(\trigo[2;\typeLigne](\widehat{\NomAngle})=
      \frac{\text{\long \NUM[6]}\;\widehat{\text{\NomAngle}}}{\text{\long \DEN[6]}}\)}</p>
  <p>\(\trigo[2;\typeLigne](\widehat{\NomAngle})=\frac{\NomNum}{\NomDen}\)</p>
  <p>\(\trigo[2;\typeLigne](\widehat{\NomAngle})=\frac{\num_t}{\den_t}\)</p>
</div>
}
