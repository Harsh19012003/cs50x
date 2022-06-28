function rating(event)
{
    var trigger = event.srcElement;
    var ratinglabel = document.querySelector("#starrating");
    if (event.target.id == "star1")
    {
        ratinglabel.innerHTML = "Help us improve by answering some questions...";
    }
    else if (event.target.id == "star2")
    {
        ratinglabel.innerHTML = "Help us improve by answering some questions...";
    }
    else if (event.target.id == "star3")
    {
        ratinglabel.innerHTML = "Thanks for balanced feedback";
    }
    else if (event.target.id == "star4")
    {
        ratinglabel.innerHTML = "Thanks for 4star rating";
    }
    else if (event.target.id == "star5")
    {
        ratinglabel.innerHTML = "Thanks for 5star rating its really inspiring";
    }
}

function answerradio(event)
{
    var trigger = event.srcElement;
    console.log(trigger);
    document.querySelector("#answerradio").innerHTML = "Thanks for feedback";
}

function answercheck(event)
{
    document.querySelector("#answercheckbox").innerHTML = "Thanks for feedback";
}

function shipping(event)
{
    document.querySelector("#shippinginfo").innerHTML = "Your order is placed successfully....."
    document.querySelector("")
}