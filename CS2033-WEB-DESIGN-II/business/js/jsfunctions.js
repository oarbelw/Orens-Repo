function scroll() {
    var t = window.scrollY;
    var para1 = document.getElementById("para1");
    var para2 = document.getElementById("para2");
    var m = -0.25;
    var b = 0;

    var newY = m*t + b;
    para1.style.backgroundPositionY = newY + "px";
    para2.style.backgroundPositionY = newY + "px";

    var nav = document.getElementById("nav");

    var l1 = document.getElementById("l1");
    var l2 = document.getElementById("l2");
    var l3 = document.getElementById("l3");
    var l4 = document.getElementById("l4");

    var s1 = document.getElementById("s1");
    var s2 = document.getElementById("s2");
    var s3 = document.getElementById("s3");
    var s4 = document.getElementById("s4");

    var t1 = s1.offsetTop;
    var t2 = s2.offsetTop;
    var t3 = s3.offsetTop;
    var t4 = s4.offsetTop;

    l1.style.borderBottomColor = "#B982B9";
    l2.style.borderBottomColor = "#B982B9";
    l3.style.borderBottomColor = "#B982B9";
    l4.style.borderBottomColor = "#B982B9";

    if (t > (t4-30)) {
        l4.style.borderBottomColor = "#FF6BEC";
    } else if (t > (t3-30)) {
        l3.style.borderBottomColor = "#FF6BEC";
    } else if (t > (t2-30)) {
        l2.style.borderBottomColor = "#FF6BEC";
    } else if (t > (t1-30)) {
        l1.style.borderBottomColor = "#FF6BEC";
    } 

    var msg = document.getElementById("scrollmsg");

    if (t > 1750) {
        msg.style.marginLeft = "0px";
    }
}

function checkName () {
    var nameBox = document.getElementById("name");
    var name = nameBox.value;

    if (name.length < 4 || /\d/.test(name)) {
        nameBox.style.borderColor = "red";
    } else {
        nameBox.style.borderColor = "green";
    }
}

function checkPhoneNumber () {
    var numberBox = document.getElementById("phone-number");
    var number = numberBox.value;

    var regexNumber = /^\d{3} \d{3} \d{4}$/;

    if (regexNumber.test(number)) {
        numberBox.style.borderColor = "green";
    } else {
        numberBox.style.borderColor = "red";
    }
}

function updateReason () {
    var PI = document.getElementById("PI");
    var productLabel = document.getElementById("productLabel");
    var productIDBox = document.getElementById("productID");
    var inputtedID = productIDBox.value;
    if (PI.checked) {
        productLabel.className = "visible";
        productIDBox.className = "textbook textbox";

        if (inputtedID == "C2B224" || inputtedID == "S1A223" || inputtedID == "D9G221" || inputtedID == "S5P124" || inputtedID == "C2Y227" || inputtedID == "W1C220") {
             productIDBox.style.borderColor = "green";
        } else {
            productIDBox.style.borderColor = "red";
        }                    
    } else {
        productLabel.className = "hidden";
        productIDBox.className = "textbook hidden";
    }
}

function checkMessage () {
    var messageBox = document.getElementById("msgBox");
    var msg = messageBox.value;

    var charCount = msg.length;
    var charMsg = document.getElementById("char_count");

    charMsg.innerHTML = charCount + " / 30";

    if (charCount >= 10 && charCount <= 30) {
        messageBox.style.borderColor = "green";
        charMsg.style.color = "green";
    } else {
        messageBox.style.borderColor = "red";
        charMsg.style.color = "red";
    }
}