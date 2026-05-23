target=06AssocVocTrigo

#include "lang_title.inc"
#include "avant_header.inc"
#include "lang_descobs.inc"

#include "avant_css.inc"

%%%% DATA
#include "data_triangle.inc"

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\matrix{Colonne1=
\(sin(\widehat{\NomAngle})\)
\(cos(\widehat{\NomAngle})\)
\(tan(\widehat{\NomAngle})\)
}

\matrix{Colonne2=
\(\frac{\Sommet\Hyp[2]}{\Hyp[1]\Hyp[2]}\)
\(\frac{\Sommet\Hyp[1]}{\Hyp[1]\Hyp[2]}\)
\(\frac{\Sommet\Hyp[2]}{\Sommet\Hyp[1]}\)
}

\integer{N=rows(\Colonne1)}
\text{melange=shuffle(\N)}

\text{\col1=
\Colonne1[\melange[1];],
\Colonne1[\melange[2];],
\Colonne1[\melange[3];],
}
\text{\col2=
\Colonne2[\melange[1];],
\Colonne2[\melange[2];],
\Colonne2[\melange[3];],
}

%%%%% TEXTES DE L'EXERCICE DANS LA LANGUE %%%%%

#include "lang.inc"

%%%% FIGURES JSXGRAPH
#include "data_JsxGraph.inc"

%%%%%%%% HINT %%%%%%%%%%%
#include "lang_hint.inc"

\matrix{Colonne3=
\(\frac{\text{\co}\; \widehat{\text{\NomAngle}}}{\text{\hypot}}\)
\(\frac{\text{\ca}\;\widehat{\text{\NomAngle}}}{\text{\hypot}}\)
\(\frac{\text{\co}\; \widehat{\text{\NomAngle}}}{\text{\ca}\;\widehat{\text{\NomAngle}}}\)
}

\text{\col3=
\Colonne3[\melange[1];],
\Colonne3[\melange[2];],
\Colonne3[\melange[3];],
}

%%%%%%%%%%%%%%%%%%%%%
%%%%% STATEMENT %%%%%
%%%%%%%%%%%%%%%%%%%%%

\statement{
<div class="grid-x grid-margin-x">
 <div class="cell small-12 \if{1 notin \confparm1}{medium-7 large-7}{medium-12 large-12}">
    <div class="euler_quest"> 
     \enonce1
    </div> 
    <div class="\if{\sc_reply1=}{euler_answer}{\if{\sc_reply1=1}{euler_rep_good_nobg}{\if{\sc_reply1=0}{euler_rep_bad_nobg}{euler_rep_prec_nobg}}}" style="margin-left:0.2em"> 
      <div style="overflow-x:auto;">
       <table>
         <tr>
           <td>
             \embed{reply 1,50x100x50}
           </td>
         </tr>
       </table>
      </div>
   </div>         
   <div class ="accordion">
    <div>\if{\sc_reply1=}{\title_accord1}{\title_accord2}</div>
    <div class="box_content proced" >
      \if{\sc_reply1=}{\procedure1}{\procedure2}
    </div>
   </div>        
 </div>
  
 <div class="cell small-12 \if{1 notin \confparm1}{medium-5 large-5}" style="padding-top:1em;">
    \if{1 notin \confparm1}{\FigEnonce}
 </div>
</div>
}

%%%%%%%%%%%%%%%%%%
%%%%% ANSWER %%%%%
%%%%%%%%%%%%%%%%%%
\answer{}{\col1;\col2}{type=correspond}{ option=split}


%%%%%%%%%%%%%%%%%%%%
%%%%%%% HELP  %%%%%%
%%%%%%%%%%%%%%%%%%%%
\help{
<style>
ul.euler_ul{
  padding-left: 1.2em;
  margin-top: 0.2em;
  margin-bottom: 0.2em;
}
</style>

<div class="wims_instruction">
  <div>
   <strong>\title_accord1</strong>
   \procedure1
  </div>
  <div class="spacer">
   <strong>\title_accord2</strong>
   \procedure2
  </div>
</div>
}

%%%%%%%%%%%%%%%%
%%%%% HINT %%%%%
%%%%%%%%%%%%%%%%

\hint{
  <div class="grid-x grid-margin-x">
    <div class="cell small-12 medium-12 large-8">
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
  <div class="cell small-12 \if{2 notin \confparm1}{medium-6 large-6}{medium-12 large-12}">
   <div class ="euler_quest_nobg">
    \enonce2
   </div>
  </div>
  \if{2 notin \confparm1}{
   <div class="cell small-12 medium-5 large-4">
    \FigSol
   </div>
    }
  </div>
  
  <div class="euler_rep_good_nobg" style="overflow-x:auto;"> 
   <table class="tabSol wimscenter">
    <tr>
     <th class="vide"></th>
     <th>\th1</th>
     <th>\th2</th>
    </tr>
    \for{i=1 to \N}{
      <tr>
       <td>
        \col1[\i]
      </td>
      <td>
        \col3[\i]
      </td>
      <td>
       <span class="oef_indgood">\col2[\i]</span>
      </td>
     </tr>
       }
    </table>
  </div>
</div>
}
