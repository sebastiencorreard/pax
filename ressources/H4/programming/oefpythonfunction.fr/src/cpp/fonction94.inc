\title{FCT 14}

\text{nbfct=(\confparm2==)?1,2,3,4,5,6,7:\confparm2}

\text{fct_alg=??}
\integer{a_aff=randomitem(-1,1)*randint(1..5)}
\integer{b_aff=randomitem(-1,1)*randint(1..3)}
\text{aff=\a_aff*t+\b_aff}
\text{aq=randitem(\nbfct)}
\integer{aq=\aq}
\text{rr=sqrt(t),1/t,-t^3,-t^2,t^2,t^3,\aff}
\text{fct_pari=(\aq==1)?sqrt(t):\rr[\aq]}
\integer{xi=(\aq==1)?randint(0..3):randint(-3..-1)}
\integer{xm=\xi+randint(4..6)}


###A virer
\text{crochet=[]}
\text{cri=wims(char 1 of \crochet)}
\text{cre=wims(char 2 of \crochet)}
\text{gau1=\left\cri}
\text{droi1=(\aq==2)?\left\cri:\left\cre}
\text{gau2=(\aq==2)?\left\cre:\left\cri}
\text{droi2=\left\cre}
###
\text{gau1=\left \lbracket \,}
\text{droi1=(\aq==2)?\left \lbracket \, : \, \right \rbracket}
\text{gau2=(\aq==2)?\, \right \rbracket:\left \lbracket \, }
\text{droi2=\, \right \rbracket}




\text{eta=reply1,reply2,reply3,reply4}
\text{etape=(\aq==1 or \aq==3 or \aq==6 or \aq=7)?\eta:\eta,reply5,reply6,reply7}
\matrix{STEP=\etape}
\steps{\STEP}

\text{COND=(\aq==1 or \aq==3 or \aq==6 or \aq==7)?1}
\text{rep_np=(\aq==1 or \aq==6 or (\aq==7 and \a_aff>0))?croissante:décroissante}
\text{rep_npp=(\aq==4)?croissante:décroissante}
\text{rep_nppp=(\aq==4)?décroissante:croissante}
\text{COND=(\aq==2)?2,3}
\text{COND=(\aq==4 or \aq==5)?4,5}

\conditions{\COND}

\real{pas=randomitem(0.01,0.02,0.03,0.04,0.05)}
\text{xi_alg=??}
\text{xm_alg=??}
\text{pas_alg=??}
\text{instruction_code=instruction=[3**2,from math import *,sqrt(2),&lt;,>,&lt;=,>=]}

\integer{gv=randint(1..2)}
\text{colorg=(\gv==1)?green:violet}
\text{colorv=(\gv==1)?violet:green}
\text{colorin=(\gv==1)?>:<}

\text{parialgo=if(nn>=2,if(yl[nn]\colorin yl[nn-1],colorll=concat(colorll,[\colorg]);,colorll=concat(colorll,[\colorv]);););}
\text{paricolor=\colorl[\kj]}

\text{initpythn=n=0}
\text{initpythcol=color_list=['black']}
\text{scriptpyth=if (n>=1):
    if(y_list[n] ?? y_list[n-1]):
      color_list.append('\colorg')
    else:
      color_list.append('\colorv')
  n=n+1}
\text{scriptpythh=print(color_list[\:10])}
\text{javalc=color_liste=Sk.ffi.remapToJs(Sk.globals["color_list"]);}
