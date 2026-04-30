#!/bin/sh

name="VreemdeEend"
gifs="ok.gif nok.gif"
htmfile="1.html"
rm *.class

for p in 1 2 ;do
    n="VreemdeEend$p"
    javac -verbose -source 1.4 -target 1.4 $n.java
done

jar cvf $name.jar *.class $gifs
tar cvzf $name.src.tar.gz  $gifs *.java *.html make.sh
appletviewer 1.html 
appletviewer 2.html
