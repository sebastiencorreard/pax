target=oefvocprop1 oefvocprop2 oefvocprop3 oefvocprop4 oefvocprop5
\langage{fr}
\author{Jean-Luc, Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}

#if defined TARGET_oefvocprop1
#define NUM 1
\keywords{proportionality}
#endif
#if defined TARGET_oefvocprop2
#define NUM 2
\keywords{pbsolving, proportionality}
#endif
#if defined TARGET_oefvocprop3
#define NUM 3
\keywords{proportionality}
#endif
#if defined TARGET_oefvocprop4
#define NUM 4
\keywords{pbsolving, proportionality}
#endif
#if defined TARGET_oefvocprop5
#define NUM 5
\keywords{pbsolving, proportionality}
#endif
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefvocprop1
\integer{cnt=rows(\enonc)}
\text{a=randint(1..\cnt)}
\text{enonc=row(\a,\enonc)}
\text{enonc1=item(1..4,\enonc)}
\text{enonc2=item(5..7,\enonc)}

\text{enonc1m=shuffle(\fbox{\enonc1[1]},\fbox{\enonc1[2]},\fbox{\enonc1[3]},\fbox{\enonc1[4]})}
\text{enonc2m=shuffle(\fbox{\enonc2[1]},\fbox{\enonc2[2]},\fbox{\enonc2[3]})}
\statement{
\name_instruction :
<div class="spacer">
\embed{r1,200x50} <br>\embed{r2,200x50}
</div>
}
\answer{}{\enonc1;\enonc1}{type=dragfill}{option=shuffle}
\answer{}{\enonc2;\enonc2}{type=dragfill}{option=shuffle}
\latex{
\begin{statement}
\name_instruction :
\begin{itemize}
	\item \enonc1m
	\item \enonc2m
\end{itemize}
\end{statement}

\begin{solution}
\begin{itemize}
	\item \enonc1
	\item \enonc2
\end{itemize}
\end{solution}
}
#endif

#if defined TARGET_oefvocprop2
\integer{cnt=rows(\name_t)}
\integer{a=randint(1..\cnt)}
\text{t=row(\a,\name_t)}
\if{\t[2]=1}{\text{reponseredigee=\name_repred[1]}}{\text{reponseredigee=\name_repred[2]}}

\statement{\t[1]
<div class="spacer">
\name_instruction[1;] \embed{r1} \name_instruction[2;]
</div>
}
\answer{}{\t[2];\reps}{type=menu}
\latex{
\begin{statement}
\t[1]
\name_instruction[1] \emph{\reps} \name_instruction[2]\par
\dotfill
\end{statement}

\begin{solution}
\name_solution[1;] \textbf{\reponseredigee} \name_solution[2;]
\end{solution}
}
#endif
#if defined TARGET_oefvocprop3
!! depend de name_t (les 8 premières sont 1, les 9 suivantes ont un 2) ...
code à comprendre ....
\text{a=shuffle(8)}
\text{b=shuffle(9,10,11,12,13,14,15,16,17)}
\text{c=randint(1..2)}
\text{d=randint(1..2)}
\text{t1=row(\a[1],\name_t)}
\text{rep1=\rep[\t1[2]]}
\text{t2=row(\b[1],\name_t)}
\text{rep2=\rep[\t2[2]]}
\if{\c=1}{\text{t3=row(\a[2],\name_t)}
  \text{rep3=\rep[\t3[2]]}}
{ \text{t3=row(\b[2],\name_t)}
  \text{rep3=\rep[\t3[2]]}}
\if{\d=1}{\text{t4=row(\a[3],\name_t)}
   \text{rep4=\rep[\t4[2]]}}
   {\text{t4=row(\b[4],\name_t)}
   \text{rep4=\rep[\t4[2]]}}
\text{t=\t1[1],\t2[1],\t3[1],\t4[1]}
\text{reps=\rep1,\rep2,\rep3,\rep4}
\statement{\name_instruction:
<div class="wimscenter">\embed{r1,80x400}</div>
}
\answer{}{\t;\reps}{type=correspond}{option=shuffle}
#endif
#if defined TARGET_oefvocprop4
\integer{cnt=rows(\name_t)}
\integer{a=randint(1..\cnt)}
\text{t=row(\a,\name_t)}
\text{p=\name_p[\t[2]]}
\text{b=randint(1..2)}
\if{\b=1}{
  \text{enonc1=}
  \text{enonc2= est \p \t[6].}
  \text{rep=\t[3]}
}{
  \text{enonc1=\t[3] est \p}
  \text{enonc2= .}
  \text{rep=\t[6]}}
\text{reps=\t[4],\t[5],\t[7],\t[8]}
%%% Rajout jbf pour latex
\text{repm=shuffle(\fbox{\t[3]},\fbox{\t[4]},\fbox{\t[5]},\fbox{\t[6]})}
\statement{<div class="wims_question">
\t[1]
</div>
<p>\name_instruction.</p>
<div class="spacer">
<label for="reply1">\enonc1</label> \embed{r1,150x30} \enonc2
</div>
}
\answer{}{\rep;\reps}{type=dragfill}{option=shuffle}
\latex{
\begin{statement}
\t[1]
\name_instruction:\par

\enonc1 \dotfill \enonc2
\begin{itemize}
	\item \repm
\end{itemize}
\end{statement}

\begin{solution}
\enonc1 \rep \enonc2
\end{solution}
}
#endif
#if defined TARGET_oefvocprop5
\integer{cnt=rows(\name_t)}
\integer{a=randint(1..\cnt)}
\text{t=row(\a,\name_t)}
\text{b=randint(1..2)}
\if{\b=1}{\text{rep=\t[6]}}{\text{rep=\t[3]}}
\text{reps=\t[4],\t[5],\t[7],\t[8]}
%%% Rajout JBF pour Latex
\text{repm=shuffle(\fbox{\t[3]},\fbox{\t[4]},\fbox{\t[5]},\fbox{\t[6]},\fbox{\t[7]},\fbox{\t[8]},\fbox{\t[9]},\fbox{\t[10]},\fbox{\t[11]},\fbox{\t[12]})}
\statement{<div class="wims_question">
\t[1]
</div>
<div class="spacer">
\name_instruction</div>
\if{\b=1}{<table class="wimscenter wimsborder"><tr>
<th>\embed{r1,150x50}</th>
<td style="min-width:150px">\t[11]</td>
<td>\embed{r2,150x50}</td></tr>
<tr><th>\t[3]</th><td>\t[9]</td>
<td>\embed{r3,150x50}</td></tr>
</table>}
{<table class="wimscenter wimsborder"><tr>
<th>\t[6]</th>
<td style="min-width:150px">\t[11]</td>
<td>\embed{r2,150x50}</td>
</tr><tr><th>\embed{r1,150x50}</th>
<td>\t[9]</td>
<td>\embed{r3,150x50}</td></tr>
</table>}
}
\answer{}{\rep;\reps}{type=dragfill}{option=shuffle}
\answer{}{\t[12];\t[11]}{type=dragfill}{option=shuffle}
\answer{}{\t[10];\t[9]}{type=dragfill}{option=shuffle}

\if{\b=1}{\latex{
\begin{statement}
\t[1]
\name_instruction:
\begin{center}
	\begin{tabular}{|l|c|c|}
		\hline
		\ldots & \t[11] & \ldots \\ \hline
		\t[3] & \t[9] & \ldots \\ \hline
	\end{tabular}
\end{center}
\begin{itemize}
	\item \repm[1], \repm[2], \repm[3], \repm[4]
	\item \repm[5], \repm[6], \repm[7], \repm[8]
	\item \repm[9], \repm[10], \repm[11], \repm[12]
\end{itemize}
\end{statement}

\begin{solution}
\begin{center}
	\begin{tabular}{|l|c|c|}
		\hline
		\t[6] & \t[11] & \t[12] \\ \hline
		\t[3] & \t[9] & \t[10] \\ \hline
	\end{tabular}
\end{center}
\end{solution}}{\latex{
\begin{statement}
\t[1]
\name_instruction:
\begin{center}
	\begin{tabular}{|l|c|c|}
		\hline
		\t[6] & \t[11] & \ldots \\ \hline
		\ldots & \t[9] & \ldots \\ \hline
	\end{tabular}
\end{center}
\begin{itemize}
	\item \repm[1], \repm[2], \repm[3], \repm[4]
	\item \repm[5], \repm[6], \repm[7], \repm[8]
	\item \repm[9], \repm[10], \repm[11], \repm[12]
\end{itemize}
\end{statement}
\begin{solution}
\begin{center}
	\begin{tabular}{|l|c|c|}
		\hline
		\t[6] & \t[11] & \t[12] \\ \hline
		\t[3] & \t[9] & \t[10] \\ \hline
	\end{tabular}
\end{center}
\end{solution}
}}
}
#endif
