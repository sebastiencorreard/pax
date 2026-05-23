target=fli1 fli2

#include "author.inc"
#include "header.inc"
#include "lang_titles.inc"
#include "css.inc"

#if defined TARGET_fli1
\title{TITRE}
#endif
#if defined TARGET_fli2
\title {TITRE}
#endif

\text{nom=randitem(f,g,h)}
\text{B=shuffle(-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,1,2,3,4,5,6,7,8,9,10)}
\integer{ant1=\B[1]}
\integer{img1=\B[2]}
\integer{oppant1=-1*\ant1}
\text{listest=\ant1,\oppant1}
\text{B=wims(listcomplement \listest in \B)}
\integer{ant2=\B[3]}
\text{tant2=\ant2<0?(\ant2):\ant2}
\text{tant1=\ant1<0?(\ant1):\ant1}
\rational{a=simplify(\img1/\ant1)}
\integer{numa=pari(numerator(\a))}
\integer{denoma=pari(denominator(\a))}
\rational{inva=\denoma/\numa}


#if defined TARGET_fli1
\integer{aux=abs(\numa)}
\if{\ant1=\denoma and \denoma<>1 and \numa<0 }{\text{solu=\(a=\frac{\img1}{\ant1}=-\frac{\aux}{\denoma}\)}}
\if{\ant1=\denoma and \denoma=1 and \numa<0}{\text{solu=\(a=\frac{\img1}{\ant1}=-\aux\)}}
\if{\ant1<>\denoma and \denoma<>1 and \numa<0}{\text{solu=\(a=\frac{\img1}{\ant1}=\frac{\numa}{\denoma}=-\frac{\aux}{\denoma}\)}}
\if{\ant1<>\denoma and \denoma=1 and \numa<0}{\text{solu=\(a=\frac{\img1}{\ant1}=-\aux\)}}
\if{\ant1=\denoma and \denoma<>1 and \numa>0}{\text{solu=\(a=\frac{\img1}{\ant1}\)}}
\if{\ant1=\denoma and \denoma=1 and \numa>0}{\text{solu=\(a=\frac{\img1}{\ant1}=\numa\)}}
\if{\ant1<>\denoma and \denoma<>1 and \numa>0}{\text{solu=\(a=\frac{\img1}{\ant1}=\frac{\numa}{\denoma}\)}}
\if{\ant1<>\denoma and \denoma=1 and \numa>0}{\text{solu=\(a=\frac{\img1}{\ant1}=\numa\)}}
#endif


#if defined TARGET_fli2
\rational{img2=\img1*\ant2/\ant1}
\rational{badimg2=\img1*\ant1/\ant2}
\integer{numimg2=pari(numerator(\img2))}
\integer{denomimg2=pari(denominator(\img2))}
\rational{img2ir=simplify(\img2)}
\integer{numimg2ir=pari(numerator(\img2ir))}
\integer{denomimg2ir=pari(denominator(\img2ir))}
\integer{aux=abs(\numimg2ir)}
\if{\denomimg2=\denomimg2ir and \denomimg2ir<>1 and \numimg2ir<0 }{\text{solu=\(\nom (\ant2)=\frac{\img1 \times \tant2}{\ant1}=\frac{\numimg2ir}{\denomimg2ir}=-\frac{\aux}{\denomimg2ir}\)}}
\if{\denomimg2=\denomimg2ir and \denomimg2ir=1 and \numimg2ir<0}{\text{solu=\(\nom (\ant2)=\frac{\img1 \times \tant2}{\ant1}=\numimg2ir)}}
\if{\denomimg2<>\denomimg2ir and \denomimg2ir<>1 and \numimg2ir<0}{\text{solu=\(\nom (\ant2)=\frac{\img1 \times \tant2}{\ant1}=\frac{\numimg2}{\denomimg2}=\frac{\numimg2ir}{\denomimg2ir}=-\frac{\aux}{\denomimg2ir}\)}}
\if{\denomimg2<>\denomimg2ir and \denomimg2ir=1 and \numimg2ir<0}{\text{solu=\(\nom (\ant2)=\frac{\img1 \times \tant2}{\ant1}=\frac{\numimg2}{\denomimg2}=\numimg2ir\)}}
\if{\denomimg2=\denomimg2ir and \denomimg2ir<>1 and \numimg2ir>0}{\text{solu=\(\nom (\ant2)=\frac{\img1 \times \tant2}{\ant1}=\frac{\numimg2ir}{\denomimg2ir}\)}}
\if{\denomimg2=\denomimg2ir and \denomimg2ir=1 and \numimg2ir>0}{\text{solu=\(\nom (\ant2)=\frac{\img1 \times \tant2}{\ant1}=\numimg2ir)}}
\if{\denomimg2<>\denomimg2ir and \denomimg2ir<>1 and \numimg2ir>0}{\text{solu=\(\nom (\ant2)=\frac{\img1 \times \tant2}{\ant1}=\frac{\numimg2}{\denomimg2}=\frac{\numimg2ir}{\denomimg2ir}\)}}
\if{\denomimg2<>\denomimg2ir and \denomimg2ir=1 and \numimg2ir>0}{\text{solu=\(\nom (\ant2)=\frac{\img1 \times \tant2}{\ant1}=\frac{\numimg2}{\denomimg2}=\numimg2ir\)}}
#endif

\integer{test1=2}
\integer{test2=2}
\integer{\ch=randint(3..6)}

#include "lang.inc"
\text{reply_class=euler_answer_nobg}
\statement{
\name_enon
<div class="euler_quest_nobg spacer"> 
  \name_quest[1] \name_quest[\ch] \name_quest[2]
</div>
<div class="spacer">
  <div class="\reply_class">
    <label for="reply1">\name_ans1</label>\embed{r1,4}.
  </div>
</div>
<div class="wims_instruction spacer">\name_inst</div>
}

#if defined TARGET_fli1
\answer{}{\rep}{type=numexp}{option=noreduction}
\condition{\name_goodans}{\rep=\a}
\if{\rep=\a}{\integer{test1=1}}{\integer{test1=0}}
\condition{\name_cond}{\rep issamecase \a}
\integer{test2=\rep issamecase \a?1:0}
\feedback{\rep=\a and (\rep notsamecase \a)}{<div class="highlight">\name_feed1</div>}
\feedback{\rep=\inva}{<div class="highlight">\name_feed2</div>}
\hint{\name_hint}
\solution{\name_hint
<p>\name_sol1</p>
\name_sol2
<p>\name_sol3 <span class="nowrap">\solu.</span></p>}
#endif

#if defined TARGET_fli2
\answer{}{\rep}{type=auto}{option=noreduction}
\condition{\name_goodans}{\rep=\img2}
\feedback{\rep=\badimg2}{<div class="highlight">\name_feed2[1]
<p>\name_feed2[2] \(\frac{\img1 \times \tant1}{\ant2}\) \name_feed2[3] \(\frac{\img1 \times \tant2}{\ant1}\).</p></div>}

\integer{test1=\rep=\img2?1:0}
\condition{\name_cond}{\rep issamecase \img2}
\integer{test2=\rep issamecase \img2?1:0}
\feedback{\rep=\img2 and (\rep notsamecase \img2)}{<div class="highlight">\name_feed1 <p>\name_feed2 <span class="nowrap">\(\sol).</span></p></div>}
\hint{\name_hint}
\solution{\name_sol1
<table class="wimsborder"><tr>
              <td>\(x\)</td>
              <td>\(\ant1\)</td>
              <td>\(\ant2\)</td>
          </tr>
          <tr>
              <td>\(\nom(x)\)</td>
              <td>\(\img1\)</td>
              <td>\(\nom(\ant2)\)</td>
          </tr>
</table>
\name_sol2  
<p>\solu</p>}
#endif
\if{\test1<1 or \test2<1}{\text{reply_class=euler_rep_bad_nobg cross}
                         }{
                         \text{reply_class=euler_rep_good_nobg tick}
                         }
