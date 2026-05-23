target= coeq,cof

%% Inspiré d'un ex de Fabrice Guérimand.
#include "css.inc"
#include "author.inc"
#include "header.inc"
#include "lang_titles.inc"
#include "helpjsx.inc"

#if defined TARGET_cof
#define TYPE 1
#endif

#if defined TARGET_coeq
#define TYPE 2
#endif

\if{\confparm1=}{\text{confparm1=1}}
\if{\confparm1 issametext 1,2}{\text{confparm1=randitem(1,2)}}
\if{\confparm2=}{\text{confparm2=1}}
\if{\confparm3=}{\text{confparm3=3}}


\title{TITRE}
\integer{type=TYPE}

\if{\confparm3=3}{\integer{number=3}}
\if{\confparm3=4}{\integer{number=4}}
\if{\confparm3=5}{\integer{number=5}}
\if{3 isitemof \confparm3 and 4 isitemof \confparm3}{\integer{number=random(3,4)}}
\if{3 isitemof \confparm3 and 5 isitemof \confparm3}{\integer{number=random(3,5)}}
\if{4 isitemof \confparm3 and 5 isitemof \confparm3}{\integer{number=random(4,5)}}
\if{3 isitemof \confparm3 and 4 isitemof \confparm3 and 5 isitemof \confparm3}{\integer{number=random(3,4,5)}}

\if{\type=1}{\text{size=80x150x100}
            }{
             \text{size=80x150x100}
             }
             
#include "lang.inc"

%%Détermination du nombre b (rappel:Confparm1=1 affine, confparm1=2 lineaire)
\text{b=}
\for{j=1 to \number}{\if{\confparm1=2}{\integer{tmp=0}}
                                      {\integer{tmp=random(1,-1)*(randint(1..5))}}
                      \text{b=wims(append item \tmp to \b)}
                    
                    }
\integer{maxb=(pari(vecmax([\b])))+3}
\integer{minb=(pari(vecmin([\b])))-3}               
%%Détermination du coef a (rappel : confparm2 :1 entier, 2 rationnel)
\text{ae=1,2,3,4,5}
\text{ar=1/2,1/3,1/4,1/5,2/3,2/5,3/2,3/4,3/5,4/3,4/5,5/2,5/3,5/4}
\text{ae=random(1,-1)*\ae}
\text{ar=random(1,-1)*\ar}
\if{\confparm2=1}{\text{a=\ae}}
\if{\confparm2=2}{\text{a=\ar}}
\if{1 isitemof \confparm2 and 2 isitemof \confparm2}{\text{a=\ae,\ar}}                           
\text{a=shuffle(\a)}
\matrix{co=\(d_1\) \name_red,\(d_1\),#FF0000
\(d_2\) \name_orange,\(d_2\),#FFA500
\(d_3\) \name_brown,\(d_3\),#8B4513
\(d_4\) \name_blue,\(d_4\),#0000FF
\(d_5\) \name_black,\(d_5\),#000000}
\text{mix=shuffle(rows(\co))}
\matrix{co=\co[\mix[1..\number];]}
\text{coord=}
\text{graphe=}
\for{i=1 to \number}{\text{A=\a[\i]}
                     \text{B=\b[\i]}
                     
                     \text{graph=
                     
                     var graph\i=board.create('line',[[-10,-10*\A+\B],[10,10*\A+\B]],{name:'\co[\i;2]',fixed:true,withLabel:true,strokeColor:'\co[\i;3]',strokeWidth: 2,label:{anchorX:'middle',anchorY:'middle',offset:[ 10, 10 ],offsetUnit: 'screen'}});
                    }
                     \text{graphe=wims(append item \graph to \graphe)}
                    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                     \text{val=simplify(\A*x+\B)}
                     text{val=wims(replace internal * by in \val)}
                     \text{val=pari(Polrev(\val))}
                     \text{val=texmath(\val)}
                     \text{tmp=\type=1?\(x \mapsto \val):\(y=\val)}
                     \text{coord=wims(append item \tmp to \coord)}
                    }
%%Dessin jsxgraph%%
\text{script=JXG.Options.label.autoPosition = false;
JXG.Options.elements.highlight = false;
var board=JXG.JSXGraph.initBoard('jsxbox',{boundingbox: [-5,\maxb,5,\minb],axis:true, showCopyright:false, showNavigation:true,keepAspectRatio:false});
\graphe[1]
\graphe[2]
\graphe[3]
\graphe[4]
\graphe[5]
}
%%Fin dessin jsxgraph%%
\text{image=slib(geo2D/jsxgraph jsxbox brd,[500x500, min=250px max=350px left],
\script)}



\statement{
<div class="euler_quest_nobg spacer">\name_quest</div>
<div class="container">
  <div class="image-wrapper">\image</div>
  <div class="table-wrapper">
    \embed{r1,\size}
  </div>
</div>

}

\answer{Réponse}{\coord;\co[;1]}{type=correspond}
