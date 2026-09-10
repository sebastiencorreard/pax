%%% data
\text{pente=1}
\text{dec=0.7}

\integer{lg_=items(\data[1;])}
\text{dessin=xrange -\pente*\lg_+1,\lg_*1.5
yrange -1,\lg_*(\pente+1)
line 0,0,\lg_,\lg_*\pente,black
}
\for{j=1 to \lg_}{
  \real{dec=\dec+1}
  \text{dessin=\dessin
  segment \j,\pente*\j, (\pente+1)*\j - \pente*\lg_,\lg_*\pente,black
  linewidth 2
  point \j,\pente*(\j),black
  linewidth 1
  textup blue,(\pente+1)*\j-\pente*\lg_-0.1,\lg_*\pente+0.1,normal,\data[1;\j]}
  \text{dessin=\data[2;\j]!= ? \dessin
  text red,\j-0.7,\pente*(\j-0.7)-0.3, normal,\data[2;\j]
  segment \j-0.7,\pente*(\j-0.7)+0.2,\j-0.7,\pente*(\j-0.7)-0.2,black}
}
