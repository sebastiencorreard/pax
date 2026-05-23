target = course05_1step course05_1 course05_2step course05_2

\author{Bruno,Mifsud}
\email{communaute.mutuwims@laposte.net}
\computeanswer{no}
\precision{1000000000}
%%%%%% option nonstop %%%%%%%%
\text{confparm2=items(\confparm2)=0 ? 1:\confparm2}
\text{confparm2=\confparm2=2?nonstop:}

#define KEYWORD1 mental_calculation,division,fraction,subtraction,equations,proportionality,conversion,time,coordinates,pbsolving,divisibility,calculation,multiplication,decimals,rational_number,number_writing,addition
#define KEYWORD2  mental_calculation,multiplication,conversion,volume,number_writing,lines,coordinates,number_line,decimals,addition,pbsolving,masse,length,time,division,methodical_calculation,proportionality,geometry,area

#include "instruction_cycle4.inc"

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#if defined TARGET_course05_1 || defined TARGET_course05_1step
# include "0501.inc"
\text{enonce1=\enonce}
\text{enonceb1=\enonceb}
\text{rep1=\rep}
\text{feedback1=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0502.inc"
\text{enonce2=\enonce}
\text{enonceb2=\enonceb}
\text{rep2=\rep}
\text{feedback2=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0503.inc"
\text{enonce3=\enonce}
\text{enonceb3=\enonceb}
\text{rep3=\rep}
\text{feedback3=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0504.inc"
\text{enonce4=\enonce}
\text{enonceb4=\enonceb}
\text{rep4=\rep}
\text{feedback4=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0505.inc"
\text{enonce5=\enonce}
\text{enonceb5=\enonceb}
\text{rep5=\rep}
\text{feedback5=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0506.inc"
\text{enonce6=\enonce}
\text{enonceb6=\enonceb}
\text{rep6=\rep}
\text{feedback6=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0507.inc"
\text{enonce7=\enonce}
\text{enonceb7=\enonceb}
\text{rep7=\rep}
\text{feedback7=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0508.inc"
\text{enonce8=\enonce}
\text{enonceb8=\enonceb}
\text{rep8=\rep}
\text{feedback8=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0509.inc"
\text{enonce9=\enonce}
\text{enonceb9=\enonceb}
\text{rep9=\rep}
\text{feedback9=\feedback}
\text{bad09091=\bad1}
\text{bad09092=\bad2}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0510.inc"
\text{enonce10=\enonce}
\text{enonceb10=\enonceb}
\text{rep10=\rep}
\text{feedback10=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0511.inc"
\text{enonce11=\enonce}
\text{enonceb11=\enonceb}
\text{rep11=\rep}
\text{feedback11=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0512.inc"
\text{enonce12=\enonce}
\text{enonceb12=\enonceb}
\text{rep12=\rep}
\text{feedback12=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0513.inc"
\text{enonce13=\enonce}
\text{enonceb13=\enonceb}
\text{rep13=\rep}
\text{feedback13=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0514.inc"
\text{enonce14=\enonce}
\text{enonceb14=\enonceb}
\text{rep14=\rep}
\text{rep17=\repb}
\text{feedback14=\feedback}
\text{enonce0514c=\enoncec}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0515.inc"
\text{enonce15=\enonce}
\text{enonceb15=\enonceb}
\text{rep15=\rep}
\text{feedback15=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#endif
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#if defined TARGET_course05_2 || defined TARGET_course05_2step
# include "0516.inc"
\text{enonce1=\enonce}
\text{enonceb1=\enonceb}
\text{rep1=\rep}
\text{feedback16=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0517.inc"
\text{enonce2=\enonce}
\text{enonceb2=\enonceb}
\text{rep2=\rep}
\text{feedback2=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0518.inc"
\text{enonce3=\enonce}
\text{enonceb3=\enonceb}
\text{rep3=\rep}
\text{feedback3=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0519.inc"
\text{enonce4=\enonce}
\text{enonceb4=\enonceb}
\text{rep4=\rep}
\text{feedback4=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0520.inc"
\text{enonce5=\enonce}
\text{enonceb5=\enonceb}
\text{rep5=\rep}
\text{feedback5=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0521.inc"
\text{enonce6=\enonce}
\text{enonceb6=\enonceb}
\text{rep6=\rep}
\text{feedback6=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0522.inc"
\text{enonce7=\enonce}
\text{enonceb7=\enonceb}
\text{rep7=\rep}
\text{feedback7=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0523.inc"
\text{enonce8=\enonce}
\text{enonceb8=\enonceb}
\text{rep8=\rep}
\text{feedback8=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0524.inc"
\text{enonce9=\enonce}
\text{enonceb9=\enonceb}
\text{rep9=\rep}
\text{feedback9=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0525.inc"
\text{enonce10=\enonce}
\text{enonceb10=\enonceb}
\text{rep10=\rep}
\text{feedback10=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0526.inc"
\text{enonce11=\enonce}
\text{enonceb11=\enonceb}
\text{rep11=\rep}
\text{feedback11=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0527.inc"
\text{enonce12=\enonce}
\text{enonceb12=\enonceb}
\text{rep12=\rep}
\text{feedback12=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0528.inc"
\text{enonce13=\enonce}
\text{enonceb13=\enonceb}
\text{rep13=\rep}
\text{feedback13=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0529.inc"
\text{enonce14=\enonce}
\text{enonceb14=\enonceb}
\text{rep14=\rep}
\text{feedback14=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0530.inc"
\text{enonce15=\enonce}
\text{enonceb15=\enonceb}
\text{rep15=\rep}
\text{feedback15=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

#define TITLE Course aux nombres niveau

#if defined TARGET_course05_1step
\title{TITLE 05 part.1 (step)}
\observation{Questions 0501 à 0515. Course aux Nombres de mai 2022 (académie de Strasbourg) pour des élèves de CM2. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD1}
#define ALL 1
#endif
#if defined TARGET_course05_1
\title{TITLE 05 part.1}
\observation{Questions 0501 à 0515. Course aux Nombres de mai 2022 (académie de Strasbourg) pour des élèves de CM2. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD1}
#define ALL 0
#endif

#if defined TARGET_course05_2step
\title{TITLE 05 part.2 (step)}
\observation{Questions 0516 à 0530. Course aux Nombres de mai 2022 (académie de Strasbourg) pour des élèves de CM2. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD2}
#define ALL 1
#endif
#if defined TARGET_course05_2
\title{TITLE 05 part.2}
\observation{Questions 0516 à 0530. Course aux Nombres de mai 2022 (académie de Strasbourg) pour des élèves de CM2. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD2}
#define ALL 0
#endif
\text{choix=\confparm1= ? wims(makelist x for x=1 to 15): \confparm1}
\integer{cnt=items(\choix)}

\matrix{STEP=wims(makelist reply x for x in \choix)}
#if ALL==1
\matrix{STEP=wims(replace internal , by ; in \STEP)}
#endif

#if defined TARGET_course05_1 || defined TARGET_course05_1step
%%%%%% Questions 0512 avec deux champs de réponse.
\matrix{STEP=wims(replace item reply 12 by reply 12,reply 16 in \STEP)}
\integer{rg12=position(12,\choix)}
%%%%%% Questions 0514 avec deux champs de réponse.
\matrix{STEP=wims(replace item reply 14 by reply 14,reply 17 in \STEP)}
\integer{rg14=position(14,\choix)}

\steps{\STEP}
#endif
#if defined TARGET_course05_2 || defined TARGET_course05_2step
%%%% question 0520 tracé figure
\integer{rg5=position(5,\choix)}
\steps{\STEP}
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
\text{feed=\feedback1;\feedback2;\feedback3;\feedback4;\feedback5;\feedback6;\feedback7;
\feedback8;\feedback9;\feedback10;\feedback11;\feedback12;\feedback13;\feedback14;\feedback15}

\text{latexversion=\begin{enumerate}}
\for{h=1 to \cnt}{
# if defined TARGET_course05_1 || defined TARGET_course05_1step
%% afficher les choix de anstype=radio
  \if{\choix[\h] notitemof 6,8}{
#endif
# if defined TARGET_course05_2 || defined TARGET_course05_2step
%% il faudrait faire les figures ou le tableau ...
  \if{\choix[\h] notitemof 5,9,11,15}{
#endif
    \text{latexversion=\latexversion
    \item
    \enonce[\choix[\h];]
    \dots \enonceb[\choix[\h];]
  }
# if defined TARGET_course05_1 || defined TARGET_course05_1step
}{\if{\choix[\h]==8}{\text{latexversion=\latexversion
    \item
    \enonce[\choix[\h];]
    \begin{radio}
    \item \prop[1]
    \item \prop[2]
    \item \prop[3]
    \item \prop[4]    
    \end{radio}}}
    }
#endif
# if defined TARGET_course05_2 || defined TARGET_course05_2step
{\if{\choix[\h]==11}{\text{latexversion=\latexversion
    \item
    \enonce[\choix[\h];]
    \begin{radio}
    \item \prop[1]
    \item \prop[2]
    \item \prop[3]    
    \end{radio}}}
   }
}
#endif
}

\text{latexversion=\latexversion \end{enumerate}}

#if ALL==1
\statement{ 
  <div class="wims_score_bar"><div class="inline">
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
#if defined TARGET_course05_1step
        \enonce[\choix[\j];]
        \embed{r\choix[\j],10
      autofocus  }
        \enonceb[\choix[\j];]
      \if{\step=\rg12}{ et \embed{reply 16,10} }
      \if{\step=\rg14}{\embed{reply 17,10} \enonce0514c}
#endif
#if defined TARGET_course05_2step
       \if{\step=\rg5}{\enonce[\choix[\j];]
                      \embed{reply 5,400x200 
                      id1 brd [responsive center min=250px max=400px scroll]
                      \jsxscript}}
                     {\enonce[\choix[\j];]
                      \embed{r\choix[\j],10
      autofocus  }
                      \enonceb[\choix[\j];]}
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
#if defined TARGET_course05_1 
  \enonce[\choix[\j];]
  \embed{r\choix[\j],10} \enonceb[\choix[\j];]
  \if{\j=\rg12}{et \embed{reply 16,10} } 
  \if{\j=\rg14}{\embed{reply 17,10} \enonce0514c} 
#endif  
#if defined TARGET_course05_2
       \if{\j=\rg5}{\enonce[\choix[\j];]
                      \embed{reply 5,400x200 
                      id1 brd [responsive center min=250px max=400px scroll]
                      \jsxscript}}
                     {\enonce[\choix[\j];]
                      \embed{r\choix[\j],10  }
                      \enonceb[\choix[\j];]}
#endif
  
  </div>
}
}
#endif


#if defined TARGET_course05_1step || TARGET_course05_1
\text{list_cond=12 isitemof \choix?1:}
#if defined TARGET_course05_1step
\integer{affstep12=position(12,\choix)}
\text{list_cond=\step>\affstep12?\list_cond:}
#endif
\conditions{\list_cond} 
\answer{}{\rep1}{type=numeric}{option=\confparm2 default=0 weight=3}
\answer{}{\rep2}{type=numeric}{option=\confparm2 default=0 weight=3}
\answer{}{\rep3}{type=algexp}{option=\confparm2 default=0 weight=3}
\answer{}{\rep4}{type=numeric}{option=\confparm2 default=0 weight=3}
\answer{}{\rep5}{type=numeric}{option=\confparm2 default=0 weight=3}
\answer{}{\rep6}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep7}{type=numeric}{option=\confparm2 default=0 weight=2}
\answer{}{\rep8;\prop}{type=checkbox}{option=\confparm2 default=\prop[1] weight=2}
\answer{}{\rep9}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep10}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep11}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\reponse1}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep13}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep14}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep15}{type=numeric}{option=\confparm2 comma default=0}
%%%%%%%% condition pour 0512
\answer{}{\reponse2}{type=numeric}{option=\confparm2 comma default=0}
%%%% question 0514
\answer{}{\rep17}{type=numeric}{option=\confparm2 comma default=0}

\condition{Bonnes réponses ?}{(\reponse1=\a0512/\b0512) and (\reponse2=\a0512/\b0512) and (\reponse1 notsametext \a0512/\b0512) and (\reponse2 notsametext \a0512/\b0512) and (\reponse1 notsametext \reponse2)}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#endif
#if defined TARGET_course05_2step || TARGET_course05_2
\answer{}{\rep1}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep2}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep3}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\rep4}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{Construction}{\sol0420}{type=jsxgraph}{option=noanalyzeprint default=0 weight=3}
\answer{}{\rep6}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep7}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep8}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep9}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep10}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep11;\prop}{type=mark}{option=\confparm2 default=\prop[1] weight=2}
\answer{}{\rep12}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep13}{type=numeric}{option=\confparm2 comma default=0}
\answer{}{\rep14}{type=numeric}{option=\confparm2 default=0}
\answer{}{\rep15}{type=numeric}{option=\confparm2 comma default=0}
#endif

#if defined TARGET_course05_1step || defined TARGET_course05_2step
\text{screp=\sc_reply1,\sc_reply2,\sc_reply3,\sc_reply4,\sc_reply5,\sc_reply6,\sc_reply7,
\sc_reply8,\sc_reply9,\sc_reply10,\sc_reply11,\sc_reply12,\sc_reply13,\sc_reply14,\sc_reply15}
\feedback{1=1}{
  \for{t=1 to \cnt}{
    \if{\screp[\choix[\t]]!=\empty and \screp[\choix[\t]]<1 and \feed[\choix[\t];] !=}{
      <div class="feedback">\feed[\choix[\t];]</div>
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
