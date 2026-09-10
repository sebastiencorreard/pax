target=ecran1 ecran2 ecran3 ecran4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{range=10}
\text{S=0,10}
\text{ecran=randint(3..4)}
\text{trou=pari([\ecran-0.5,\ecran+2.5])}
#if defined TARGET_ecran1
\text{n=1}
\text{m=1}
\text{List=S}
\text{list=B}
#endif
#if defined TARGET_ecran2
\text{n=1}
\text{m=randint(3..4)}
\text{List=S}
\text{list=B1,B2,B3,B4,B5}
\text{list=\list[1..\m]}
#endif
#if defined TARGET_ecran3
\text{n=randint(3..4)}
\text{m=1}
\text{List=S1,S2,S3,S4,S5}
\text{List=\List[1..\n]}
\text{list=B}
#endif
#if defined TARGET_ecran4
\text{n=3}
\text{m=2}
\text{List=S1,S2,S3,S4,S5}
\text{list=B1,B2,B3,B4,B5}
\text{List=\List[1..\n]}
\text{list=\list[1..\m]}
#endif
\text{b=wims(makelist 2*x for x=1 to \range/2-1)}
\text{b=shuffle(\b)}
\text{obs=\b[1..\n]} abscisse range
\text{obj=\b[-\m..-1]} abscisse 0
\text{dessin=xrange -2,\range+2
yrange -2,12
frectangle -1,-1,\range+1,11,lightgrey}
\text{mid=5}
\text{dessin=\dessin
linewidth 6
segments black, \mid,0,\mid,\trou[1],\mid,\trou[2],\mid,10
string black,\mid,\range+1,E
linewidth 2}

\for{j=1 to \n}{
  \text{dessin=\dessin
crosshair \range,\obs[\j],orange
string black,\range+0.5,\obs[\j],\List[\j]}
}
\for{i=1 to \m}{
  \text{dessin=\dessin
crosshair 0,\obj[\i],blue
string black,-2,\obj[\i],\list[\i]}
}
\text{RES=}
\text{cnt1=0}
\text{cnt2=0}
\for{i=1 to \m}{
  \text{res=\i}
  \for{j=1 to \n}{
    \real{test=\obj[\i]+(\obs[\j]-\obj[\i])/\range*\mid}
    \if{\test>\trou[1] and \test <\trou[2]}{
      \if{\cnt1=0}{
        \text{dessinarrows=linewidth 1
arrows blue,10}
      }
      \integer{cnt1=\cnt1+1}
      \text{res=\res,\j}
      \text{dessinarrows=\dessinarrows,\range,\obs[\j],0,\obj[\i]}
    }{
      \if{\cnt2=0}{
        \text{dessinarrows2=linewidth 1
arrows red,10}
      }
      \integer{cnt2=\cnt2+1}
      \text{dessinarrows2=\dessinarrows2,\range,\obs[\j],5,\test}
    }
  }
  \text{res=wims(nonempty items \res)}
  \matrix{RES=\RES
\res}
}
#if defined TARGET_ecran1
\text{rep=\RES[1;2]=1 ? 1:2}
#endif
#if defined TARGET_ecran2
\text{rep=wims(select \RES where column 2=1)}
\text{rep=\rep[;1]}
#endif
#if defined TARGET_ecran3
\text{rep=\RES[2..-1]}
#endif
#if defined TARGET_ecran4
\text{rep1=\RES[1;2..-1]}
\text{rep1=\rep1=0 or \rep1=? \n+1}
\text{rep2=\RES[2;2..-1]}
\text{rep1=\rep2=0 or \rep2=? \n+1}
#endif

\statement{
  \name_enonce?
  \canvasdraw{200,200}{
  \dessin
  userdraw segment,blue
  }
<div class="wims_instruction">\name_hint</div>
}
#if defined TARGET_ecran1
\answer{}{\rep;\name_yesno}{type=radio}
#endif
#if defined TARGET_ecran2
\answer{}{\rep;\list}{type=checkbox}
#endif
#if defined TARGET_ecran3
\answer{}{\rep;\List}{type=checkbox}
#endif
#if defined TARGET_ecran4
\answer{\name_obs B1:}{\rep1;\List,\name_none}{type=checkbox}
\answer{\name_obs B2:}{\rep2;\List,\name_none}{type=checkbox}
#endif

\feedback{1=1}{
\canvasdraw{200,200}{
\dessin
\dessinarrows
\dessinarrows2
}
}
