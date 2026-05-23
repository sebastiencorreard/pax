target=11LigneTrigoUniteEtape 12LigneTrigoUnite

#include "lang_title.inc"
#include "avant_header.inc"
#include "lang_descobs.inc"

#include "avant_css.inc"

%%%% DATA
#include "data_triangle.inc"

#if defined TARGET_11LigneTrigoUniteEtape
%%% EXERCICE A ETAPES
\matrix{etap=r1
r2}

\nextstep{\etap}

\text{shf=shuffle(3)}
\text{listechoix=\trigo[1;\shf]}
\text{posirep=position(\typeLigne,\shf)}


%%%%% RECUPERATION CASES COCHEES
\text{checked=}
\text{rep1=}
#endif

%%%%% QUESTION ANGLE
\text{verif=}
\text{rep_t=}

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
#if defined TARGET_11LigneTrigoUniteEtape
    <p class="quest">
     \enonce0
     <br>
     \if{\conf3=1}{\introetap}
    </p>
#endif
    <p>\enonce1</p>
#if defined TARGET_11LigneTrigoUniteEtape
    <p>\enonce2</p>
#endif
   </div>
  </div>
  <div class="cell small-12 medium-6">
   \FigEnonce
  </div>
  <div class="cell small-12  medium-6">
#if defined TARGET_11LigneTrigoUniteEtape
   <p class="quest">\etap1 - \enonce3</p>
#endif
#if defined TARGET_12LigneTrigoUnite
   <p class="quest">\enonce4</p>
#endif
  </div>
 </div>
}
{
 <div>
#if defined TARGET_11LigneTrigoUniteEtape
  <p class="quest">
   \enonce0
   <br>
   \introetap
  </p>
#endif
  <p>\enonce1</p>
#if defined TARGET_11LigneTrigoUniteEtape
  <p>\enonce2</p>
  <p class="quest">\etap1 - \enonce3</p>
#endif
#if defined TARGET_12LigneTrigoUnite
  <p class="quest">\enonce4</p>
#endif
 </div>
}
</div>

#if defined TARGET_11LigneTrigoUniteEtape

\if{\step =1}
{
<div class="\if{\conf3=1}{\if {\sc_reply1=0}{euler_rep_bad}{euler_answer}}{euler_answer}">
  \if{\conf3=1 and \sc_reply1=0}{<p>\phrase </p>}

  <fieldset class="euler_field">
   <legend>\quest1&nbsp;:</legend>
    <ul class="wims_nopuce euler_ul_check">
     \for{e=1 to 3}
       {<li \if {\conf3=1 and \sc_reply1=0}{\if {\checked[\e]=1}{class="euler_radio_checked"}{class="euler_radio_nochecked"}}>
        \embed{reply1,\e,\listechoix[\e]} \delangle \(\widehat{\NomAngle}\)
        </li>}
    </ul>
  </fieldset>

</div>
}


\if{\step >1 }
{
<div class =\if{\conf3!=4}{\if{\sc_reply1=1}{"euler_rep_good"}{"euler_rep_bad"}}{\if{\step>2}{\if{\sc_reply1=1}{"euler_rep_good"}{"euler_rep_bad"}}{"euler_answer"}}>
  \phrase <br class="spacer">\quest1&nbsp;:
   <ul class="wims_nopuce euler_ul_check">
     \for{ee=1 to 3}
      {<li \if {\checked[\ee]=1}{class="euler_radio_checked"}{class="euler_radio_nochecked"}>
        <span class="\if{\checked[\ee]=1 and \conf3!=4}{\if {\sc_reply1=1}{oef_indgood}{oef_indbad}}{oef_indneutral}">\listechoix[\ee]</span> \delangle \(\widehat{\NomAngle}\)
       </li>}
   </ul>
  \if{\conf3!=4}{<p>\if {\sc_reply1=1}{<span class="oef_indgood">\rep_exacte</span>}{<span class="oef_indbad">\rep_fausse</span>}</p>}
  \if{\conf3=2 and \sc_reply1!=1}{<p><strong>\la_sol</strong> \quest1 <span class="oef_indgood">\listechoix[\posirep]</span> \delangle \(\widehat{\NomAngle}\).</p>}
</div>
}
\if{\step >=2 }
{
<div class="euler_quest">

 <p class="quest">\etap2 - \enonce4</p>
</div>
}
\if{\step =2 }
{<div class ="euler_answer">
  <label for="reply2">\quest2</label> <span class="nowrap">\embed{r2,5}.</span>
</div>
}
\if{\step >2 }
{
<div class =\if{\verif=1}{"euler_rep_good"}{"euler_rep_bad"}>
 <p>\phrase</p>
 \quest2 <span class="nowrap \if{\verif=1}{oef_indgood}{oef_indbad}">\rep_t.</span>
 \if{\conf3!=4}{<p>\if {\verif=1}{<span class="oef_indgood">\rep_exacte</span>}{<span class="oef_indbad">\rep_fausse</span>}</p>}
 \if{\conf3=2 and \verif=0}
   {<strong>\la_sol</strong> \quest2 <span class="nowrap"><span class="oef_indgood">\Solution_1</span>.</span>}
</div>

}

#endif

#if defined TARGET_12LigneTrigoUnite
<div class =\if {\verif=}{"euler_answer"}{\if{\verif=1}{"euler_rep_good"}{"euler_rep_bad"}}>
 \if {\verif!=}{\phrase <br class="spacer">}
 <label for="reply1">\quest2</label>
   <span class="nowrap \if{\verif!=}{\if{\verif=1}{oef_indgood}{oef_indbad}}">\embed{r1,5}.</span>
 \if {\verif!=}{<p>\if{\verif=1}{<span class="oef_indgood">\rep_exacte</span>}{<span class="oef_indbad">\rep_fausse</span>}</p>}
</div>
#endif
}

%%%%%%%%%%%%%%%%%%
%%%%% ANSWER %%%%%
%%%%%%%%%%%%%%%%%%

#if defined TARGET_11LigneTrigoUniteEtape
\answer{\etap1 - }{\posirep;\shf}{type=radio}{option=\opt}

\text{rep1=\reply1}
\integer{nb_prop=wims(itemcnt \shf)}

\text{checked=}
\for {k=1 to \nb_prop}
  {\if{\shf[\k] isitemof \rep1}
    {\text{temp=1}}
    {\text{temp=0}}
   \text{checked=wims(append item \temp to \checked)}
  }

\answer{}{\rep}{type=numeric}{option=nonstop noanalyzeprint}

\text{rep1=\reply1}
\integer{nb_prop=wims(itemcnt \trigo[1;])}

\text{checked=}
\for {k=1 to \nb_prop}
  {\if{\shf[\k] isitemof \rep1}
    {\text{temp=1}}
    {\text{temp=0}}
   \text{checked=wims(append item \temp to \checked)}
  }
#endif

#if defined TARGET_12LigneTrigoUnite
\answer{}{\rep}{type=numeric}{option=noanalyzeprint}
#endif

\if {\rep!=}{
\text{rep_t=slib(numeration/ecriturenombre [\rep], comma)}
\text{rep2isint=pari(frac(\rep)==0)}
}

%% arrondis et troncatures du quotient
\real{quot=\num/\den}
\integer{quot=round(\quot)}

%% arrondis et troncatures de la sol en degrés
\text{arrond_sol=pari(vector(11,i,round(10^(i-1)*\angle)/(10.^(i-1))))}
\text{tronc_sol=pari(vector(11,i,floor(10^(i-1)*\angle)/(10.^(i-1))))}
\text{ens_sol=wims(listunion \arrond_sol and \tronc_sol)}
\text{ens_sol=wims(sort numeric item \ens_sol)}

%% la sol en radians
\real{angle_rad=\angle*Pi/180}
\integer{angle_rad=round(\angle_rad)}

%% la sol en grades
\real{angle_grade=\angle*10/9}
\integer{angle_grade=round(\angle_grade)}

%% complémentaire de la sol en degrés
\real{compl=90-\angle}
\integer{compl=round(\compl)}

\real{difference=\rep-\Solution_1}
\integer{nbdigit=wims(charcnt \difference)}
\if{\difference=0 and \nbdigit=1}{\text{dif=0}}{\text{dif=1}}

\if{\dif=1}{
  \if{\rep isitemof \ens_sol }
    {\text{verif1=1}
     \if{\rep isitemof \arrond_sol}
      {\text{verif2=1}
       \text{posi=wims(positionof item \rep in \arrond_sol)}
       \text{precis=wims(item \posi[1] of \pre_arr)}
      }
      {\text{verif2=2}
       \text{posi=wims(positionof item \rep in \tronc_sol)}
       \text{precis=wims(item \posi[1] of \pre_tronc)}
      }
    }
    {\text{verif1=0}}
}

%% Pour la couleur du background
\if{\dif=0}
  {\text{verif=1}}
  {\text{verif=0}}

%% Cacher condition de étape 2 si conf3=1 et rep1 fausse
\if{\conf3=1 and \sc_reply1=0}{\text{hid1=hide}}

#if defined TARGET_11LigneTrigoUniteEtape
\text{nom_etap=\etap2 - }
#endif
#if defined TARGET_12LigneTrigoUnite
\text{nom_etap=}
#endif

\condition{\nom_etap &nbsp; \rep_t \text_cond2a \(\widehat{\NomAngle}\) \text_cond2b}{\dif=0 }{option=\hid1}

%%%%%%%%%%%%%%%%%%%%
%%%%% FEEDBACK %%%%%
%%%%%%%%%%%%%%%%%%%%

\feedback{\verif1=1}
  {<div class="wims_msg warning"> \feed1a \(\widehat{\NomAngle}\) \feed1b
   \feed2 \if{\verif2=1}
         {\feed3}
         {\feed4}
         \precis.
   </div>
  }

\feedback{\rep!= and \rep2isint!=1 and \verif1=0}{<div class="wims_msg warning">\feed12</div>}

\feedback{(\dif!=0) and (\rep=\compl)}
 {<div class="wims_msg warning" style="line-height: 1.7;">
  \if{\typeLigne!=3}
   {\feed6}
   {\feed7}</div>
 }

\feedback{\rep!= and (\rep>=90 or \rep<=0)}
{<div class="wims_msg warning">\feed8 </div>}

\feedback{(\dif!=0) and (\rep=\angle_grade or \rep=\angle_rad)}
{<div class="wims_msg warning">\feed10.}

\feedback{(\dif!=0) and (\rep=\quot)}
{<div class="wims_msg warning">
\feed11a \(\widehat{\NomAngle}\) \feed11b <span class="nowrap">\(\trigo[2;\typeLigne](\widehat{\NomAngle})\).</span>
}


%%%%%%%%%%%%%%%%
%%%%% HINT %%%%%
%%%%%%%%%%%%%%%%

#if defined TARGET_12LigneTrigoUnite
\hint{
<div class="indication">\hint_title4</div>
<p>\hint_text5</p>
<ul class="euler_ul">
 <li>\hint_text6</li>
 <li>\hint_text7</li>
</ul>
}
#endif

#if defined TARGET_11LigneTrigoUniteEtape
\hint{
<div class="grid-x grid-margin-x">
 <div class="cell small-12 medium-12 large-8">
   <div class="indication">\hint_title4</div>
   <div>\hint_text4</div>
   <div class="indication">\hint_title3</div>
   <div>\hint_text3</div>
 </div>
 <div class="cell small-12 medium-12 large-4">
   \FigIndic
 </div>
</div>
}
#endif


%%%%%%%%%%%%%%%%%%%%
%%%%% SOLUTION %%%%%
%%%%%%%%%%%%%%%%%%%%

\solution{

<div class="grid-x grid-margin-x">
  <div class="cell small-12 \if{2 notin \confparm1}{medium-7 large-8}{medium-12 large-12}">
    <div class="euler_quest_nobg">
     <p>\enonce1</p>
     <p>\enonceSol2</p>
    </div>
  </div>
  \if{2 notin \confparm1}{
  <div class="cell small-12 medium-5 large-4">
    \FigSol
  </div>}
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
  <p style="line-height: 1.5;">\SolDetails3&nbsp;:</p>
  <div class="grid-x grid-margin-x">
    <div class="cell small-12 medium-6 large-6">
        \SolDetails4
        <span class="nowrap">
        <span class="oef_indgood">\Solution_1°</span>.
        </span>
     </div>
    <div class="cell small-12 medium-6 large-6">
      \Fig3
    </div>
  </div>

</div>
}
