// Get the typing text from the JSON file
fetch("/static/text/doing.json")
    .then(response => response.json())
    .then(data => {
        // Create a new instance of Typed.js
        var typed = new Typed("#typing-text", {
            strings: data.text,
            typeSpeed: 50,
            startDelay: 1000,
            loop: true
        });
    });

