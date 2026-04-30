target=01colineaire 02memesens 03sensoppose 04egaux 05oppose 06memenorme 07memenormenoncoli

#include "lang_title.inc"
#include "avant_header.inc"
#include "lang_descobs.inc"

#define CSS 1
#include "avant_css.inc"

%%%% DATA %%%%
#include "data_generation.inc"

#define GGB 1
#include "data_GGB.inc"

%%%%% TEXTES DE L'EXERCICE DANS LA LANGUE %%%%%
#include "lang.inc"

%%%%% TABLE HELP %%%%%
\text{signification=\signif1,\signif2,\signif3,\signif4,\signif5,\signif6}
\text{list_img=select.png,move.png,zoom_plus.png,zoom_moins.png,annuler_refaire.png,cursor.png}
\text{list_alt=Select,Move,Zoom in,Zoom out,Cancel Redo,Cursor}
\integer{nb_line_table=wims(itemcnt \signification)}
%%%%%%%%%%%%%%%%%%%%%%%

\text{verif1=}
\text{verif2=}
\text{verif3=}
\text{coef_colin=}
%%%% STATEMENT %%%%
\statement{
#define CSS 2
#include "avant_css.inc"

<div class="grid-x grid-margin-x">
 <div class="cell small-12 medium-5 large-6">
  <div class="euler_quest">
    \enonce1
  </div>
  
#if !defined TARGET_04egaux && !defined TARGET_05oppose
  \if{\sc_reply1!=}
  { <div class="wims_instruction" style="font-style:normal;color:black;">
    \explication0
    \if{\test=1}{\explication1a}{\explication1b}
    \explication1c
    \explication2
  </div>
  }
#else
\if{\test!=1}
  {\if{\sc_reply1!=}
  { <div class="wims_instruction" style="font-style:normal;color:black;">
    \explication0
    \explication1
    \explication2
  </div>
  }
  }
#endif
  </div>
 <div class="cell small-12 medium-7 large-6">
  <div class="wimscenter flex_box" >
  <div class="sigle \sigle"></div>
  \embed{r1,\appletoption}
  </div>
  <div class="center"><em>Figure réalisée avec</em> <img src="\imagedir/logo_GGB.png" style="width:20px;vertical-align: middle;" alt ="Logo GeoGebra"/> GeoGebra</div>
 </div>
</div>
}

%%%%% ANSWER %%%%%

\answer{Vérification}
#if defined TARGET_04egaux
{n,x_u - x_v ==0 & y_u - y_v ==0 ,hiden;}
#endif
#if defined TARGET_05oppose
{n,x_u + x_v ==0 & y_u + y_v ==0 ,hiden;}
#endif
#if defined TARGET_01colineaire || defined TARGET_02memesens || defined TARGET_03sensoppose
{n,(x_\D-x_\C)!=0||(y_\D-y_\C)!=0 & (x_u)*(y_v)-(y_u)*(x_v)==0 ,hiden;
# if defined TARGET_01colineaire
}
# endif
# if defined TARGET_02memesens
n,(x_\D-x_\C)!=0 || (y_\D-y_\C)!=0 & (x_u)*(y_v)-(y_u)*(x_v)==0 & (x_u)*(x_v)+(y_u)*(y_v)>0,hiden;}
# endif
# if defined TARGET_03sensoppose
n,(x_\D-x_\C)!=0 || (y_\D-y_\C)!=0 & (x_u)*(y_v)-(y_u)*(x_v)==0 & (x_u)*(x_v)+(y_u)*(y_v)<0,hiden;}
# endif
#endif
#if defined TARGET_06memenorme
{n,(x_u)^2+(y_u)^2-(x_v)^2-(y_v)^2==0,hiden;}
#endif
#if defined TARGET_07memenormenoncoli
{n,(x_u)^2+(y_u)^2-(x_v)^2-(y_v)^2==0 , hiden;
n,(x_u)^2+(y_u)^2-(x_v)^2-(y_v)^2==0 & (x_u)*(y_v)-(y_u)*(x_v)!=0, hiden;}
#endif
{type=geogebra}{option=max=11 extra=yes output=noobjet noanalyzeprint feedbackscript=Correction namebutton=\ElemSol}


#include "feedback.inc"

#define GGB 2
#include "data_GGB.inc"


\feedback{1=1}{
<script>
const element = document.querySelector("#geogebra_feedback");
element.classList.add("wims_button");
</script>
#if defined TARGET_04egaux || defined TARGET_05oppose
\if{\test=1}{
<script>document.querySelector("#geogebra_feedback").style.display = 'none';</script>
}
#endif
<script>
function Correction(){
#if !defined TARGET_04egaux && !defined TARGET_05oppose
\script_curseur
#endif
\script_vec_v
\script_ptD
\if{\conf1=1}{
# if defined TARGET_01colineaire || defined TARGET_02memesens || defined TARGET_03sensoppose
ggbApplet0.evalCommand('tableau=If(k<>0,TableText({LaTeX("'+"\\\"+"overrightarrow{\C\D} = "+'")+(If(k*(1/pgcd)==1,"",k*(1/pgcd)==-1,"-",FractionText[k*(1/pgcd)]))+ LaTeX("'+"\\\"+";"+"\\\"+"overrightarrow{\A\B}"+'")}, "ch"))');
# endif
# if defined TARGET_04egaux
ggbApplet0.evalCommand('tableau=TableText({{TableText({LaTeX("'+"\\\"+"overrightarrow{\C\D} ="+"\\\"+"overrightarrow{\A\B}"+'")}, "ch")},{LaTeX("'+"\A\B\D\C \\\"+"text{ \para.}"+'")}}, "ch")');
# endif
# if defined TARGET_05oppose
ggbApplet0.evalCommand('tableau=TableText({{TableText({LaTeX("'+"\\\"+"overrightarrow{\C\D} = - "+"\\\"+"overrightarrow{\A\B}"+'")}, "ch")},{LaTeX("'+"\A\B\C\D \\\"+"text{ \para.}"+'")}}, "ch")');
# endif
#if defined TARGET_06memenorme || defined TARGET_07memenormenoncoli
ggbApplet0.evalCommand('tableau=TableText({LaTeX("'+"\\\"+"left"+"\\\"+"|"+"\\\"+"overrightarrow{\C\D}"+"\\\"+"right"+"\\\"+"|"+" = "+"\\\"+"left"+"\\\"+"|"+"\\\"+"overrightarrow{\A\B}"+"\\\"+"right"+"\\\"+"|"+'")}, "ch")');
#endif
ggbApplet0.evalCommand('SetVisibleInView[tableau,1,true]');
}
{
# if defined TARGET_04egaux
ggbApplet0.evalCommand('tableau=TableText({LaTeX("'+"\A\B\D\C \\\"+"text{ \para.}"+'")}, "ch")');
ggbApplet0.evalCommand('SetVisibleInView[tableau,1,true]');
# endif
# if defined TARGET_05oppose
ggbApplet0.evalCommand('tableau=TableText({LaTeX("'+"\A\B\C\D \\\"+"text{ \para.}"+'")}, "ch")');
ggbApplet0.evalCommand('SetVisibleInView[tableau,1,true]');
# endif
}
}
</script>
}
#if !defined TARGET_04egaux && !defined TARGET_05oppose
\feedback{\verif1=0}{
  <div class="wims_msg \sigle"> \feed1</div>
}
#endif
#if defined TARGET_01colineaire || defined TARGET_02memesens || defined TARGET_03sensoppose
\feedback{\verif2=0}{
  <div class="wims_msg \sigle"> \feed2</div>
}
#endif
#if defined TARGET_07memenormenoncoli
\feedback{\verif1=1 and \verif2=1}{
  <div class="wims_msg \sigle"> \feed2</div>
}
#endif
#if defined TARGET_02memesens || defined TARGET_03sensoppose
\feedback{\verif3=0}{
  <div class="wims_msg \sigle"> \feed3 \if{\conf1=1}{<span class="nowrap">\(\overrightarrow{\C\D} = \coef_colin \; \overrightarrow{\A\B}\).</span>}</div>
}
#endif

#if defined TARGET_04egaux || defined TARGET_05oppose
\feedback{\verif1=1}{
  \if{\verif2=0}
    {<div class="wims_msg \sigle"> \feed1</div>}
    {\if{\verif3=0}{<div class="wims_msg \sigle"> \feed2 \if{\conf1=1}{<span class="nowrap">\(\overrightarrow{\C\D} = \coef_colin \; \overrightarrow{\A\B}\).</span>}</div>}}
}
#endif
#if defined TARGET_04egaux || defined TARGET_05oppose
\feedback{\verif1=0}{
  \if{\verif2=0}
    {<div class="wims_msg \sigle"> \feed3</div>}
    {\if{\verif3=0}
      {<div class="wims_msg \sigle"> \feed4 \if{\conf1=1}{<span class="nowrap">\(\overrightarrow{\C\D} = \coef_colin \; \overrightarrow{\A\B}\).</span>}</div>}
      {<div class="wims_msg \sigle"> \feed5 \if{\conf1=1}{<span class="nowrap">\(\overrightarrow{\C\D} = \coef_colin \; \overrightarrow{\A\B}\).</span>}</div>}
    }
}
#endif
%%% IN CASE REP IS GOOD %%%
\feedback{\test=1}
  {<div class="wims_msg \sigle"> \feed_good 
#if !defined TARGET_06memenorme && !defined TARGET_07memenormenoncoli    
    \if{\conf1=1}{<span class="nowrap">\(\overrightarrow{\C\D} = \coef_colin \; \overrightarrow{\A\B}\).</span>}
#endif
  }
%%%%% HINT %%%%%

\hint{
<div class="grid-x grid-margin-x">
  <div class="cell small-12 large-10 medium-9">
    <div class="wims_thm">
#if !defined TARGET_04egaux && !defined TARGET_05oppose 
      \definition1
      <ul>
        <li>\li1</li>
        <li>\li2</li>
        <li>\li3</li>
      </ul>
      <br class="spacer">
      \definition2
#endif
#if defined TARGET_04egaux
      \definition1
      <br class="spacer">
      \definition2
#endif
#if defined TARGET_05oppose
      \definition1
      <br class="spacer">
      \definition2
#endif
    </div>
   </div>
  <div class="cell small-12 large-2 medium-3">
    <div class="wimscenter">
#if !defined TARGET_04egaux && !defined TARGET_05oppose 
     <img  src="\imagedir/hint1.png"  alt ="Vector"/>
#endif
#if defined TARGET_04egaux
  <img  src="\imagedir/hint2.png"  alt ="Parallelogram1"/>
#endif
#if defined TARGET_05oppose
  <img  src="\imagedir/hint3.png"  alt ="Parallelogram2"/>
#endif
    </div>
  </div>
</div> 
}

%%%%% HELP %%%%%
\help{
<div class="table-scroll">
 <table class="wimstable wimscenter">
  <caption>\help_caption</caption>
   <thead>
    <tr>
     <th>\ico</th>
     <th>\signif</th>
    </tr>
   </thead>
   <tbody>
    \for{tt=1 to \nb_line_table}
    {
    <tr>
     <td><img  src="\imagedir/\list_img[\tt]"  alt ="\list_alt[\tt]"/></td>
     <td>\signification[\tt]</td>
    </tr>
    }
   </tbody>
 </table>
</div>

}
