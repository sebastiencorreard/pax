var welinvullen=["input", "textarea", "select"]
welinvullen=welinvullen.join("|")

function disableselect(e)
{
    if (welinvullen.indexOf(e.target.tagName.toLowerCase())==-1)
    {
	return false
    }
}

function Aanzetten()
{
    return true
}

if (typeof document.onselectstart!="undefined")
{
    document.onselectstart=new Function ("return false")
}
else
{
    document.onmousedown=disableselect;
    document.onmouseup=Aanzetten;
}
