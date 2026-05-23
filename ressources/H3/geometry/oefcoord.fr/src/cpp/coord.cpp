target=coord1 coord2
#if defined TARGET_coord1
\title{Placer un point comme intersection}
\keywords{coordinates}
#endif
#if defined TARGET_coord2
\title{Placer un vecteur}
\keywords{vectors,coordinates}
#endif
\author{Bernadette, Perrin-Riou}
\email{bpr@math.u-psud.fr}

\precision{100}
\text{rangex=-10,10}
\text{rangey=-10,10}
\text{size=300,300}
\text{a=randint(1..2)*randitem(1,-1), randint(1..2)*randitem(1,-1)}
\text{a=pari([\a])}
#if defined TARGET_coord1
\text{script=var brd = JXG.JSXGraph.initBoard('jxgbox', {boundingbox:[\rangex[1],\rangey[2],\rangex[2],\rangey[1]],axis:true,keepaspectratio:true,grid:true});
   var l1=brd.create('line',[[0,0],[0,\rangey[2]]],{strokeColor:'black',fixed:true,visible:false});
   var sl1=brd.create('glider',[l1],{fillColor:'green',strokeColor:'black',name:'',snapToGrid:true});
   var l2=brd.create('line',[[0,0],[\rangex[2],0]],{strokeColor:'black',fixed:true,visible:false});
   var sl2=brd.create('glider',[l2],{fillColor:'green',strokeColor:'black',name:'',snapToGrid:true});
   var l3=brd.create('line',[[0,function(){return sl1.Y()}],[\rangex[2],function(){return sl1.Y()}]],{strokeColor:'green'});
   var l4=brd.create('line',[[function(){return sl2.X()},0],[function(){return sl2.X()},\rangey[2]]],{strokeColor:'green'});

}
\text{script2=jxgbox_var1=[function(){return sl2.X()},function(){return sl1.Y()}];}
\text{rep=\a}
#endif

#if defined TARGET_coord2
 \text{b=randint(1..7)*randitem(1,-1), randint(1..7)*randitem(1,-1)}
 \text{b=pari([\b])}
 \text{script=var brd = JXG.JSXGraph.initBoard('jxgbox', {boundingbox:[\rangex[1],\rangey[2],\rangex[2],\rangey[1]],axis:true,keepaspectratio:true,grid:true});
   var P=brd.create('point',[\a],{fixed:true,name:'',visible:false});
   var Q=brd.create('point',[\a[1]+1,\a[2]+1],{name:'',snapToGrid:true,size:1});
   var v=brd.create('arrow',[P,Q],{strokeColor:'black',name:''});
}
\text{script2=jxgbox_var1=[function(){return Q.X()},function(){return Q.Y()}],{name:'',visible:false} ;}
\text{rep=pari([\b] + [\a])}
#endif

#include "lang_coord.inc"

\text{jsxgraph=slib(geo2D/jsxgraph jxgbox,\size[1]x \size[2],\script)}
\text{script= \script
jxgbox_rep1 = brd.create('point',jxgbox_var1,{strokeColor:'transparent',fillColor:'transparent',name:''}); }

\statement{\instruction
<div class="wimscenter">
 \embed{r1,400x400
jxgbox brd
\script
\script2
 }
 </div>
 \if{\name_help!=}{
 <div class="wims_instruction">
 \name_help
 </div>
 }
}
\answer{}{\rep}{type=jsxgraph}

\text{z=\reply1}
\text{color=\sc_reply1=1?green:red}
#if defined TARGET_coord1
\text{script2=\sc_reply1<1 ?
   l5=brd.create('line',[[0,\a[2]],[\rangex[2],\a[2]]],{strokeColor:'green',fixed:true,visible:true});
   l6=brd.create('line',[[\a[1],0],[\a[1],\rangey[2]]],{strokeColor:'green',fixed:true,visible:true});
}
\feedback{1=1}{
<script>
/*<![CDATA[*/
   sl2.setProperty('visible:false');sl1.setProperty('visible:false');
   l3=brd.create('line',[[0,\z[2]],[\rangex[2],\z[2]]],{strokeColor:'\color',fixed:true,visible:true});
   l4=brd.create('line',[[\z[1],0],[\z[1],\rangey[2]]],{strokeColor:'\color',fixed:true,visible:true});
   \script2
/*]]>*/
</script>
}
#endif

#if defined TARGET_coord2
\text{script2=\sc_reply1<1 ?
 var Q2=brd.create('point',[\a[1]+\b[1],\a[2]+\b[2]],{name:'',visible:false,fixed:true});
 var v2=brd.create('arrow',[P,Q2],{strokeColor:'green',name:''});
}
\feedback{1=1}{
<script type="text/javascript">
/*<![CDATA[*/
   Q.setProperty('visible:false');v.setProperty('visible:false');
   var Q1=brd.create('point',[\z[1],\z[2]],{name:'',visible:false,fixed:true});
   var v1=brd.create('arrow',[P,Q1],{strokeColor:'\color',name:''});
   \script2
/*]]>*/
</script>
}
#endif
