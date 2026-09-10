n\title{Question 213 NS Isoler une variable}
\keywords{quizz,literal_calculation}
\observation{Question du sujet zéro sujet-specifique-2_0.pdf publié sur EDUSCOL en juin 2025 }

\matrix{preambule=Le volume \(\mathcal{V}\) d'un cylindre de rayon \(r\) et de hauteur \(h\) est \(\mathcal{V}=\pi r^2 h\)
Le volume \(\mathcal{V}\) d'un cône de rayon \(r\) et de hauteur \(h\) est \(\mathcal{V}=\frac{1}{3}\pi r^2 h\)
Le volume \(\mathcal{V}\) d'une pyramide de hauteur \(h\) et de base un carré de côté \(a\) est \(\mathcal{V}=\frac{1}{3}a^2 h\)
Le volume \(\mathcal{V}\) d'un tétraèdre de hauteur \(h\) et de base un triangle équilatéral de côté \(a\) est \(\mathcal{V}=\frac{\sqrt{3}}{12}a^2 h\)
Le volume \(\mathcal{V}\) d'un tore de rayon \(r\) et de distance à l'axe \(d\) est \(\mathcal{V}=2\pi ^2 r^2 d\)
L'aire latérale \(\mathcal{A}\) d'un cylindre de rayon \(r\) et de hauteur \(h\) est \(\mathcal{A}=2\pi r h\)
L'aire \(\mathcal{A}\) d'un tore de rayon \(r\) et de distance à l'axe \(d\) est \(\mathcal{A}=4\pi ^2 r d\)
L'aire \(\mathcal{A}\) d'une couronne de rayon intérieur \(r\) et de rayon extérieur \(R\) est \(\mathcal{A}=\pi R^2-\pi r^2\)
}

\matrix{variable=\(h\),\(r\)
\(h\),\(r\)
\(h\),\(a\)
\(h\),\(a\)
\(d\),\(r\)
\(h\),\(r\)
\(r\),\(d\)
\(R\),\(r\)
} 

\matrix{mgood=\(h=\frac{\mathcal{V}}{\pi r^2}\),\(r=\sqrt{\frac{\mathcal{V}}{\pi h}}\)
\(h=\frac{3\mathcal{V}}{\pi r^2}\),\(r=\sqrt{\frac{3\mathcal{V}}{\pi h}}\)
\(h=\frac{3\mathcal{V}}{a^2}\),\(r=\sqrt{\frac{3\mathcal{V}}{h}}\)
\(h=\frac{12\mathcal{V}}{\sqrt{3}a^2}\),\(a=\sqrt{\frac{12\mathcal{V}}{\sqrt{3}h}}\)
\(d=\frac{\mathcal{V}}{2\pi^2 r^2}\),\(r=\frac{1}{\pi}\sqrt{\frac{\mathcal{V}}{2d}}\)
\(h=\frac{\mathcal{A}}{2\pi r}\),\(r=\frac{\mathcal{A}}{2\pi h}\)
\(r=\frac{\mathcal{A}}{4\pi^2 d}\),\(d=\frac{\mathcal{A}}{4\pi^2 r}\)
\(R=\sqrt{\frac{\mathcal{A}}{\pi}+r^2}\),\(r=\sqrt{R^2-\frac{\mathcal{A}}{\pi}}\)
}
\matrix{mbad1=\(h=\frac{\pi \mathcal{V}}{r^2}\),\(r=\sqrt{\frac{\pi \mathcal{V}}{h}}\)
\(h=\frac{\mathcal{V}}{3 \pi r^2}\),\(r=\sqrt{\frac{\mathcal{V}}{3\pi h}}\)
\(h=\frac{\mathcal{V}}{3a^2}\),\(r=\sqrt{\frac{\mathcal{V}}{3h}}\)
\(h=\frac{\mathcal{V}}{12\sqrt{3}a^2}\),\(a=\sqrt{\frac{\mathcal{V}}{12\sqrt{3}h}}\)
\(d=\frac{2\mathcal{V}}{(\pi r)^2}\),\(r=\frac{1}{\pi}\sqrt{\frac{2\mathcal{V}}{d}}\)
\(h=\frac{4\mathcal{A}}{\pi r}\),\(r=\frac{4\mathcal{A}}{\pi h}\)
\(r=\frac{4\mathcal{A}}{\pi^2 d}\),\(d=\frac{4\mathcal{A}}{\pi^2 r}\)
\(R=\sqrt{\frac{\mathcal{A}}{\pi}}+r\),\(r=R-\sqrt{\frac{\mathcal{A}}{\pi}}\)
}
\matrix{mbad2=\(h=\frac{\mathcal{V}^2}{\pi r}\),\(r=\sqrt{\frac{h}{\pi \mathcal{V}}}\)
\(h=\frac{3\mathcal{V}^2}{\pi r}\),\(r=\frac{3\mathcal{V}^2}{\pi h}\)
\(h=\frac{3\mathcal{V}^2}{a}\),\(r=\frac{3\mathcal{V}^2}{h}\)
\(h=\frac{12\mathcal{V}^2}{3a}\),\(a=\sqrt{\frac{4\mathcal{V}}{h}}\)
\(d=\frac{\mathcal{V}}{\sqrt{2}\pi r}\),\(r=\sqrt{\frac{\mathcal{V}}{\sqrt{2}\pi d}}\)
\(h=\frac{\mathcal{A}r}{2\pi }\),\(r=\frac{\mathcal{A}h}{2\pi }\)
\(r=\frac{\sqrt{\mathcal{A}}}{2\pi d}\),\(d=\frac{\sqrt{\mathcal{A}}}{2\pi r}\)
\(R=\sqrt{\frac{\mathcal{A}}{\pi}-r^2}\),\(r=\sqrt{\frac{\mathcal{A}}{\pi}-R^2}\)
}
\matrix{mbad3=\(h=\frac{\sqrt{\mathcal{V}}}{\pi r}\),\(r=\frac{\mathcal{V}}{\sqrt{\pi h}}\)
\(h=\frac{3\sqrt{\mathcal{V}}}{\pi r}\),\(r=\frac{3\mathcal{V}}{\sqrt{\pi h}}\)
\(h=\frac{3\sqrt{\mathcal{V}}}{a}\),\(r=\frac{3\mathcal{V}}{\sqrt{h}}\)
\(h=\frac{12}{a}\sqrt{\frac{\mathcal{V}}{3}}\),\(a=\frac{12\sqrt{\mathcal{V}}}{\sqrt{3}h}\)
\(d=\frac{\sqrt{\mathcal{V}}}{2\pi r}\),\(r=\frac{1}{2}\sqrt{\frac{\mathcal{V}}{\pi d}}\)
\(h=2\pi r \mathcal{A}\),\(r=2\pi h \mathcal{A}\)
\(r=\frac{\mathcal{A}}{2\pi \sqrt{d}}\),\(d=\frac{\mathcal{A}}{2\pi \sqrt{r}}\)
\(R=\sqrt{\frac{\mathcal{A}}{\pi r}}\),\(r=\sqrt{\frac{\mathcal{A}}{\pi R}}\)
}
\integer{c=randint(1..8)}
\integer{d=randitem(1,1,2)}
\text{pre=\preambule[\c;1]}
\text{q=\variable[\c;\d]}
\text{good=\mgood[\c;\d]}
\text{bads=\mbad1[\c;\d],\mbad2[\c;\d],\mbad3[\c;\d]}
\text{feedback=La bonne réponse est \good.}

\text{enonce=\pre. <br>On cherche à isoler la variable <span class="nowrap">\q.</span> On a&nbsp;&#58;}
