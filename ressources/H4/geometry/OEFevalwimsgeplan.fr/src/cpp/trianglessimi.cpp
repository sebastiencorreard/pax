target=trianglessimi1 trianglessimi2 trianglessimi3 trianglessimi4 trianglessimi5
#define TITRE Triangles semblables
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}

\integer{a=random(2..8)}
#include "isoqcm.inc"

#if defined TARGET_trianglessimi1
 \title{TITRE I}
 \integer{kk=random(1,1,1,1,2,2)}
 \if{\kk=1} {
   \text{data=randomrow(\simiVFquest)}
   \text{quest=\data[1]}
   \text{goodrep=\data[2]}
   \text{replist=Vrai,Faux}
  }{
 \integer{n=items(\simiquest)}
 \integer{ind=randint(1..\n)}
 \text{quest=\simiquest[\ind]}
 \text{replist=\similstrep[\ind;]}
 \text{goodrep=\simigrep[\ind;]}
  }
\statement{
 Cocher la bonne réponse:
<p>
\quest
</p>
<ol>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
\if{\kk=2}
{
<li>\embed{reply1,3}</li>
}
</ol>
}
\answer{Bonne réponse;}{\goodrep;\replist}{type=radio}{option=shuffle}
#endif
#if defined TARGET_trianglessimi2
 \title{TITRE II}
\integer{k=random(1,2)}
\if{\k=1}
 {
 \text{dessin=
 xrange -10,10
 yrange -8,8
 poly black,-6,4,6,4,6,-4,-6,-4
 poly black,-3,2,3,2,3,-2,-3,-2
 poly green,-6,0,0,4,6,0,0,-4
 segment -6,4,6,-4,red
 segment -6,-4,6,4,red
 text black,-6.5,4.6,medium,A
 text black,6.3,4.6,medium,B
 text black,-0.2,4.6,medium,I
 text black,-6.5,-4.7,medium,D
 text black,6.3,-4.7,medium,C
 text black,-0.2,-4.7,medium,K
 text black,-7,0,medium,L
 text black,6.8,0,medium,J
 text black,-0.3,-0.8,medium,O
 text black,-3,2.8,medium,E
 text black,3,2.8,medium,F
 text black,-3,-2.8,medium,H
 text black,3,-2.8,medium,G
 }

 \matrix{triangles=AEI,IFB,DHK,KGC,EIF,HKG,EOF,HOG,AOB,DOC
AEL,ELH,LHD,EOH,FOG,FJG,BFJ,JGC
KJC,IJB,ILA,KLD,BDA,DBC,CAD,ACB,GEH,EGF,HFG,FHE}
 \matrix{numrep=1,2,3,4,5,6,7,8,9,10
11,12,13,14,15,16,17,18
19,20,21,22,23,24,25,26,27,28,29,30}

 \integer{i=randint(1..3)}
 \text{data=row(\i,\triangles)}
 \text{cetriangle=randitem(\data)}
 \text{tintro=Soit \(ABCD) un rectangle de centre \(O). On note \(I,J,K,L,E,F,G) et \(H)
   les milieux respectifs des segments \([AB],[BC],[CD],[DA],[IL],[IJ],[JK]) et \([KL]).<p>
   Cocher les triangles semblables à \cetriangle.</p>}
 \text{goodrep=row(\i,\numrep)}
 \text{mstep=r2}
 }
 {
 \text{dessin=
 xrange -4,28
 yrange -2,14
 polygon black,2.75,0,24,0,-11/6,10
 segment 24,0,0,6,green
 segment 2.75,0,4,5,red
 segment 8.5,6,8,4,red
 segment 0,6,8.5,6,green
 segment 2.75,0,8.5,6,green
 polyline black,3,5.25,2.75,4.25,3.75,4
 polyline black,9,3.75,9.25,4.75,8.25,5
 text black,24,-0.3,medium,B
 text black,2.5,-0.3,medium,C
 text black,-2,10.8,medium,A
 text black,-0.8,6.6,medium,E
 text black,9,6.6,medium,D
 text black,4,5.6,medium,F
 text black,8,4,medium,G
 text black,6.5,5,medium,I
 }
 \text{data=\(ABC),AED,
\(EGD),BFC,
\(EID),BIC,
\(CFI),DGI}
 \text{triangle=randomrow(\data)}
 \text{goodrep=\triangle[2]}
 \text{tintro=Soit \(ABC) un triangle. La droite \((ED)) est parallèle à \((BC)).
  Les points \(F) et \(G) sont les pieds des perpendiculaires à \((BE)) issues de \(C) et \(D).
 Le point\(I) est l'intersection des droites \((CD)) et \((BE)).<p>
   Déterminer avec les seuls points nommés sur la figure
  un triangle semblable à \triangle[1] en respectant bien l'ordre
  des lettres.</p>
 }
 \text{mstep=r1}
}
\steps{\mstep}
\statement{<div class="float_right">\draw{500,300}{\dessin}</div>
\tintro

\if{\k=1}
{
\embed{reply2}
}
{\embed{reply1,4}
}
}
\answer{nom du triangle semblable}{\goodrep}{type=text}
\answer{triangles semblables;}{\goodrep;\triangles[1;],\triangles[2;],\triangles[3;]}{type=checkbox}{option=shuffle}
#endif
#if defined TARGET_trianglessimi3
 \title{TITRE III}
\text{clickList=aucun,\(A),\(B),\(C)}
\integer{a=random(4..20)}
\integer{b=random(4..20)}
\integer{b=\a=\b?\b+random(1..5)}
\integer{c=\b>\a?random(\b-\a..\b+\a):random(\a-\b..\a+\b)}
\integer{c=\c=\b?\c+1}
\integer{c=\c=\a?\c+1}
\integer{c=\c=\b?\c+1}

\integer{k=random(2..8)}
\integer{a1=\k*\a}
\integer{b1=\k*\b}
\integer{c1=\k*\c}
\text{data=\a,\b,\c,\(A),\(B),\(C)
\a,\c,\b,\(B),\(A),\(C)
\b,\a,\c,\(C),\(B),\(A)
\c,\a,\b,\(C),\(A),\(B)
\b,\c,\a,\(B),\(C),\(A)
\c,\b,\a,\(A),\(C),\(B)}
\text{letriangle=\a1,\b1,\c1}
\text{cetriangle=randomrow(\data)}
\integer{i=random(1..3)}
\if{\i=1}
 {
 %% pas semblable
 \integer{j=random(1..3)}
 \integer{e=\letriangle[\j]+random(2..4)}
 \text{letriangle=wims(replace item number \j by \e in \letriangle)}
 \text{goodrep1=aucun}
 \text{goodrep2=aucun}
 \text{goodrep3=aucun}
 }
 {
 \text{goodrep1=\cetriangle[4]}
 \text{goodrep2=\cetriangle[5]}
 \text{goodrep3=\cetriangle[6]}
 }
\text{size=60x40x1}
\statement{
   On considère un triangle \(ABC) tel que:
<div class="wimscenter"> \(AB=\letriangle[1]), \(BC=\letriangle[2]) et \(CA=\letriangle[3]).</div>

   On a tracé d'autre part le triangle \(EFG) vérifiant:
<div class="wimscenter"> \(EF=\cetriangle[1]), \(FG=\cetriangle[2]) et \(GE=\cetriangle[3]).</div>

   Associer les sommets correspondants
 lorsque les triangles sont semblables sinon associer
 l'étiquette <span class="tt">aucun</span>.
<table class="wimscenter wimsborder">
<tr><td>\(E)</td><td>\embed{reply1,\size}</td></tr>
<tr><td>\(F)</td><td>\embed{reply2,\size}</td></tr>
<tr><td>\(G)</td><td>\embed{reply3,\size}</td></tr>
</table>
}
\answer{}{\goodrep1;\clickList}{type=clickfill}
\answer{}{\goodrep2;\clickList}{type=clickfill}
\answer{}{\goodrep3;\clickList}{type=clickfill}
#endif
#if defined TARGET_trianglessimi4
 \title{TITRE IV}
\integer{a=random(4..20)}
\integer{b=random(4..20)}
\integer{b=\a=\b?\b+random(1..5)}
\integer{c=\b>\a?random(\b-\a..\b+\a):random(\a-\b..\a+\b)}
\integer{c=\c=\b?\c+1}
\integer{c=\c=\a?\c+1}
\integer{c=\c=\b?\c+1}

\integer{k=random(2..8)}
\integer{a1=\k*\a}
\integer{b1=\k*\b}
\integer{c1=\k*\c}
\integer{k=\k*10}
\integer{e1=\k}
\rational{f1=simplify(\b1*10/ \a)}
\rational{g1=simplify(\c1*10 / \a)}
\rational{e2=simplify(\a1*10 / \b)}
\rational{f2=\k}
\rational{g2=simplify(\c1*10 /\b)}
\rational{e3=simplify(\a1*10 / \c)}
\rational{f3=simplify(\b1*10 / \c)}
\rational{g3=\k}
\statement{
   On considère un triangle \(T) tel que les longueurs des côtés sont \a1, \b1 et \c1.
<p>
   On désire tracer un triangle EFG de même forme que \(T), tel que
   l'un des côtés a pour longueur \k.
</p><p>
   Compléter le tableau ci-dessous.
</p>
<table class="wimscenter wimsborder">
<tr><td>\(EF)</td><td>\(FG)</td><td>\(GE)</td></tr>
<tr><td>\e1</td><td>\embed{reply1,4}</td><td>\embed{reply2,4}</td></tr>
<tr><td>\embed{reply3,4}</td><td>\f2</td><td>\embed{reply4,4}</td></tr>
<tr><td>\embed{reply5,4}</td><td>\embed{reply6,4}</td><td>\g3</td></tr>
</table>
<div class="wims_instruction">
   Les résultats doivent être donnés sous forme de fractions irréductibles.
</div>
}
\answer{}{\f1}{type=numexp}
\answer{}{\g1}{type=numexp}
\answer{}{\e2}{type=numexp}
\answer{}{\g2}{type=numexp}
\answer{}{\e3}{type=numexp}
\answer{}{\f3}{type=numexp}
#endif
#if defined TARGET_trianglessimi5
 \title{TITRE V}
\integer{a=random(4..20)}
\integer{b=random(4..20)}
\integer{b=\b=\a?\b+2}
\text{cl=wims(makelist x for x=abs(\b-\a) to \a+\b)}
\text{rcl=\a,\b}
\text{cl=wims(listcomplement \rcl in \cl)}
\integer{c=randitem(\cl)}
\integer{t=random(10..140)}
\integer{s=random(5..160-\t)}
\integer{s=\s=\t?\s+5}
\integer{u=180-\s-\t}
\if{\u=\s or \u=\t}
 {
 \integer{s=\s+2}
 \integer{t=\t+2}
 \integer{u=\u-4}
 }
\integer{v=\u>20?\u-10:\u+10}
\integer{k=random(2..10)}
\integer{a1=\k*\a}
\integer{b1=\k*\b}
\integer{c1=\k*\c}

\text{lstquest=AB=\a &#44;  AC=\b &#44; \(\hat{A}=\u) &#44; \(PS=\a1) &#44; \(PT=\b1) &#44; \(\hat{S}=\s) et \(\hat{T}=\t) ,1
AB=\a &#44;  AC=\b &#44; BC=\c &#44; \(\hat{A}=\v) &#44; \(PS=\a1) &#44; \(PT=\b1) &#44; \(\hat{S}=\s) et \(\hat{T}=\t) ,3
AB=\a &#44;  AC=\b &#44; \(\hat{A}=\u) &#44; \(PS=\a1) &#44; \(PT=\b1) et \(\hat{P}=\u),1
AB=\a &#44;  AC=\b &#44;  BC=\c &#44; \(\hat{A}=\u) &#44; \(PS=\a1) &#44; \(PT=\b1) et \(\hat{P}=\v),3
AB=\a &#44;  AC=\b &#44; BC=\c &#44; \(\hat{A}=\u) &#44; \(PS=\a1) &#44; \(PT=\b1) et \(\hat{S}=\u),3
AB=\a &#44;  AC=\b &#44; \(\hat{A}=\u) &#44; \(PS=\a1) &#44; \(PT=\b1) et \(\hat{T}=\u),3
AB=\a &#44;  AC=\b &#44; \(\hat{B}=\u) &#44; \(PS=\a1) &#44; \(PT=\b1) et \(\hat{S}=\u),1
AB=\a &#44;  AC=\b &#44; \(\hat{C}=\u) &#44; \(PS=\a1) &#44; \(PT=\b1) et \(\hat{T}=\u),1
AB=\a &#44;  BC=\b &#44; AC=\c &#44; \(\hat{B}=\u) &#44; \(PS=\a1) &#44; \(PT=\b1) et \(\hat{S}=\u),3
AB=\a &#44;  BC=\b &#44; \(\hat{B}=\u) &#44; \(PS=\a1) &#44; \(ST=\b1) et \(\hat{S}=\u),1
AB=\a &#44;  BC=\b &#44; AC=\c &#44; \(PS=\a1) &#44; \(ST=\b1) et \(PT=\c1),1
AB=\a &#44;  BC=\b &#44; AC=\c &#44; \(PS=\a1) &#44; \(PT=\b1) et \(ST=\c1),2
AB=\a &#44;  BC=\b &#44; AC=\c &#44; \(PS=\b1) &#44; \(PT=\c1) et \(ST=\a1),2
\(\hat{A}=\u) &#44; \(\hat{B}=\s) &#44; \(\hat{C}=\t) &#44; \(\hat{P}=\u) &#44; \(\hat{S}=\s) et \(\hat{T}=\t),1
\(\hat{A}=\s) &#44; \(\hat{B}=\u) &#44; \(\hat{C}=\t) &#44; \(\hat{P}=\u) &#44; \(\hat{S}=\s) et \(\hat{T}=\t),2
\(\hat{A}=\u) &#44; \(\hat{B}=\t) &#44; \(\hat{C}=\s) &#44; \(\hat{P}=\u) &#44; \(\hat{S}=\s) et \(\hat{T}=\t),2
\(\hat{A}=\u) &#44; \(\hat{B}=\s) &#44; \(\hat{S}=\s) et \(\hat{T}=\t),1
\(\hat{B}=\s) &#44; \(\hat{C}=\t) &#44; \(\hat{P}=\u) et \(\hat{T}=\t),1
\(\hat{A}=\s) &#44; \(\hat{C}=\t) &#44; \(\hat{S}=\u) et \(\hat{T}=\t),1
}
 \integer{i=randint(1..18)}
 \text{data=row(\i,\lstquest)}
 \text{quest=\data[1]}
 \text{goodrep=\data[2]}
\text{lstrep=Ils sont de même forme et les sommets A&#44;B&#44;C correspondent aux sommets P&#44;S&#44;T dans cet ordre,
   Ils sont de même forme mais les sommets A&#44;B&#44;C correspondent aux sommets P&#44;S&#44;T dans un ordre différent,
   Ils ne sont pas de même forme,On ne peut rien dire}
#endif

#if defined TARGET_trianglessimi5
\statement{
   On considère deux triangles \(ABC) et \(PST) pour lesquels on connaît
   les mesures suivantes:
<div class="wimscenter">\quest.</div>
<p>
   Que peut-on dire des triangles \(ABC) et \(PST) ?
</p>
<ul><li>\embed{reply1,1}</li><li>\embed{reply1,2}
</li><li>\embed{reply1,3}</li><li>\embed{reply1,4}</li></ul>

}
\answer{Semblables?}{\goodrep;\lstrep}{type=radio}
#endif
