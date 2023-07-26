const HEALTHY_BMI_MIN = 18.5;
const HEALTHY_BMI_MAX = 24.9;
const OVERWEIGHT_BMI_MIN = 25;
const OVERWEIGHT_BMI_MAX = 29.9;
const OBESE_BMI_MIN = 30;

 const BMI_RANGE = {
    underweight: [0, 18.4],
    healthy: [18.5, 24.9],
    overweight: [25, 29.9],
    obese: [30, Infinity],
 }


function main() {
    const bmiWidgetEl = document.querySelector('.bmi-widget');
    const bioData = {
        height: 0,
        weight: 0,
        bmi: 0,
        idealWeightMin: 0,
        idealWeightMax: 0,
        weightClassification: '',
        calculateBmiData: function() {
            this.bmi = (this.weight / (this.height ** 2)).toFixed(1);
            this.idealWeightMin = (BMI_RANGE.healthy[0] * (this.height ** 2)).toFixed(1);
            this.idealWeightMax = (BMI_RANGE.healthy[1] * (this.height ** 2)).toFixed(1);
        },
        setWeightClassification: function () {
            if (this.bmi < BMI_RANGE.healthy[0]) {
                this.weightClassification = 'underweight';
            }
            else if (this.bmi < BMI_RANGE.overweight[0]) {
                this.weightClassification = 'healthy';
            }
            else if (this.bmi < BMI_RANGE.obese[0]) {
                this.weightClassification = 'overweight';
            }
            else {
                this.weightClassification = 'obese';
            }
        }
    }

    bmiWidgetEl.addEventListener('input', e => {
        if (!['input-height', 'input-weight'].includes(e.target.id)) {
            return 
        }

        [bioData.height, bioData.weight] = getBioData();
        bioData.calculateBmiData();
        bioData.setWeightClassification();
        console.log(bioData.bmi, bioData.idealWeightMin, bioData.idealWeightMax, bioData.weightClassification);
        updateHTML(bioData);
    })
}

function getBioData() {
    let height = document.getElementById('input-height').value / 100;
    let weight = document.getElementById('input-weight').value;

    return [height, weight];
}

function updateHTML(bioData) {
    const claculatedBmiFigureEl = document.querySelector('#calculated-bmi-figure');
    const weightRangeMinEl = document.querySelector('#weight-range-min');
    const weightRangeMaxEl = document.querySelector('#weight-range-max');
    const bmiRangeMinEl = document.querySelector('#bmi-range-min');
    const bmiRangeMaxEl = document.querySelector('#bmi-range-max');
    const weightClassificationEls = document.querySelectorAll('.weight-classification');

    claculatedBmiFigureEl.textContent = bioData.bmi;
    weightRangeMinEl.textContent = bioData.idealWeightMin;
    weightRangeMaxEl.textContent = bioData.idealWeightMax;
    bmiRangeMinEl.textContent = BMI_RANGE[bioData.weightClassification][0];
    bmiRangeMaxEl.textContent = BMI_RANGE[bioData.weightClassification][1];
    weightClassificationEls.forEach(el => el.textContent = bioData.weightClassification);

    

}

main();