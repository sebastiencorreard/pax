\title{FCT 13}

\text{nbfct=(\confparm2==)?1,2,3,4,5,6,7:\confparm2}

\text{fct_alg=??}
\integer{a_aff=randomitem(-1,1)*randint(1..5)}
integer{a_aff=-1}
\integer{b_aff=randomitem(-1,1)*randint(1..3)}
integer{b_aff=3}
\text{aff=\a_aff*t+\b_aff}
\text{aq=randitem(\nbfct)}
\integer{aq=\aq}
\text{rr=sqrt(t),1/t,-t^3,-t^2,t^2,t^3,\aff}
\text{fct_pari=(\aq==1)?sqrt(t):\rr[\aq]}
\integer{xi=(\aq==1)?randint(0..3):randint(-3..-1)}
integer{xi=-3}
\integer{xm=\xi+randint(4..6)}
integer{xm=2}

\text{crochet=[]}
###A virer
\text{cri=wims(char 1 of \crochet)}
\text{cre=wims(char 2 of \crochet)}

\text{cri=\lbracket}
\text{cre=\rbracket}

\text{gau1=(\aq==2)?\left \cre:\left \cri}
\text{droi1=\left \cre}
\text{gau2=\left \cri}
\text{droi2=(\aq==2)?\left \cri:\left \cre}
###
\text{gau1=(\aq==2)?\left \rbracket \,:\left \lbracket \,}
\text{droi1= \, \right \rbracket}
\text{gau2=\left \lbracket \,}
\text{droi2=(\aq==2)?\left \lbracket \,: \, \right \rbracket}


\if{\aq==7}{\real{sol=-\b_aff/\a_aff}}
\if{(\xi<\sol) and (\sol<\xm) and \aq==7}{\integer{zzz=2}
\real{fsol=evalue(\fct_pari,t=\sol+0.01)}
\integer{plus=(\fsol>0)?1}}{
\integer{zzz=(\aq==7)?1:}
\real{fsoll=evalue(\fct_pari,t=\xi+1)}
\integer{plus=(\fsoll>0)?1}}
\text{eta=reply1,reply2,reply3,reply4}
\text{etape=(\aq==1 or \aq==4 or \aq==5 or \zzz=1)?\eta:\eta,reply5,reply6,reply7}
\matrix{STEP=\etape}
\steps{\STEP}
\text{COND=(\aq==1 or \aq==5 or \aq==4 or \zzz==1)?1}
\text{rep_np=(\aq==1 or \aq==5 or \aq==3 or \plus==1)?positive:négative}
\text{rep_npp=(\aq==3 or \plus==1)?négative:positive}
\text{COND=(\aq==2)?2,3}
\text{COND=(\aq==3 or \aq==6)?4,5}
\text{COND=(\zzz==2)?6,7}
\conditions{\COND}

\real{pas=randomitem(0.01,0.02,0.03,0.04,0.05)}
\text{xi_alg=??}
\text{xm_alg=??}
\text{pas_alg=??}
\text{instruction_code=instruction=[3**2,from math import *,sqrt(2),&lt;,>,&lt;=,>=]}

\integer{rb=randint(1..2)}
\text{colorr=(\rb==1)?red:blue}
\text{colorb=(\rb==1)?blue:red}
\text{colorin=(\rb==1)?>=:<}

\text{parialgo=if(abs(yl[nn])<10^-(9),nzero=nn;);
if(yl[nn]>= 0 || abs(yl[nn])<10^-(9),colorl=concat(colorl,[red]);,colorl=concat(colorl,[blue]););}
\text{paricolor=\colorl[\kj]}

\text{initpythn=n=0}
\text{initpythcol=color_list=[]}
\text{scriptpyth=if y_list[n] ?? 0:
      color_list.append('\colorr')
  else:
      color_list.append('\colorb')
  n=n+1}
\text{scriptpythh=print(color_list[\:10])}

\text{javalc=color_liste=Sk.ffi.remapToJs(Sk.globals["color_list"]);}
