target= oefrelpourcfract4 oefrelpourcfract5
#include "author.inc"
\precision{100000}
#if defined TARGET_oefrelpourcfract4
# define NUM 4
#endif
#if defined TARGET_oefrelpourcfract5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefrelpourcfract4
\text{den=shuffle(2,4,5,10,20,25,50)}
\integer{rep1=100/\den[1]}
\integer{rep2=100/\den[2]}
\integer{rep3=100/\den[3]}
\integer{rep4=100/\den[4]}
\text{gauche=\rep1 %,\rep2 %,\rep3 %,\rep4 %}
\text{droite=\(\dfrac{1}{\den[1]}\),\(\dfrac{1}{\den[2]}\),\(\dfrac{1}{\den[3]}\),\(\dfrac{1}{\den[4]}\),}
\text{droitem=shuffle(\droite)}
#endif
#if defined TARGET_oefrelpourcfract5
\matrix{fra=3
2,3,4
3,7,9
3,7,9,11,13,17,19
2,3,4,6,7,8,9,11,12,13,14,16,17,18,19,21,22,23,24
3,7,9,11,13,17,19,21,23,27,29,31,33,37,39,41,43,47,49}
\text{a=shuffle(6)}
\text{den=4,5,10,20,25,50}
\text{num=randomitem(row(\a[1],\fra)),randomitem(row(\a[2],\fra)),randomitem(row(\a[3],\fra)),randomitem(row(\a[4],\fra))}
\integer{rep1=\num[1]*100/\den[\a[1]]}
\integer{rep2=\num[2]*100/\den[\a[2]]}
\integer{rep3=\num[3]*100/\den[\a[3]]}
\integer{rep4=\num[4]*100/\den[\a[4]]}
\text{gauche=\rep1 %,\rep2 %,\rep3 %,\rep4 % }
\text{droite=\(\dfrac{\num[1]}{\den[\a[1]]}\),\(\dfrac{\num[2]}{\den[\a[2]]}\),\(\dfrac{\num[3]}{\den[\a[3]]}\),\(\dfrac{\num[4]}{\den[\a[4]]}\),}
\text{droitem=shuffle(\droite)}
#endif

\statement{
\name_instruction
<div class="wimscenter">
\embed{r1,60x60x60}
</div>
}
\answer{}{\gauche;\droite}{type=correspond}

\latex{
\begin{statement}
\name_instruction
\begin{center}
	\renewcommand{\arraystretch}{2}
	\begin{tabular}{rccl}
		\rep1 \% & \textbullet & \textbullet & \droitem[1] \\\
		\rep2 \% & \textbullet & \textbullet & \droitem[2] \\\
		\rep3 \% & \textbullet & \textbullet & \droitem[3] \\\
		\rep4 \% & \textbullet & \textbullet & \droitem[4]
	\end{tabular}
\end{center}
\end{statement}

\begin{solution}

\begin{center}
	\renewcommand{\arraystretch}{2}
	\begin{tabular}{rccl}
		\rep1 \% & \textbullet & \textbullet & \droite[1] \\\\
		\rep2 \% & \textbullet & \textbullet & \droite[2] \\\\
		\rep3 \% & \textbullet & \textbullet & \droite[3] \\\\
		\rep4 \% & \textbullet & \textbullet & \droite[4]
	\end{tabular}
\end{center}
\end{solution}
}
