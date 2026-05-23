target = course06_1step course06_1 course06_2step course06_2

\author{Cyrille,Douriez}
\email{communaute.mutuwims@laposte.net}
\computeanswer{no}
\precision{1000000000}
%%%%%% option nonstop %%%%%%%%
\text{confparm2=items(\confparm2)=0 ? 1:\confparm2}
\text{confparm2=\confparm2=2?nonstop:}

#define KEYWORD1 skill_calculate,mental_calculation,multiplication,division,fraction,mental_calculation,proportionality,time,conversion,coordinates,addition,subtraction,divisibility,pbsolving,calculation,decimals,clock,
#define KEYWORD2 mental_calculation,pbsolving,multiplication,conversion,masse,length,numeration,geometry,fraction,coordinates,number_line,decimals,time,division,methodical_calculation,proportionality,area

#include "instruction_cycle4.inc"
\integer{taille=6}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#if defined TARGET_course06_1 || defined TARGET_course06_1step
# include "0601.inc"
\text{enonce1=\enonce}
\text{enonceb1=\enonceb}
\text{rep1=\rep}
\text{feedback1=\feedback}
\integer{taille1=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0602.inc"
\text{enonce2=\enonce}
\text{enonceb2=\enonceb}
\text{rep2=\rep}
\text{feedback2=\feedback}
\integer{taille2=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0603.inc"
\text{enonce3=\enonce}
\text{enonceb3=\enonceb}
\text{rep3=\rep}
\text{feedback3=\feedback}
\integer{taille3=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0604.inc"
\text{enonce4=\enonce}
\text{enonceb4=\enonceb}
\text{rep4=\rep}
\text{feedback4=\feedback}
\integer{taille4=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0605.inc"
\text{enonce5=\enonce}
\text{enonceb5=\enonceb}
\text{rep5=\rep}
\text{feedback5=\feedback}
\integer{taille5=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0606.inc"
\text{enonce6=\enonce}
\text{enonceb6=\enonceb}
\text{rep6=\rep}
\text{feedback6=\feedback}
\integer{taille6=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0607.inc"
\text{enonce7=\enonce}
\text{enonceb7=\enonceb}
\text{rep7=\rep}
\text{feedback7=\feedback}
\integer{taille7=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0608.inc"
\text{enonce8=\enonce}
\text{enonceb8=\enonceb}
\text{rep8=\rep}
\text{prop8=\prop}
\text{feedback8=\feedback}
\integer{taille8=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0609.inc"
\text{enonce9=\enonce}
\text{enonceb9=\enonceb}
\text{rep9=\rep}
\text{feedback9=\feedback}
\integer{taille9=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0610.inc"
\text{enonce10=\enonce}
\text{enonceb10=\enonceb}
\text{rep10=\rep}
\text{feedback10=\feedback}
\integer{taille10=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0611.inc"
\text{enonce11=\enonce}
\text{enonceb11=\enonceb}
\text{rep11=\rep}
\text{feedback11=\feedback}
\integer{taille11=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0612.inc"
\text{enonce12=\enonce}
\text{enonceb12=\enonceb}
\text{enoncec12=\enoncec}
\text{rep12=\rep}
\text{rep16=\repb}
\text{feedback12=\feedback}
\integer{taille12=4}
\integer{taille16=4}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0613.inc"
\text{enonce13=\enonce}
\text{enonceb13=\enonceb}
\text{rep13=\rep}
\text{feedback13=\feedback}
\integer{taille13=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0614.inc"
\text{enonce14=\enonce}
\text{enonceb14=\enonceb}
\text{enoncec14=\enoncec}
\text{rep14=\rep}
\text{rep17=\repb}
\text{feedback14=\feedback}
\integer{taille14=4}
\integer{taille17=4}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0615.inc"
\text{enonce15=\enonce}
\text{enonceb15=\enonceb}
\text{rep15=\rep}
\text{feedback15=\feedback}
\integer{taille15=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#endif
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#if defined TARGET_course06_2 || defined TARGET_course06_2step
# include "0616.inc"
\text{enonce1=\enonce}
\text{enonceb1=\enonceb}
\text{rep1=\rep}
\text{feedback1=\feedback}
\integer{taille1=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0617.inc"
\text{enonce2=\enonce}
\text{enonceb2=\enonceb}
\text{rep2=\rep}
\text{feedback2=\feedback}
\integer{taille2=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0618.inc"
\text{enonce3=\enonce}
\text{enonceb3=\enonceb}
\text{rep3=\rep}
\text{feedback3=\feedback}
\integer{taille3=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0619.inc"
\text{enonce4=\enonce}
\text{enonceb4=\enonceb}
\text{rep4=\rep}
\text{feedback4=\feedback}
\integer{taille4=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0620.inc"
\text{enonce5=\enonce}
\text{enonceb5=\enonceb}
\text{rep5=\rep}
\text{feedback5=\feedback}
\integer{taille5=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0621.inc"
\text{enonce6=\enonce}
\text{enonceb6=\enonceb}
\text{rep6=\rep}
\text{feedback6=\feedback}
\integer{taille6=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0622.inc"
\text{enonce7=\enonce}
\text{enonceb7=\enonceb}
\text{rep7=\rep}
\text{feedback7=\feedback}
\integer{taille7=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0623.inc"
\text{enonce8=\enonce}
\text{enonceb8=\enonceb}
\text{rep8=\rep}
\text{feedback8=\feedback}
\integer{taille8=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0624.inc"
\text{enonce9=\enonce}
\text{enonceb9=\enonceb}
\text{rep9=\rep}
\text{feedback9=\feedback}
\integer{taille9=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0625.inc"
\text{enonce10=\enonce}
\text{enonceb10=\enonceb}
\text{rep10=\rep}
\text{feedback10=\feedback}
\integer{taille10=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0626.inc"
\text{enonce11=\enonce}
\text{enonceb11=\enonceb}
\text{rep11=\rep}
\text{prop11=\prop}
\text{feedback11=\feedback}
\integer{taille11=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0627.inc"
\text{enonce12=\enonce}
\text{enonceb12=\enonceb}
\text{rep12=\rep}
\text{feedback12=\feedback}
\integer{taille12=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0628.inc"
\text{enonce13=\enonce}
\text{enonceb13=\enonceb}
\text{rep13=\rep}
\text{feedback13=\feedback}
\integer{taille13=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0629.inc"
\text{enonce14=\enonce}
\text{enonceb14=\enonceb}
\text{rep14=\rep}
\text{feedback14=\feedback}
\integer{taille14=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0630.inc"
\text{enonce15=\enonce}
\text{enonceb15=\enonceb}
\text{rep15=\rep}
\text{feedback15=\feedback}
\integer{taille15=\taille}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

#define TITLE Course aux nombres niveau

#if defined TARGET_course06_1step
\title{TITLE 06 part.1 (step)}
\observation{Questions 0601 à 0615. Course aux Nombres de mai 2022 (académie de Strasbourg) pour des élèves de 6ème. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD1}
#define ALL 1
#endif
#if defined TARGET_course06_1
\title{TITLE 06 part.1}
\observation{Questions 0601 à 0615. Course aux Nombres de mai 2022 (académie de Strasbourg) pour des élèves de 6ème. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD1}
#define ALL 0
#endif

#if defined TARGET_course06_2step
\title{TITLE 06 part.2 (step)}
\observation{Questions 0616 à 0630. Course aux Nombres de mai 2022 (académie de Strasbourg) pour des élèves de 6ème. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD2}
#define ALL 1
#endif
#if defined TARGET_course06_2
\title{TITLE 06 part.2}
\observation{Questions 0616 à 0630. Course aux Nombres de mai 2022 (académie de Strasbourg) pour des élèves de 6ème. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD2}
#define ALL 0
#endif
\text{choix=\confparm1= ? wims(makelist x for x=1 to 15): \confparm1}
\integer{cnt=items(\choix)}

\matrix{STEP=wims(makelist reply x for x in \choix)}
#if ALL==1
\matrix{STEP=wims(replace internal , by ; in \STEP)}
#endif

#if defined TARGET_course06_1 || defined TARGET_course06_1step
%%%%%% Questions 0612 et 0614 avec deux champs de réponse.
\matrix{STEP=wims(replace item reply 12 by reply 12,reply 16 in \STEP)}
\integer{rg12=position(12,\choix)}
\matrix{STEP=wims(replace item reply 14 by reply 14,reply 17 in \STEP)}
\integer{rg14=position(14,\choix)}
%%%%%% Question 0608 sans taille de réponse (checkbox)
\integer{rg8=position(8,\choix)}
\steps{\STEP}
#endif
#if defined TARGET_course06_2 || defined TARGET_course06_2step
\steps{\STEP}
%%%%%% Question 0626 sans taille de réponse (mark)
\integer{rg11=position(11,\choix)}
#endif

*****
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
\matrix{taille=\taille1
\taille2
\taille3
\taille4
\taille5
\taille6
\taille7
\taille8
\taille9
\taille10
\taille11
\taille12
\taille13
\taille14
\taille15
}
\text{feed=\feedback1;\feedback2;\feedback3;\feedback4;\feedback5;\feedback6;\feedback7;\feedback8;\feedback9;\feedback10;\feedback11;\feedback12;\feedback13;\feedback14;\feedback15}

\text{latexversion=\begin{enumerate}}
\for{h=1 to \cnt}{
# if defined TARGET_course06_1 || defined TARGET_course06_1step
%% exclure dessins et tableaux
  \if{\choix[\h] notitemof 6}{
#endif
# if defined TARGET_course06_2 || defined TARGET_course06_2step
  \if{\choix[\h] notitemof 5,9,15}{
#endif
    \text{latexversion=\latexversion
    \choix[\h]
    \item
    \enonce[\choix[\h];]
    \dots \enonceb[\choix[\h];]
  }
# if defined TARGET_course06_1 || defined TARGET_course06_1step
\if{\choix[\h]==12}{\text{latexversion=\latexversion
    \item
    \enonce12 \dots \enonceb12 \dots \enoncec12
   }}
 \if{\choix[\h]==14}{\text{latexversion=\latexversion
    \item
    \enonce14 \dots \enonceb14 \dots \enoncec14
   }}
 } {} 
#endif
# if defined TARGET_course06_2 || defined TARGET_course06_2step
}{}
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
#if defined TARGET_course06_1step 
     \if{\step=\rg8}{\embed{reply 8}}{\embed{r\choix[\j],\taille[\j;]
      autofocus  } \enonceb[\choix[\j];]}
     \if{\step=\rg12}{\embed{reply 16,\taille16} \enoncec12}
     \if{\step=\rg14}{\embed{reply 17,\taille17} \enoncec14}
     
    
#endif
#if defined TARGET_course06_2step
\if{\step=\rg11}{\embed{reply 11}}{\embed{r\choix[\j],\taille[\j;]
      autofocus} \enonceb[\choix[\j];]}
#endif  
   
    </div>}
  }
</div>
<div class="wims_instruction">\instruction</div>
}
#endif
%%%%%%%%%%%%%%
#if ALL==0
\statement{<div class="wims_instruction">\instruction</div>
\for{j=1 to \cnt}{
  <h2><label for="reply\choix[\j]">Question \j:</label></h2>
  <div class="wims_question">
  \enonce[\choix[\j];]
#if defined TARGET_course06_1 
     \if{\j=\rg8}{
       \embed{reply 8} \enonceb8
       }{
       \embed{r\choix[\j],\taille[\j;] } 
       \enonceb[\choix[\j];]
       }
     \if{\j=\rg12}{\embed{reply 16,\taille16} \enoncec12}
     \if{\j=\rg14}{\embed{reply 17,\taille17} \enoncec14}
     
    
#endif
#if defined TARGET_course06_2 
  \if{\j=\rg11}{\embed{reply 11} \enonceb11}{\embed{r\choix[\j],\taille[\j;]  } \enonceb[\choix[\j];]}
#endif  
  
  </div>
}
}
#endif

#if defined TARGET_course06_1step || TARGET_course06_1
\answer{}{\rep1}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep2}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep3}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep4}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep5}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep6}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep7}{type=numeric}{option=\confparm2 default=0 weight=2}
\answer{}{\rep8;\prop8}{type=checkbox}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep9}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep10}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep11}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep12}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep13}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep14}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep15}{type=numeric}{option=\confparm2 comma default=0}

\answer{}{\rep16}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep17}{type=numeric}{option=\confparm2 comma default=0}

#endif
#if defined TARGET_course06_2step || TARGET_course06_2
\answer{}{\rep1}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep2}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep3}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep4}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep5}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep6}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep7}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep8}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep9}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep10}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep11;\prop11}{type=mark}{option=\confparm2 comma default=0}
\answer{}{\rep12}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep13}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep14}{type=numeric}{option=\confparm2 default=0}
\answer{}{\rep15}{type=numeric}{option=\confparm2 comma default=0}
#endif

#if defined TARGET_course06_1step || defined TARGET_course06_2step
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
