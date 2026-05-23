target=tval

#include "author.inc"
#include "lang_titles.inc"
#include "header.inc"
#include "helpjsx.inc"
#include "css.inc"

\title{TITRE}
\if{\confparm1=}{\text{confparm1=1}}
\if{\confparm1 issametext 1,2}{\text{confparm1=randitem(1,2)}}
\if{\confparm2=}{\text{confparm2=1}}

\keywords{functions,graphing}

%%Mise en place des coefficients a et b confparm1 =1 affine =2 lineaire
\text{coef=shuffle(0.5,1,1.5,2,2.5,3,-0.5,-1,-1.5,-2,-2.5,-3)}
\text{coef=\coef[1]}
\if{\confparm1=1}{\text{tmp=shuffle(-5,-4,-3,-2,-1,1,2,3,4,5)}
                  \text{b=\tmp[1]}
                 }
                {\text{b=0}
                }
%% Choix de 4 points dans le cadre
\text{x=randint(-6..-4),randint(-3..-1),randint(0..3),randint(4..6)}
\real{y1=\coef*\x[1]+\b}
\real{y2=\coef*\x[2]+\b}
\real{y3=\coef*\x[3]+\b}
\real{y4=\coef*\x[4]+\b}
\if{\y1>0 or \y1=0}{\text{offAx=-8,-10}}{\text{offAx=-8,30}}
\text{offAy=10,3}
\if{\y2>0 or \y2=0}{\text{offBx=-8,-10}}{\text{offBx=-8,30}}
\text{offBy=10,15}
\if{\y3>0 or \y3=0}{\text{offCx=-5,-10}}{\text{offCx=-8,30}}
\text{offCy=-40,15}
\if{\y4>0 or \y4=0}{\text{offDx=-8,-10}}{\text{offDx=-8,30}}
\text{offDy=-30,15}
\integer{haut=max(abs(\y1),max(abs(\y2),max(abs(\y3),abs(\y4))))+2}

\text{montab2=<table id="mytab2" class="wimsborder mytab2" style="font-size: 16px; width: 100%; border-collapse: collapse;">
    <tr>
        <td></td>
        <td>\(A\)</td>
        <td>\(B\)</td>
        <td>\(C\)</td>
        <td>\(D\)</td>
    </tr>
    <tr>
        <td>\(x\)</td>
        <td>\(\x[1]\)</td>
        <td>\(\x[2]\)</td>
        <td>\(\x[3]\)</td>
        <td>\(\x[4]\)</td>
    </tr>
    <tr>
        <td>\(f(x)\)</td>
        <td>\(\y1\)</td>
        <td>\(\y2\)</td>
        <td>\(\y3\)</td>
        <td>\(\y4\)</td>
    </tr>
</table>}

%% Dessin jsxgraph%%
\text{script=JXG.Options.elements.highlight = false;
JXG.Options.elements.tabindex=-1;
var board = JXG.JSXGraph.initBoard('jsxbox', {
    boundingbox: [-7,\haut,7,-\haut],
    showCopyright:false,
    keepAspectRatio:false,
    axis: true,
    grid: {
    drawGrid: true,  
    gridX:    1,     
    gridY:    1      
  }});
    var graph = board.create('functiongraph',[function(x){ return \coef*x+\b;}, -15, 15]);
    var ptA = board.create('point', [\x[1], \y1], { name: 'A', size: 6, color: 'black',face:'plus',showInfobox:false,fixed:true,label:{fontSize:25}});
    var ptB = board.create('point', [\x[2], \y2], { name: 'B', size: 6, color: 'black',face:'plus',showInfobox:false,fixed:true,label:{fontSize:25}});
    var ptC = board.create('point', [\x[3], \y3], { name: 'C', size: 6, color: 'black',face:'plus',showInfobox:false,fixed:true,label:{fontSize:25}});
    var ptD = board.create('point', [\x[4], \y4], { name: 'D', size: 6, color: 'black',face:'plus',showInfobox:false,fixed:true,label:{fontSize:25}});
    }
%% Dessin jsxgraph de la solution%%
\text{script2=var board2 = JXG.JSXGraph.initBoard('jsxbox2', {
    boundingbox: [-7, \haut, 7, -\haut],
    showCopyright: false,
    keepAspectRatio: false,
    axis: true,
    grid: {
    drawGrid: true,  
    gridX:    1,     
    gridY:    1     
  }
});
var ptA = board2.create('point', [\x[1], \y1], { name: 'A', size: 6, color: 'black', face: 'plus', showInfobox: false, fixed: true,label:{fontSize:25} });
var ptB = board2.create('point', [\x[2], \y2], { name: 'B', size: 6, color: 'black', face: 'plus', showInfobox: false, fixed: true,label:{fontSize:25} });
var ptC = board2.create('point', [\x[3], \y3], { name: 'C', size: 6, color: 'black', face: 'plus', showInfobox: false, fixed: true,label:{fontSize:25} });
var ptD = board2.create('point', [\x[4], \y4], { name: 'D', size: 6, color: 'black', face: 'plus', showInfobox: false, fixed: true,label:{fontSize:25} });
var graph = board2.create('line', [ptA,ptB],{strokeWidth:2,strokeColor:'blue'});
var Ax = board2.create('point', [\x[1], 0], { name: '\x[1]', visible: false, color: 'blue', strokeColor: 'red', face: 'cross', showInfobox: false, fixed: true, label: {fontSize:25,autoPosition: false,anchorX:'middle',anchorY:'top', offset: [\offAx[1], \offAx[2]], color: 'blue'} });
var Ay = board2.create('point', [0, \y1], { name: '\y1', visible: false, color: 'green', strokeColor: 'red', face: 'cross', showInfobox: false, fixed: true, label: {fontSize:25, autoPosition: false,anchorX:'left',anchorY:'middle', offset: [\offAy[1], \offAy[2]], color: 'green' } });
var dxA = board2.create('segment', [[\x[1], \y1], [0, \y1]], { size: 2, color: 'green', dash: 1, fixed: true });
var dyA = board2.create('segment', [[\x[1], \y1], [\x[1], 0]], { size: 2, color: 'blue', dash: 1, fixed: true });

var Bx = board2.create('point', [\x[2], 0], { name: '\x[2]', visible: false, color: 'blue', strokeColor: 'red', face: 'cross', showInfobox: false, fixed: true, label: {fontSize:25, autoPosition: false,anchorX:'middle',anchorY:'top', offset: [\offBx[1], \offBx[2]], color: 'blue' } });
var By = board2.create('point', [0, \y2], { name: '\y2', visible: false, color: 'green', strokeColor: 'red', face: 'cross', showInfobox: false, fixed: true, label: {fontSize:25, autoPosition: false,anchorX:'left',anchorY:'middle', offset: [\offBy[1], \offBy[2]], color: 'green' } });
var dxB = board2.create('segment', [[\x[2], \y2], [0, \y2]], { size: 2, color: 'green', dash: 1, fixed: true });
var dyB = board2.create('segment', [[\x[2], \y2], [\x[2], 0]], { size: 2, color: 'blue', dash: 1, fixed: true });

var Cx = board2.create('point', [\x[3], 0], { name: '\x[3]', visible: false, color: 'blue', strokeColor: 'red', face: 'cross', showInfobox: false, fixed: true, label: {fontSize:25, autoPosition: false,anchorX:'middle',anchorY:'top', offset: [\offCx[1], \offCx[2]], color: 'blue' } });
var Cy = board2.create('point', [0, \y3], { name: '\y3', visible: false, color: 'green', strokeColor: 'red', face: 'cross', showInfobox: false, fixed: true, label: {fontSize:25, autoPosition: false,anchorX:'left',anchorY:'middle', offset: [\offCy[1], \offCy[2]], color: 'green' } });
var dxC = board2.create('segment', [[\x[3], \y3], [0, \y3]], { size: 2, color: 'green', dash: 1, fixed: true });
var dyC = board2.create('segment', [[\x[3], \y3], [\x[3], 0]], { size: 2, color: 'blue', dash: 1, fixed: true });

var Dx = board2.create('point', [\x[4], 0], { name: '\x[4]',visible: false, color: 'blue', strokeColor: 'red', face: 'cross', showInfobox: false, fixed: true, label: {fontSize:25, autoPosition: false,anchorX:'middle',anchorY:'top', offset: [\offDx[1], \offDx[2]], color: 'blue' } });
var Dy = board2.create('point', [0, \y4], { name: '\y4', visible: false, color: 'green', strokeColor: 'red', face: 'cross', showInfobox: false, fixed: true, label: {fontSize:25, autoPosition: false,anchorX:'left',anchorY:'middle', offset: [\offDy[1], \offDy[2]], color: 'green' } });
var dxD = board2.create('segment', [[\x[4], \y4], [0, \y4]], { size: 2, color: 'green', dash: 1, fixed: true });
var dyD = board2.create('segment', [[\x[4], \y4], [\x[4], 0]], { size: 2, color: 'blue', dash: 1, fixed: true });

var groups = {
    A: { main: ptA, auxPoints: [Ax, Ay], segments: [dxA, dyA] },
    B: { main: ptB, auxPoints: [Bx, By], segments: [dxB, dyB] },
    C: { main: ptC, auxPoints: [Cx, Cy], segments: [dxC, dyC] },
    D: { main: ptD, auxPoints: [Dx, Dy], segments: [dxD, dyD] },
};

var letters = ["A", "B", "C", "D"];
var currentIndex = 0;
var btnExt = document.getElementById('startBtn2');
  btnExt.addEventListener('click', function() {
    btnExt.disabled = true;
    setTimeout(animateBoundingBox(board2, targetBbox2, 1200),1000);
    setTimeout(startAnimation, 600);
  });
}
  
\text{image=slib(geo2D/jsxgraph jsxbox board,[350x350, min=250px max=350px center],\script)}
\text{image2=slib(geo2D/jsxgraph jsxbox2 board2,[350x350, min=250px max=350px center],\script2)}
#include "lang.inc"
\text{name_enon=\confparm1=1?\name_enona:\name_enonl}
\text{reply_class=euler_answer_nobg}
\statement{\name_enon
<div class="container">
  <div class="image-wrapper">\image</div>
  <div>
    <div class="euler_quest_nobg spacer">\name_quest</div>
      <div class="\reply_class" style="padding:30px">
         <table id="mytab" class="wimsborder">
          <tr>
           <td></td>
           <td><label for="reply1">\(\mathrm{A}\)</label></td>
           <td><label for="reply2">\(\mathrm{B}\)</label></td>
           <td><label for="reply3">\(\mathrm{C}\)</label></td>
           <td><label for="reply4">\(\mathrm{D}\)</label></td>
          </tr>
          <tr>
           <td>\(x\)</td>
           <td>\embed{r1,4}</td>
           <td>\embed{r3,4}</td>
           <td>\embed{r5,4}</td>
           <td>\embed{r7,4}</td>
          </tr>
          <tr>
           <td>\(f(x)\)</td>
           <td>\embed{r2,4}</td>
           <td>\embed{r4,4}</td>
           <td>\embed{r6,4}</td>
           <td>\embed{r8,4}</td>
          </tr>
        </table>
     </div>
  </div>
</div>
}

if{\sc_reply1<1 or \sc_reply2<1 or \sc_reply3<1 or \sc_reply4<1 or \sc_reply5<1 or \sc_reply6<1 or \sc_reply7<1 or \sc_reply8<1}{
      \text{reply_class=euler_rep_bad_nobg cross}
      }{
      \text{reply_class=euler_rep_good_nobg tick}
      }
\if{\repx1<>\x[1] or \repy1<\y1 or \repx2<\x[2] or \repy2<\y2 or \repx3<\x[3] or \repy3<\y3 or \repx4<\x[4] or \repy4<\y4}{
      \text{reply_class=euler_rep_bad_nobg cross}
      }{
      \text{reply_class=euler_rep_good_nobg tick}
      }     
      
      
\answer{}{\repx1}{type=auto}
\answer{}{\repy1}{type=auto}
\answer{}{\repx2}{type=auto}
\answer{}{\repy2}{type=auto}
\answer{}{\repx3}{type=auto}
\answer{}{\repy3}{type=auto}
\answer{}{\repx4}{type=auto}
\answer{}{\repy4}{type=auto}     
\real{repx1=wims(replace internal , by . in \repx1)}
\real{repy1=wims(replace internal , by . in \repy1)}
\real{repx2=wims(replace internal , by . in \repx2)}
\real{repy2=wims(replace internal , by . in \repy2)}
\real{repx3=wims(replace internal , by . in \repx3)}
\real{repy3=wims(replace internal , by . in \repy3)}
\real{repx4=wims(replace internal , by . in \repx4)}
\real{repy4=wims(replace internal , by . in \repy4)}
\condition{\name_cond}{\repx1=\x[1]}
\condition{\name_cond}{\repy1=\y1}
\condition{\name_cond}{\repx2=\x[2]}
\condition{\name_cond}{\repy2=\y2}
\condition{\name_cond}{\repx3=\x[3]}
\condition{\name_cond}{\repy3=\y3}
\condition{\name_cond}{\repx4=\x[4]}
\condition{\name_cond}{\repy4=\y4}

\text{listrep=\repx1,\repx2,\repx3,\repx4,\repy1,\repy2,\repy3,\repy4}
\text{listinv=\y1,\y2,\y3,\y4,\x}
\feedback{\listrep issamecase \listinv}{<div class="highlight">\name_feed}
      
\hint{\name_hint}

\solution{
<div class="container">
  <div class="image-block">
    <button id="startBtn2"  style="background-color: #ddd;border: 1px solid #bbb;border-radius: 6px;padding: 8px 14px;font-size: 1rem;cursor: pointer;transition: background 0.2s;margin-bottom: 8px;">Démarrer l’animation</button>
    <div class="image_wrapper">\image2</div>
  </div>
  <div class="table-wrapper spacer">\name_hint<p>\name_sol1</p>
    \montab2
  </div>
</div>

<script type="text/javascript">
function resetGraph() {
    for (var letter in groups) {
        groups[letter].main.setAttribute({ color: 'black', size: 6, face: 'cross', visible: true, label:{color:'black'}});
        groups[letter].auxPoints.forEach(function(pt) {
            pt.setAttribute({ visible: false,visible: false });
        });
        groups[letter].segments.forEach(function(seg) {
            seg.setAttribute({ visible: false });
        });
    }
}

function highlightGroup(letter) {
    resetGraph();
    groups[letter].main.setAttribute({ color: 'blue', size: 6, face: 'cross',withLabel:true,label:{color:'red',fontSize:25}});
    groups[letter].auxPoints.forEach(function(pt) {
        pt.setAttribute({ visible: true});
    });
    groups[letter].segments.forEach(function(seg) {
        seg.setAttribute({ visible: true });
    });
    updateTableHighlight(letter);
        
}

function updateTableHighlight(letter) {
  var table = document.getElementById("mytab2");
  var colMap = { A: 1, B: 2, C: 3, D: 4 };
  var colIndex = colMap[letter];
  var defaultRowColors = ['white', 'lightblue', 'lightgreen'];
  var rows = table.getElementsByTagName("tr");
  for (var i = 0; i < rows.length; i++) {
    var cells = rows[i].getElementsByTagName("td");
    for (var j = 0; j < cells.length; j++) {
      if (j === colIndex) {
        cells[j].style.backgroundColor = "red";
      } else {
        cells[j].style.backgroundColor = defaultRowColors[i] || 'white';
      }
    }
  }
}

function animateGroups() {
    var letter = letters[currentIndex];
    highlightGroup(letter);
    currentIndex = (currentIndex + 1) % letters.length;
}

document.getElementById('startBtn2').addEventListener('click', function() {
   this.disabled = true;
   highlightGroup(letters[currentIndex]);
   setInterval(animateGroups, 2500);
  }); 
</script>
}
