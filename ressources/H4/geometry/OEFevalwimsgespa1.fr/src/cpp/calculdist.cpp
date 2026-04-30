target=Calculdist1 Calculdist2 Calculdist3 Calculdist4 Calculdist5
#include "author.inc"
\precision{100}
\computeanswer{yes}
#include "lang_titles.inc"
#include "lang.inc"
\integer{ggb=(\confparm1==)?1:\confparm1}
#if defined TARGET_Calculdist4
\text{tetra=linewidth 3
polyline black,0,0,0,12,8,0,3,-3,0,0
segment 0,12,3,-3,black
dsegment 0,0,8,0,black
polyline red,0,6,1.5,4.5,4,6
dsegment 0,6,4,6,red
}
\text{cadre=
xrange -4,16
yrange -5,15
\tetra
text blue,-0.4,-0.5,medium,A
text blue,8.2,-0.5,medium,C
text blue,3,-3.5,medium,B
text blue,-0.4,12.5,medium,S
text red,-0.8,6.2,medium,A'
text red,1.7,4.5,medium,B'
text red,4.2,6.2,medium,C'
text black,-0.6,3,medium,z
text black,1,-1.5,medium,x
text black,5.5,-1.5,medium,y
linewidth 5
points blue,0,0,8,0,3,-3,0,12
points red,0,6,1.5,4.5,4,6
linewidth 3
}
#endif
#if defined TARGET_Calculdist1
#include "cubepts.inc"
%%%%choix de 2 points sur une même face
\text{lstpts=}
\integer{face=randint(1..6)}
\for{i=1 to 20}
 {
 \if{\face isitemof \faces[\i;]}{
    \text{lstpts=wims(append item \listpoint[\i] to \lstpts)}
   }
 }
\text{lstpts=shuffle(\lstpts)}
\text{pt1=\lstpts[1]}
\text{pt2=\lstpts[2]}
\integer{indpt1=position(\pt1,\listpoint)}
\integer{indpt2=position(\pt2,\listpoint)}
\real{rep=sqrt((\PT[\indpt2;1]-\PT[\indpt1;1])^2+(\PT[\indpt2;2]-\PT[\indpt1;2])^2+(\PT[\indpt2;3]-\PT[\indpt1;3])^2)}
\text{rep=\rep*a}
\text{quest=Calculer la distance \(\pt1 \pt2\).}
\text{nomquest=\(\pt1 \pt2\)}
\text{dessin=
segment \pt[\indpt1;1],\pt[\indpt1;2],\pt[\indpt2;1],\pt[\indpt2;2],red
}
#endif
#if defined TARGET_Calculdist2
#include "cubepts.inc"
%%%%%choix de 2 points pas sur une même face
\text{lstpts=}
\integer{indpt1=randint(1..20)}
\text{pt1=\listpoint[\indpt1]}
\for{i=1 to 20}{
 \text{faceinter=wims(listintersect \faces[\indpt1;] and \faces[\i;])}
 \if{\faceinter=}{
    \text{lstpts=wims(append item \listpoint[\i] to \lstpts)}
  }
}
\text{lstpts=shuffle(\lstpts)}
\text{pt2=\lstpts[1]}
\integer{indpt2=position(\pt2,\listpoint)}
\real{rep=sqrt((\PT[\indpt2;1]-\PT[\indpt1;1])^2+(\PT[\indpt2;2]-\PT[\indpt1;2])^2+(\PT[\indpt2;3]-\PT[\indpt1;3])^2)}
\text{rep=\rep*a}
\text{dessin=
segment \pt[\indpt1;1],\pt[\indpt1;2],\pt[\indpt2;1],\pt[\indpt2;2],red
}
\text{quest=Calculer la distance \(\pt1 \pt2\).}
\text{nomquest=\(\pt1 \pt2\)}
#endif
#if (defined TARGET_Calculdist1  || defined TARGET_Calculdist2)
\if{\ggb==2}{
\text{lp_enon=aa=Segment(\pt1,\pt2)
SetColor[aa,red]
ShowLabel[aa, false]
SetLineThickness[aa,8]}}
#endif
#if defined TARGET_Calculdist3
#include "cubepts.inc"
\text{data=a^2/2,ABC,ABD,AEF,ABF,ACD,BCD,ABE,BEF,ADE,AEH,DEH,ADH,EFH,EGH,FGH,EFG,BCF,BFG,CFG,BCG,CDH,DGH,CGH,CDG
  a^2/4,AEI,AIM,AIM,AEM,BFM,BIM,FIM,BIF,BFP,BLP,FLP,BFL,CGP,CLP,CGL,GLP,DHJ,HJN,DHN,DHJ,CGJ,GJN,CJN,CGN,EKO,AEK,AEO,AKO,DHO,DKO,HKO,DHK,EFO,FOP,EOP,EFP,GHO,GOP,HOP,GHP,AKL,ABL,ABK,BKL,CDK,CKL,DKL,CDL
  sqrt(2)*a^2/2,ACE,ACG,AEG,ACG,BDH,BFH,DFH,BDF
  sqrt(2)*a^2/4,IKO,KOM,IOM,IKM,JON,KJO,KON,JKN,LNP,JLN,JNP,JLP,LMP,IML,IMP,ILP,IQT,JQT,IJQ,IJT,IRS,JRS,IJR,IJS,MRS,NRS,MNS,MNR,MNQ,MNT,MQT,NQT,lQR,KQR,KLR,KLQ,KLS,KLT,KST,LST,PST,OST,OPS,OPT,OPQ,OPR,OQR,PQR
}
\text{cedata=randomrow(\data)}
\text{rep=\cedata[1]}
\integer{n=items(\cedata)}
\integer{i=randint(2..\n)}
\text{triangle=\cedata[\i]}
\text{pt1=wims(text copy \triangle mask 100)}
\text{pt2=wims(text copy \triangle mask 010)}
\text{pt3=wims(text copy \triangle mask 001)}
\integer{indpt1=position(\pt1,\listpoint)}
\integer{indpt2=position(\pt2,\listpoint)}
\integer{indpt3=position(\pt3,\listpoint)}
\text{dessin=
  poly red,\pt[\indpt1;1],\pt[\indpt1;2],\pt[\indpt2;1],\pt[\indpt2;2],\pt[\indpt3;1],\pt[\indpt3;2],
}

\text{quest=Calculer l'aire du triangle \(\pt1 \pt2 \pt3\).}
\text{nomquest=Aire}
\if{\ggb==2}{
  \text{lp_enon=aa=Polygon(\pt1,\pt2,\pt3)
SetColor[aa,red]
ShowLabel[aa, false]
SetLineThickness[aa,8]}
  \text{suplab=a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w}
\for{i in \suplab}{\text{t=ShowLabel[\i, false]
ShowLabel[\i _1, false]}
\text{lp_enon=wims(append line \t to \lp_enon)}}
}
#endif
#if defined TARGET_Calculdist4
\text{quest=Calculer le volume du solide \(A B C D S T U V\).}
\text{nomquest=Volume}
#endif
#if defined TARGET_Calculdist5
#include "cubepts.inc"
\text{data=a^3/6,ABDE,ABCF,BCDG,ACDH,AEFH,BEFG,CFGH,EGHD
  a^3/48,AIKQ,BILR,CJLS,DJKT,EMOQ,FMPR,GNPS,HNOT
  a^3/24,AEIK,BFIL,CGJL,DHJK,AEMO,BFMP,CGNP,DHNO,ABKQ,ABLR,CDLS,CDKT,EFOQ,EFPR,GHPS,GHOT,ADIQ,ADJT,BCIR,BCJS,EHMQ,EHNT,FGMR,FGNS
  a^3/12,ABEK,ADEK,ABDQ,BCFI,ABFL,ABCR,CDGL,BCGJ,BCDS,CDHK,ADHJ,ACDT,AEHM,EFHQ,AEFO,BFGM,BEFP,EFGR,CGHP,FGHS,CFGN,DEHN,DGHO,EGHT
}
\text{cedata=randomrow(\data)}
\text{rep=\cedata[1]}
\integer{n=items(\cedata)}
\integer{i=randint(2..\n)}
\text{triangle=\cedata[\i]}
\text{pt1=wims(text copy \triangle mask 1000)}
\text{pt2=wims(text copy \triangle mask 0100)}
\text{pt3=wims(text copy \triangle mask 0010)}
\text{pt4=wims(text copy \triangle mask 0001)}
\integer{indpt1=position(\pt1,\listpoint)}
\integer{indpt2=position(\pt2,\listpoint)}
\integer{indpt3=position(\pt3,\listpoint)}
\integer{indpt4=position(\pt4,\listpoint)}
\text{dessin=
poly red,\pt[\indpt1;1],\pt[\indpt1;2],\pt[\indpt2;1],\pt[\indpt2;2],\pt[\indpt3;1],\pt[\indpt3;2]
polyline red,\pt[\indpt1;1],\pt[\indpt1;2],\pt[\indpt4;1],\pt[\indpt4;2],\pt[\indpt2;1],\pt[\indpt2;2]
segment \pt[\indpt3;1],\pt[\indpt3;2],\pt[\indpt4;1],\pt[\indpt4;2],red
}

\text{quest=Calculer le volume du tétraèdre \(\pt1 \pt2 \pt3 \pt4\).}
\text{nomquest=Volume}
\if{\ggb==2}{
\text{lp_enon=aa=Pyramid(\pt1,\pt2,\pt3,\pt4)
SetColor[aa,red]
ShowLabel[aa, false]
SetLineThickness[aa,8]}
}
#endif
#if defined TARGET_Calculdist4
\text{lstrepVp=\(\frac{1}{8}V),\(\frac{1}{2}V),\(\frac{1}{4}V),\(\frac{1}{16}V)}
\text{lstrepV=\(\frac{1}{3}x y z),\(\frac{1}{6}x y z),\(\frac{1}{2}x y z),\(\frac{z}{3}\sqrt{x^2+y^2})}
\text{lstrepT=\(\frac{7}{24}x y z),\(\frac{z}{12}\sqrt{x^2+y^2}),\(\frac{1}{6}x y z),\(\frac{1}{4}x y z)}
\statement{
<div class="wims_columns">
  <div class="medium_size img_col">\draw{400,400}{\cadre}</div>
  <div class="medium_size text_col">
   Le tronc de pyramide \(A B C A'B'C') est déterminé ainsi:
<ul>
<li> Le triangle \(A B C) est rectangle en \(B\).</li>
<li> Le point \(S\) est un point de la perpendiculaire au plan \((A B C)) passant par \(A').</li>
<li> Les points \(A',B',C') sont les milieux des segments \([S A],[S B],[S C]\). </li>
<li> On pose \(x=A B\), \(y=B C\), \(z=A A'\).</li>
</ul>
  On note:
<ul>
<li> \(V) le volume du tétraèdre \(S A B C\).</li>
<li> \(V') le volume du tétraèdre \(S A' B' C'\).</li>
<li> \(T) le volume du tronc de pyramide \(A B C A' B' C'\).</li>
</ul>
  Déterminer les bonnes réponses.
<ul><li>\(V=)\embed{reply1}</li>
<li>\(V'=)\embed{reply2}</li>
<li>\(T=)\embed{reply3}</li>
</ul>
</div>
</div>
}
\answer{V}{1;\lstrepV}{type=radio}{option=shuffle}
\answer{V'}{1;\lstrepVp}{type=radio}{option=shuffle}
\answer{T}{1;\lstrepT}{type=radio}{option=shuffle}
#else
#include "ggbc_milieu.inc"
#include "ggbc.inc"
\if{\ggb==2}{
  \text{A=slib(geo2D/geogebra width=600
height=600
\fig_ggb)}
}
# include "cubedraw.inc"
\statement{
#include "intro_stat.inc"
\objet. \tpoints.<p>
\dimension.</p><p>\quest</p>
<div>
<label for="reply1">\nomquest =</label> \embed{reply1}.
</div>
<div class="wims_instruction">
 Taper <span class="tt">sqrt(...)</span> pour racine carrée, exemple taper
 <span class="tt">sqrt(2)</span> pour \(\sqrt{2}).
</div>
</div>
\if{\ggb=1}{</div>}
}
\answer{\nomquest}{\rep}{type=function}
#endif
