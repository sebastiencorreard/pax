\text{Y=shuffle(\B,\C)}
\integer{ch=randint(1..4)}
\if{\ch=1}{
  \text{dessin=range -0.1,1.1,-0.2,1.2
square 0,0.1,10,red
triangle 0,0,1,0,0,1,black
text black,-0.05,0,medium,\A
text black,-0.05,1.05,medium,\Y[1]
text black,1,0,medium,\Y[2]}
}{\if{\ch=2}{
  \text{dessin=range -0.1,1.1,1.2,-0.2
square 0,0,10,red
triangle 0,0,1,0,0,1,black
text black,-0.05,0,medium,\A
text black,-0.05,0.95,medium,\Y[1]
text black,1,0,medium,\Y[2]}
}{\if{\ch=3}{
  \text{dessin=range 1.1,-0.1,-0.2,1.2
square 0.05,0.1,10,red
triangle 0,0,1,0,0,1,black
text black,-0.05,0,medium,\A
text black,-0.05,1.05,medium,\Y[1]
text black,1.05,0,medium,\Y[2]}
}{
  \text{dessin=range 1.1,-0.1,1.2,-0.2
square 0.05,0,10,red
triangle 0,0,1,0,0,1,black
text black,-0.05,-0.05,medium,\A
text black,-0.05,0.95,medium,\Y[1]
text black,1.05,-0.05,medium,\Y[2]}
}}}
