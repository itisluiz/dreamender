R"(
window.addEventListener('load', function () {
    let boldLabels = document.getElementsByTagName("b");
    if (boldLabels.length > 0 && boldLabels[0].innerText == "Left Hand:") {
        let content = document.getElementsByClassName("uiContent")[0];

        let synd_graballbtn = document.createElement('a');
        synd_graballbtn.style.background = "#9d0808";
        synd_graballbtn.style.display = "block";
        synd_graballbtn.style.width = "95%";
        synd_graballbtn.style.margin = "0 auto";
        synd_graballbtn.style.textAlign = "center";

        synd_graballbtn.innerText = "Take Everything";

        synd_graballbtn.addEventListener("click", function () {
            let anchors = document.getElementsByTagName("a");
            let basehref = window.location.href;
            for (i = 0; i < anchors.length; ++i) {
                if (anchors[i] == this || anchors[i].innerText == "Close" || anchors[i].innerText == "")
                    continue;

                if (anchors[i].href)
                    window.location.href = basehref + anchors[i].href;
            }
        });
        content.insertBefore(synd_graballbtn, content.firstChild);
    }

});
)"