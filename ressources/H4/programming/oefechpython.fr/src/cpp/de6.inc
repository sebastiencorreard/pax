\text{prob=Étude de la somme de deux dés avec Python}
\integer{zz=randint(0..90)}
\integer{ntt=10000+1000*\zz}

\text{instructionf=Jouer le code plusieurs fois et envoyer la réponse.}
\integer{nnfe=randint(1..\nf)}
\integer{somme=\nf+\nf1}
\integer{pro=\nf*\nf1}

\if{(3==\nf and 3==\nf1)}{\matrix{repp=1/\pro,2/\pro,3/\pro,2/\pro,1/\pro}}
\if{(4==\nf and 3==\nf1) or (3==\nf and 4==\nf1)}{\matrix{repp=1/\pro,2/\pro,3/\pro,3/\pro,2/\pro,1/\pro}}
\if{(6==\nf and 3==\nf1) or (3==\nf and 6==\nf1)}{\matrix{repp=1/\pro,2/\pro,3/\pro,3/\pro,3/\pro,3/\pro,2/\pro,1/\pro}}
\if{(4==\nf and 4==\nf1)}{\matrix{repp=1/\pro,2/\pro,3/\pro,4/\pro,3/\pro,2/\pro,1/\pro}}
\if{(6==\nf and 4==\nf1) or (4==\nf and 6==\nf1)}{\matrix{repp=1/\pro,2/\pro,3/\pro,4/\pro,4/\pro,4/\pro,3/\pro,2/\pro,1/\pro}}
\if{(6==\nf and 6==\nf1)}{\matrix{repp=1/\pro,2/\pro,3/\pro,4/\pro,5/\pro,6/\pro,5/\pro,4/\pro,3/\pro,2/\pro,1/\pro}}


\text{lr=wims(makelist r x for x = 4 to \somme+2)}
\text{de=wims(makelist x for x=2 to \somme)}
\text{freq=wims(makelist f x for x=2 to \somme)}
\text{freq=wims(nospace \freq)}
\text{freqq=wims(replace , by = in \freq)}
\text{ff_Sk_ffi_remap=}
\for{az=2 to \somme}{
\text{ff_Sk_ffi_remap=wims(append line f\az=Sk.ffi.remapToJs(Sk.globals["f\az"]); to \ff_Sk_ffi_remap)}
}

\matrix{nstep=r1,r2,r3}
\nextstep{\nstep}
\text{A=}
\text{AA=}
\integer{AA1=}
\text{BB=}
\text{grr=}
\text{instruction4=<li>Déterminer les formules permettant de calculer la fréquence
 pour l'ensemble des sommes. La formule qui calcule la fréquence pour la somme 2
 est donnée dans le code.</li>}



\text{gr=jsxbox,600 x 400,JXG.Options.point.fixed = true;
JXG.Options.point.highlight=false;
JXG.Options.point.showInfobox=false;
JXG.Options.point.name = "";
JXG.Options.point.face = "[]";
JXG.Options.point.withLabel=true;
color_liste=['red','yellow','blue','green','orange','purple','brown','pink',"violet","black","lightblue","grey"];
JXG.Options.point.size =2;
var brd = JXG.JSXGraph.initBoard('jsxbox', {axis:false, boundingbox: [-1,0.5,15,-0.1],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : false,showFullscreen: true});
xaxis = brd.create('axis', [[0,0], [1,0]],
      {name:'Issues possibles',
      withLabel: true,
      label: {position: 'rt',/* possible values are 'lft', 'rt', 'top', 'bot'*/
      offset: [-60, 30]   /*(in pixels)*/},Color:'red'});
      yaxis = brd.create('axis', [[0, 0], [0,1]],
      {name:'Fréquence d\'apparition de la somme de deux dés',withLabel: true,
      label: {position: 'rt',/* possible values are 'lft', 'rt', 'top', 'bot'*/
      offset: [10, 0]   /*(in pixels)*/},Color:'red'});}
\text{B=slib(geo2D/jsxgraph \gr)}


\text{code=\code
videun=??
vfdeun=??
videdeux=??
vfdedeux=??
nt=??
\freqq=0
\#################
for i in range(nt):
  issue = rand\pp(videun,vfdeun)+rand\pp(videdeux,vfdedeux)
  if issue==2:
    f2=f2+1/nt
  if issue==3:
    f3=??
  if issue==4:
    f4=??
  if issue==5:
    f5=??
  if issue==6:
    f6=??

??????
    
print(\freq)
}

\text{variable=[videun,1],[vfdeun,\nf],[videdeux,1],[vfdedeux,\nf1],[nt,\ntt]}

\text{instruction3=<li>Déterminer les conditions à remplir pour compter le nombre
d'apparitions de chacune des faces.</li>}

\text{sscr=<script>
var tp=[];
var tpl=[];
var ch;
function graph(){brd.removeObject(ch);
brd.removeObject(tp);
brd.removeObject(tpl);
\ff_Sk_ffi_remap
nn=[\freq];
const xlen=nn.length;
brd.suspendUpdate();
for(var jj = 0; jj < xlen; jj=jj+1) {
var tt=nn[jj].toFixed(3);
tp[jj]=brd.create('point', [jj+2,nn[jj]],{name:tt,label:{offset:[-10, 10]},color:color_liste[jj]});
tpl[jj]=brd.create('line', [[jj+2,0],[jj+2,nn[jj]]],{straightFirst:false, straightLast:false, strokeWidth:20,color:color_liste[jj],shadow:true});}
brd.unsuspendUpdate();}
execidtest2.addEventListener('click',graph);
</script>}
\text{dec=3}

\text{arbre=rankdir = LR
nodesep=0.4
ranksep="1"
bgcolor= grey80
node0 [label="" shape=point];}
\text{titi=}
\text{tata=}
\text{toto=}

\text{test=\arbre}
/*1er lancer d'un dé à 6 faces*/
\for{ri=1 to \nf}{
\text{toto=\toto
"node\ri"}
\text{test=\test
"node0"->"node\ri"[color=black, arrowsize=2];
node\ri [color=black,shape=box,style=rounded,label="\ri"];}
/*2ème lancé d'un dé à 3 faces*/
\for{rj=1 to \nf1}{
\integer{aa=\nf+\rj+\nf1*(\ri-1)}
\integer{bb=\nf*(\nf1+1)+\rj+\nf1*(\ri-1)}
\integer{cc=\ri+\rj}
\text{tata=\tata
"node\aa"}
\text{titi=\titi
"node\bb"}
\text{test=\test
"node\ri"->"node\aa"[color=red, arrowsize=2];
node\aa [color=red,shape=box,style="rounded",label="\rj"];
"node\aa"->"node\bb"[arrowhead=none,color=yellow,style=bold, label=""];
node\bb [color=yellow,shape=box,style="rounded",label="\cc"];}
}}

\text{orga=\test
subgraph cluster_cache1 {
  label = "Lancé du premier dé bleu" fontcolor =blue4
  style="rounded, filled"
  color =blue4
  fillcolor=deepskyblue1
        \toto
        }
subgraph cluster_cache2 {
  label = "Lancé du deuxième dé" fontcolor = darkgreen
  style="rounded, filled"
  color = darkgreen
  fillcolor= darkolivegreen3
  \tata
        }
subgraph cluster_cache3 {
  label = "Somme des 2 dés" fontcolor =violetred3
  style="rounded, filled"
  color = violetred3
  fillcolor = darksalmon
  \titi
  } 
}
\text{arbre2 =slib(draw/graphviz digraph  { \orga
},png dot url)}

\text{lde1=wims(makelist <span style="Color:red;">x</span> for x = 1 to \nf)}
\text{llde1=<span style="Color:red;">dé1</span><br/><span style="Color:green;">dé2</span>,\lde1}
\text{lde2=wims(makelist <span style="Color:green;">u</span> for u = 1 to \nf1)}
\text{llde2=\lde2}
\integer{so=}
\text{tableau1=<table class="wimscenter wimsborder">}
\for{zi=1 to \nf1+1}{
\text{tableau1=\tableau1<tr>}
\for{zj=1 to \nf+1}{\text{tableau1=(\zi==1)?\tableau1<th>\llde1[\zj]</th>}
\integer{so=\zj+\zi-2}
\text{tableau1=(\zj==1 and \zi!=1)?\tableau1<th>\llde2[\zi-1]</th>}
\text{tableau1=(\zi!=1 and \zj!=1)?\tableau1<td>\so</td>}
}
\text{tableau1=\tableau1</tr>}
}
\text{tableau1=\tableau1</table>}
