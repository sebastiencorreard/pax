target=signeProdQuot2 signeProdQuotient
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\computeanswer{no}
\format{html}
\precision{100}
%%%%%%%%%%% ajout MutuWIMS %%%%%%%%%%%%%%%%%%%
1 : produit %%%% 2 : quotient %%%%%%%%%%% 3 : l'un ou l'autre
\text{confparm1= items(\confparm1)=0 ? 3:\confparm1}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\integer{a = (-1)^random(0,1)*random(1..10)}
\integer{b = (-1)^random(0,1)*random(1..10)}
\integer{c = (-1)^random(0,1)*random(1..10)}
\integer{d = (-1)^random(0,1)*random(1..10)}
\rational{racu=-(\b)/(\a)}

/** Faire en sorte que les racines soient distinctes **/
\integer{d=(-(\d)/(\c)=\racu)?-\d}
\rational{racv=-(\d)/(\c)}
#if defined TARGET_signeProdQuot2 || TARGET_signeProdQuotient
\function{u=\a*x + \b}
\function{u=\a==1?x + \b}
\function{u=\a==-1?-x + \b}
\function{v=\c*x + \d}
\function{v=\c==1?x + \d}
\function{v=\c==-1?-x + \d}
#endif

/** produit ou quotient **/
%%%%%%%%% mutuwims %%%%%%%%%%%
\if{\confparm1=3}{
\integer{cas=random(1,2)}
}
{\integer{cas=\confparm1}}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\text{nomf=P,Q}
\text{nom=item(\cas,\nomf)}
\text{listf=(\u)(\v),(\u)/(\v)}
\function{f=item(\cas,\listf)}
\rational{vi=\racv}

/** placer le terme ayant la plus petite racine en premier **/
/** rgerac = 1 : u avant v ; rgerac = 2 : v avant u **/
\integer{rgerac=\racu<\racv?1:2}

/** ordonner les racines ; preparer les tests de signe **/
\rational{x1=\rgerac==1?\racu:\racv}
\rational{x2=\rgerac==1?\racv:\racu}
\rational{ug = evaluate(\u,x=\x1-1)}
\rational{um = evaluate(\u,x=(\x1+\x2)/2)}
\rational{ud = evaluate(\u,x=\x2+1)}
\rational{vg = evaluate(\v,x=\x1-1)}
\rational{vm = evaluate(\v,x=(\x1+\x2)/2)}
\rational{vd = evaluate(\v,x=\x2+1)}

/** choix pour les barres et signes **/
\text{ch3=+,-}
\text{ch4=0,||,|}
\text{ch5=+,-}
\text{ch6=0,||,|}
\text{ch7=+,-}

\text{ch8=+,-}
\text{ch9=0,||,|}
\text{ch10=+,-}
\text{ch11=0,||,|}
\text{ch12=+,-}

\text{ch13=+,-}
\text{ch14=0,||,|}
\text{ch15=+,-}
\text{ch16=0,||,|}
\text{ch17=+,-}

/** bonnes réponses **/
\rational{rep1=\x1}
\rational{rep2=\x2}
\text{rep3=\ug>0?1:2}
\text{rep4=\x1==\racu?1:3}
\text{rep5=\um>0?1:2}
\text{rep6=\x2==\racu?1:3}
\text{rep7=\ud>0?1:2}

\text{rep8=\vg>0?1:2}
\text{rep9=\x1==\racv?1:3}
\text{rep10=\vm>0?1:2}
\text{rep11=\x2==\racv?1:3}
\text{rep12=\vd>0?1:2}

\text{rep13=\rep3*\rep8==2?2:1}
\text{rep14=\cas==2 and \x1==\vi?2:1}
\text{rep15=\rep5*\rep10==2?2:1}
\text{rep16=\cas==2 and \x2==\vi?2:1}
\text{rep17=\rep7*\rep12==2?2:1}

\text{feed0=wims(replace internal YYYY by \x2 in \name_feed4)}
\text{feed2=wims(replace internal VVVV by \vi in \name_feed2)}
\text{feed3=wims(replace internal XXXX by \x1 in \name_feed3)}
\text{feed4=wims(replace internal YYYY by \x2 in \name_feed4)}

\statement{
  <div class="monenonce">
#if defined TARGET_signeProdQuotient
  <p>\name_question
  \if{\cas==1}{\name_on \(\,\RR\) }{, \name_forall \(x\neq\vi\), } \name_by \(f(x) = \f\).
  </p>
#endif
#if defined TARGET_signeProdQuot2
  <p>\name_question \if{\cas==1}{\name_produit[1] }{\name_produit[2] }
  \(\nom(x) = \f\).</p>
#endif
  </div>
<div class="center">
<table class="wimsborder">
<tr>
<td style="width:20%;text-align:center">\(x\)</td>
<td style="width:20%;text-align:left">\(-\infty\)</td>
<td style="text-align:center">\embed{reply1,3}</td>
<td style="text-align:center"></td>
<td style="text-align:center">\embed{reply2,3}</td>
<td style="width:20%;text-align:right">\(+\infty\)</td>
</tr><tr>
<td style="text-align:center"> \(\u\)</td>
<td style="text-align:center">\embed{reply3}</td>
<td style="text-align:center">\embed{reply4}</td>
<td style="text-align:center">\embed{reply5}</td>
<td style="text-align:center">\embed{reply6}</td>
<td style="text-align:center">\embed{reply7}</td>
</tr><tr>
<td style="text-align:center">\(\v)</td>
<td style="text-align:center">\embed{reply8}</td>
<td style="text-align:center">\embed{reply9}</td>
<td style="text-align:center">\embed{reply10}</td>
<td style="text-align:center">\embed{reply11}</td>
<td style="text-align:center">\embed{reply12}</td>
</tr><tr>
<td style="text-align:center">\(f(x)\)</td>
<td style="text-align:center">\embed{reply13}</td>
<td style="text-align:center">\embed{reply14}</td>
<td style="text-align:center">\embed{reply15}</td>
<td style="text-align:center">\embed{reply16}</td>
<td style="text-align:center">\embed{reply17}</td>
</tr>
</table>
</div>
}

\answer{}{\rep1}{type=numexp}
\answer{}{\rep2}{type=numexp}
\answer{}{\rep3 ; \ch3}{type=menu}
\answer{}{\rep4 ; \ch4}{type=menu}
\answer{}{\rep5 ; \ch5}{type=menu}
\answer{}{\rep6 ; \ch6}{type=menu}
\answer{}{\rep7 ; \ch7}{type=menu}
\answer{}{\rep8 ; \ch8}{type=menu}
\answer{}{\rep9 ; \ch9}{type=menu}
\answer{}{\rep10 ; \ch10}{type=menu}
\answer{}{\rep11 ; \ch11}{type=menu}
\answer{}{\rep12 ; \ch12}{type=menu}
\answer{}{\rep13 ; \ch13}{type=menu}
\answer{}{\rep14 ; \ch14}{type=menu}
\answer{}{\rep15 ; \ch15}{type=menu}
\answer{}{\rep16 ; \ch16}{type=menu}
\answer{}{\rep17 ; \ch17}{type=menu}

\hint{<p>\name_hint1</p><p>\name_hint2</p>}

\integer{errordo=\reply1>\reply2?1:0}

\integer{errvi1=(\cas==2 and \errordo==0 and \x1=\vi and \reply14 notsametext ||)?1:0}
\integer{errvi1=(\cas==2 and \errordo==0 and \x2=\vi and \reply16 notsametext ||)?1}

\integer{errvi2=(\cas==2 and \errordo==0 and \x1!=\vi and \reply14 issametext ||)?1:0}
\integer{errvi2=(\cas==2 and \errordo==0 and \x2!=\vi and \reply16 issametext ||)?2}
\feedback{\errordo==1}{<div class="macorrection enrouge">\name_feed1</div}
\feedback{\errvi1==1}{<div class="macorrection enrouge">\name_feed2</div>}
\feedback{\errvi2==1}{<div class="macorrection enrouge">\feed3</div>}
\feedback{\errvi2==2}{<div class="macorrection enrouge">\feed0</div>}
