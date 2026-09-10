target=oefprobprop1 oefprobprop2 oefprobprop3 oefprobprop4 oefprobprop5
#include "author.inc"

\range{-5..5}
\precision{10000}
\keywords{proportionality}
#if defined TARGET_oefprobprop1
# define NUM 1
#endif
#if defined TARGET_oefprobprop2
# define NUM 2
#endif
#if defined TARGET_oefprobprop3
# define NUM 3
#endif
#if defined TARGET_oefprobprop4
# define NUM 4
#endif
#if defined TARGET_oefprobprop5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"

\integer{a=randint(1..10)}
\text{t=row(\a,\name_t)}
\if{\a=7}{\real{d=100}}{\real{d=1}}
\if{\a=3}{\real{d=3}}
#if defined TARGET_oefprobprop1 || defined TARGET_oefprobprop2 || defined TARGET_oefprobprop3
\real{v1=randint(\t[13]..\t[14])*\t[15]}
\real{v2=randint(\t[16]..\t[17])*\t[18]}
\real{rep=\v1*\v2/\d}
#endif
#if defined TARGET_oefprobprop1
\statement{\name_instruction.
<div class="wims_question">
\if{\t[2]=}{\t[1] \v1 \t[6].}{\t[1] \v1 \t[6] \t[2].}
</div>
<p>\t[3] \v2 \t[5] \t[4]?</p>
<table class="wimscenter wimsborder">
<tr><th>\t[10]</th><td>\d</td><td>\v2</td></tr>
<tr><th>\t[7]</th><td>\v1</td><td> ? </td></tr>
</table>
<div class="spacer"><label for="reply1">\name_reponse:</label> \embed{r1,4} \t[6]</div>
}
\answer{}{\rep}{type=numeric}
\latex{
\begin{statement}
\name_instruction : \t[1] \v1 \t[6]. \t[3] \v2 \t[5] \t[4]?\par
  \begin{center}
    \begin{tabular}{|l|c|c|}
      \hline
      \t[10] & \d & \v2 \\ \hline
      \t[7] & \v1 & \ldots \\ \hline
    \end{tabular}
  \end{center}
  Réponse en \t[6] : \dotfill
\end{statement}

\begin{solution}
  \name_easy \rep \t[6].
\end{solution}
}
#endif
#if defined TARGET_oefprobprop2
\statement{\name_instruction.
<div class="wims_question">
<p>\if{\t[2]=}{\t[1] \v1 \t[6].}{\t[1] \v1 \t[6] \t[2].}</p>
</div>
<p>\t[3] \v2 \t[5] \t[4]?</p>
<table class="wimscenter wimsborder">
<tr><th><label for="reply1">\t[10]</label></th><td>\d</td><td>\embed{r1,5}</td></tr>
<tr> <th><label for="reply2">\t[7]</label></th><td>\v1</td><td>\embed{r2,5}</td></tr>
</table>
<div class="spacer"><label for="reply3">\name_reponse:</label> \embed{r3,5} \t[6]</div>
}
\answer{}{\v2}{type=numeric}
\answer{}{\rep}{type=numeric}
\answer{}{\rep}{type=numeric}
\latex{
\begin{statement}
\name_instruction : \t[1] \v1 \t[6]. \t[3] \v2 \t[5] \t[4]?\par

  \begin{center}
    \begin{tabular}{|l|c|c|}
      \hline
      \t[10] & \d & \ldots \\ \hline
      \t[7] & \v1 & \ldots \\ \hline
    \end{tabular}
  \end{center}
  Réponse en \t[6] : \dotfill
\end{statement}

\begin{solution}
  \name_easy \rep \t[6].
\end{solution}
}
#endif
#if defined TARGET_oefprobprop3
\statement{\name_instruction.
<div class="wims_question">
\if{\t[2]=}{\t[1] \v1 \t[6].}{\t[1] \v1 \t[6] \t[2].}
</div>
<p>\t[3] \v2 \t[5] \t[4]?</p>
<table class="wimscenter wimsborder">
<tr>
<th>\t[10]</th><td>\embed{r1,5}</td><td>\embed{r2,5}</td></tr>
<tr> <th>\t[7]</th><td>\embed{r3,5}</td><td>\embed{r4,5}</td></tr>
</table>
<div class="spacer">
<label for="reply5">\name_reponse:</label> \embed{r5,5} \t[6]</div>
}
\answer{}{\d}{type=numeric}
\answer{}{\v2}{type=numeric}
\answer{}{\v1}{type=numeric}
\answer{}{\rep}{type=numeric}
\answer{}{\rep}{type=numeric}
\latex{
\begin{statement}
\name_instruction :
\t[1] \v1 \t[6]. \t[3] \v2 \t[5] \t[4]?\par

  \begin{center}
    \begin{tabular}{|l|c|c|}
      \hline
      \t[10] & \ldots & \ldots \\ \hline
      \t[7] & \ldots & \ldots \\ \hline
    \end{tabular}
  \end{center}
  Réponse en \t[6] : \dotfill
\end{statement}

\begin{solution}
Complétons le tableau :

  \begin{center}
    \begin{tabular}{|l|c|c|}
      \hline
      \t[9] & \d & \v2 \\ \hline
      \t[6] & \v1 & \rep \\ \hline
    \end{tabular}
  \end{center}
  \name_easy \rep \t[6].
\end{solution}}
#endif
#if defined TARGET_oefprobprop4 || defined TARGET_oefprobprop5
\real{v1=randint(\t[14]..\t[15])*\t[16]}
\real{v2=randint(\t[17]..\t[18])*\t[19]}
\real{v=randint(\t[17]..\t[18])*\t[19]}
\if{\v=\v2}{\real{v=\v2+randint(1..3)*\d}}
\real{v=\v/\d}
\real{rep=\v1*\v2/\d}
\real{e=\d*\v}
\real{f=\v1*\v}
# if defined TARGET_oefprobprop4
\statement{
\name_instruction:
<div class="wims_question">\t[1] \e \t[2] \f \t[7] \t[3].</div>
<p>\t[4] \v2 \t[6]?</p>
<table class="wimscenter wimsborder">
<tr><th><label for="reply1">\t[11]</label></th><td>\e</td><td>\embed{r1,5}</td></tr>
<tr> <th><label for="reply2">\t[8]</label></th><td>\f</td><td>\embed{r2,5}</td></tr>
</table>
<div class="spacer"><label for="reply3">\name_reponse:</label> \embed{r3,5} \t[7]</div>
}
\answer{}{\v2}{type=numeric}
\answer{}{\rep}{type=numeric}
\answer{}{\rep}{type=numeric}
\latex{
\begin{statement}
\name_instruction :
\t[1] \e \t[2] \f \t[7] \t[3]. \t[4] \v2 \t[6]?\par

  \begin{center}
    \begin{tabular}{|l|c|c|}
      \hline
      \t[10] & \d & \ldots \\ \hline
      \t[7] & \v1 & \ldots \\ \hline
    \end{tabular}
  \end{center}
  Réponse en \t[7] : \dotfill
\end{statement}

\begin{solution}
Complétons le tableau :

  \begin{center}
    \begin{tabular}{|l|c|c|}
      \hline
      \t[11] & \d & \v2 \\ \hline
      \t[8] & \v1 & \rep \\ \hline
    \end{tabular}
  \end{center}
  \name_easy \rep \t[7].
\end{solution}}

# endif
#if defined TARGET_oefprobprop5
\statement{
\name_instruction:
<div class="wims_question">\t[1] \e \t[2] \f \t[7] \t[3].
</div>
<p>\t[4] \v2 \t[6] \t[5]?</p>

<table class="wimscenter wimsborder">
<tr><th>\t[11]</th><td>\e</td><td>\embed{r1,5}</td></tr>
<tr><th>\embed{r2,150x35}</th> <th>\embed{r3,5}</th><th>\embed{r4,5}</th></tr>
</table>
<div>
<label for="reply5">\name_reponse:</label> \embed{r5,5} \t[7]</div>
}
\answer{}{\v2}{type=numeric}
\answer{}{\t[8];\t[9],\t[10]}{type=dragfill}{option=shuffle}
\answer{}{\f}{type=numeric}
\answer{}{\rep}{type=numeric}
\answer{}{\rep}{type=numeric}
\latex{
\begin{statement}
Compléter le tableau et répondre à la question.\par

\name_instruction :
\t[1] \e \t[2] \f \t[7] \t[3]. \t[4] \v2 \t[6] \t[5]?\par

  \begin{center}
    \begin{tabular}{|l|c|c|}
      \hline
      \t[9] & \e & \ldots \\ \hline
      \ldots & \ldots & \ldots \\ \hline
    \end{tabular}
  \end{center}
  Réponse en \t[8] : \dotfill
\end{statement}
\begin{solution}
Complétons le tableau :

  \begin{center}
    \begin{tabular}{|l|c|c|}
      \hline
      \t[10] & \e& \v2 \\ \hline
      \t[8] & \f & \rep \\ \hline
    \end{tabular}
  \end{center}
  \name_easy \rep \t[7].
\end{solution}

}
# endif
#endif
