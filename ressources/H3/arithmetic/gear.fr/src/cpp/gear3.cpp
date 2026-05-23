target=gear31 gear32

#include "intro.inc"
#include "css.inc"
#include "lang_title_fr.inc"

#if defined TARGET_gear31
\title{03. TITRE 3 roues 1}
#endif

#if defined TARGET_gear32
\title{04. TITRE 3 roues 2}
#endif

\if{\confparm1=}{\text{confparm1=1}}

\text{type=La roue bleue,La roue marron,dents,elle,roues,elles,la roue bleue,la roue marron,La roue noire,la roue noire,Elle}

\text{dents=shuffle(3,4,5,4)}
\integer{z1=\dents[1]}
\integer{z2=2*randint(1..3)+1}
\if{\z1=\z2}{\integer{z2=\z2+2*randint(1..3)}}
\integer{z3=2*randint(1..3)+1}
\if{\z2=\z3}{\integer{z3=\z3+2*randint(1..3)}}
\text{list=shuffle(1,3,5)}
\integer{tmp=\list[1]}
\integer{z1=\tmp*\z1}
\integer{z2=\tmp*\z2}
\integer{z3=\tmp*\z3}
\integer{rep=lcm(lcm(\z1,\z2),\z3)}
\integer{sol1=\rep/\z1}
\integer{sol2=\rep/\z2}
\integer{sol3=\rep/\z3}
\text{liste1=wims(makelist x for x=\z1 to (\sol1+2)*\z1 step \z1)}
\text{liste2=wims(makelist x for x=\z2 to (\sol2+2)*\z2 step \z2)}
\text{liste3=wims(makelist x for x=\z1 to 5*\z1 step \z1)}
\text{liste4=wims(makelist x for x=\z2 to 5*\z2 step \z2)}
\text{liste5=wims(makelist x for x=\z3 to (\sol3+2)*\z3 step \z3)}
\text{liste6=wims(makelist x for x=\z3 to 5*\z3 step \z3)}
\text{trep=<span style="color:red">\rep</span>}
\text{liste1=wims(replace item number \sol1 by \trep in \liste1)}
\text{liste2=wims(replace item number \sol2 by \trep in \liste2)}
\text{liste5=wims(replace item number \sol3 by \trep in \liste5)}

\integer{larg=(\z1+\z2+\z3+7.5)+15}
\real{c=0.5*(\z1+\z3)+\z2}
\integer{ma=(max(\z1,\z2)+\larg)/2}

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

\matrix{decz3=pari(factor(\z3))}
\integer{nb3=rows(\decz3)}
\text{listz3=\decz3[1;1]^{\decz3[1;2]}}
\for{l=2 to \nb3}{\text{temp=\decz3[\l;1]^{\decz3[\l;2]}}
                  \text{listz3=wims(append item \temp to \listz3)}
                 }
\text{listz3=wims(replace internal , by \times in \listz3)}
\text{listz3=texmath(\listz3)}
\matrix{decrep=pari(factor(\rep))}
\integer{nbrep=rows(\decrep)}
\text{listrep=\decrep[1;1]^{\decrep[1;2]}}
\for{l=2 to \nbrep}{\text{temp=\decrep[\l;1]^{\decrep[\l;2]}}
                  \text{listrep=wims(append item \temp to \listrep)}
                 }
\text{listrep=wims(replace internal , by \times in \listrep)}
\text{listrep=texmath(\listrep)}

\text{script=JXG.Options.elements.highlight=false;
JXG.Options.elements.tabindex=-1;
var board = JXG.JSXGraph.initBoard('jsxbox', {
    boundingbox: [-\larg,\larg,\larg,-\larg],
    showCopyright:false,
    keepAspectRatio:true,
    axis: false});

var z1 = \z1;
var z2 = \z2;
var z3 = \z3;

var p1 = board.create('point', [-\c, 0], {visible: false,fixed:true});
var p2 = board.create('point', [-\c+z1+z2, 0], {visible: false,fixed:true});
var p3 = board.create('point', [\c, 0], {visible: false,fixed:true});

var slider = board.create('slider', [[-\larg+7,\ma], [\larg-7,\ma], [0, 0, 10000]],{snapWidth:\z1,tabindex:10,withLabel: false});
var x1=function(t) { return (z1 + 1.25*Math.cos(z1*t + slider.Value()*Math.PI / 180))*Math.cos(t) -\c ; } ;
var y1=function(t) { return (z1 + 1.25*Math.cos(z1*t + slider.Value()*Math.PI / 180))*Math.sin(t) ; } ;
var gear1 = board.create('curve', [x1,y1,0,2*Math.PI], {strokeWidth:2, strokeColor:'blue'});
var dep1 = board.create('point', [-\c+z1+1.25,0],{visible: false, fixed: true,color: 'black', name: '',size: 3,showInfobox: false});
var seg1 = board.create('segment', [p1,dep1],{visible: true, label: false, fixed: true,color: 'blue',strokeWidth: 3,showInfobox: false});

var x2=function(t) { return (z2 + 1.25*Math.cos(z2*t - slider.Value()*Math.PI / 180))*Math.cos(t) -\c+z1+z2 ; } ;
var y2=function(t) { return (z2 + 1.25*Math.cos(z2*t - slider.Value()*Math.PI / 180))*Math.sin(t) ; } ;
var gear2 = board.create('curve', [x2,y2,0,2*Math.PI], {strokeWidth:2, strokeColor:'brown'});
var dep2 = board.create('point', [-\c+z1+2*z2+1.25,0], {visible: false, fixed: true, color: 'black',name: '',size:3,showInfobox: false});
var seg2 = board.create('segment', [p2,dep2],{visible: true, label: false, fixed: true,color: 'brown',strokeWidth:3,showInfobox: false});

var x3=function(t) { return (z3 + 1.25*Math.cos(z3*t + slider.Value()*Math.PI / 180))*Math.cos(t) +\c ; } ;
var y3=function(t) { return (z3 + 1.25*Math.cos(z3*t + slider.Value()*Math.PI / 180))*Math.sin(t) ; } ;
var gear3 = board.create('curve', [x3,y3,0,2*Math.PI], {strokeWidth:2, strokeColor:'black'});
var dep3 = board.create('point', [\c+z3+1.25,0], {visible: false, fixed: true, color: 'black',name: '',size:3,showInfobox: false});
var seg3 = board.create('segment', [p3,dep3],{visible: true, label: false, fixed: true,color: 'black',strokeWidth: 3,showInfobox: false});

board.on('update', function() {
    var angle1 = -slider.Value()*Math.PI/180/z1;
    var angle2 = -angle1*z1/z2;
    var angle3 = angle1*z1/z3;
    dep1.moveTo([-\c+(z1+1.25)* Math.cos(angle1), (z1+1.25)* Math.sin(angle1)]);
    dep2.moveTo([-\c+z1+z2+(z2+1.25)* Math.cos(angle2), (z2+1.25)* Math.sin(angle2)]);
    dep3.moveTo([\c+(z3+1.25)* Math.cos(angle3), (z3+1.25)* Math.sin(angle3)]);

});

var t1=board.create('text', [-\larg+9,\ma+5,"Déplacer le curseur pour faire tourner l'engrenage"],{fixed: true});
var t2=board.create('text', [\c+z3+3,0,"Départ"],{fixed: true});

board.update();
}

\text{image=slib(geo2D/jsxgraph jsxbox board,[250x250, min=250px max=350px left],\script)}

#if defined TARGET_gear31
\statement{
\image
<span style="color:blue">\type[1] a <b>\(\z1\)</b> dents</span>, <span style="color:brown">\type[8] a <b>\(\z2\)</b> dents</span> et <span style="color:black">\type[10] a \(\z3\) dents</span>.
<p>On fait tourner l'engrenage.</p>
Combien de tours complets doit effectuer chacune des roues pour qu'elles se retrouvent en même temps, de nouveau, et pour la première fois, dans la position de départ&nbsp;?
<p>L'ensemble sera, <b>pour la première fois</b>, à nouveau dans la position de départ lorsque&nbsp;:</p>
<ul><li><label for="reply1"><span style="color:blue">\type[7]</span> aura fait</label>\embed{reply1,5} tour(s),
<li><label for="reply2"><span style="color:brown">\type[8]</span> aura fait</label>\embed{reply2,5} tour(s),
<li><label for="reply3"><span style="color:black">\type[10]</span> aura fait</label>\embed{reply3,5} tour(s).</ul>
}
\answer{}{\sol1}{type=numexp}
\answer{}{\sol2}{type=numexp}
\answer{}{\sol3}{type=numexp}

\hint{
<p><span style="color:blue">\type[1]</span> atteint sa position initiale toutes les \z1 \type[3], c'est-à-dire lorsqu'\type[4] aura tourné de \liste3, ...\type[3].</p>
<span style="color:brown">\type[2]</span> atteint sa position initiale toutes les \z2 \type[3], c'est-à-dire lorsqu'\type[4] aura tourné de \liste4, ...\type[3].
<p>\type[9] atteint sa position initiale toutes les \z3 \type[3], c'est-à-dire lorsqu'\type[4] aura tourné de \liste6, ...\type[3].</p>
}
\solution{<span style="color:blue">\type[1]</span> retrouve sa position initiale lorsqu'\type[4] a tourné d'un multiple de \(\z1\) \type[3].
<p><span style="color:brown">\type[2]</span> retrouve sa position initiale lorsqu'\type[4] a tourné d'un multiple de \(\z2\) \type[3].</p>
\type[9] retrouve sa position initiale lorsqu'\type[4] a tourné d'un multiple de \(\z3\) \type[3].
<p>Les trois \type[5] retrouvent leur position de départ, en même temps et pour la première fois, lorsqu'\type[6] ont tourné d'un nombre de \type[3] égal au \(1^er\) multiple commun à \(\z1\), \(\z2\) et <span class="nowrap">\(\z3\).</span></p>
\if{\confparm1=1}{<div style="overflow:auto">Multiples de \z1&nbsp;: \liste1 ...</div>
                  <div style="overflow:auto">Multiples de \z2&nbsp;: \liste2 ...</div>
                  <div style="overflow:auto">Multiples de \z3&nbsp;: \liste5 ...</div>
                  Le <b><span style="color:red">plus petit multiple commun</span></b> à \(\z1\),\(\z2\) et \(\z3\) est <span class="nowrap">\(\rep\).</span></p>
                 }{La décomposition en facteurs premiers de \(\z1\) est <span class="nowrap">\(\z1=\listz1\).
                  <p>La décomposition en facteurs premiers de \(\z2\) est <span class="nowrap">\(\z2=\listz2\).</span></p>
                  La décomposition en facteurs premiers de \(\z3\) est <span class="nowrap">\(\z3=\listz3\).</span>
                  <p>Le <b><span style="color:red">plus petit multiple commun</span></b> à \(\z1\),\(\z2\) et \(\z3\) est <span class="nowrap">\(\listrep=\rep\).</span></p>
                  }
                  \(\rep=\z1 \times \sol1\), \(\rep=\z2 \times \sol2\) et <span class="nowrap">\(\rep=\z3 \times \sol3\).</span>
                  <p><span style="color:blue">\type[1]</span> a fait \(\sol1\) tours,<span style="color:brown">\type[8]</span> a fait \(\sol2\) tours et \type[10] a fait \(\sol3\) tours.</p>
                  }

\feedback{\reply1*\z1-\reply2*\z2=0 and \reply1<>\sol1 and \reply2<>\sol2 and \reply3<>\sol3}{
<span class="macss">Votre réponse permet à l'ensemble de retrouver leur position initiale <b>mais ce n'est pas pour la première fois</b>.</span>}
#endif

#if defined TARGET_gear32
\integer{ch=randint(3)}
\if{\ch=1}{\text{r1=<span style="color:blue">\type[1]</span>}
           \integer{dr1=\z1}
           \text{r2=<span style="color:brown">\type[8]</span>}
           \integer{dr2=\z2}
           \text{r3=<span style="color:black">\type[10]</span>}
           \integer{dr3=\z3}
           \integer{dsol1=\sol1}
           \text{r21=<span style="color:brown">\type[2]</span>}
           \text{r31=<span style="color:black">\type[9]</span>}
           \integer{dsol2=\sol2}
           \integer{dsol3=\sol3}
           }
\if{\ch=2}{\text{r2=<span style="color:blue">\type[7]</span>}
           \integer{dr2=\z1}
           \text{r3=<span style="color:brown">\type[8]</span>}
           \integer{dr3=\z2}
           \text{r1=<span style="color:black">\type[9]</span>}
           \integer{dr1=\z3}
           \integer{dsol2=\sol1}
           \text{r31=<span style="color:brown">\type[2]</span>}
           \text{r21=<span style="color:blue">\type[1]</span>}
           \integer{dsol3=\sol2}
           \integer{dsol1=\sol3}
          }
\if{\ch=3}{\text{r2=<span style="color:blue">\type[7]</span>}
           \integer{dr2=\z1}
           \text{r1=<span style="color:brown">\type[2]</span>}
           \integer{dr1=\z2}
           \text{r3=<span style="color:black">\type[10]</span>}
           \integer{dr3=\z3}
           \integer{dsol2=\sol1}
           \text{r21=<span style="color:blue">\type[1]</span>}
           \text{r31=<span style="color:black">\type[9]</span>}
           \integer{dsol1=\sol2}
           \integer{dsol3=\sol3}
          }
\text{tour1=\dsol1=1?tour:tours}
\text{tour2=\dsol2=1?tour:tours}
\text{tour3=\dsol3=1?tour:tours}

\statement{
\image
<span style="color:blue">\type[1] a <b>\(\z1\)</b> dents</span>,
<span style="color:brown">\type[8] a <b>\(\z2\)</b> dents</span> et
<span style="color:black">\type[10] a \(\z3\) dents</span>.
<p>On fait tourner l'engrenage.</p>
\r1 tourne de \(\dsol1\) tours.
<p>Combien de tours ont effectué \r2 et \r3&nbsp;?</p>
<ul><li><label for="reply1">\r21 a effectué</label> \embed{reply1,5} tour(s).</li>
<li><label for="reply2">\r31 a effectué</label> \embed{reply2,5} tour(s).</li></ul>
}
\answer{}{\dsol2}{type=numexp}
\answer{}{\dsol3}{type=numexp}
\solution{
\r1 tourne de \(\dsol1\) \tour1.
<p>\type[11] tourne au total de \(\dsol1 \times \dr1 = \rep\) \type[3].</p>
\r21, composée de \(\dr2\) \type[3], a également tourné de \(\rep\) dents.
<p>\(\rep \div \dr2 = \dsol2\)</p>
\r21 a tourné de \(\dsol2\) \tour2.
<p>\r31, composée de \(\dr3\) \type[3], a également tourné de \(\rep\) dents.</p>
\(\rep \div \dr3 = \dsol3\)
<p>\r31 a tourné de \(\dsol3\) \tour3.</p>
}
#endif
