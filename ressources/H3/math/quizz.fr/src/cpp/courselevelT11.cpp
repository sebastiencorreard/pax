target=courseT11_1 courseT11_1step courseT11_2 courseT11_2step
\author{Cyrille,Douriez}
\email{cyrille.douriez@ac-amiens.fr}
\computeanswer{no}
\precision{1000000000}
%%%%%% option nonstop %%%%%%%%
\text{confparm2=items(\confparm2)=0 ? 1:\confparm2}
\text{confparm2=\confparm2=2?nonstop:}

#define KEYWORD1 methodical_calculation,subtraction,addition,mean,decimals,pbsolving,equations,percents,multiplication,coordinates,integers,literal_calculation,functions,probability,percentage,power,fraction,mental_calculation,proportionality
#define KEYWORD2 literal_calculation,functions,time,power,circle,percents,convertion,squareroot,equations,area,exponent,python,intervals,multiplication,velocity,rational,methodical_calculation,inequalities,subtraction,lines,factorization,rectangles,mental_calculation,proportionality,addition

#include "instruction.inc"

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#if defined TARGET_courseT11_1 || defined TARGET_courseT11_1step
# include "T1101.inc"
\text{enonce1=\enonce}
\text{enonceb1=\enonceb}
\text{rep1=\rep}
\text{feedback1=\feedback}
\text{size1=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1102.inc"
\text{enonce2=\enonce}
\text{enonceb2=\enonceb}
\text{rep2=\rep}
\text{feedback2=\feedback}
\text{size2=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1103.inc"
\text{enonce3=\enonce}
\text{enonceb3=\enonceb}
\text{rep3=\rep}
\text{feedback3=\feedback}
\text{size3=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1104.inc"
\text{enonce4=\enonce}
\text{enonceb4=\enonceb}
\text{rep4=\rep}
\text{feedback4=\feedback}
\text{size4=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1105.inc"
\text{enonce5=\enonce}
\text{enonceb5=\enonceb}
\text{rep5=\rep}
\text{feedback5=\feedback}
\text{size5=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1106.inc"
\text{enonce6=\enonce}
\text{enonceb6=\enonceb}
\text{rep6=\rep}
\text{feedback6=\feedback}
\text{size6=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1107.inc"
\text{enonce7=\enonce}
\text{enonceb7=\enonceb}
\text{rep7=\rep}
\text{feedback7=\feedback}
\text{size7=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1108.inc"
\text{enonce8=\enonce}
\text{enonceb8=\enonceb}
\text{rep8=\rep}
\text{feedback8=\feedback}
\text{size8=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1109.inc"
\text{enonce9=\enonce}
\text{enonceb9=\enonceb}
\text{rep9=\rep}
\text{feedback9=\feedback}
\text{bad09091=\bad1}
\text{bad09092=\bad2}
\text{size9=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1110.inc"
\text{enonce10=\enonce}
\text{enonceb10=\enonceb}
\text{rep10=\rep}
\text{feedback10=\feedback}
\text{size10=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1111.inc"
\text{enonce11=\enonce}
\text{enonceb11=\enonceb}
\text{rep11=\rep}
\text{feedback11=\feedback}
\text{size11=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1112.inc"
\text{enonce12=\enonce}
\text{enonceb12=\enonceb}
\text{rep12=\rep}
\text{feedback12=\feedback}
\text{size12=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1113.inc"
\text{enonce13=\enonce}
\text{enonceb13=\enonceb}
\text{rep13=\rep}
\text{feedback13=\feedback}
\text{size13=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1114.inc"
\text{enonce14=\enonce}
\text{enonceb14=\enonceb}
\text{rep14=\rep}
\text{feedback14=\feedback}
\text{size14=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1115.inc"
\text{enonce15=\enonce}
\text{enonceb15=\enonceb}
\text{rep15=\rep}
\text{feedback15=\feedback}
\text{size15=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#if defined TARGET_courseT11_2 || defined TARGET_courseT11_2step
# include "T1116.inc"
\text{enonce1=\enonce}
\text{enonceb1=\enonceb}
\text{rep1=\rep}
\text{feedback16=\feedback}
\text{size1=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1117.inc"
\text{enonce2=\enonce}
#if defined TARGET_courseT11_2 
\text{enonceb2=\enoncebcourse}
\text{rep2=\repcourse}
#endif
#if defined TARGET_courseT11_2step
\text{enonceb2=\enonceb}
\text{rep2=\rep}
#endif
\text{feedback2=\feedback}
\text{size2=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1118.inc"
\text{enonce3=\enonce}
\text{enonceb3=\enonceb}
\text{rep3=\rep}
\text{feedback3=\feedback}
\text{size3=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1119.inc"
\text{enonce4=\enonce}
\text{enonceb4=\enonceb}
\text{rep4=\rep}
\text{feedback4=\feedback}
\text{size4=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1120.inc"
\text{enonce5=\enonce}
\text{enonceb5=\enonceb}
\text{rep5=\rep}
\text{feedback5=\feedback}
\text{size5=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1121.inc"
\text{enonce6=\enonce}
#if defined TARGET_courseT11_2 
\text{enonceb6=\enoncebcourse}
\text{rep6=\repcourse}
#endif
#if defined TARGET_courseT11_2step
\text{enonceb6=\enonceb}
\text{rep6=\rep}
#endif
\text{feedback6=\feedback}
\text{size6=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1122.inc"
\text{enonce7=\enonce}
\text{enonceb7=\enonceb}
\text{rep7=\rep}
\text{feedback7=\feedback}
\text{size7=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1123.inc"
\text{enonce8=\enonce}
\text{enonceb8=\enonceb}
\text{rep8=\rep}
\text{feedback8=\feedback}
\text{size8=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1124.inc"
\text{enonce9=\enonce}
\text{enonceb9=\enonceb}
\text{rep9=\rep}
\text{feedback9=\feedback}
\text{size9=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1125.inc"
\text{enonce10=\enonce}
\text{enonceb10=\enonceb}
\text{rep10=\rep}
\text{feedback10=\feedback}
\text{size10=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1126.inc"
\text{enonce11=\enonce}
\text{enonceb11=\enonceb}
\text{rep11=\rep}
\text{feedback11=\feedback}
\text{size11=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1127.inc"
\text{enonce12=\enonce}
\text{enonceb12=\enonceb}
\text{rep12=\rep}
\text{feedback12=\feedback}
\text{size12=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1128.inc"
\text{enonce13=\enonce}
\text{enonceb13=\enonceb}
\text{rep13=\rep}
\text{feedback13=\feedback}
\text{size13=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1129.inc"
\text{enonce14=\enonce}
\text{enonceb14=\enonceb}
\text{enoncec14=\enoncec}
\text{rep14=\rep}
\text{repb14=\repb}
\text{feedback14=\feedback}
\text{size14=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "T1130.inc"
\text{enonce15=\enonce}
\text{enonceb15=\enonceb}
\text{rep15=\rep}
\text{feedback15=\feedback}
\text{size15=\size}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

#define TITLE Course aux nombres niveau

#if defined TARGET_courseT11_1step
\title{TITLE T11 part.1 (step)}
\observation{Questions T1101 à T1115. Course aux Nombres de mars 2022 (académie de Strasbourg) pour des élèves de 1ère technologique. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD1}
#define ALL 1
#endif
#if defined TARGET_courseT11_1
\title{TITLE T11 part.1}
\observation{Questions T1101 à T1115. Course aux Nombres de mars 2022 (académie de Strasbourg) pour des élèves de 1ère technologique.<br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD1}
#define ALL 0
#endif

#if defined TARGET_courseT11_2step
\title{TITLE T11 part.2 (step)}
\observation{Questions T1116 à T1130. Course aux Nombres de mars 2022 (académie de Strasbourg) pour des élèves de 1ère technologique. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD2}
#define ALL 1
#endif
#if defined TARGET_courseT11_2
\title{TITLE T11 part.2}
\observation{Questions T1116 à T1130. Course aux Nombres de mars 2022 (académie de Strasbourg) pour des élèves de 1ère technologique. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD2}
#define ALL 0
#endif
\text{choix=\confparm1= ? wims(makelist x for x=1 to 15): \confparm1}
\integer{cnt=items(\choix)}

\matrix{STEP=wims(makelist reply x for x in \choix)}
#if ALL==1
\matrix{STEP=wims(replace internal , by ; in \STEP)}
#endif
#if defined TARGET_courseT11_1 || defined TARGET_courseT11_1step
\steps{\STEP}
#endif
#if defined TARGET_courseT11_2 || defined TARGET_courseT11_2step
%%%%%% Question T1129 avec deux champs de réponse.
\steps{wims(replace item reply 14 by reply 14,reply 16 in \STEP)}
\integer{rg14=position(14,\choix)}
#endif
*****
#if defined TARGET_courseT11_2step
pbm des tailles des étiquettes
\integer{rg2=position(2,\choix)}
\integer{rg6=position(6,\choix)}
#endif
#if defined TARGET_courseT11_2step || defined TARGET_courseT11_2
%%% slib question 4
\integer{rg4=position(4,\choix)}
#endif

#if defined TARGET_courseT11_1 || defined TARGET_courseT11_1step
\matrix{enonce=\enonce1
\enonce2
\enonce3
\enonce4
\enonce5
\enonce6
\enonce7
\enonce8
\enonce9
\enonce10
\enonce11
\enonce12
\enonce13
\enonce14
\enonce15}
\matrix{size=\size1
\size2
\size3
\size4
\size5
\size6
\size7
\size8
\size9
\size10
\size11
\size12
\size13
\size14
\size15
}
#endif

#if defined TARGET_courseT11_2 || defined TARGET_courseT11_2step
\matrix{enonce=\enonce1
\enonce2
\enonce3
&nbsp;
\enonce5
\enonce6
\enonce7
\enonce8
\enonce9
\enonce10
\enonce11
\enonce12
\enonce13
\enonce14
\enonce15}
\matrix{size=\size1
\size2
\size3
\size4
\size5
\size6
\size7
\size8
\size9
\size10
\size11
\size12
\size13
\size14
\size15
}
#endif
\text{enonceb=\enonceb1;
\enonceb2;
\enonceb3;
\enonceb4;
\enonceb5;
\enonceb6;
\enonceb7;
\enonceb8;
\enonceb9;
\enonceb10;
\enonceb11;
\enonceb12;
\enonceb13;
\enonceb14;
\enonceb15}
\text{feed=\feedback1;\feedback2;\feedback3;\feedback4;\feedback5;\feedback6;\feedback7;
\feedback8;\feedback9;\feedback10;\feedback11;\feedback12;\feedback13;\feedback14;\feedback15}

\text{latexversion=\begin{enumerate}}
\for{h=1 to \cnt}{
#if defined TARGET_courseT11_1 || defined TARGET_courseT11_1step
%% pas de version latex pour les énoncés avec des images ou slib
  \if{\choix[\h] notitemof 14,15}{
#endif
#if defined TARGET_courseT11_2 || defined TARGET_courseT11_2step
%% il faudrait faire les figures ou le tableau ...
  \if{\choix[\h] notitemof 1,2,3,4,15}{
#endif
    \text{latexversion=\latexversion
    \item
    \enonce[\choix[\h];]
    \dots \enonceb[\choix[\h];]
  }
#if defined TARGET_courseT11_1 || defined TARGET_courseT11_1step
}{
    }
#endif
#if defined TARGET_courseT11_2 || defined TARGET_courseT11_2step
}{\if{\choix[\h]=6}{\text{latexversion=\latexversion
\item
\enonce6
\dots}}

\if{\choix[\h]==14}{\text{latexversion=\latexversion
    \item
    \enonce14 \dots \enonceb14 \dots \enoncec14
   }}}
#endif
}



\text{latexversion=\latexversion \end{enumerate}}
#if ALL==1
\statement{  <div class="wims_score_bar"><div class="inline">
    \for{j=1 to \step-1}{
    <div class="inline wims_seed_item" style="background-color:blue" title="done"></div>
  }
  \for{j=\step to \cnt}{
    <div class="inline wims_seed_item" style="background-color:#FFF" title="todo"></div>
  }
</div></div>
<div class="wims_center">
\for{j=1 to \cnt}{
  \if{\step=\j}{
    <h2><label for="reply\choix[\j]">Question \j</label></h2>
    <div class="wims_question">
    \enonce[\choix[\j];]
#if defined TARGET_courseT11_2step 
     \if{\step=\rg4}{\enonce4}
#endif
#if defined TARGET_courseT11_2step
     \if{\step=\rg2}{\embed{reply 2,50x35x11}}
     \if{\step=\rg6}{\embed{reply 6,75x35x1}}
     \if{\step<>\rg2 and \step<>\rg6}{\embed{r\choix[\j],\size[\j;]
      autofocus}}
#endif
#if defined TARGET_courseT11_1step
\embed{r\choix[\j],\size[\j;]
      autofocus}
#endif  
    \enonceb[\choix[\j];]
#if defined TARGET_courseT11_2step
     \if{\step=\rg14}{\embed{reply 16,\size14} \enoncec14}
#endif   
    </div>}
  }
</div>
<div class="wims_instruction">\instruction</div>
}
#endif
%%%%%%%%%%%%%%
#if ALL==0
\statement{
<div class="wims_instruction">\instruction</div>
\for{j=1 to \cnt}{
  <h2><label for="reply\choix[\j]">Question \j:</label></h2>
  <div class="wims_question">
  \enonce[\choix[\j];]
#if defined TARGET_courseT11_2 
     \if{\j=\rg4}{\enonce4}
#endif
  \embed{r\choix[\j],\size[\j;]  } \enonceb[\choix[\j];]
#if defined TARGET_courseT11_2
   \if{\choix[\j]=14}{\embed{reply 16,\size14} \enoncec14}
#endif   
  
  </div>
}
}
#endif

#if defined TARGET_courseT11_1step || TARGET_courseT11_1
\answer{}{\rep1}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep2}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep3}{type=litexp}{option=\confparm2 default=0 weight=3}
\answer{}{\rep4}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep5}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep6}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep7}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep8}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep9}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep10}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep11}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep12}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep13}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep14}{type=formal}{option=\confparm2 comma default=0}
\answer{}{\rep15}{type=numeric}{option=\confparm2 comma default=0}
#endif
#if defined TARGET_courseT11_2step || TARGET_courseT11_2
\answer{}{\rep1}{type=fset}{option=\confparm2 comma default=0 weight=3}
#if defined TARGET_courseT11_2 
\answer{}{\goodrepT1117;\rep2}{type=mark}{option=\confparm2 default=0 weight=3}
#endif
#if defined TARGET_courseT11_2step
\answer{}{\rep2}{type=clickfill}{option=\confparm2 comma default=0 weight=3}
#endif
\answer{}{\rep3}{type=equations}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep4}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep5}{type=litexp}{option=\confparm2 polfactor default=0 weight=3}
#if defined TARGET_courseT11_2 
\answer{}{\rep6}{type=mark}{option=\confparm2 default=0 weight=2}
#endif
#if defined TARGET_courseT11_2step
\answer{}{\rep6}{type=clickfill}{option=\confparm2 comma default=0 weight=2}
#endif
\answer{}{\rep7}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep8}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep9}{type=fset}{option=\confparm2 default=0 weight=2}
\answer{}{\rep10}{type=nocase}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep11}{type=nocase}{option=\confparm2 comma default=0}
\answer{}{\rep12}{type=formal}{option=\confparm2 comma default=0}
\answer{}{\rep13}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep14}{type=nocase}{option=\confparm2 comma default=0}
\answer{}{\rep15}{type=formal}{option=\confparm2 comma default=0}
\answer{}{\repb14}{type=numeric}{option=\confparm2 comma default=0}
#endif

#if defined TARGET_courseT11_1step || defined TARGET_courseT11_2step
\text{screp=\sc_reply1,\sc_reply2,\sc_reply3,\sc_reply4,\sc_reply5,\sc_reply6,\sc_reply7,
\sc_reply8,\sc_reply9,\sc_reply10,\sc_reply11,\sc_reply12,\sc_reply13,\sc_reply14,\sc_reply15}
\feedback{1=1}{
  \for{t=1 to \cnt}{
    \if{\screp[\choix[\t]]!=\empty and \screp[\choix[\t]]<1 and \feed[\choix[\t];] !=}{
      <style>.feedmutu {
    border: 1px solid;
    border-radius: 5px;
    padding: .5em;}
</style>
      <div class="feedmutu">\feed[\choix[\t];]</div>
    }
  }
}

#endif

\latex{
\begin{statement}
\latexversion
\end{statement}
\begin{solution}
\end{solution}
}
