// Waits for full page to load first
document.addEventListener('DOMContentLoaded', function() {
    // Button 1
    let b1 = document.querySelector('#button1');
    let b2 = document.querySelector('#button2');
    b1.addEventListener('click', function() {
        b1.style.backgroundColor = 'gray';
        b2.style.backgroundColor = 'green';
        b2.innerHTML = 'No. Click Me';
    });

    b2.addEventListener('click', function() {
        b2.style.backgroundColor = 'gray';
        b1.style.backgroundColor = 'green';
        b1.innerHTML = 'Click Me!!!';
    });
});