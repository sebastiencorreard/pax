target=coef

#include "author.inc"
#include "header.inc"
#include "lang_titles.inc"
#include "css.inc"
#include "helpjsx.inc"

\title{TITRE}
\if{\confparm1=}{\text{confparm1=1}}
\if{\confparm2=}{\text{confparm2=1}}

\text{schema=capture.png}

%%Mise en place des coefficients a et b confparm2 =1 entiers relatifs =2 rationnels
\if{1 isitemof \confparm2}{\text{coefe=shuffle(1,2,3,4,5,-1,-2,-3,-4,-5)}}
\if{2 isitemof \confparm2}{\text{coefr=shuffle(1/5,2/5,3/5,4/5,1/4,3/4,5/4,1/3,2/3,4/3,5/3,1/2,3/2,5/2,-1/5,-2/5,-3/5,-4/5,-1/4,-3/4,-5/4,-1/3,-2/3,-4/3,-5/3,-1/2,-3/2,-5/2)}}
\if{\confparm2=1}{\text{coef=\coefe}}
\if{\confparm2=2}{\text{coef=\coefr}}
\if{1 isitemof \confparm2 and 2 isitemof \confparm2}{\text{coef=shuffle(\coefe,\coefr)}}                                        
\rational{coef=\coef[1]}
\text{num=pari(numerator(\coef))} 
\text{den=pari(denominator(\coef))}
\text{sol=\num/\den}
\rational{rsol=\sol}
\text{tsol=\den=1? \num : texmath(\num/\den)}
\if{\confparm2=2 and \den<>1}{\text{solu=\(a=\tsol\)}}{\text{solu=\(a=\frac{\num}{\den}=\tsol)}}
\text{fon=\coef*x}
#include "langjsx.inc"
\text{dessin=JXG.Options.label.autoPosition = true;
JXG.Options.elements.highlight = false;
var bb=[-6,6,6,-6];
var xdep=Math.floor(3/\coef);
var board = JXG.JSXGraph.initBoard('jsxbox', {boundingbox: bb,showCopyright:false,showNavigation:true,axis:true,keepAspectRatio:true,grid:{gridX:1,gridY:1,drawGrid:true}});
var xmin=Math.ceil(bb[0]), xmax=Math.floor(bb[1]);
var graph=board.create('line',[[0,0],[1,\coef]],{strokeWidth:2,strokeColor:'red',fixed:true});
var attractors=[];
for (var i=xmin; i<=xmax;i++) {attractors.push(board.create('point',[i,\coef*i],{visible:true,name:'',size:2,fixed:true,showInfobox:false}));}
var pt=board.create('glider',[-2,\coef*(-2),graph],{name:'A',label:{fontSize:20},face:'cross',size:8,color:'black',showInfobox:false,fixed:false,snapToPoints:true,attractors:attractors,attractorDistance:1,attractorUnit:'user'});
var ptx=board.create('point',[function() {return pt.X();},0],{face:'cross',size:4,color:'brown',visible:false});
board.create('segment',[pt,ptx],{color:'blue',dash:2});

board.create('text',[function() {return pt.X();},0,function(){var x=Number(JXG.toFixed(pt.X(),1));return x.toLocaleString('fr-FR');}],{fontSize: 25,strokeColor: 'blue',anchorX: 'middle',anchorY: function() { return pt.Y()> 0 ? 'top' : 'bottom';},offset: function() {return pt.Y()>0?[0, 10]:[0, -10];}});
var pty=board.create('point',[0,function(){return pt.Y();}],{face:'cross',size: 4,color: 'brown',visible: false});
board.create('segment',[pt,pty],{ color: 'green', dash: 2 });

board.create('text', [0,function(){return pt.Y();},function(){var y=Number(JXG.toFixed(pt.Y(),2));return y.toLocaleString('fr-FR');}],{fontSize: 25,strokeColor: 'green',anchorY: 'middle',anchorX:function(){return pt.X()>0?'right':'left';},offset: function(){return pt.X()>0?[10,0]:[-10, 0];}});
}

\text{image=slib(geo2D/jsxgraph jsxbox board,[350x350, min=250px max=350px left],\dessin)}

%%Dessin jsxgraph de la solution%%
\text{dessin2=JXG.Options.label.autoPosition = true;
JXG.Options.elements.highlight=false;
var bb=[-6,6,6,-6];
var board2= JXG.JSXGraph.initBoard('jsxbox2', {boundingbox: bb,showCopyright:false,showNavigation:true,axis:true,keepAspectRatio:true,grid:{gridX:1,gridY:1,drawGrid:true}});
var xmin=Math.ceil(bb[0]), xmax=Math.floor(bb[1]);
var graph=board2.create('functiongraph',[function(x){ return \fon;}, -50, 50],{strokeColor:'red'});
var attractors=[];
for (var i=xmin; i<=xmax;i++) {attractors.push(board2.create('point',[i,\coef*i],{visible:true,face:'cross',name:'',fixed:true,showInfobox:false}));}
var A=null;
for (var i=0; i<attractors.length; i++){
    var p=attractors[i];
    if (p.X()>0 && Math.abs(p.Y()-Math.round(p.Y()))<0.000001) {
        A=p;
        break;
    }
}
A.setAttribute({size:10,color:'black',name:'A',label:{fontSize:16}});
function startAnimation() {
  blink(A,2000,100);
  var xA=A.X(),yA=A.Y();
  var arrowX=board2.create('arrow',[[0,0],[xA,0]],{color:'blue',dash:2,visible:false});
  var arrowXDep=board2.create('arrow',[[0,0],[0,0]],{color:'blue',dash:2,visible:true});
  var textX=board2.create('text', [xA/2,0,xA],{visible:false,fontSize: 25,strokeColor: 'blue',anchorX: 'middle',anchorY: 'bottom'});
  var arrowY=board2.create('arrow',[[xA,0],A],{color: 'green', dash: 2,visible:false});
  var arrowYDep=board2.create('arrow',[[xA,0],[xA,0]],{color: 'green', dash:2,visible:false});
  var textY=board2.create('text',[xA+0.1,yA/2,yA],{visible:false,fontSize: 25,strokeColor: 'green',anchorX: 'left',anchorY:'middle'});
  var minY=Math.min(0,yA),
      maxY=Math.max(0,yA);   
  var marginX=xA*0.2,
      marginY=(maxY-minY)*0.2;
  var targetBbox2=[
      xA*(-1)*0.2,
      Math.max(0,yA)+marginY,
      xA*1.2,
      Math.min(0,yA)-marginY];          
  setTimeout(function() {
    animateBoundingBox(board2,targetBbox2, 3000);
  }, 2000);
  var step1=0;
  setTimeout(function() {
  (function animateSteps(){
          arrows=[],
          step=0;
     
      function next(){
          if (step<xA) {
              var k=step;     
              var P1= board2.create('point',[k,\coef*k], {visible:false});
              var P2= board2.create('point',[k+1,\coef*k], {visible:false});
              var hArrow = board2.create('arrow',[P1,P2],    {strokeColor:'blue', dash:2});
              var hLabel = board2.create('text',[
                  function(){ return k + 0.5; },
                  function(){ return \coef*k + 0.1; },
                  "1"
              ],{
                  fontSize:14, strokeColor:'blue',
                  anchorX:'middle', anchorY:'bottom',offset:[0,10]
              });
              arrows.push(P1, P2, hArrow, hLabel);
  
              setTimeout(function(){
                  var Q1     = board2.create('point',[k+1,\coef*k],    {visible:false});
                  var Q2     = board2.create('point',[k+1,\coef*(k+1)],{visible:false});
                  var vArrow = board2.create('arrow',[Q1,Q2],{strokeColor:'green', dash:2});
                  var vLabel = board2.create('text',[
                      function(){ return k+1+ 0.1; },
                      function(){ return \coef*k + \coef/2; },
                      "a"
                  ],{
                      fontSize:14, strokeColor:'green',
                      anchorX:'left', anchorY:'middle',offset:[-20,0]
                  });
                  arrows.push(Q1, Q2, vArrow, vLabel);
                  step++;
                  setTimeout(next, 800);
              }, 800);
              } else {
                  if (step1<1){                    
                               var t1=0;
                               var interval1=setInterval(function(){
                                arrowXDep.setAttribute({visible:true});
                                t1+=0.02;
                                var xEnd=xA*t1;
                                arrowXDep.point2.moveTo([xEnd,0],0);
                                if(t1>=1){clearInterval(interval1);
                                arrowX.setAttribute({visible:true});
                                textX.setAttribute({visible:true});
                                var t2=0;
                                                     var interval2=setInterval(function(){
                                                       arrowYDep.setAttribute({visible:true});
                                                       t2+=0.02;
                                                       var yEnd=yA*t2;
                                                       arrowYDep.point2.moveTo([xA,yEnd],0);
                                                       if(t2>=1){clearInterval(interval2);
                                                                 arrowY.setAttribute({visible:true});
                                                                 textY.setAttribute({visible:true});
                                                                 }
                                                                 },100);            
                                          
                                          
                                          
                                          }
                                                                   },100);
                                                         }
         
              arrows.forEach(function(obj){
                  board2.removeObject(obj);
              });
              setTimeout(function(){
                  arrows = [];
                  step   = 0;
                  next();
                  step1++;
                  
              }, 500);
             
          }
      }
      next();                        
      })();
      }, 2000);
}
var btnExt=document.getElementById('startBtn2');
btnExt.addEventListener('click', function(){
            btnExt.disabled = true;
            startAnimation();
                                            });
                                                      
}

\text{image2=slib(geo2D/jsxgraph jsxbox2 board2,[350x350, min=250px max=350px left],\dessin2)}

\integer{test1=2}
\integer{test2=2}
\real{nbcoef=\coef}
#include "lang.inc"
\if{\nbcoef<0}{\text{pente=\name_pented}
             \text{signe=\name_signen}
             }
            {\text{pente=\name_pentem}
             \text{signe=\name_signep}
             }
\text{reply_class=euler_answer_nobg}
\statement{
\name_enon 
<div class="container">
  <div class="image-wrapper">\image</div>
  <div class="table-wrapper">
    <div class="euler_quest_nobg spacer">\name_quest</div>
    <div class="\reply_class"><label for="reply1">\name_ans</label> <span class="nowrap">\embed{reply1,4}.</span></div>
    <div class="wims_instruction spacer">\name_inst</div>
  </div>
</div>}

\answer{\name_goodans}{\rep}{type=numexp}{option=noreduction}
\condition{\name_cond1}{\rep=\sol}
\condition{\name_cond2}{\rep issamecase \rsol}

\integer{test1=\rep=\sol?1:0}
\integer{test2=\rep issamecase \rsol?1:0}
\feedback{\rep=\sol and (\rep notsamecase \rsol)}{<span style="color: red;">\name_feed</span>.}
\if{\test1<1 or \test2<1}{\text{reply_class=euler_rep_bad_nobg cross}
                         }{
                         \text{reply_class=euler_rep_good_nobg tick}
                         }
\solution{
<span style="text-decoration-line: underline" class="font-weight: bold">\name_method1</span>
<div class="container">
  <div class="image-wrapper spacer">
    <button id="startBtn2" style="background-color: #ddd;border: 1px solid #bbb;border-radius: 6px;padding: 8px 14px;font-size: 1rem;cursor: pointer;transition: background 0.2s;margin-bottom: 8px;">Démarrer l’animation</button>
    \image2
  </div>
  <div class="table-wrapper">
    \name_sol1
    <p>\name_sol2</p>
    <div class ="accordion">
      <div>\name_accord</div>
        <div class="box_content">
           <div class="container">
             <div class="image-wrapper">\img{\imagedir/\schema alt="pente" style="width:500px"}<p>\name_illu</p></div>
             <div class="table-wrapper">
               <p>\name_dem1</p>
               \(f(x+1)-f(x)=a \times (x+1)-a \times x\)
               <p>\(f(x+1)-f(x)=a\times x + a \times 1 - a \times x\)</p>
               \(f(x+1)-f(x)=a x + a - a x\)
               <p>\(f(x+1)-f(x)=a\)</p>
             </div>
          </div>
        </div>
      </div>
      \name_sol3 <span class="nowrap">\(A(\den \, ; \,\num)\).</span>
      <p>\name_sol4</p>
      <span class="nowrap">\solu.</span>
    </div>
</div>
<span style="text-decoration-line: underline" class="font-weight: bold">\name_method2</span>
\name_sol5 <span class="nowrap">\(f(x)=a \times x\).</span>
<p>\name_sol6 \(A(\den \, ; \,\num)\).</p>
\name_sol7 <span class="nowrap">\solu.</span>
}

\hint{\name_hint}
\if{\rep>0 and \sol<0}{\text{feed=\name_feed1d}}{\text{feed=\name_feed1m}}

\feedback{\rep*\sol<0}{<div class="highlight">\feed</div>}
