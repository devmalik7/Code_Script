# Flip a Coin Simulator

A web-based coin flip simulator inspired by Google's coin flip feature. Flip a virtual coin with smooth 3D animations and get random heads or tails results.

## Features

- 🎲 **Random coin flips** - Fair 50/50 chance for heads or tails
- 🎨 **Smooth 3D animations** - Beautiful spinning coin effect with CSS 3D transforms
- ⌨️ **Keyboard support** - Press Space or Enter to flip
- ♿ **Accessibility** - Supports reduced motion preferences and proper ARIA labels
- 📱 **Responsive design** - Works on desktop and mobile devices
- 🎯 **Simple interface** - Clean, modern UI with dark theme

## How to Use

1. Open `index.html` in any modern web browser
2. Click the "Flip" button or press Space/Enter to flip the coin
3. Watch the coin spin and see the result (Heads or Tails)

## Files

- `index.html` - Main HTML structure
- `style.css` - Styling and animations
- `script.js` - Flip logic and interactions

## Browser Compatibility

Works in all modern browsers that support:
- CSS 3D Transforms
- Web Animations API (with fallback to CSS transitions)
- ES6 JavaScript

## Technical Details

- Uses CSS `transform-style: preserve-3d` for 3D coin effect
- Implements both Web Animations API and CSS transition fallback
- Respects `prefers-reduced-motion` media query for accessibility
- Fair random selection using `Math.random()`

## License

Free to use and modify.

