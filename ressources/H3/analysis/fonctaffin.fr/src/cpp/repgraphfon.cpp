target=gfon

#include "author.inc"
#include "header.inc"
#include "lang_titles.inc"
#include "helpjsx.inc"
#include "css.inc"


\title{TITRE}
\if{\confparm1=}{\text{confparm1=1}}
\if{\confparm1 issametext 1,2}{\text{confparm1=randitem(1,2)}}
\if{\confparm2=}{\text{confparm2=1}}


%%Mise en place des coefficients a et b confparm1 =1 affine =2 lineaire  confparm2=1 entiers relatifs =2 rationnels
\text{coefe=1,2,3,4,5,-1,-2,-3,-4,-5}
\text{coefr=1/2,1/3,1/4,1/5,2/3,2/5,3/2,3/4,3/5,4/3,4/5,5/2,5/3,5/4,-1/2,-1/3,-1/4,-1/5,-2/3,-2/5,-3/2,-3/4,-3/5,-4/3,-4/5,-5/2,-5/3,-5/4}
\if{\confparm2=1}{\text{coef=shuffle(\coefe)}}
\if{\confparm2=2}{\text{coef=shuffle(\coefr)}}
\if{1 isitemof \confparm2 and 2 isitemof \confparm2}{\text{coef=shuffle(\coefe,\coefr)}}
\text{coefa=\coef[1]}
\if{\confparm1=1}{\text{coefb=randitem(-5,-4,-3,-2,-1,1,2,3,4,5)}
                }
                {\text{coefb=0}
                }
\text{nomfct=randitem(f,g,h,i)}
\integer{b=\coefb}
\text{fon=\coefa*x+(\b)}
\text{texfon=texmath(\fon)}
\real{ordo=0}
%%Calcul de l'image pour la solution
\if{\coefa isitemof \coefr}{\rational{a=\coefa}
                            \integer{denom=pari(denominator(\a))}
                            \integer{ant=\denom}
                            }
                            {\integer{ant=1}
                            }
\text{tant=\ant<0?(\ant):\ant}
\if{\coefa isitemof \coefr}{\text{pa=\a<0?(\a):\a}
                            \text{tpa=\a<0?(texmath(\pa)):\texmath(\pa)}
                            \text{fon=(\a)*x+(\b)}
                            \text{fon1=simplify(\fon)}
                            \text{fon2=pari(Polrev(\fon1))}
                            \text{texfon=texmath(\fon2)}
                            \text{fonction=\nomfct (x)=\texfon}             
                            \integer{num=pari(numerator(\a))}
                            \rational{cim=(\a)*(\ant)+(\b)}
                            \rational{temp=(\a)*(\ant)}
                            \rational{tmp1=\cim-(\b)}
                            \text{tcim=texmath(\cim)}
                            \text{ttemp=texmath(\temp)}
                            \text{ttmp1=texmath(\tmp1)}
                            \if{\b>0}{\text{tim1=\(\nomfct (\ant)= \frac{\num}{\denom} \times \tant + \b\)}
                                      \text{tim2=\(\nomfct (\ant)= \ttemp + \b\)}
                                      \text{tim3=\(\nomfct (\ant) = \tcim\)}
                                      \text{tmp2=\tcim- \b}
                                      }                                     
                            \if{\b=0}{\text{tim1=\(\nomfct (\ant)= \frac{\num}{\denom} \times \tant\)}
                                      \text{tim2=\(\nomfct (\ant)=\tcim\)}
                                      \text{tmp2=\tcim}                                       
                                       }
                            \if{\b<0}{\text{tim1=\(\nomfct (\ant)= \frac{\num}{\denom} \times \tant \b\)}
                                      \text{tim2=\(\nomfct (\ant)= \ttemp \b\)}
                                      \text{tim3=\(\nomfct (\ant)= \tcim\)}
                                      \text{tmp2=\tcim + \absb}     
                                       }    
                           }
                           {\integer{a=\coefa}
                            \text{pa=\a<0?(\a):\a}
                            \text{tpa=\a<0?(texmath(\pa)):\texmath(\pa)}
                            \text{fon=(\a)*x+(\b)}
                            \text{fon1=simplify(\fon)}
                            \text{fon2=pari(Polrev(\fon1))}
                            \text{texfon=texmath(\fon2)}
                            \text{fonction=\nomfct (x)=\texfon}              
                            \integer{cim=(\a)*(\ant)+(\b)}
                            \integer{tmp=(\a)*(\ant)}
                            \integer{tmp1=\cim-\b}
                            \text{tcim=texmath(\cim)}
                            \if{\b>0}{\text{tim1=\a=1?\(\nomfct (\ant)= \ant + \b\):\(\nomfct (\ant)= \a \times \tant + \b\)}
                                      \text{tim2=\a=1?:\(\nomfct (\ant)=\tmp + \b\)}
                                      \text{tim3=\(\nomfct (\ant)=\tcim\)}
                                      \text{ttmp1=\tcim - \b}
                                     }
                            \if{\b=0}{\text{tim1=\a=1?\(\nomfct (\ant)= \tant\):\(\nomfct (\ant)=\a \times \tant\)}
                                      \text{tim2=\a=1?:\(\nomfct (\ant)=\tcim\)}
                                      \text{ttmp1=\tcim}
                                     }
                            \if{\b<0}{\text{tim1=\a=1?\(\nomfct (\ant)= \ant \b\):\(\nomfct (\ant)= \a \times \tant \b\)}
                                      \text{tim2=\a=1?:\(\nomfct (\ant)= \tmp \b\)}
                                      \text{tim3=\(\nomfct (\ant)=\tcim\)}
                                      \text{ttmp1=\tcim + \absb}
                                     }
                          } 
\real{rcim=\cim}  
                                  
%%Dessin jsxgraph
\text{dessin=JXG.Options.line.highlight = false;
JXG.Options.label.autoPosition = true;
var board=JXG.JSXGraph.initBoard('jsxbox',{boundingbox: [-10,10,10,-10], showCopyright:false, showNavigation:true,keepAspectRatio:true, axis:true,
 grid: {
    drawGrid: true, 
    gridX:    1,     
    gridY:    1      
  }
});
var jsxbox_rep1 = board.create('point',jsxbox_var1,{face:'plus',name:'A',size:8,color:'black',showInfobox:false,snapToGrid:true,label:{fontSize:15}});
var jsxbox_rep2 = board.create('point',jsxbox_var2, {face:'plus',name:'B',size:8,color:'black',showInfobox:false,snapToGrid:true,label:{fontSize:15}});
var d = board.create('line',[jsxbox_rep1,jsxbox_rep2]);
}

\real{xrepA=0}
\real{xrepB=0}
\real{yrepA=0}
\real{yrepB=0}

\text{dessin2=JXG.Options.line.highlight = false;
JXG.Options.label.autoPosition = true;
var board2=JXG.JSXGraph.initBoard('jsxbox2',{boundingbox: [-10,10,10,-10], showCopyright:false, showNavigation:true,keepAspectRatio:true,
 axis:true,
  grid: {
    drawGrid: true, 
    gridX:    1,    
    gridY:    1     
  }
});
var pA = board2.create('point',[0,\b],{face:'plus',name:'A',size:4,color:'black',showInfobox:false,fixed:true,label:{fontSize:15}});
var pB = board2.create('point',[\ant,\rcim], {face:'plus',name:'B',size:4,color:'black',showInfobox:false,fixed:true,label:{fontSize:15}});
var d1 = board2.create('line',[pA,pB],{name:'',color:'green',withLabel:true,label:{color:'green',fontSize:15}});
}
\text{image2=slib(geo2D/jsxgraph jsxbox2 board2,[500x500, min=250px max=350px center],\dessin2)}
\text{test3=}
#include "lang.inc"
\if{\confparm1=1}{\text{name_sol0=\name_sol0a}
                  \text{name_sol1=\name_sol1a}  
                  \text{name_sol3=\name_sol3a}
                  \text{name_quest=\name_questa}
                  \text{name_sol6=\name_sol6a}
                  }
                 {\text{name_sol0=\name_sol0l}
                  \text{name_sol1=\name_sol1l}
                  \text{name_quest=\name_questl}
                  \text{name_sol6=\name_sol6l}
                  }
\if{\confparm2=2}{\text{name_sol4=\name_sol4f}}{\text{name_sol4=\name_sol4e}}
\text{reply_class=euler_answer_nobg}
\statement{
<div class="euler_quest_nobg spacer">\name_quest <span class="nowrap">\(\nomfct(x)=\texfon\).</span></div>
<div class="spacer">
<div class="\reply_class">\embed{r1,400x400
jsxbox board[responsive center min=250px max=500px scroll]
\dessin
jsxbox_var1=[-3,2] ; jsxbox_var2=[3,2]}
  </div>
</div>
} 

\real{xrepA=\rep[1;1]}
\real{xrepB=\rep[2;1]}
\real{yrepA=\rep[1;2]}
\real{yrepB=\rep[2;2]}

\real{test1=\rep[1;2]-(\coefa*(\rep[1;1])+(\b))}
\real{test2=\rep[2;2]-(\coefa*(\rep[2;1])+(\b))}

\answer{}{\rep}{type=jsxgraph}{option=precision=10 }
\condition{\name_condA}{\test1=0 and \rep[1;1] notsamecase \rep[2;1]}
\condition{\name_condB}{\test2=0 and \rep[1;1] notsamecase \rep[2;1]}
\if{\test1=0 and \rep[1;1] notsamecase \rep[2;1] and \test2=0}{\integer{test3=1}}{\integer{test3=0}}
\if{\test3<1}{\text{reply_class=euler_rep_bad_nobg cross}
              }{
              \text{reply_class=euler_rep_good_nobg tick}
              }
\text{dessin2=\dessin2
var pC=board2.create('point',[\xrepA,\yrepA],{name:'',size:4,fixed:true,showInfobox:false,face:'plus',color:'black'});
var pD=board2.create('point',[\xrepB,\yrepB],{name:'',size:4,fixed:true,showInfobox:false,face:'plus',color:'black'});
var d2= board2.create('line',[pC,pD],{name:'',color:'red',dash:2})
}
\text{image2=slib(geo2D/jsxgraph jsxbox2 board2,[350x350, min=250px max=350px left],\dessin2)}
\solution{
<div class="container">
         <div class="image-block">
              <div class="image-wrapper">\image2</div>
              <div class="container"><span style="width:25px; height:25px; display:inline-block;border-color:red;margin-right:0px;background-image:repeating-linear-gradient(
        -45deg,
        red 0,
        red 2px,
        transparent 2px,
        transparent 6px);"></span><span style="color:red">\name_yourans</span>
                 <span style="width:25px; height:25px; background-color:green; display:inline-block; margin-left:20px;margin-right:0px;"></span><span style="color:green">\name_goodans</span>
              </div> 
         </div>
         <div class="table-wrapper">
              <p>\name_sol0 <span class="nowrap">\(\nomfct(x)=\texfon\).</span></p>
              \name_sol1
              <p>\name_sol2</p>
              \name_sol3
              <p>\name_sol4</p>
              \name_sol5
              <p><span class="nowrap">\tim1</span></p>
              <span class="nowrap">\tim2</span>
              <p><span class="nowrap">\tim3</span></p>
              \name_sol7 <span class="nowrap">\(\mathrm{B}(\ant \, ; \, \tcim)\).</span>
              <p>\name_sol6 <span class="nowrap">\(\mathrm{B}(\ant \, ; \, \tcim)\).</span></p>
         </div>
</div>
}
