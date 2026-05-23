target=oefvocabulaire1
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}

%Paramètres de l'exercice%

%Programmation%

\text{liste1=shuffle(9)}
\integer{nb1=\liste1[1]\liste1[2]}

\integer{nb2=\liste1[1]}
\integer{nb3=\liste1[2]}
\integer{nb4=randint(10..99)}
\integer{nb5=randint(10..99)}
\integer{rep1=\nb4+\nb5}
\integer{nb6=randint(50..99)}
\integer{nb7=randint(1..49)}
\integer{rep2=\nb6-\nb7}
\text{mot2=\name_mot[2]}
\text{mot1=\name_mot[1]}
\text{mot3=\name_mot[3]}
\text{mot4=\name_mot[4]}
\text{mot5=\name_mot[5]}
\text{mot6=\name_mot[6]}

%Présentation de la page%

\statement{
\name_stat :
<ul><li>
\name_quest1[1] \embed{r1,10} \nb1 \name_quest1[2] \embed{r2,10} \nb2 \name_quest1[3] \nb3.
</li><li>
\nb4+\nb5 \name_quest2[1] \embed{r3,10} \name_quest2[2] \embed{r4,10} \nb4 \name_quest2[3] \nb5.
\name_quest2[4] \embed{r5,10} \name_quest2[5] \nb4 \name_quest2[6] \nb5.
\name_quest2[7] \embed{r6,10} \name_quest2[8] \embed{r7,5}.
</li><li>
\nb6-\nb7 \name_quest3[1] \embed{r8,10} \name_quest3[2] \embed{r9,5} \name_quest3[3] \nb7.
\name_quest3[4] \embed{r10,10} \name_quest3[5] \nb6 \name_quest3[6] \nb7.
\name_quest3[7] \embed{r11,10} \name_quest3[8] \embed{r12,5}.
</li></ul>
}

%Analyse de la réponse de l'élève%

\answer{}{\mot1}{type=case nocase}
\answer{}{\mot2}{type=case nocase}
\answer{}{\mot3}{type=case nocase}
\answer{}{\mot4}{type=case nocase}
\answer{}{\mot6}{type=case nocase}
\answer{}{\mot3}{type=case nocase}
\answer{}{\rep1}{type=numeric}
\answer{}{\mot5}{type=case nocase}
\answer{}{\nb6}{type=numeric}
\answer{}{\mot6}{type=case nocase}
\answer{}{\mot5}{type=case nocase}
\answer{}{\rep2}{type=numeric}
