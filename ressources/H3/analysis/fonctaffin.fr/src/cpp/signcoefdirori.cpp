target=scol scora

#include "author.inc"
#include "header.inc"
#include "lang_titles.inc"
#include "css.inc"
#include "helpjsx.inc"

\title{TITRE}
\if{\confparm1=}{\text{confparm1=1}}
\if{\confparm2=}{\text{confparm2=1}}


\text{nom=random(f,g,h)}

\integer{\confparm1=1}

#if TARGET_scol
\integer{\confparm1=2}
#endif

%%Mise en place des coefficients a et b confparm1 =1 affine =2 lineaire
\text{coefe=1,2,3,4,5,-1,-2,-3,-4,-5}
\text{coefr=1/2,1/3,1/4,1/5,2/3,2/5,3/2,3/4,3/5,4/3,4/5,5/2,5/3,5/4,-1/2,-1/3,-1/4,-1/5,-2/3,-2/5,-3/2,-3/4,-3/5,-4/3,-4/5,-5/2,-5/3,-5/4}
\text{coef=shuffle(\coefe,\coefr)}
\text{coefa=\coef[1]}
\if{\confparm1=2}{\text{coefb=0}}
                 {\text{tmp=shuffle(-5,-4,-3,-2,-1,1,2,3,4,5)}
                  \text{coefb=\tmp[1]}
                 }
#include "lang.inc"
#if defined TARGET_scol
\text{script= var board = JXG.JSXGraph.initBoard('jxgbox', {
axis:true,boundingbox: [-10, 10, 10, -10], grid:true,showCopyright:false});
var d = board.create('functiongraph',[function (x) {return \coefa*x+\coefb},-50,50],{highlight:false});
}
\text{ans1=\name_ansl}
#endif

#if defined TARGET_scora
\text{script= var board = JXG.JSXGraph.initBoard('jxgbox', {
axis:true,boundingbox: [-10, 10, 10, -10], grid:true,showCopyright:false});
var sx = sessionStorage.getItem('A_x');
var sy = sessionStorage.getItem('A_y');
var initX, initY;
  if (sx === null || isNaN(sx)) {
    initX = -2;
  } else {
    initX = parseFloat(sx);
  }
  if (sy === null || isNaN(sy)) {
    initY = -2 * \coefa + \coefb;
  } else {
    initY = parseFloat(sy);
  }
var d = board.create('functiongraph',[function (x) {return \coefa*x+\coefb},-50,50],{highlight:false});
var pt=board.create('glider',[initX,initY,d],{name:'A',face:'cross',size:8,color:'black',showInfobox:false,fixed:false,label:{fontSize:14}});
var ptx=board.create('point',[function() {return pt.X();},0],{face:'cross',size:4,color:'brown',visible:false});
board.create('segment',[pt,ptx],{color:'blue',dash:2});
board.create('text',[function() {return pt.X();},0,function(){var s = JXG.toFixed(pt.X(), 2);var x = Number(s);return x.toLocaleString('fr-FR');}],{fontSize: 25,strokeColor: 'blue',anchorX: 'middle',anchorY: function() { return pt.Y()> 0 ? 'top' : 'bottom';},offset: function() {return pt.Y()>0?[0, 10]:[0, -10];}});
var pty=board.create('point',[0,function(){return pt.Y();}],{face:'cross',size: 4,color: 'brown',visible: false});
board.create('segment',[pt,pty],{ color: 'green', dash: 2 });
board.create('text', [0,function(){return pt.Y();},function() {var s = JXG.toFixed(pt.Y(), 2);var y = Number(s);return y.toLocaleString('fr-FR');}],{fontSize: 25,strokeColor: 'green',anchorY: 'middle',anchorX:function(){return pt.X()>0?'right':'left';},offset: function(){return pt.X()>0?[10,0]:[-10, 0];}});
pt.on('drag', function() {
    var x = Number(JXG.toFixed(this.X(), 2));
    var y = Number(JXG.toFixed(this.Y(), 2));
    sessionStorage.setItem('A_x', x);
    sessionStorage.setItem('A_y', y);
  });
}
#endif

\text{scriptsol= var brd2 = JXG.JSXGraph.initBoard('jxgbox2', {
axis:true,boundingbox: [-10, 10, 10, -10], grid:true,showCopyright:false,highlight:false});
var d = brd2.create('functiongraph',[function (x) {return \coefa*x+\coefb},-50,50]);
var p1= brd2.create('point', [-10,\coefa*(-10)+\coefb+1],{face:'',name:''});
var p2= brd2.create('point', [-1,\coefa*(-1)+\coefb+1],{face:'',name:''});
var l1 = brd2.create('arrow', [p1, p2],{highlight:false});
}
#include "langjsx.inc"             
#if TARGET_scora
\text{scriptsol=\scriptsol
var p = brd2.create('point',[0,\coefb],{fixed:'true',face:'cross',withLabel:true,name:'\coefb',label:{fontSize:24,anchorX:'right',anchorY:'middle',offset:[-5,0]}});
var t2 = brd2.create('text',[1.5,\coefb,"\name_ordo"],{fontSize:20});
var a=brd2.create('arrow',[[1.3,\coefb],[0.2,\coefb]],{fixed:true, visible:true, color:'red'});
}
\text{ans1=\name_ansa}
#endif

\text{image=slib(geo2D/jsxgraph jxgbox brd,[350x350, min=250px max=350px left],\script)}
\text{imagesol=slib(geo2D/jsxgraph jxgbox2 brd2,[350x350, min=250px max=350px left],\scriptsol)}

\text{liste=\name_signen[1],\name_signep[1]}
\if{\coefa>0}{\text{sign=2}
              \text{depl=\name_signep[2]}
              }{
              \text{sign=1}
              \text{depl=\name_signen[2]}       
              }
\text{signe=\liste[\sign]}
\text{reply_class1=euler_answer_nobg}
\text{reply_class2=euler_answer_nobg}
\statement{\name_enon
<div class="container">
  <div class="image-wrapper">\image</div>
  <div class="table-wrapper">
    <div class="euler_quest_nobg">\name_quest1</div>
    <div class="\reply_class1">\ans1 <span class="nowrap">\embed{reply1}.</span></div> 
#if defined TARGET_scora
    <div class="euler_quest_nobg spacer">\name_quest2</div>
    <div class="\reply_class2"><label for="reply2">\name_ans2</label><span class="nowrap">\embed{reply2,5}.</span></div>
#endif
  </div>
</div>
}
\hint{\name_hint
<p>\name_hinta</p>
\name_hintb}
\answer{}{\sign;\liste}{type=radio}{option=sort}
\if{\sc_reply1<1}{\text{reply_class1=euler_rep_bad_nobg cross}
              }{
              \text{reply_class1=euler_rep_good_nobg tick}
              }
#if defined TARGET_scora
\answer{}{\coefb}{type=litexp}
\if{\sc_reply2<1}{\text{reply_class2=euler_rep_bad_nobg cross}
              }{
              \text{reply_class2=euler_rep_good_nobg tick}
              }
#endif

#if defined TARGET_scora
\solution{
<div class="container">
  <div class="image-wrapper">\imagesol</div>
  <div class="table-wrapper">
    \name_enon
    <ul><li>\name_hinta
    <p>\name_sol[1] \depl \name_sol[2] \liste[\sign].</p>
    \name_solaa <span class="nowrap">\liste[\sign].</span></li>
    <li><p>\name_hintb</p>
    \name_sol3 <span class="nowrap">\(\coefb\).</span></li>
    </ul>
  </div>
</div>
}
#endif
#if defined TARGET_scol
\solution{
<div class="container">
  <div class="image-wrapper">\imagesol</div>
  <div class="table-wrapper">
    \name_enon
    <p>\name_hinta</p>
    \name_sol[1] \depl \name_sol[2] \liste[\sign].
    <p>\name_soll \liste[\sign].</p>
  </div>
</div>
}
#endif
