// set up logic to determin correct answer
function handleMultipleChoice(answer) {
    const choiceBtnElements = document.getElementsByClassName('answer-choice');
    const multiChoiceFeedbackElement = document.getElementById('multiple-choice-feedback');

    Array.from(choiceBtnElements).forEach(choiceBtn => {
        choiceBtn.addEventListener('click', () => {
            if (choiceBtn.textContent === answer) {
                choiceBtn.style.backgroundColor = "#A2CDB0";
                multiChoiceFeedbackElement.textContent = "Correct!";
            } else {
                choiceBtn.style.backgroundColor = "#FF9B9B";
                multiChoiceFeedbackElement.textContent = "Incorrect!";
            }
        })

    })
}

// for free response,
function handleFreeResponse(answer) {
    const freeResponseInputElement = document.getElementById('free-response-input');
    const freeResponseCheckElement = document.getElementById('free-response-check');
    const freeResponseFeedbackElement = document.getElementById('free-response-feedback');

    freeResponseCheckElement.addEventListener('click', () => {
        let userAnswer = freeResponseInputElement.value.toUpperCase();

        if (userAnswer === answer) {
            freeResponseInputElement.style.color = "#A2CDB0";
            freeResponseFeedbackElement.textContent = "Correct!";
            console.log(userAnswer);
        } else {
            freeResponseInputElement.style.color = "#FF9B9B";
            freeResponseFeedbackElement.textContent = "Incorrect!";
            console.log("incorrect");
            console.log(userAnswer);
        }
    })

}

function main() {
    multipleChoiceAnswer = "Airbus 380";
    freeResponseAnswer = "EGLL";

    handleMultipleChoice(multipleChoiceAnswer);
    handleFreeResponse(freeResponseAnswer);
}

main();