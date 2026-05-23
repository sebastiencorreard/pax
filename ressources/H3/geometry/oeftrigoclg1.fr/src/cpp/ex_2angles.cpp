target=10DeuxMesures

#include "lang_title.inc"
#include "avant_header.inc"
#include "lang_descobs.inc"

#include "avant_css.inc"

%%%% DATA
#include "data_triangle.inc"

\integer{NumSol1=\typeLigne*2-1}
\integer{NumSol2=\typeLigne*2}
\text{Sol1=\NumSol1,\NumSol2}
\text{shf=shuffle(6)}
\text{listechoix=\ListeLignesTrigo[\shf]}
\text{posirep=position(\NumSol1,\shf),position(\NumSol2,\shf)}

\matrix{perm=\Cat2,\Hyp[1]\Hyp[2]
\Cat1,\Hyp[1]\Hyp[2]
\Cat2,\Cat1}

\matrix{rang=1,1
1,1
1,2
}

\text{elem=\perm[\typeLigne;1],\perm[\typeLigne;2]}
\matrix{propo=\(\frac{\elem[1]}{\elem[2]}\),\(\frac{\elem[2]}{\elem[1]}\),\(\elem[1] \times \elem[2]\)}
\text{shf2=shuffle(3)}
\text{listepropo2=\propo[\shf2]}

\text{posirep2=position(\rang[\typeLigne;1],\shf2)}
\text{shf3=shuffle(3)}
\text{listepropo3=\propo[\shf3]}

\text{posirep3=position(\rang[\typeLigne;2],\shf3)}

%%% ETAPES
\matrix{etap=r1
r2,r3
r4,r5
}
\nextstep{\etap}


%%%%% RECUPERATION CASES COCHEES
\text{checked1=}
\text{checked2=}
\text{checked3=}
\text{rep1=}
\text{rep1good=}
\text{rep2=}
\text{rep2good=}
\text{rep3=}
\text{rep3good=}


%%%%% QUESTION ANGLE
\text{verif4=}
\text{verif5=}
\text{rep4_t=}
\text{rep5_t=}

%%%%% TEXTES DE L'EXERCICE DANS LA LANGUE %%%%%
#include "lang.inc"

%%%% FIGURES JSXGRAPH

\integer{Val_Inf=floor(\angle)}
\integer{Val_Sup=\Val_Inf+1}
\real{Val_Med=(\Val_Sup+\Val_Inf)/2}
\text{Val_Inf_t=wims(replace internal . by , in \Val_Inf)}
\text{Val_Sup_t=wims(replace internal . by , in \Val_Sup)}
\text{Val_Med_t=wims(replace internal . by , in \Val_Med)}
\real{Borne_Inf=\Val_Inf-0.3}
\real{Borne_Sup=\Val_Sup+0.3}

\integer{Val_Inf2=floor(\angle2)}
\integer{Val_Sup2=\Val_Inf2+1}
\real{Val_Med2=(\Val_Sup2+\Val_Inf2)/2}
\text{Val_Inf2_t=wims(replace internal . by , in \Val_Inf2)}
\text{Val_Sup2_t=wims(replace internal . by , in \Val_Sup2)}
\text{Val_Med2_t=wims(replace internal . by , in \Val_Med2)}
\real{Borne_Inf2=\Val_Inf2-0.3}
\real{Borne_Sup2=\Val_Sup2+0.3}

#include "data_JsxGraph.inc"

%%%%%%%%% HINT %%%%%%%%%
#include "lang_hint.inc"

%%%%%%%%%%%%%%%%%%%%%
%%%%% STATEMENT %%%%%
%%%%%%%%%%%%%%%%%%%%%

\statement{

<script>
jQuery(function(){
  jQuery("table.answeranalysis td").css('text-align', 'left');
  });
</script>

<div class="euler_quest">
\if{1 notin \confparm1}{
 <div class="grid-x grid-margin-x">
  <div class="cell small-12 medium-6">
   <div>
    <p class="quest">
     \enonce0
     <br>
     \if{\conf3=1}{\introetap}
    </p>
    <p>\enonce1</p>
    <p>\enonce2</p>
   </div>
  </div>
  <div class="cell small-12 medium-6">
   \FigEnonce
  </div>
  <div class="cell small-12  medium-6">
   <p class="quest">\etap1 - \enonce3</p>
  </div>
 </div>
}
{
 <div>
  <p class="quest">
   \enonce0
   <br>
   \introetap
  </p>
  <p>\enonce1</p>
  <p>\enonce2</p>
  <p class="quest">\etap1 - \enonce3</p>
 </div>
}
</div>

\if{\step =1}
{
<div class="\if{\conf3=1}{\if {\sc_reply1=0}{euler_rep_bad}{euler_answer}}{euler_answer}">
  \if{\conf3=1 and \sc_reply1=0}{<p>\phrase </p>}
  <fieldset class="euler_field">
   <legend>\quest1&nbsp;:</legend>
    <ul class="wims_nopuce euler_ul_check">
     \for{e=1 to 6}
       {<li \if {\conf3=1 and \sc_reply1=0}{\if {\checked1[\e]=1}{class="euler_box_checked"}{class="euler_box_nochecked"}}>
        \embed{reply1,\e,\listechoix[\e]}
        </li>}
    </ul>
  </fieldset>
</div>
}
\if{\step >1 }
{
<div class =\if{\conf3!=4}{\if{\sc_reply1=1}{"euler_rep_good"}{\if{\sc_reply1=0}{"euler_rep_bad"}{"euler_rep_prec"}}}{\if{\step>3}{\if{\sc_reply1=1}{"euler_rep_good"}{\if{\sc_reply1=0}{"euler_rep_bad"}{"euler_rep_prec"}}}{"euler_answer"}}>
  \phrase \quest1
   <ul class="wims_nopuce euler_ul_check">
     \for{ee=1 to 6}
      {<li \if {\checked1[\ee]=1}{class="euler_box_checked"}{class="euler_box_nochecked"}>
        <span class="\if{\checked1[\ee]=1 and \conf3!=4}{\if {\rep1good[\ee]=1}{oef_indgood}{oef_indbad}}{oef_indneutral}">\listechoix[\ee]</span>
       </li>}
   </ul>
  \if{\conf3!=4}{<br class="spacer"> \if {\sc_reply1=1}{<p><span class="oef_indgood">\rep_exacte</span>}{\if{\sc_reply1=0}{<span class="oef_indbad">\rep_fausse</span>}{<span class="oef_indprec">\rep_imprec</span>}}}
  \if{\conf3=2 and \sc_reply1!=1}
    {<br><strong>\la_sol</strong> \quest1 <span class="oef_indgood nowrap">\ListeLignesTrigo[\NumSol1],</span>
      <span class="oef_indgood nowrap">&nbsp;\ListeLignesTrigo[\NumSol2].</span>}
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
<div class="grid-x grid-margin-x">
 <div class="cell small-12 medium-6 large-6">
  <div class="\if{\conf3=1}{\if {\sc_reply2=0}{euler_rep_bad}{\if {\sc_reply2=1}{euler_rep_good}{euler_answer}}}{euler_answer}">
    \if{\conf3=1 and (\sc_reply2=0 or \sc_reply3=0)}{<p>\phrase </p>}
    <fieldset class="euler_field">
     <legend>\quest2&nbsp;:</legend>
      <ul class="wims_nopuce euler_ul_check">
       \for{f=1 to 3}
         {<li \if {\conf3=1 and (\sc_reply2=0 or \sc_reply3=0)}{\if {\checked2[\f]=1}{class="euler_radio_checked"}{class="euler_radio_nochecked"}}>
          \embed{reply2,\f,\listepropo2[\f]}
          </li>}
      </ul>
    </fieldset>
  </div>
 </div>
 <div class="cell small-12 medium-6 large-6">
  <div class="\if{\conf3=1}{\if {\sc_reply3=0}{euler_rep_bad}{\if {\sc_reply3=1}{euler_rep_good}{euler_answer}}}{euler_answer}">
    \if{\conf3=1 and (\sc_reply2=0 or \sc_reply3=0)}{<p>\phrase </p>}
    <fieldset class="euler_field">
     <legend>\quest3&nbsp;:</legend>
      <ul class="wims_nopuce euler_ul_check">
       \for{g=1 to 3}
         {<li \if {\conf3=1 and (\sc_reply2=0 or \sc_reply3=0)}{\if {\checked3[\g]=1}{class="euler_radio_checked"}{class="euler_radio_nochecked"}}>
          \embed{reply3,\g,\listepropo3[\g]}
          </li>}
      </ul>
    </fieldset>
  </div>
 </div>
</div>
}
\if{\step >2 }
{
<div class="grid-x grid-margin-x">
 <div class="cell small-12 medium-6 large-6">
  <div class =\if{\conf3!=4}{\if{\sc_reply2=1}{"euler_rep_good"}{\if{\sc_reply2=0}{"euler_rep_bad"}{"euler_rep_prec"}}}{\if{\step>3}{\if{\sc_reply2=1}{"euler_rep_good"}{"euler_rep_bad"}}{"euler_answer"}}>
    \phrase \quest2
     <ul class="wims_nopuce euler_ul_check">
       \for{ff=1 to 3}
        {<li \if {\checked2[\ff]=1}{class="euler_radio_checked"}{class="euler_radio_nochecked"}>
          <span class="\if{\checked2[\ff]=1 and \conf3!=4}{\if {\rep2good[\ff]=1}{oef_indgood}{oef_indbad}}{oef_indneutral}">\listepropo2[\ff]</span>
         </li>}
     </ul>
    \if{\conf3!=4}{<br class="spacer">\if {\sc_reply2=1}{<span class="oef_indgood">\rep_exacte</span>}{\if{\sc_reply2=0}{<span class="oef_indbad">\rep_fausse</span>}{<span class="oef_indprec">\rep_imprec</span>}}}
    \if{\conf3=2 and \sc_reply2!=1}
      {<br><strong>\la_sol</strong> \quest2 <span class="oef_indgood nowrap">\propo[\rang[\typeLigne;1]].</span>}
  </div>
 </div>
 <div class="cell small-12 medium-6 large-6">
  <div class =\if{\conf3!=4}{\if{\sc_reply3=1}{"euler_rep_good"}{\if{\sc_reply3=0}{"euler_rep_bad"}{"euler_rep_prec"}}}{\if{\step>3}{\if{\sc_reply3=1}{"euler_rep_good"}{"euler_rep_bad"}}{"euler_answer"}}>
    \phrase \quest3
     <ul class="wims_nopuce euler_ul_check">
       \for{gg=1 to 3}
        {<li \if {\checked3[\gg]=1}{class="euler_radio_checked"}{class="euler_radio_nochecked"}>
          <span class="\if{\checked3[\gg]=1 and \conf3!=4}{\if {\rep3good[\gg]=1}{oef_indgood}{oef_indbad}}{oef_indneutral}">\listepropo3[\gg]</span>
         </li>}
     </ul>
    \if{\conf3!=4}{<br class="spacer">\if {\sc_reply3=1}{<span class="oef_indgood">\rep_exacte</span>}{\if{\sc_reply3=0}{<span class="oef_indbad">\rep_fausse</span>}{<span class="oef_indprec">\rep_imprec</span>}}}
    \if{\conf3=2 and \sc_reply3!=1}
      {<br><strong>\la_sol</strong> \quest3 <span class="oef_indgood nowrap">\propo[\rang[\typeLigne;2]].</span>}
  </div>
 </div>
</div>
}

\if{\step >=3 }
{
<div class="euler_quest">
  <p class="quest">\etap3 - \enonce5</p>
</div>
}
\if{\step =3 }
{
<div class="grid-x grid-margin-x">
 <div class="cell small-12 medium-6 large-6">
  <div class ="euler_answer">
    <label for="reply4">\quest4</label> <span class="nowrap">\embed{r4,5}.</span>
  </div>
 </div>
 <div class="cell small-12 medium-6 large-6">
  <div class ="euler_answer">
   <label for="reply5">\quest5</label> <span class="nowrap">\embed{r5,5}.</span>
  </div>
 </div>
</div>
}
\if{\step >3 }
{
<div class="grid-x grid-margin-x">
 <div class="cell small-12 medium-6 large-6">
  <div class =\if{\verif4=1}{"euler_rep_good"}{"euler_rep_bad"}>
   \phrase
   <br class="spacer">\quest4 <span class="nowrap \if{\verif4=1}{oef_indgood}{oef_indbad}">\rep4_t.</span>

   \if{\conf3!=4}{<br class="spacer">\if {\verif4=1}{<span class="oef_indgood">\rep_exacte</span>}{<span class="oef_indbad">\rep_fausse</span>}}
    \if{\conf3=2 and \verif4!=1}
      {<br><strong>\la_sol</strong> \quest4 <span class="oef_indgood nowrap">\Solution_1.</span>}
  </div>
 </div>
 <div class="cell small-12 medium-6 large-6">
  <div class =\if{\verif5=1}{"euler_rep_good"}{"euler_rep_bad"}>
   \phrase
   <br class="spacer">\quest5 <span class="nowrap \if{\verif5=1}{oef_indgood}{oef_indbad}">\rep5_t.</span>

    \if{\conf3!=4}{<br class="spacer">\if {\verif5=1}{<span class="oef_indgood">\rep_exacte</span>}{<span class="oef_indbad">\rep_fausse</span>}}
    \if{\conf3=2 and \verif5!=1}
      {<br><strong>\la_sol</strong> \quest5 <span class="oef_indgood nowrap">\Solution_2.</span>}
  </div>
 </div>
</div>
}
}

%%%%%%%%%%%%%%%%%%
%%%%% ANSWER %%%%%
%%%%%%%%%%%%%%%%%%
\answer{\etap1 -}{\posirep;\shf}{type=checkbox}{option=\opt \opt_split}
\answer{\etap2 -&nbsp;}{\posirep2;\shf2}{type=radio}{option=\opt}
\answer{}{\posirep3;\shf3}{type=radio}{option=\opt}
\answer{\etap3 -}{\rep4}{type=numeric}{option=noanalyzeprint }
\answer{}{\rep5}{type=numeric}{option=noanalyzeprint }

%%% Etape 1 %%%
\text{rep1=\reply1}
\integer{nb_prop=wims(itemcnt \shf)}

\text{checked1=}
\text{rep1good=}
\for {k=1 to \nb_prop}
  {\if{\shf[\k] isitemof \rep1}
    {\text{temp=1}
     \if{\shf[\k] isitemof \Sol1}
      {\text{temp2=1}}
      {\text{temp2=0}}
    }
    {\text{temp=0}
     \text{temp2=0}
    }
   \text{checked1=wims(append item \temp to \checked1)}
   \text{rep1good=wims(append item \temp2 to \rep1good)}
  }

%%% ETAPE 2 %%%
\text{rep2=\reply2}
\integer{nb_prop2=wims(itemcnt \shf2)}

\text{checked2=}
\text{rep2good=}
\for {kk=1 to \nb_prop2}
  {\if{\shf2[\kk] isitemof \rep2}
    {\text{temp=1}
     \if{\shf2[\kk]=\rang[\typeLigne;1]}
      {\text{temp2=1}}
      {\text{temp2=0}}
    }
    {\text{temp=0}
     \text{temp2=0}
    }
   \text{checked2=wims(append item \temp to \checked2)}
   \text{rep2good=wims(append item \temp2 to \rep2good)}
  }

\text{rep3=\reply3}
\integer{nb_prop3=wims(itemcnt \shf3)}

\text{checked3=}
\text{rep3good=}
\for {kkk=1 to \nb_prop3}
  {\if{\shf3[\kkk] isitemof \rep3}
    {\text{temp=1}
     \if{\shf3[\kkk]=\rang[\typeLigne;2]}
      {\text{temp2=1}}
      {\text{temp2=0}}
    }
    {\text{temp=0}
     \text{temp2=0}
    }
   \text{checked3=wims(append item \temp to \checked3)}
   \text{rep3good=wims(append item \temp2 to \rep3good)}
  }

%%% ETAPE 3 %%%

\text{rep4=\reply4}
\text{rep5=\reply5}
\text{somme=\rep4 + \rep5}

\if {\rep4!=}{
\text{rep4_t=slib(numeration/ecriturenombre [\rep4], comma)}
\text{rep4isint=pari(frac(\rep4)==0)}
}
\if {\rep5!=}{
\text{rep5_t=slib(numeration/ecriturenombre [\rep5], comma)}
\text{rep5isint=pari(frac(\rep5)==0)}
}

\real{quot=\num/\den}
\integer{quot=round(\quot)}

\if{\typeLigne=3}{
\real{quot2=\den/\num}
\integer{quot2=round(\quot2)}
}
{
\real{quot2=\quot}
}

%% arrondis et troncatures de sol1 en degrés
\text{arrond_sol=pari(vector(11,i,round(10^(i-1)*\angle)/(10.^(i-1))))}
\text{tronc_sol=pari(vector(11,j,floor(10^(j-1)*\angle)/(10.^(j-1))))}
\text{ens_sol=wims(listunion \arrond_sol and \tronc_sol)}
\text{ens_sol=wims(sort numeric item \ens_sol)}

%% arrondis et troncatures de sol2 en degrés
\text{arrond_sol2=pari(vector(11,k,round(10^(k-1)*\angle2)/(10.^(k-1))))}
\text{tronc_sol2=pari(vector(11,z,floor(10^(z-1)*\angle2)/(10.^(z-1))))}
\text{ens_sol2=wims(listunion \arrond_sol2 and \tronc_sol2)}
\text{ens_sol2=wims(sort numeric item \ens_sol2)}

%% la sol1 en radians
\real{angle_rad=\angle*Pi/180}
\integer{angle_rad=round(\angle_rad)}

%% la sol2 en radians
\real{angle_rad2=\angle2*Pi/180}
\integer{angle_rad2=round(\angle_rad2)}


%% la sol1 en grades
\real{angle_grade=\angle*10/9}
\integer{angle_grade=round(\angle_grade)}

%% la sol2 en grades
\real{angle_grade2=\angle2*10/9}
\integer{angle_grade2=round(\angle_grade2)}

\real{difference1=\rep4-\Solution_1}
\integer{nbdigit1=wims(charcnt \difference1)}
\if{\difference1=0 and \nbdigit1=1}{\text{dif1=0}}{\text{dif1=1}}

\real{difference2=\rep5-\Solution_2}
\integer{nbdigit2=wims(charcnt \difference2)}
\if{\difference2=0 and \nbdigit2=1}{\text{dif2=0}}{\text{dif2=1}}

\if{\dif1=1}{
  \if{\rep4 isitemof \ens_sol }
    {\text{verif41=1}
     \if{\rep4 isitemof \arrond_sol}
      {\text{verif42=1}
       \text{posi1=wims(positionof item \rep4 in \arrond_sol)}
       \text{precis1=wims(item \posi1[1] of \pre_arr)}
      }
      {\text{verif42=2}
       \text{posi1=wims(positionof item \rep4 in \tronc_sol)}
       \text{precis1=wims(item \posi1[1] of \pre_tronc)}
      }
    }
    {\text{verif41=0}}
}

\if{\dif2=1}{
  \if{\rep5 isitemof \ens_sol2 }
    {\text{verif51=1}
     \if{\rep5 isitemof \arrond_sol2}
      {\text{verif52=1}
       \text{posi2=wims(positionof item \rep5 in \arrond_sol2)}
       \text{precis2=wims(item \posi2[1] of \pre_arr)}
      }
      {\text{verif52=2}
       \text{posi2=wims(positionof item \rep5 in \tronc_sol2)}
       \text{precis2=wims(item \posi2[1] of \pre_tronc)}
      }

    }
    {\text{verif51=0}}
}


%% Pour la couleur du background
\if{\dif1=0}
  {\text{verif4=1}}
  {\text{verif4=0}}

\if{\dif2=0}
  {\text{verif5=1}}
  {\text{verif5=0}}

%% Cacher conditions  de étape 3 si conf3=1 et rep4 vide
\if{\conf3=1 and \rep4=}{\text{hid1=hide}}

%% Cacher condition de étape 2 si conf3=1 et rep5 vide
%% if{\conf3=1 and \rep5=}{\text{hid2=hide}}

\condition{\etap3 - &nbsp; \rep4_t \text_cond2a \(\widehat{\NomAngle}\) \text_cond2b}{\dif1=0 }{option=\hid1}
\condition{<span class="pad_cond"> \rep5_t \text_cond2a \(\widehat{\NomAngle2}\) \text_cond2b</span>}{\dif2=0 }{option=\hid1}

%%%%%%%%%%%%%%%%%%%%
%%%%% FEEDBACK %%%%%
%%%%%%%%%%%%%%%%%%%%

\feedback{\step>3 and \verif41=1}
  {<div class="wims_msg warning"> \feed1a \(\widehat{\NomAngle}\) \feed1b
       \feed2 \if{\verif42=1}
         {\feed3}
         {\feed4}
         \precis1.
   </div>
  }
\feedback{\step>3 and \verif51=1}
  {<div class="wims_msg warning"> \feed1a \(\widehat{\NomAngle2}\) \feed1b
       \feed2 \if{\verif52=1}
         {\feed3}
         {\feed4}
         \precis2.
   </div>
  }

\feedback{ \step>3 and ((\rep4isint!=1 and \verif41=0) or (\rep5isint!=1 and \verif51=0))}{<div class="wims_msg warning">\feed12</div>}

\feedback{(\dif1!=0) and (\rep4=\Solution_2 and \rep5=\Solution_1)}
 {<div class="wims_msg warning">\feed13</div>}

\feedback{\step>3 and (\rep4>=90 or \rep4<=0 or \rep5>=90 or \rep5<=0)}
{<div class="wims_msg warning">\feed8 </div>}

\feedback{\step>3 and \somme!=90}
{<div class="wims_msg warning">\feed14 </div>}


\feedback{\step>3 and (((\dif1!=0) and (\rep4=\angle_grade or \rep4=\angle_rad)) or ((\dif2!=0) and (\rep5=\angle_grade2 or \rep5=\angle_rad2)))}
{<div class="wims_msg warning">\feed10.}

\feedback{\step>3 and (\dif1!=0) and (\rep4=\quot)}
{<div class="wims_msg warning">
\feed11a \(\widehat{\NomAngle}\) \feed11b <span class="nowrap">\ListeLignesTrigo2[\NumSol1].</span>
}

\feedback{\step>3 and (\dif2!=0) and (\rep5=\quot2)}
{<div class="wims_msg warning">
\feed11a \(\widehat{\NomAngle2}\) \feed11b <span class="nowrap">\ListeLignesTrigo2[\NumSol2].</span>
}

%%%%%%%%%%%%%%%%
%%%%% HINT %%%%%
%%%%%%%%%%%%%%%%
\hint{
<div class="grid-x grid-margin-x">
 <div class="cell small-12 medium-12 large-8">
   <div class="indication">\hint_title4</div>
   <div>\hint_text4</div>
   <div class="indication">\hint_title2</div>
   <div>\hint_text2</div>
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
<div class="grid-x grid-margin-x">
  <div class="cell small-12 \if{2 notin \confparm1}{medium-7 large-8}{medium-12 large-12}">
    <div class="euler_quest_nobg">
     <p>\enonce1</p>
     <ol class="euler_ol">
      <li>\enonceSol1</li>
      <li>\enonceSol2</li>
      <li>\enonceSol3</li>
     </ol>
    </div>
  </div>
  \if{2 notin \confparm1}{
  <div class="cell small-12 medium-5 large-4">
    \FigSol
  </div>}
</div>

<div class ="euler_rep_good_nobg">
  <p>1. \SolDetails1a
        <br>\SolDetails1b
        \if{\typeLigne!=3}{\SolDetails1c}{\SolDetails1d}
        <br>\SolDetails1e
  </p>
  <p>2.
  \if{\typeLigne=3}
    {\(\trigo[2;\typeLigne](\widehat{\NomAngle})=\frac{\text{\long \NUM[6]}\;\widehat{\text{\NomAngle}}}{\text{\long \DEN[6]}\;\widehat{\text{\NomAngle}}}\)}
    {\(\trigo[2;\typeLigne](\widehat{\NomAngle})=\frac{\text{\long \NUM[6]}\;\widehat{\text{\NomAngle}}}{\text{\long \DEN[6]}}\)}
  </p>
  <p>\(\trigo[2;\typeLigne](\widehat{\NomAngle})=\frac{\NomNum}{\NomDen}\)</p>
  <p>\(\trigo[2;\typeLigne](\widehat{\NomAngle})=\frac{\num_t}{\den_t}\)</p>

  \if{\typeLigne=3}
   {<p> et
   \(\trigo[2;\suiv](\widehat{\NomAngle2})=\frac{\text{\long \NUM[6]}\;\widehat{\text{\NomAngle2}}}{\text{\long \DEN[6]}\;\widehat{\text{\NomAngle2}}}\)
  </p>
  <p>\(\trigo[2;\suiv](\widehat{\NomAngle2})=\frac{\NomDen}{\NomNum}\)</p>
  <p>\(\trigo[2;\suiv](\widehat{\NomAngle2})=\frac{\den_t}{\num_t}\)</p>
  }
  {
  <p> et
   \(\trigo[2;\suiv](\widehat{\NomAngle2})=\frac{\text{\long \NUM_suiv[6]}\;\widehat{\text{\NomAngle2}}}{\text{\long \DEN[6]}}\)
  </p>
  <p>\(\trigo[2;\suiv](\widehat{\NomAngle2})=\frac{\NomNum}{\NomDen}\)</p>
  <p>\(\trigo[2;\suiv](\widehat{\NomAngle2})=\frac{\num_t}{\den_t}\)</p>
  }

  <p style="line-height: 1.5;">3. \if{\typeLigne!=3}{\SolDetails3 \SolDetails3b&nbsp;:}{\SolDetails3&nbsp;:}</p>
  <div class="grid-x grid-margin-x">
    <div class="cell small-12 medium-6 large-6">
        - \SolDetails4
        <span class="nowrap">
        <span class="oef_indgood">\Solution_1°</span>.
        </span>
     </div>
    <div class="cell small-12 medium-6 large-6">
      \Fig3
    </div>
  </div>
  <div class="grid-x grid-margin-x">
    <div class="cell small-12 medium-6 large-6">
      - \SolDetails5
        <span class="nowrap">
        <span class="oef_indgood">\Solution_2°</span>.
    </div>
    <div class="cell small-12 medium-6 large-6">
      \Fig4
    </div>
  </div>
</div>
}
