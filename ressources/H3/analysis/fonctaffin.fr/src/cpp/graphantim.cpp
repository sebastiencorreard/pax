target=gant gim

#include "author.inc"
#include "lang_titles.inc"
#include "header.inc"
#include "css.inc"
#include "helpjsx.inc"

\title{TITRE}

\if{\confparm1=}{\text{confparm1=1}}
\if{\confparm1 issametext 1,2}{\text{confparm1=randitem(1,2)}}
\if{\confparm2=}{\text{confparm2=1}}

\text{nom=randitem(f,g,h)}

%%Détermination du coef a (rappel : confparm2 :1 entier, 2 rationnel)
\text{ae=0.5,1.5,2,2.5,-0.5,-1.5,-2,-2.5}
\text{ar=1/2,1/3,1/4,1/5,2/3,2/5,3/2,3/4,3/5,4/3,4/5,5/2,5/3,5/4,-1/2,-1/3,-1/4,-1/5,-2/3,-2/5,-3/2,-3/4,-3/5,-4/3,-4/5,-5/2,-5/3,-5/4}
\if{\confparm2=1}{\text{a=shuffle(\ae)}}
\if{\confparm2=2}{\text{a=shuffle(\ar)}}
\if{1 isitemof \confparm2 and 2 isitemof \confparm2}{\text{a=shuffle(\ae,\ar)}}
\real{a=\a[1]}

\if{\confparm1=1}{\text{tmp=shuffle(-4,-3.5,-3,-2.5,-2,-1.5,-1,-0.5,0.5,1,1.5,2,2.5,3,3.5,4)}
                  \real{b=\tmp[1]}
                 \text{nature=affine}
                 }
                {\integer{b=0}
                \text{nature=linéaire}
                }           
%%Détermination des valeurs du repère pour jsxgraph, de l'antécédent
\integer{tmp1=(-5-\b)/\a}
\integer{tmp2=(5-\b)/\a}              
\if{\a>0 or \a=0}{\integer{xmin=\tmp1}
          \integer{Xmin=\xmin-2}
          \integer{xmax=\tmp2}
          \integer{Xmax=\xmax+1}
         }{\integer{xmin=\tmp2}
           \integer{Xmin=\xmin-2}
           \integer{xmax=\tmp1}
           \integer{Xmax=\xmax+1}
         }                                 
\text{listant=shuffle(wims(makelist x for x=\xmin to \xmax step 0.5))}
\text{ant=\listant[1]}

%%Eviter que l'image de l'image donne l'antécédent
\real{xinter=\b/(1-\a)}
\if{\ant=\xinter and \b<>0}{\real{ant=\ant*(-1)}                  }

\text{fon=\a*x+\b}
\real{img=\a*(\ant)+(\b)}
\text{vimg=slib(numeration/ecriturenombre \img,comma)}
\text{vant=slib(numeration/ecriturenombre \ant,comma)}
\integer{maxi=max(\xmax-2,1)}
\integer{mini=min(\xmin+2,-1)}
\if{\ant<0}{\real{alea=randint(\maxi..\xmax)}}
\if{\ant>0 or \ant=0}{\real{alea=randint(\xmin..\mini)}}

\integer{Ymax=max(5,\a*(\alea)+\b+1)}
\integer{Ymin=min(-5,\a*(\alea)+\b-1)}
\text{ech=\Xmin,\Ymax,\Xmax,\Ymin}
\real{aux=\a+\b}
#include "langjsx_fr.inc"

#if defined TARGET_gant
%%Inversion image et antécédent pour le feedback
\real{xfeed2=\a*(\img)+\b+0.1}                 
\real{xfeed1=\a*(\img)+\b-0.1}

\real{tol1=\ant+0.1}
\real{tol2=\ant-0.1}
\text{don=\vimg}
\real{antarron=(round(\ant*100))/100}
\text{vantarron=slib(numeration/ecriturenombre \antarron,comma)}
\text{deuxlignes=var deuxlignes=antv + '<br>\name_ant'}
\text{uneligne=var uneligne=imgv}
#endif

#if defined TARGET_gim
%%Inversion image et antécédent pour le feedback
\real{xfeed2=(\ant-\b)/\a+0.1}                 
\real{xfeed1=(\ant-\b)/\a-0.1}

\real{tol1=\img+0.1}
\real{tol2=\img-0.1}
\text{don=\vant}
\text{deuxlignes=var deuxlignes=antv}
\text{uneligne=var uneligne=imgv +' \name_im'}
#endif

%%Dessin jsxgraph%%
\text{defautaxe=defaultAxes: {
    x: {ticks:{insertTicks:false,ticksDistance:2,drawLabels:true,minorTicks:0}},
    y:{ticks:{insertTicks:false,ticksDistance: 2,drawLabels:true,minorTicks:0}}
    },  
    grid:{drawGrid:true,gridX:1,gridY:1,}
}
#include "langjsx.inc"
\text{dessin=JXG.Options.label.autoPosition = true;
JXG.Options.elements.highlight = false;
var board=JXG.JSXGraph.initBoard('jsxbox',{boundingbox: [\ech[1],\ech[2],\ech[3],\ech[4]], showCopyright:false, showNavigation:true,axis:true,keepAspectRatio:false,
\defautaxe});
var sx = sessionStorage.getItem('A_x');
var sy = sessionStorage.getItem('A_y');
var initX;
if (sx == null || isNaN(sx) === true) {
  initX = \alea;
} else {
  initX = parseFloat(sx);
}
var initY;
if (sy == null || isNaN(sy) === true) {
  initY = 0;
} else {
  initY = parseFloat(sy);
}
var graph = board.create('line',[[0,\b],[1,\aux]],{strokeWidth:2,strokeColor:'red',fixed:true});
var point = board.create('glider', [initX,initY,graph], {face:'cross',name:'A',label:{fontSize:18},size:8,color:'black',showInfobox:false});
var ptx = board.create('point', [function(){return point.X()},0], {face:'cross',name:'',size:4,color:'brown',showInfobox:false,visible:false});
var tx=board.create('text',[function(){return point.X();},function(){return point.Y()>0?-0.5:0.7;},function(){var x=Number(JXG.toFixed(point.X(),2));
                                                                       return x.toLocaleString('fr-FR');}]
                          ,{fontSize:14,StrokeColor:'blue',anchorX: 'middle',anchorY:function(){return point.Y() > 0 ? 'top' : 'top';}});
var segx=board.create('segment',[point,ptx],{color:'blue',dash:2,strokeWidth:2});
var pty = board.create('point', [0,function(){return point.Y()}], {face:'cross',name:'',size:4,color:'brown',showInfobox:false,visible:false});
var ty=board.create('text',[function(){return point.X()>0?-0.5:0.5;},function(){return point.Y()},function(){var y=Number(JXG.toFixed(pty.Y(),2));
                                                                      return y.toLocaleString('fr-FR');}]
                             ,{fontSize:14,StrokeColor:'green',anchorY: 'middle',anchorX:function(){return point.X() > 0 ? 'right' : 'left';}});
var segy=board.create('segment',[point,pty],{color:'green',dash:2,fontSize:4,strokeWidth:2});
point.on('drag', function() {
var x = Number(JXG.toFixed(this.X(), 2));
var y = Number(JXG.toFixed(this.Y(), 2));
sessionStorage.setItem('A_x', x);
sessionStorage.setItem('A_y', y);
});
}

\text{image=slib(geo2D/jsxgraph jsxbox board,[350x350, min=250px max=350px left],\dessin)}


%%Dessin jsxgraph de la solution%%
\text{dessin2=JXG.Options.label.autoPosition = true;
var board2 = JXG.JSXGraph.initBoard('jsxbox2', {
  boundingbox: [-6,6,6,-6],axis:true,
  showCopyright: false,
  showNavigation: true,
  axis: true,
  keepAspectRatio: false,
\defautaxe});
var graph = board2.create('line',[[0,\b],[1,\aux]],{strokeWidth:2,strokeColor:'red'});
var pMid = board2.create('point', [\ant, \img], {
  name:        '',
  fixed:       true,
  face:        'cross',
  size:        8,
  color:       'black',
  showInfobox: false,
  visible:     false,
});

var pant = board2.create('point', [\ant,0], {
  name:        '',
  fixed:       true,
  face:        '',
  size:        4,
  color:       'brown',
  showInfobox: false,
  visible:     false,
});

var pimg = board2.create('point', [0,\img], {
  name:        '',
  fixed:       true,
  face:        '',
  size:        4,
  color:       'brown',
  showInfobox: false,
  visible:     false,
});
var ant=Number(\ant);
var antv=ant.toLocaleString('fr-FR');
\deuxlignes;
var tant = board2.create('text', [\ant,function() { return \img > 0 ?-0.3:0.2;},deuxlignes], {
  fontSize:   14,
  strokeColor:'blue',
  visible:    false,
  anchorX:    'middle',
  anchorY:    function() { return \img > 0 ? 'top' : 'bottom'; },
});
var img=Number(\img);
var imgv=img.toLocaleString('fr-FR');
\uneligne;
var timg = board2.create('text', [function() { return \ant > 0 ? -0.2:0.2;}, \img,uneligne], {
  fontSize:   14,
  strokeColor:'green',
  visible:    false,
  anchorY:    'middle',
  anchorX:    function() { return \ant > 0 ? 'right' : 'left'; }});
var xA = pMid.X(), yA = pMid.Y(); 
var xA = pMid.X(), yA = pMid.Y(); 
var targetBbox2;
if (yA > 0 && xA > 0) {targetBbox2=[-1.5,yA*1.3,xA*1.3,-1.5];}
else if (yA > 0 && xA < 0) {targetBbox2 = [xA*1.3,yA*1.3,1.5,-1.5];}
else if (yA < 0 && xA > 0) {targetBbox2 = [-1.5,1.5,xA*1.3,yA*1.3];}
else if (yA < 0 && xA < 0) {targetBbox2 = [xA*1.3,1.5,1.5,yA*1.3];}
else targetBbox2 = board2.getBoundingBox();
}

#if defined TARGET_gim
\text{dessin2=\dessin2
function startAnimation(){
tant.setAttribute({size:10,color:'blue',visible:false});
blink(tant,3000,100);
pMid.setAttribute({visible:false});
tant.setAttribute({visible:true});
timg.setAttribute({visible:false});
var arrow1 = board2.create('arrow',[[\ant,0],[\ant,0]],{strokeColor:'blue',lastArrow:1,dash:2});
var t1 = 0;
var interval1 = setInterval(function(){
    t1+= 0.02;
    arrow1.point2.moveTo([\ant, t1*\img],0);
    if(t1>=1){
      clearInterval(interval1);
      arrow1.setAttribute({visible:true});
      pMid.setAttribute({visible:true});
      arrow1.setAttribute({lastArrow:0});
      setTimeout(startArrow2,500);
      }
     },30);
  function startArrow2(){
    var arrow2=board2.create('arrow',[[\ant,\img],[\ant,\img]],{strokeColor:'green',lastArrow:1,dash:2});
    var t2=0;
    var interval2=setInterval(function(){
    t2+=0.02;
    var xEnd=\ant*(1-t2);
    arrow2.point2.moveTo([xEnd,\img], 0);
      if(t2>=1){
        clearInterval(interval2);
        timg.setAttribute({visible:true});
        arrow2.setAttribute({lastArrow:0});
        blink(timg,3000,100);
   setTimeout(function(){
          board2.removeObject(arrow1);
          board2.removeObject(arrow2);
          timg.setAttribute({visible:false});
          pMid.setAttribute({visible:false});
          startAnimation();
          },3000);
           
        }
        
    },30);
  }
  }

var btnExt = document.getElementById('startBtn2');
  btnExt.addEventListener('click', function() {
    btnExt.disabled = true;
    blink(tant,3000,100); 
    setTimeout(animateBoundingBox(board2, targetBbox2, 2400),3000);
    setTimeout(startAnimation, 1250);
  });
}
#endif

#if defined TARGET_gant
\text{dessin2=\dessin2
function startAnimation(){
  timg.setAttribute({size:10,color:'green',visible:false});
  blink(timg,3000,100);
  pMid.setAttribute({visible:false});
  timg.setAttribute({visible:true});
  tant.setAttribute({visible:false});
  var arrow1 = board2.create('arrow',[[0,\img],[0,\img]],{strokeColor:'green',lastArrow:1,dash:2});
  var t1 = 0;
  var interval1 = setInterval(function(){
    t1+= 0.02;
    arrow1.point2.moveTo([t1*\ant, \img], 0);
    if(t1>=1){
      clearInterval(interval1);
      pMid.setAttribute({visible:true});
      arrow1.setAttribute({lastArrow:0});
      setTimeout(startArrow2,500);     
           }
    },30);
    function startArrow2(){
      var arrow2=board2.create('arrow',[[\ant,\img],[\ant,\img]],{strokeColor:'blue',lastArrow:1,dash:2});
      var t2=0;
      var interval2=setInterval(function(){
      t2+=0.02;
      var yEnd=\img*(1-t2);
      arrow2.point2.moveTo([\ant,yEnd],0);
      if(t2>=1){
        clearInterval(interval2);
        arrow1.setAttribute({visible:true});
        tant.setAttribute({visible:true});
        arrow2.setAttribute({lastArrow:0});
        blink(tant,3000,100);
        setTimeout(function(){
          board2.removeObject(arrow1);
          board2.removeObject(arrow2);
          tant.setAttribute({visible:false});
          pMid.setAttribute({visible:false});
          startAnimation();
          },3000);
        }     
    },30);
  }
  }
var btnExt = document.getElementById('startBtn2');
  btnExt.addEventListener('click', function() {
    btnExt.disabled = true;
    blink(timg,3000,100);
    setTimeout(animateBoundingBox(board2, targetBbox2, 1200),6000);
    setTimeout(startAnimation, 1250);
  });
}
#endif

\text{image2=slib(geo2D/jsxgraph jsxbox2 board2,[350x350, min=250px max=350px left],\dessin2)}
#include "lang.inc"
\text{enon=\confparm1=1?\name_enona:\name_enonl}
\text{reply_class=euler_answer_nobg}

\statement{
\enon <span class="nowrap">\(\nom\).</span>
<div class="container">
  \image
  <div>
    <div class="euler_quest_nobg spacer">\name_quest1</div>
    <div class="\reply_class"><label for="reply1">\name_quest2 \(\don\) \name_quest3 </label> \embed{r1,5}.</div>
<div class="wims_instruction spacer">\name_instr</div>
</div>
</div>}

\answer{\name_cond}{\rep}{type=auto}
\text{rep1=wims(replace internal , by . in \rep)}
\if{\rep1>\tol2 and \rep1<\tol1}{\integer{test=1}}{\integer{test=0}}
\if{\test<1}{\text{reply_class=euler_rep_bad_nobg cross}
                 }{
                  \text{reply_class=euler_rep_good_nobg tick}
                  }
\condition{\name_cond}{\test=1}

\feedback{\rep1<\xfeed2 and \rep1>\xfeed1 and \b<>0}{<div class="highlight">\name_feed</div>}  
               
\solution{
<div class="container">
   <div class="image-block">
     <button id="startBtn2"  style="background-color: #ddd;border: 1px solid #bbb;border-radius: 6px;padding: 8px 14px;font-size: 1rem;cursor: pointer;transition: background 0.2s;margin-bottom: 8px;">Démarrer l’animation</button>
     <div class="image-wrapper">\image2</div>
   </div>
   <div class="table-wrapper">\name_ans1
    <p>\name_ans2 <span class="nowrap">\(\nom\).</span></p>
   </div>
</div>
}

\hint{\name_hint}
