target=gear21 gear22 gear23 gear24

#include "intro.inc"
#include "lang_title_fr.inc"
#include "css.inc"

#if defined TARGET_gear21
\title{01. TITRE 2 roues 1}
#endif
#if defined TARGET_gear22
\title{05. TITRE 1}
#endif
#if defined TARGET_gear23
\title{02. TITRE 2 roues 2}
#endif
#if defined TARGET_gear24
\title{06. TITRE 2}
#endif

#if defined TARGET_gear21 | TARGET_gear22
\if{\confparm1=}{\text{confparm1=1}}
#endif

#if defined TARGET_gear21 | TARGET_gear23
\text{type=La roue bleue,La roue marron,dents,elle,roues,elles,la roue bleue,la roue marron,Elle}
\text{dents=shuffle(3,4,5)}
\integer{z1=\dents[1]}
\integer{z2=2*randint(1..3)+1}
\if{\z1=\z2}{\integer{z2=\z2+2*randint(1..3)}}
\text{list=3,5}
\integer{tmp1=randitem(\list)}
\integer{tmp2=\tmp1*randint(2..4)}
\integer{z1=\tmp2*\z1}
\integer{z2=\tmp1*\z2}
\integer{larg=(\z1+\z2)+9.25}
\integer{ma=(max(\z1,\z2)+\larg)/2}
\real{c=0.5*(\z1+\z2)}
\real{h=-\larg+\z1+2}
\real{f=-\larg+2*\z1+\z2+2}
\real{g=\f+\z2+5.25}



\text{script=JXG.Options.elements.highlight=false;
JXG.Options.elements.tabindex=-1;
var board = JXG.JSXGraph.initBoard('jsxbox', {
    boundingbox: [-\larg,\larg,\larg,-\larg],
    showCopyright:false,
    keepAspectRatio:true,
    axis:  false});

var z1 = \z1;
var z2 = \z2;
var p1 = board.create('point', [\h, 0], {visible: false,name:'p1',fixed:true});
var p2 = board.create('point', [\f, 0], {visible: false,name:'p2',fixed:true});
var slider = board.create('slider', [[-\larg+7,\ma], [\larg-7,\ma], [0, 0, 10000]],{snapWidth:\z1,tabindex:10,withLabel: false});
var x1=function(t) { return (z1 + 1.25*Math.cos(z1*t + slider.Value()*Math.PI / 180))*Math.cos(t) +\h ; } ;
var y1=function(t) { return (z1 + 1.25*Math.cos(z1*t + slider.Value()*Math.PI / 180))*Math.sin(t) ; } ;
var gear1 = board.create('curve', [x1,y1,0,2*Math.PI], {strokeWidth:2, strokeColor:'blue',fixed:true});
var dep1 = board.create('point', [\h+\z1+1.25,0],{visible: false, label: false, fixed: true,color: 'black', name: 'dep1',size: 3,showInfobox: false});
var seg1 = board.create('segment', [p1,dep1],{visible: true, label: false, fixed: true,color: 'blue',showInfobox: false,fixed:true});

var x2=function(t) { return (z2 + 1.25*Math.cos(z2*t - slider.Value()*Math.PI / 180))*Math.cos(t) +\f ; } ;
var y2=function(t) { return (z2 + 1.25*Math.cos(z2*t - slider.Value()*Math.PI / 180))*Math.sin(t) ; } ;
var gear2 = board.create('curve', [x2,y2,0,2*Math.PI], {strokeWidth:2, strokeColor:'brown',fixed:true});
var dep2 = board.create('point', [\f+\z2+1.25,0], {visible: false, fixed: true, color: 'black',name: 'B',size:3,showInfobox: false,face: 'triangleleft'});
var seg2 = board.create('segment', [p2,dep2],{visible: true, label: false, fixed: true,color: 'brown',showInfobox: false});

board.on('update', function() {
    var angle1 = -slider.Value() * Math.PI / 180/z1;
    var angle2 = -angle1*z1/z2;
    dep1.moveTo([\h+(z1+1.25)* Math.cos(angle1), (z1+1.25)* Math.sin(angle1)]);
    dep2.moveTo([\f+(z2+1.25)* Math.cos(angle2), (z2+1.25)* Math.sin(angle2)]);
});

var t1=board.create('text', [-\larg+9,\ma+5,"Déplacer le curseur pour faire tourner l'engrenage"],{fixed: true});
var t2=board.create('text', [\g,0,"Départ"],{fixed: true});

board.update();
}
#endif

#if defined TARGET_gear22 | TARGET_gear24
\text{type=Le segment bleu,Le segment marron,secteurs,il,segments,ils,le segment bleu,le segment marron,Il}
\text{dents=shuffle(3,4,5)}
\integer{tmp1=randint(2..5)}
\integer{tmp2=\tmp1*randint(2..5)}
\text{tmp=shuffle(\tmp1,\tmp2)}
\integer{z1=\tmp[1]*\dents[1]}
\integer{z2=\tmp[2]*\dents[2]}
\real{c=0.5*(\z1+\z2)}
\integer{larg=\z1+\z2+40}
\integer{ma=(max(\z1,\z2)+\larg)/2}
\text{script=JXG.Options.elements.highlight=false;
JXG.Options.elements.tabindex=-1;
var board = JXG.JSXGraph.initBoard('jsxbox', {
    boundingbox: [-\larg,\larg,\larg,-\larg],
    showCopyright:false,
    keepAspectRatio:true,
    axis: false});

var z1 = \z1;
var z2 = \z2;
var r1 = z1;
var r2 = z2;
var xc1 = -r2-10;
var xc2 = r1;

var wheel1 = board.create('circle', [[xc1,0],r1], {fillColor:'Lightblue',strokeColor: 'blue', strokeWidth: 2,fixed: true});
var wheel2 = board.create('circle', [[xc2,0],r2], {fillColor:'#C4A484',strokeColor: 'brown', strokeWidth: 2,fixed: true});

var pA = board.create('point', [xc1+r1, 0], {name: '', size: 2, color: 'blue',labelColor:'blue',fixed:true});
var pB = board.create('point', [xc2+r2, 0], {name: '', size: 2, color: 'brown',labelColor:'brown',fixed:true});

var slider = board.create('slider', [[-\larg+1,\ma], [\larg-1,\ma], [0, 0, 50000]],{snapWidth:\z1,tabindex:10,withLabel: false});

var seg1 = board.create('segment', [[xc1,0],pA],{visible: true, label: false, fixed: true,color: 'blue',strokeWidth:6,showInfobox: false});
var seg2 = board.create('segment', [[xc2,0],pB],{visible: true, label: false, fixed: true,color: 'brown',strokeWidth:6,showInfobox: false});

var t1=board.create('text', [-\larg+20,\ma+10,"Déplacer le curseur pour faire tourner les  segments"],{fixed: true});
var t2 = board.create('text',[xc2+r2+2.5,0,"Départ"],{fixed: true});

var teeth1 = [], teeth2 = [];
for (var i=0;i<z1;i++) {
    var angle=i*2*Math.PI/z1;
    teeth1.push(board.create('point', [xc1+r1* Math.cos(angle),r1*(Math.sin(angle))],{fixed:true,name:'',size:1,color:'black',visible:false}));
    var seg = board.create('segment', [[xc1,0],[xc1+r1*Math.cos(angle),r1*(Math.sin(angle))]],{visible:true,label:false,fixed:true,color:'black',size:1,showInfobox:false});

}
for (var i=0;i<z2;i++) {
    var angle=i*2*Math.PI/z2;
    teeth2.push(board.create('point',[xc2+r2*Math.cos(angle), r2*(Math.sin(angle))],{size:1,color:'black',fixed: true,name:'',visible:false}));
    var seg=board.create('segment',[[xc2,0],[xc2+r2*Math.cos(angle),r2*(Math.sin(angle))]],{visible:true,label:false,fixed:true,color:'black',size:1,showInfobox:false});
}


board.on('update', function() {
    var angle1=-slider.Value()*Math.PI/180/z1 ;
    var angle2=angle1*z1/z2;
    pA.moveTo([xc1+r1* Math.cos(angle1),r1* Math.sin(angle1)]);
    pB.moveTo([xc2+r2*Math.cos(angle2), r2*Math.sin(angle2)]);
});

board.update();
}
#endif

\text{image=slib(geo2D/jsxgraph jsxbox board,[250x250, min=250px max=350px left],\script)}

\integer{rep=lcm(\z1,\z2)}
\real{sol1=\rep/\z1}
\real{sol2=\rep/\z2}
\text{liste1=wims(makelist x for x=\z1 to (\sol1+2)*\z1 step \z1)}
\text{liste2=wims(makelist x for x=\z2 to (\sol2+2)*\z2 step \z2)}
\text{liste3=wims(makelist x for x=\z1 to 5*\z1 step \z1)}
\text{liste4=wims(makelist x for x=\z2 to 5*\z2 step \z2)}
\text{trep=<span style="color:red">\rep</span>}
\text{liste1=wims(replace item number \sol1 by \trep in \liste1)}
\text{liste2=wims(replace item number \sol2 by \trep in \liste2)}
\if{\sol1=1}{\text{tour1=tour}}{\text{tour1=tours}}
\if{\sol2=1}{\text{tour2=tour}}{\text{tour2=tours}}
\matrix{decz1=pari(factor(\z1))}
\integer{nb1=rows(\decz1)}
\text{listz1=\decz1[1;1]^{\decz1[1;2]}}
\for{j=2 to \nb1}{\text{temp=\decz1[\j;1]^{\decz1[\j;2]}}
                  \text{listz1=wims(append item \temp to \listz1)}
                 }
\text{listz1=wims(replace internal , by \times in \listz1)}
\text{listz1=texmath(\listz1)}
\matrix{decz2=pari(factor(\z2))}
\integer{nb2=rows(\decz2)}
\text{listz2=\decz2[1;1]^{\decz2[1;2]}}
\for{k=2 to \nb2}{\text{temp=\decz2[\k;1]^{\decz2[\k;2]}}
                  \text{listz2=wims(append item \temp to \listz2)}
                 }
\text{listz2=wims(replace internal , by \times in \listz2)}
\text{listz2=texmath(\listz2)}
\matrix{decrep=pari(factor(\rep))}
\integer{nb3=rows(\decrep)}
\text{listrep=\decrep[1;1]^{\decrep[1;2]}}
\for{l=2 to \nb3}{\text{temp=\decrep[\l;1]^{\decrep[\l;2]}}
                  \text{listrep=wims(append item \temp to \listrep)}
                 }
\text{listrep=wims(replace internal , by \times in \listrep)}
\text{listrep=texmath(\listrep)}

#if defined TARGET_gear21
\statement{
\image
<p><span style="color:blue">\type[1] a <b>\(\z1\)</b> dents</span> et <span style="color:brown">\type[8] a <b>\(\z2\)</b> dents.</span></p>
On fait tourner l'engrenage.
<p>Combien de tours complets doit effectuer chacune des roues pour qu'elles se retrouvent en même temps, de nouveau, et pour la première fois, dans la position de départ&nbsp;?</p>
L'ensemble sera, <b>pour la première fois</b>, à nouveau dans la position de départ lorsque&nbsp;:
<ul><li><label for="reply1"><span style="color:blue">\type[1]</span> aura fait</label>\embed{reply1,5} tour(s).</li>
<li><label for="reply2"><span style="color:brown">\type[2]</span> aura fait</label>\embed{reply2,5} tour(s).</li></ul>}
#endif

#if defined TARGET_gear22
\statement{
\image
<span style="color:blue">Le disque bleu est partagé en <b>\(\z1\)</b> secteurs égaux</span> et <span style="color:brown">le disque marron est partagé en <b>\(\z2\)</b> secteurs égaux.</span>.
<p>Les segments avancent à la même vitesse.</p>
Combien de tours complets doit effectuer chacun des segments pour qu'ils se retrouvent en même temps, de nouveau, et pour la première fois, dans la position de départ&nbsp;?
<p>Les deux segments seront, <b>pour la première fois</b>, ensemble à nouveau dans la position de départ lorsque&nbsp;:</p>
<ul><li><label for="reply1"><span style="color:blue">le segment bleu</span> aura fait</label>\embed{reply1,5} tour(s),</li>
<li><label for="reply2"><span style="color:brown">le segment marron</span> aura fait</label>\embed{reply2,5} tour(s).</li></ul>
}
#endif

#if defined TARGET_gear23
\statement{
\image
<span style="color:blue">\type[1] a <b>\(\z1\)</b> dents</span> et <span style="color:brown">\type[8] a <b>\(\z2\)</b> dents.</span>
<p><span style="color:blue">\type[1]</span> tourne de \(\sol1\) \tour1.</p>
Combien de tour(s) effectue <span style="color:brown">\type[8]</span>&nbsp;?
<div><label for="reply1"><span style="color:brown">\type[2]</span> a effectué</label>\embed{reply1,5} tour(s).</div>
}
#endif

#if defined TARGET_gear24
\statement{
\image
<span style="color:blue">Le disque bleu est partagé en <b>\(\z1\)</b> secteurs égaux</span> et <span style="color:brown">le disque marron est partagé en <b>\(\z2\)</b> secteurs égaux.</span>.
<p>Les segments avancent à la même vitesse.</p>
<span style="color:blue">\type[1]</span> tourne de \(\sol1\) \tour1.
<p>Combien de tour(s) effectue <span style="color:brown">\type[8]</span>&nbsp;?</p>
<div><label for="reply1"><span style="color:brown">\type[2]</span> a effectué</label> \embed{reply1,5} tour(s).</div>
}
#endif

#if defined TARGET_gear23
\answer{}{\sol2}{type=numexp}
\solution{
<span style="color:blue">\type[1]</span> tourne de \(\sol1\) \tour1.
<p><span style="color:bleu">\type[9]</span> tourne au total de \(\sol1 \times \z1 = \rep\) \type[3].</p>
<span style="color:brown">\type[2]</span>, composée de \(\z2\) \type[3], a également tourné de \(\rep\) \type[3].
<p>\(\rep \div \z2 = \sol2\)</p>
<span style="color:brown">\type[2]</span> a effectué \(\sol2\) \tour2.}
#endif

#if defined TARGET_gear24
\answer{}{\sol2}{type=numexp}
\solution{
<span style="color:blue">\type[1]</span> tourne de \(\sol1\) \tour1.
<p><span style="color:bleu">\type[9]</span> tourne au total de \(\sol1 \times \z1 = \rep\) \type[3].</p>
<span style="color:brown">\type[2]</span> a également tourné de \(\rep\) secteurs sur une roue composée de \(\z2\) \type[3],
<p>\(\rep \div \z2 = \sol2\)</p>
<span style="color:brown">\type[2]</span> a effectué \(\sol2\) \tour2.}
#endif

#if defined TARGET_gear21 | TARGET_gear22
\answer{}{\sol1}{type=numexp}
\answer{}{\sol2}{type=numexp}
\feedback{\reply1*\z1-\reply2*\z2=0 and \reply1<>\sol1 and \reply2<>\sol2}{
<span class="macss">Votre réponse permet à l'ensemble de retrouver leur position initiale <b>mais ce n'est pas pour la première fois</b>.</span>}
\solution{
<span style="color:blue">\type[1]</span> retrouve sa position de départ lorsqu'\type[4]
a tourné d'un multiple de \(\z1\) \type[3].
<p><span style="color:brown">\type[2]</span> retrouve sa position initiale lorsqu'\type[4]
a tourné d'un multiple de \(\z2\) \type[3].</p>
Les deux \type[5] retrouvent leur position de départ, en même temps et pour la première fois,
lorsqu'\type[6] ont tourné d'un nombre de \type[3] égal au
<b><span style="color:red">\(1^er\) multiple commun</span></b> à \(\z1\)
et <span class="nowrap">\(\z2\).</span>
\if{\confparm1=1}{<p><div style="overflow:auto">Multiples de \z1&nbsp;: \liste1 ...</div></p>
                  <div style="overflow:auto">Multiples de \z2&nbsp;: \liste2 ...</div>
                  <p>Le <b><span style="color:red">premier multiple commun</span></b> à \(\z1\)
                  et \(\z2\) est <span style="color:red" class="nowrap">\(\rep\).</span></p>
                }{<p>La décomposition en facteurs premiers de \(\z1\) est \(\z1=\listz1\)</p>
                  La décomposition en facteurs premiers de \(\z2\) est \(\z2=\listz2\)
                  <p>Le plus petit multiple commun à \(\z1\) et \(\z2\) est \(\listrep=\rep\)</p>
                  }
<p>\(\rep=\z1 \times \sol1\) et <span class="nowrap">\(\rep=\z2 \times \sol2\).</span></p>
<span style="color:blue">\type[1]</span> a fait \(\sol1\) \tour1 et
<span style="color:brown">\type[8]</span> a fait \(\sol2\) \tour2.}

\hint{
<span style="color:blue">\type[1]</span> atteint sa position initiale tous les \(\z1\) \type[3],
c'est-à-dire lorsqu'\type[4] aura tourné de \liste3, ...\type[3].
<p><span style="color:brown">\type[2]</span> atteint sa position initiale tous les \(\z2\) \type[3],
c'est-à-dire lorsqu'\type[4] aura tourné de \liste4, ...\type[3].</p>
}
#endif
