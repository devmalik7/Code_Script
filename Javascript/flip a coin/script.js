(() => {
  const coin = document.getElementById('coin');
  const flipBtn = document.getElementById('flipBtn');
  const resultEl = document.getElementById('result');

  let isFlipping = false;
  let currentAngle = 0; // 0 => heads shown; 180 => tails shown (mod 360)

  function getTargetAngle(face) {
    return face === 'heads' ? 0 : 180;
  }

  function chooseRandomFace() {
    return Math.random() < 0.5 ? 'heads' : 'tails';
  }

  function setImmediateFace(face) {
    currentAngle = getTargetAngle(face);
    coin.style.transform = `rotateY(${currentAngle}deg)`;
    coin.classList.toggle('show-heads', face === 'heads');
    coin.classList.toggle('show-tails', face === 'tails');
    coin.classList.remove('spinning');
  }

  function announce(face) {
    resultEl.textContent = face === 'heads' ? 'Heads' : 'Tails';
  }

  function flip(targetFace) {
    if (isFlipping) return;
    isFlipping = true;
    flipBtn.disabled = true;

    const prefersReduced = window.matchMedia('(prefers-reduced-motion: reduce)').matches;
    const target = targetFace || chooseRandomFace();

    if (prefersReduced) {
      setImmediateFace(target);
      announce(target);
      isFlipping = false;
      flipBtn.disabled = false;
      return;
    }

    const targetAngle = getTargetAngle(target);
    // Add multiple full spins for flair
    const fullSpins = 6; // even number so facing side logic is preserved cleanly
    const start = currentAngle;
    const end = start + fullSpins * 180 + (targetAngle - (start % 360));

    const duration = 900; // ms
    const supportsWAAPI = typeof coin.animate === 'function';

    // During the spin, allow both faces to be visible to avoid popping
    coin.classList.remove('show-heads', 'show-tails');
    coin.classList.add('spinning');

    if (supportsWAAPI) {
      coin.animate(
        [
          { transform: `rotateY(${start}deg)` },
          { transform: `rotateY(${end}deg)` }
        ],
        {
          duration,
          easing: 'cubic-bezier(.22,.61,.36,1)',
          fill: 'forwards'
        }
      ).addEventListener('finish', () => {
        currentAngle = ((end % 360) + 360) % 360;
        // Snap to exact final state to avoid subpixel drift
        coin.style.transform = `rotateY(${currentAngle}deg)`;
        coin.classList.toggle('show-heads', target === 'heads');
        coin.classList.toggle('show-tails', target === 'tails');
        coin.classList.remove('spinning');
        announce(target);
        isFlipping = false;
        flipBtn.disabled = false;
      });
    } else {
      // Fallback: use CSS transition defined on .coin
      // Set starting transform explicitly to ensure transition runs from the right place
      coin.style.transform = `rotateY(${start}deg)`;
      // Next frame, set to end to trigger transition
      requestAnimationFrame(() => {
        coin.style.transform = `rotateY(${end}deg)`;
      });
      window.setTimeout(() => {
        currentAngle = ((end % 360) + 360) % 360;
        coin.style.transform = `rotateY(${currentAngle}deg)`;
        coin.classList.toggle('show-heads', target === 'heads');
        coin.classList.toggle('show-tails', target === 'tails');
        coin.classList.remove('spinning');
        announce(target);
        isFlipping = false;
        flipBtn.disabled = false;
      }, duration);
    }
  }

  flipBtn.addEventListener('click', () => flip());

  // Keyboard: Space/Enter to flip
  document.addEventListener('keydown', (e) => {
    if (e.key === ' ' || e.key === 'Enter') {
      e.preventDefault();
      flip();
    }
  });

  // Initialize with a fair random face so UI doesn’t feel static
  setImmediateFace(chooseRandomFace());
})();


