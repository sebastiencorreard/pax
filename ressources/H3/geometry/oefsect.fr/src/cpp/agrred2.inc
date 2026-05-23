\text{rep=\num2,\num1,\coef}
\text{units=\unit,\unit,}
\integer{ch=random(1..3)}
\real{rep=item(\ch,\rep)}
\text{enonce=row(\ch,\enonce)}
\text{units=item(\ch,\units)}

\if{\ch<3}{
\text{don=reply 1}
}{
\text{don=reply 2}
}

\steps{\don}

\statement{\enonce ?}

\reply{Réponse}{\rep \unit}{type=units}
\reply{Réponse}{\rep}{type=auto}
