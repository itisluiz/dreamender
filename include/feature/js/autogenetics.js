R"(
window.addEventListener('load', function () {
    let tp_update;

    if (window.update) {
        tp_update = window.update
        let solving = false;
        let makinginjector_block = 0;
        let makinginjector_state = 0;

        window.update = function (e) {
            tp_update(e);
            eJson = JSON.parse(e);

            if (eJson["config"]["title"] != "DNA Modifier access console")
                return;

            let content = document.getElementById("Layout__content");

            if (!document.getElementById("synd_makeinjectorbtn")) {
                let synd_makeinjectorbtn = document.createElement('div');
                synd_makeinjectorbtn.id = "synd_makeinjectorbtn";
                synd_makeinjectorbtn.className = "Button Button--hasContent Button--color--default";
                synd_makeinjectorbtn.innerHTML = "<i class=\"fas fa-syringe\"></i>Make Injector";
                synd_makeinjectorbtn.onclick = function () {
                    let currentBlock = document.getElementsByClassName("Button--selected Button--color--default");
                    if (currentBlock.length == 0)
                        return;

                    let currentEnzyme = currentBlock[0].parentElement;
                    makinginjector_block = parseInt(currentEnzyme.firstChild.innerText, 10);
                    makinginjector_state = 0;
                }

                content.appendChild(synd_makeinjectorbtn);
            }

            if (!document.getElementById("synd_solveblockbtn")) {
                let synd_solveblockbtn = document.createElement('div');
                synd_solveblockbtn.id = "synd_solveblockbtn";
                synd_solveblockbtn.className = "Button Button--hasContent Button--color--default";
                synd_solveblockbtn.innerHTML = "<i class=\"fas fa-magic\"></i>Automatic Enzyme Mutator";
                synd_solveblockbtn.onclick = function () {
                    solving = !solving;
                    if (solving) {
                        synd_solveblockbtn.classList.remove("Button--color--default");
                        synd_solveblockbtn.classList.add("Button--color--green");
                    }
                    else {
                        synd_solveblockbtn.classList.remove("Button--color--green");
                        synd_solveblockbtn.classList.add("Button--color--default");
                    }
                }

                content.appendChild(synd_solveblockbtn);
            }

            let dnaIcons = document.getElementsByClassName("fa-dna");
            

            if (dnaIcons.length == 0 || (dnaIcons.length > 0 && !dnaIcons[1].parentElement.classList.contains("Tabs__tab--selected"))) {

                document.getElementById("synd_makeinjectorbtn").style.visibility = "hidden";
                document.getElementById("synd_solveblockbtn").style.visibility = "hidden";
                solving = false;
            } else { 
                document.getElementById("synd_makeinjectorbtn").style.visibility = "visible";
                document.getElementById("synd_solveblockbtn").style.visibility = "visible";

                let enzymes = document.getElementsByClassName("Flex__item");

                for (let i = 0; i < enzymes.length; ++i) {
                    let blocks = enzymes[i].children;
                    let value = parseInt(blocks[1].innerText + blocks[2].innerText + blocks[3].innerText, 16);

                    if (value >= 0xDAC)
                        enzymes[i].firstChild.style.outline = "1px solid green";
                    else if (value >= 0xBEA)
                        enzymes[i].firstChild.style.outline = "1px solid yellow";
                    else if (value >= 0x802)
                        enzymes[i].firstChild.style.outline = "1px solid red";
                    else
                        enzymes[i].firstChild.style.outline = "none";
                }

            }

            if (eJson["data"]["irradiating"] != 0) {
                return;
            }

            if (makinginjector_block > 0) {
                
                switch (makinginjector_state) {
                    case 0:
                    {
                        let transferTab = document.getElementsByClassName("fa-syringe")[0];
                        transferTab.click();
                        makinginjector_state = 1;
                        break;

                    }
                    case 1:
                    {
                        let subjectse = document.getElementsByClassName("fa-arrow-circle-down")[2];
                        subjectse.click();
                        makinginjector_state = 2;
                        break;
                    }
                    case 2:
                    {
                        if (eJson["data"]["isInjectorReady"] != 1)
                            break;

                        let blockInjector = document.getElementsByClassName("fa-syringe")[2];
                        blockInjector.click();

                        makinginjector_state = 3;
                        break;
                    }
                    case 3:
                    {
                        document.getElementsByClassName("Dropdown__arrow-button")[0].click();
                        document.getElementsByClassName("Dropdown__menuentry")[makinginjector_block - 1].click();
                        makinginjector_block = 0;
                        break;
                    }
                }

            } else if (solving) {
                let currentBlock = document.getElementsByClassName("Button--selected Button--color--default");
                if (currentBlock.length == 0)
                    return;

                let irradiate = document.getElementsByClassName("fa-radiation")[0].parentElement;
                let currentEnzyme = currentBlock[0].parentElement;

                let block_1 = currentEnzyme.children[1];
                let block_2 = currentEnzyme.children[2];
                let block_3 = currentEnzyme.children[3];

                let block_1_val = parseInt(block_1.innerText, 16);
                let block_2_val = parseInt(block_2.innerText, 16);
                let block_3_val = parseInt(block_3.innerText, 16);

                if (block_1_val < 0xD) {
                    block_1.click();
                    irradiate.click();
                    return;
                } else if (block_1_val < 0xE && ( (block_3_val >= 0xC && block_2_val < 0xA) || (block_3_val < 0xC && block_2_val <= 0xA) )) {
                    block_2.click();
                    irradiate.click();
                    return;
                }
                
            }
            
        };
    }

});
)"