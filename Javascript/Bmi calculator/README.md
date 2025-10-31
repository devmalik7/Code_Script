# BMI Calculator

A simple and interactive web-based Body Mass Index (BMI) calculator that allows users to calculate their BMI by entering their height and weight.

## Features

- Calculate BMI based on height (in cm) and weight (in kg)
- Real-time validation of input values
- BMI category classification:
  - Underweight: Less than 18.5
  - Normal weight: 18.6 - 24.9
  - Overweight: 25 - 29.9
  - Obese: Greater than 29.9
- User-friendly interface with clear visual feedback
- Weight guide reference displayed on the page

## Technologies Used

- HTML5
- CSS3
- JavaScript (Vanilla JS)

## Project Structure

```
Bmi calculator/
├── index.html    # Main HTML structure
├── script.js     # JavaScript logic for BMI calculation
├── style.css     # Styling and layout
└── README.md     # Project documentation
```

## How to Use

1. Open `index.html` in your web browser
2. Enter your height in centimeters (cm)
3. Enter your weight in kilograms (kg)
4. Click the "Calculate" button
5. View your BMI result and corresponding category

## BMI Formula

BMI is calculated using the formula:
```
BMI = weight (kg) / (height (m))²
```

The calculator converts height from centimeters to meters by dividing by 10000 (since height² in cm² needs to be converted to m²).

## Getting Started

Simply clone or download this repository and open `index.html` in any modern web browser. No additional setup or dependencies are required.

## Browser Compatibility

This project works on all modern web browsers including:
- Google Chrome
- Mozilla Firefox
- Microsoft Edge
- Safari

## License

This project is open source and available for educational purposes.

