target=01CliquerHypotenuse 02CliquerAdjacent 03CliquerOppose

#include "lang_title.inc"
#include "avant_header.inc"
#include "lang_descobs.inc"

#include "avant_css.inc"
#include "data_triangle.inc"
#include "data_JsxGraph.inc"

\text{FigEnonce2=}

%%%%% TEXTES EXERCICE %%%%%
#include "lang.inc"

%%%%%%%%%% HINT %%%%%%%%%%
#include "lang_hint.inc"

%%%%%%%%%%%%%%%%%%%%%
%%%%% STATEMENT %%%%%
%%%%%%%%%%%%%%%%%%%%%


\statement{
<div class="grid-x grid-margin-x">
  <div class="cell small-12 large-6 medium-6">
    <div class="euler_quest">
      <p>\phrase1</p>
      <p class="quest">\phrase2</p>
      <div class ="accordion">
        <div>\title_accord</div>
        <div class="box_content" >
          \procedure
        </div>
      </div>
    </div>
  </div>
  <div class=" cell small-12 large-6 medium-6 ">
    \if{\sc_reply1=}{
      <div class ="euler_answer">
        \embed{r1, \LCadre x \hCadre
         jsxenonce brd
        \board_enonce\scriptComjs
        }
      </div>
    }{
      <div class ="\if{\sc_reply1=1}{euler_rep_good}{euler_rep_bad}">
       \FigEnonce2
      </div>
      }
  </div>
</div>
}

%%%%%%%%%%%%%%%%%%
%%%%% ANSWER %%%%%
%%%%%%%%%%%%%%%%%%

#if defined TARGET_01CliquerHypotenuse
\answer{}{hypo;cat1|cat2}{type=jsxgraphobjet}{option=}
#else
# if defined TARGET_02CliquerAdjacent
\answer{}{cat1;hypo|cat2}{type=jsxgraphobjet}{option=noanalyzeprint}
# else

\answer{}{cat2;hypo|cat1}{type=jsxgraphobjet}{option=noanalyzeprint}
# endif
#endif


%%%%%%%%%%%%%%%%%%%%
%%%%% FEEDBACK %%%%%
%%%%%%%%%%%%%%%%%%%%

\if{\sc_reply1!=}{
\text{idjs=jsxFeed}
}
\if{hypo isitemof \reply1}{\text{scriptHypo=hypo.setAttribute({strokeWidth:5,color:'blue'});}}
\if{cat1 isitemof \reply1}{\text{scriptCat1=cat1.setAttribute({strokeWidth:5,color:'blue'});}}
\if{cat2 isitemof \reply1}{\text{scriptCat2=cat2.setAttribute({strokeWidth:5,color:'blue'});}}

\text{err=3}
#if defined TARGET_01CliquerHypotenuse
\if{\reply1 issametext hypo}{\integer{err=0}}
\if{\reply1 issametext cat1}{\integer{err=1}}
\if{\reply1 issametext cat2}{\integer{err=2}}
#else
# if defined TARGET_02CliquerAdjacent
\if{\reply1 issametext cat1}{\integer{err=0}}
\if{\reply1 issametext hypo}{\integer{err=1}}
\if{\reply1 issametext cat2}{\integer{err=2}}
# else
\if{\reply1 issametext cat2}{\integer{err=0}}
\if{\reply1 issametext hypo}{\integer{err=1}}
\if{\reply1 issametext cat1}{\integer{err=2}}
# endif
#endif

\text{boardjs=
var brd = JXG.JSXGraph.initBoard('\idjs', {showCopyright : false,axis:false,
 boundingbox: [\xMin,\yMax,\xMax,\yMin],grid:false});}

\text{scriptFeedjs=brd.create('segment',\seg1,{strokeWidth:5,color:'green'});
#if defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose
brd.create('angle',[C,B,A],{name:' ',radius:\radiusAngle,strokeColor:'black',fillColor:'\couleur',fillOpacity:1});
#endif
var repjs=\sc_reply1;
var errjs=\err;
if(repjs==0){
 if(errjs==1){
selection=brd.create('segment',\seg2,{strokeWidth:5,dash:2,color:'red'});}
else{if(errjs==2){
selection=brd.create('segment',\seg3,{strokeWidth:5,dash:2,color:'red'});}
}
}
}

\text{FigEnonce2=slib(geo2D/jsxgraph jsxenonce,\LCadre x \hCadre,\board_enonce\scriptComjs\scriptHypo\scriptCat1\scriptCat2)}


\text{FigFeed=slib(geo2D/jsxgraph \idjs,\LCadre x \hCadre,\boardjs \scriptComjs \scriptFeedjs)}


\feedback{items(\reply1)=1 and \err=0}{
  <div class="grid-x grid-margin-x">
    <div class="cell small-12 large-6 medium-6">
     <div class="euler_rep_good">
      \feed_good
     </div>
    </div>
    <div class=" cell small-12 large-6 medium-6 ">
     \FigFeed
    </div>
  </div>
}

\feedback{items(\reply1)=1 and \err=1}{
  <div class="grid-x grid-margin-x">
    <div class="cell small-12 large-6 medium-6">
     <div class="euler_rep_bad">
      \feed_bad_1 <br>\feed_sol
     </div>
    </div>
    <div class=" cell small-12 large-6 medium-6 ">
     \FigFeed
    </div>
  </div>
}

\feedback{items(\reply1)=1 and \err=2}{
  <div class="grid-x grid-margin-x">
    <div class="cell small-12 large-6 medium-6">
     <div class="euler_rep_bad">
      \feed_bad_2 <br>\feed_sol
     </div>
    </div>
    <div class=" cell small-12 large-6 medium-6 ">
     \FigFeed
    </div>
  </div>
}

\feedback{items(\reply1)>1}
  {<div class="grid-x grid-margin-x">
    <div class="cell small-12 large-6 medium-6">
     <div class="euler_rep_bad">
      \feed_multi_clic <br>\feed_sol
     </div>
    </div>
    <div class=" cell small-12 large-6 medium-6 ">
     \FigFeed
    </div>
  </div>
  }

%%%%%%%%%%%%%%%%
%%%%% HINT %%%%%
%%%%%%%%%%%%%%%%

\hint{
#if defined TARGET_01CliquerHypotenuse
 \hint_text1
#endif

#if defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose
  <div class="grid-x grid-margin-x">
    <div class="cell small-12 medium-12 large-8">
       <div class="indication">\hint_title2</div>
       <div>\hint_text2</div>
    </div>
    <div class="cell small-12 medium-12 large-4">
      \FigIndic
    </div>
  </div>
#endif
}
%%%%%%%%%%%%%%%%%%%%
%%%%% SOLUTION %%%%%
%%%%%%%%%%%%%%%%%%%%

\solution{
<div class="euler_quest_nobg">
  <p>\phrase1</p>
  <p class="quest">\phrase3</p>
</div>
<div class="euler_rep_good_nobg">
 <div class="grid-x grid-margin-x">
  <div class="cell small-12 medium-6 large-6">
    \SolDetails
  </div>
  <div class="cell small-12 medium-6 large-6">
    \FigSol
  </div>
 </div>
</div>
}
