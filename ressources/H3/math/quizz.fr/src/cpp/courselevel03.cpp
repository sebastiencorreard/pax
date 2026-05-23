target = course03_1step course03_1 course03_2step course03_2
\author{Bruno,Mifsud}
\email{communaute.mutuwims@laposte.net}
%%%%%%%%% cas où une question >10 est sélectionnée %%%%%%%%%%%%%%%%%%%
\integer{cnt0=items(\confparm1)}
\if{\confparm1[\cnt0]>10}{\text{alert=<b>Attention, vous avez coché une question qui n'existe pas. Toutes les questions sont alors dans l'exercice.</b>}}
\observation{\alert Il n'y a que 10 questions sur le niveau 3. Plus de configuration sur le module d'exercice}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\computeanswer{no}
\precision{1000000000}
%%%%%% option nonstop %%%%%%%%
\text{confparm2=items(\confparm2)=0 ? 1:\confparm2}
\text{confparm2=\confparm2=2?nonstop:}

#include "instruction_primaire.inc"

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#if defined TARGET_course03_1 || defined TARGET_course03_1step
# include "0301.inc"
\text{enonce1=\enonce}
\text{enonceb1=\enonceb}
\text{rep1=\rep}
\text{feedback1=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0302.inc"
\text{enonce2=\enonce}
\text{enonceb2=\enonceb}
\text{rep2=\rep}
\text{feedback2=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0303.inc"
\text{enonce3=\enonce}
\text{enonceb3=\enonceb}
\text{rep3=\rep}
\text{feedback3=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0304.inc"
\text{enonce4=\enonce}
\text{enonceb4=\enonceb}
\text{rep4=\rep}
\text{feedback4=\feedback}
\integer{bad0304=(\rep+1)%3}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0305.inc"
\text{enonce5=\enonce}
\text{enonceb5=\enonceb}
\text{rep5=\rep}
\text{feedback5=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0306.inc"
\text{enonce6=\enonce}
\text{enonceb6=\enonceb}
\text{rep6=\rep}
\text{feedback6=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0307.inc"
\text{enonce7=\enonce}
\text{enonceb7=\enonceb}
\text{rep7=\rep}
\text{feedback7=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0308.inc"
\text{enonce8=\enonce}
\text{enonceb8=\enonceb}
\text{rep8=\rep}
\text{feedback8=\feedback}
\text{bad10308=\bad1}
\text{bad20308=\bad2}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0309.inc"
\text{enonce9=\enonce}
\text{enonceb9=\enonceb}
\text{rep9=\rep}
\text{feedback9=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0310.inc"
\text{enonce10=\enonce}
\text{enonceb10=\enonceb}
\text{rep10=\rep}
\text{feedback10=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#endif
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#if defined TARGET_course03_2 || defined TARGET_course03_2step
# include "0311.inc"
\text{enonce1=\enonce}
\text{enonceb1=\enonceb}
\text{rep1=\rep}
\text{feedback1=\feedback}
\text{bads1=\bads}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0312.inc"
\text{enonce2=\enonce}
\text{enonceb2=\enonceb}
\text{rep2=\rep}
\text{feedback2=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0313.inc"
\text{enonce3=\enonce}
\text{enonceb3=\enonceb}
\text{rep3=\rep}
\text{feedback3=\feedback}
\text{bads3=\bad1,\bad2}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0314.inc"
\text{enonce4=\enonce}
\text{enonceb4=\enonceb}
\text{rep4=\rep}
\text{feedback4=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0315.inc"
\text{enonce5=\enonce}
\text{enonceb5=\enonceb}
\text{rep5=\rep}
\text{feedback5=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0316.inc"
\text{enonce6=\enonce}
\text{enonceb6=\enonceb}
\text{rep6=\rep}
\text{feedback6=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0317.inc"
\text{enonce7=\enonce}
\text{enonceb7=\enonceb}
\text{rep7=\rep}
\text{feedback7=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0318.inc"
\text{enonce8=\enonce}
\text{enonceb8=\enonceb}
\text{rep8=\rep}
\text{feedback8=\feedback}
\text{bad10308=\bad1}
\text{bad20308=\bad2}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0319.inc"
\text{enonce9=\enonce}
\text{enonceb9=\enonceb}
\text{rep9=\rep}
\text{feedback9=\feedback}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# include "0320.inc"
\text{enonce10=\enonce}
\text{enonceb10=\enonceb}
\text{rep10=\rep}
\text{feedback10=\feedback}
\integer{bad10310=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#endif


#define TITLE Course aux nombres niveau
#define KEYWORD1 mental_calculation,decimals,percents,skill_calculate,area,conversion,fraction,proportionality,mental_calculation,methodical_calculation
#define KEYWORD2 skill_calculate,mental_calculation,clock,multiplication,time,addition,methodical_calculation,decimals,division,length,integers,order
#if defined TARGET_course03_1step
\title{TITLE 03 part.1 (step)}
\observation{Questions 0301 à 0310. Course aux Nombres de mai 2022 (académie de Strasbourg) pour des élèves de CE2. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD1}
#define ALL 1
#endif
#if defined TARGET_course03_1
\title{TITLE 03 part.1}
\observation{Questions 0301 à 0310. Course aux Nombres de mai 2022 (académie de Strasbourg) pour des élèves de CE2. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD1}
#define ALL 0
#endif

#if defined TARGET_course03_2step
\title{TITLE 03 part.2 (step)}
\observation{Questions 0311 à 0320. Course aux Nombres de mai 2022 (académie de Strasbourg) pour des élèves de CE2. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD2}
#define ALL 1
#endif
#if defined TARGET_course03_2
\title{TITLE 03 part.2}
\observation{Questions 0311 à 0320. Course aux Nombres de mai 2022 (académie de Strasbourg) pour des élèves de CE2. <br>A partir du module, vous pouvez modifier cette Course pour ne prendre que certaines questions.}
\keywords{KEYWORD2}
#define ALL 0
#endif

%%%% test si un item >10 est coché on met toutes les questions%%%%
\integer{cnt0=items(\confparm1)}
\if{\confparm1[\cnt0]>10}{\text{confparm1=wims(makelist x for x=1 to 10)}}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\text{choix=\confparm1= ? wims(makelist x for x=1 to 10): \confparm1}
\integer{cnt=items(\choix)}





\matrix{STEP=wims(makelist reply x for x in \choix)}
#if ALL==1
\matrix{STEP=wims(replace internal , by ; in \STEP)}
#endif
\steps{\STEP}
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
\enonce10}
\text{enonceb=\enonceb1;
\enonceb2;
\enonceb3;
\enonceb4;
\enonceb5;
\enonceb6;
\enonceb7;
\enonceb8;
\enonceb9;
\enonceb10}
\text{feed=\feedback1;\feedback2;\feedback3;\feedback4;\feedback5;\feedback6;\feedback7;
\feedback8;\feedback9;\feedback10}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%% latex version %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\text{latexversion=\begin{enumerate}}

\for{h=1 to \cnt}{
# if defined TARGET_course03_1
%% exclure les images et  anstype=radio ou menu ou chekbox
  \if{\choix[\h] notitemof 2,4,8}{
#endif
# if defined TARGET_course03_2
%% Exclure les questions avec les figures et  anstype=radio ou menu ou chekbox
  \if{\choix[\h] notitemof 1,3,10}{
#endif


    \text{latexversion=\latexversion
    \item
    \enonce[\choix[\h];]
    \dots \enonceb[\choix[\h];]
  }
# if defined TARGET_course03_1
}{%%% question 8 : menu anstype 1
\if{\choix[\h]==8}{\text{latexversion=\latexversion
    \item
    \enonce[\choix[\h];]
    \begin{radio}
    \item \rep8
    \item \bad10308
    \item \bad20308
    \end{radio}}}
    }
#endif 
# if defined TARGET_course03_2
}{%%% question 3 : menu anstype 1
\if{\choix[\h]==3}{\text{latexversion=\latexversion
    \item
    \enonce[\choix[\h];]
    \begin{radio}
    \item \rep3
    \item \bads3[1]
    \item \bads3[2]
    \end{radio}}}
}
#endif
}

\text{latexversion=\latexversion \end{enumerate}}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%% fin latex version %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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
    \enonce[\choix[\j];]
    \embed{r\choix[\j],10
      autofocus}
    \enonceb[\choix[\j];]
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
  \embed{r\choix[\j],10} \enonceb[\choix[\j];]</div>
}
}
#endif

#if defined TARGET_course03_1step || defined TARGET_course03_1
\text{list_cond=6 isitemof \choix?1,2:}
#if defined TARGET_course03_1step
\integer{affstep6=position(6,\choix)}
\text{list_cond=\step>\affstep6?\list_cond:}
#endif
\text{mot1=wims(text expand \reponse using 01)}
\text{mot1=wims(words2items \mot1)}
\text{reponse2=wims(words2items \mot1)}
\text{cntreponse=items(\reponse2)}
\integer{somme1=0}
\for{l=1 to \cntreponse}{
\integer{somme1=\somme1+\reponse2[\l]}}
\integer{somme0=\cntreponse*\chiffre}
\conditions{\list_cond} 
%%%%% fin affichage
\answer{}{\rep1}{type=numeric}{option=\confparm2 default=0 weight=3}
\answer{}{\rep2}{type=numeric}{option=\confparm2 default=0 weight=3}
\answer{}{\rep3}{type=numeric}{option=\confparm2 default=0 weight=3}
\answer{}{\rep4;Figure 1,Figure 2,Figure 3}{type=menu}{option=\confparm2 default=\bad0304 weight=3}
\answer{}{\rep5}{type=numeric}{option=\confparm2 default=0 weight=2}
\answer{}{\reponse}{type=numeric}{option=\confparm2 weight=2}
\answer{}{\rep7}{type=numeric}{option=\confparm2 default=0 weight=1}
\answer{}{1;\rep8,\bad10308,\bad20308}{type=menu}{option=\confparm2 shuffle default=\bad10308 weight=1}
\answer{}{\rep9}{type=numeric}{option=\confparm2 default=0 weight=1}
\answer{}{\rep10}{type=numeric}{option=\confparm2 comma default=0 weight=1}
%%% afficher ce qui suit que si 6 est dans confparm1
\condition{Le nombre est plus grand que 999 ?}{\reponse > 999}
\condition{Le nombre s'écrit qu'avec des \chiffre ?}{\somme0 issametext \somme1}
%%%%% fin affichage
#endif
#if defined TARGET_course03_2step || defined TARGET_course03_2
\text{list_cond=5 isitemof \choix?1,2:}
#if defined TARGET_course03_2step
\integer{affstep5=position(5,\choix)}
\text{list_cond=\step>\affstep5?\list_cond:}
#endif

%%%%%% condition pour question5
\text{mot1=wims(text expand \reponse5 using 01)}
\text{mot1=wims(words2items \mot1)}
\text{reponse2=wims(words2items \mot1)}
\text{cntreponse=items(\reponse2)}
\integer{nbcentaine=\cntreponse<3?0:\reponse2[\cntreponse-2]} 
%%% cas où le chiffre des centaines est nul, mais celui des centaines de millier non
\if{\nbcentaine==0}{\integer{nbcentaine=\cntreponse<6?0:\reponse2[\cntreponse-5]}}
%%%%% traiter les cas où on entend et le chiffre des milliers aussi
\integer{nbmillier=\cntreponse<4?0:\reponse2[\cntreponse-3]\reponse2[\cntreponse-4]\reponse2[\cntreponse-5]}
\conditions{\list_cond} 
%%%%%%%%%%%% fin condition pour question 5
\answer{}{1;\rep1,\bads1}{type=menu}{option=\confparm2 shuffle default=\bads1[1] weight=3}
\answer{}{\rep2}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{1;\rep3,\bads3}{type=menu}{option=\confparm2 shuffle default=\bads3[1] weight=3}
\answer{}{\rep4}{type=numeric}{option=\confparm2 comma default=0 weight=3}
\answer{}{\reponse5}{type=numeric}{option=\confparm2 default=0 weight=2}
\answer{}{\rep6}{type=numeric}{option=\confparm2 comma default=0 weight=2}
\answer{}{\rep7}{type=numeric}{option=\confparm2 comma default=0 weight=1}
\answer{}{\rep8}{type=numeric}{option=\confparm2 comma default=0 weight=1}
\answer{}{\rep9}{type=numeric}{option=\confparm2 comma default=0 weight=1}
\answer{}{\rep10;Figure 1,Figure 2, Figure 3}{type=menu}{option=\confparm2 default=\bad10320 weight=1}
\condition{Dans \reponse5 on entend "cent" ?}{\nbcentaine!=0}
\condition{Dans \reponse5 on entend "mille" ?}{\nbmillier!=0}
#endif



#if defined TARGET_course03_1step || defined TARGET_course03_2step 
\text{screp=\sc_reply1,\sc_reply2,\sc_reply3,\sc_reply4,\sc_reply5,\sc_reply6,\sc_reply7,
\sc_reply8,\sc_reply9,\sc_reply10}
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
