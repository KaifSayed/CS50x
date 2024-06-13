// Loads and caches the pages of the website

const urlsToCache = [
    "/home",
    "/about",
    "/skills",
    "/contact",
    "/static/css/styles.css",
]

// Open cache and add the URLs to it
caches.open("my-site-cache-v1").then((cache) => {
    return cache.addAll(urlsToCache);
}).then(() => {
    // Redirect to the first page once done
    setTimeout(() => {
        window.location.href = "/home";
    }, 3000);
});

