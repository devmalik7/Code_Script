const form = document.querySelector('form');

form.addEventListener('submit', function(e) {
  e.preventDefault();
  
  const height = parseInt(document.querySelector('#height').value);
  const weight = parseInt(document.querySelector('#weight').value);
  const results = document.querySelector('#results');

  if (isNaN(height) || height <= 0) {
    results.innerHTML = "Please give a valid Height";
  } else if (isNaN(weight) || weight <= 0) {
    results.innerHTML = "Please give a valid Weight";
  } else {
    const bmi = (weight/((height*height)/10000)).toFixed(2);
    let message ="";
    if(bmi<18.5){
        message="you'r are Underweight"
    }
    else if(bmi>=18.6 && bmi <=24.9){
        message="you'r have Normal weight"
    }
    else if(bmi >= 25 && bmi <= 29.9){
        message="you'r are overweight"
    }
    else{
        message ="you'r are obese"
    }
    //showing the results
    results.innerHTML = `<span>Your BMI is ${bmi}. ${message}</span>`;
  }
});
